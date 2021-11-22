#include "Map.h"
#include <boost/format.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "StringHash.h"
#include "../math/SPMainV.h"
#include "../math/SPMainL.h"
#include "../parser/BveDictionary.h"
#include "../parser/BveMapScript.h"
#include "../util/Path.h"
#include "../util/FmtException.h"
#include "Manager.h"
#include "../render/Manager.h"
#include "../math/Track.h"

#include <iostream>

using namespace bmets::game;

#define REPEATER_END_EXTEND 100

static FmtException ex_invalid_stmt(bmets::parser::BveMapStatement &stmt) {
  return FmtException("Invalid or unsupported element/function in '%s'", stmt.to_string().c_str());
}

static bmets::math::IFollowable* find_track(Map* map, bmets::parser::BveMapValue value) {
  bmets::math::IFollowable* targetTrack;
  if (!value.to_bool()) {
    targetTrack = &(map->track_main);
  } else {
    auto it = map->tracks.find(boost::algorithm::to_lower_copy(value.to_string()));
    if (it == map->tracks.end()) throw FmtException("Track not yet created: ", value.to_string().c_str());
    targetTrack = (*it).second.get();
  }
  return targetTrack;
}

static void parse_script_data_0(Map* map, bmets::parser::BveMapScript &data, int loadFlag) {
  int processing = 0;
  for (auto &stmt : data.statements) {
    if (processing % 500 == 0) {
      bmets::game::loader_progress((boost::format("Constructing track geometry ( %d / %d ) ...") 
        % processing % data.statements.size()).str(), -1);
    }
    processing++;

#pragma warning (disable: 4307)
    hash_t hElem1 = strhash(stmt.elem1.c_str());
    hash_t hElem2 = stmt.elem2.empty() ? 0 : strhash(stmt.elem2.c_str());
    hash_t hFunc = strhash(stmt.function.c_str());
    try {
      switch (hElem1) {

  // ---------- Geometry ----------
      case static_hash("curve"):
        switch (hFunc) {
        case static_hash("setgauge"):
        case static_hash("gauge"):
          stmt.assert_arg_count(1, 1);
          map->track_main.gauge = stmt.params[0].to_double("gauge");
          break;
        case static_hash("setcenter"):
          // TODO: SetCenter
          break;
        case static_hash("setfunction"):
          stmt.assert_arg_count(1, 1);
          switch (stmt.params[0].to_int("id")) {
          case 0:
            map->track_main.curve_ix_func = 2; break;
          case 1:
            map->track_main.curve_ix_func = 1; break;
          default:
            throw FmtException("Invalid curve interpolation function id, must be 0 or 1.");
          }
          break;
        case static_hash("begintransition"):
          stmt.assert_arg_count(0, 0);
          
          if (map->track_main.l_tx_begin_line >= 0)
            throw FmtException("BeginTransition must not be used in succession (already used at %d)", map->track_main.l_tx_begin_line);
          map->track_main.l_spline.push_back({ map->track_main.curve_ix_func }, stmt.location);
          map->track_main.cant_spline.push_back({ map->track_main.curve_ix_func }, stmt.location);
          map->track_main.l_tx_begin_line = stmt.line;
          break;
        case static_hash("begin"):
        case static_hash("begincircular"):
        case static_hash("change"):
        case static_hash("end"): {
          stmt.assert_arg_count(0, 2);

          double radius = stmt.arg_not_null(0) ? stmt.params[0].to_double("radius") : 0.0;
          double cant = stmt.arg_not_null(1) ? stmt.params[1].to_double("cant") : 0.0;
          if (radius == 0) radius = DBL_INF;
          map->track_main.last_radius = radius; map->track_main.last_cant = cant;

          map->track_main.l_spline.push_back({ radius, 0 }, stmt.location);
          map->track_main.cant_spline.push_back({ atan(cant / map->track_main.gauge), 0 }, stmt.location);
          map->track_main.l_tx_begin_line = -1;
          break;
        }
        case static_hash("interpolate"): {
          stmt.assert_arg_count(0, 2);

          double radius = stmt.arg_not_null(0) ? stmt.params[0].to_double("radius") : map->track_main.last_radius;
          double cant = stmt.arg_not_null(1) ? stmt.params[1].to_double("cant") : map->track_main.last_cant;
          if (radius == 0) radius = DBL_INF;
          map->track_main.last_radius = radius; map->track_main.last_cant = cant;

          map->track_main.l_spline.push_back({ radius, map->track_main.curve_ix_func }, stmt.location);
          map->track_main.cant_spline.push_back({ atan(cant / map->track_main.gauge), 
            map->track_main.curve_ix_func }, stmt.location);
          map->track_main.l_tx_begin_line = -1;
          break;
        }
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;

      case static_hash("gradient"):
        switch (hFunc) {
        case static_hash("begintransition"):
          stmt.assert_arg_count(0, 0);

          if (map->track_main.v_tx_begin_line >= 0) throw FmtException("BeginTransition must not be used in succession (already used at %d)", map->track_main.v_tx_begin_line);
          map->track_main.v_spline.push_back({ 2 }, stmt.location);
          map->track_main.v_tx_begin_line = stmt.line;
          break;
        case static_hash("begin"):
        case static_hash("beginconst"):
        case static_hash("end"): {
          stmt.assert_arg_count(0, 1);

          double tangent = stmt.arg_not_null(0) ? stmt.params[0].to_double("gradient") : 0.0;
          map->track_main.last_pitch = tangent;

          map->track_main.v_spline.push_back({ tangent, 0 }, stmt.location);
          map->track_main.v_tx_begin_line = -1;
          break;
        }
        case static_hash("interpolate"): {
          stmt.assert_arg_count(0, 1);

          double tangent = stmt.arg_not_null(0) ? stmt.params[0].to_double("gradient") : map->track_main.last_pitch;
          map->track_main.last_pitch = tangent;

          map->track_main.v_spline.push_back({ tangent, 1 }, stmt.location);
          map->track_main.v_tx_begin_line = -1;
          break;
        }
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;

      case static_hash("track"): {
        if (stmt.key1.empty()) {
          throw FmtException("Track commands must have a non-empty key.");
        }
        auto it = map->tracks.find(stmt.key1);
        bmets::math::ChildTrack* track;
        if (it == map->tracks.end()) {
          std::unique_ptr<bmets::math::ChildTrack> ptr = std::make_unique<bmets::math::ChildTrack>();
          track = ptr.get();
          map->tracks[stmt.key1] = std::move(ptr);
          // Manually initialize parent - is there better approach?
          track->l_spline.parts[0].parent = &map->track_main.l_spline;
          track->v_spline.parts[0].parent = &map->track_main.v_spline;
        } else {
          track = it->second.get();
        }

        switch (hElem2) {
        case static_hash("x"):
          switch (hFunc) {
          case static_hash("interpolate"): {
            stmt.assert_arg_count(0, 2);
            double x = stmt.arg_not_null(0) ? stmt.params[0].to_double("x") : track->last_x;
            double radius = stmt.arg_not_null(1) ? stmt.params[1].to_double("radius") : track->last_x_radius;
            if (radius == 0) radius = DBL_INF;
            track->last_x = x; track->last_x_radius = radius;

            track->l_spline.push_back({ &map->track_main.l_spline, x, radius }, stmt.location);
            break;
          }
          default:
            throw ex_invalid_stmt(stmt);
          }
          break;
        case static_hash("y"):
          switch (hFunc) {
          case static_hash("interpolate"): {
            stmt.assert_arg_count(0, 2);
            double y = stmt.arg_not_null(0) ? stmt.params[0].to_double("y") : track->last_y;
            double radius = stmt.arg_not_null(1) ? stmt.params[1].to_double("radius") : track->last_y_radius;
            if (radius == 0) radius = DBL_INF;
            track->last_y = y; track->last_y_radius = radius;

            track->v_spline.push_back({ &map->track_main.v_spline, y, radius }, stmt.location);
            break;
          }
          default:
            throw ex_invalid_stmt(stmt);
          }
          break;
        case static_hash("cant"):
          switch (hFunc) {
          case static_hash("setgauge"): 
            stmt.assert_arg_count(1, 1);
            track->gauge = stmt.params[0].to_double("gauge");
            break;
          case static_hash("setcenter"):
            // TODO: SetCenter
            break;
          case static_hash("setfunction"):
            stmt.assert_arg_count(1, 1);
            switch (stmt.params[0].to_int("id")) {
            case 0:
              track->curve_ix_func = 2; break;
            case 1:
              track->curve_ix_func = 1; break;
            default:
              throw FmtException("Invalid curve interpolation function id, must be 0 or 1.");
            }
            break;
          case static_hash("begintransition"):
            stmt.assert_arg_count(0, 0);

            if (track->c_tx_begin_line >= 0) throw FmtException("BeginTransition must not be used in succession (already used at %d)", track->c_tx_begin_line);
            track->cant_spline.push_back({ track->curve_ix_func }, stmt.location);
            track->c_tx_begin_line = stmt.line;
            break;
          case static_hash("begin"):
          case static_hash("end"): {
            stmt.assert_arg_count(0, 1);

            double cant = stmt.arg_not_null(0) ? stmt.params[0].to_double("cant") : 0.0;
            track->last_cant = cant;

            track->cant_spline.push_back({ atan(cant / track->gauge), 0 }, stmt.location);
            track->c_tx_begin_line = -1;
            break;
          }
          case static_hash("interpolate"): {
            stmt.assert_arg_count(0, 1);

            double cant = stmt.arg_not_null(0) ? stmt.params[0].to_double("cant") : track->last_cant;
            track->last_cant = cant;

            track->cant_spline.push_back({ atan(cant / track->gauge), track->curve_ix_func }, stmt.location);
            track->c_tx_begin_line = -1;
            break;
          }
          default:
            throw ex_invalid_stmt(stmt);
          }
          break;
          break;
        case 0:
          switch (hFunc) {
          case static_hash("position"): {
            stmt.assert_arg_count(2, 4);
            double x = stmt.params[0].to_double("x");
            double y = stmt.params[1].to_double("y");
            double radiusH = stmt.arg_not_null(2) ? stmt.params[2].to_double("radiusH") : 0;
            double radiusV = stmt.arg_not_null(3) ? stmt.params[3].to_double("radiusV") : 0;
            track->last_x = x; track->last_y = y; track->last_x_radius = radiusH; track->last_y_radius = radiusV;

            track->l_spline.push_back({ &map->track_main.l_spline, x, radiusH }, stmt.location);
            track->v_spline.push_back({ &map->track_main.v_spline, y, radiusV }, stmt.location);
            break;
          }
          case static_hash("gauge"):
            stmt.assert_arg_count(1, 1);
            track->gauge = stmt.params[0].to_double("gauge");
            break;
          case static_hash("cant"): {
            stmt.assert_arg_count(1, 1);
            double cant = stmt.params[0].to_double("cant");
            track->last_cant = cant;

            track->cant_spline.push_back({ atan(cant / track->gauge), track->curve_ix_func }, stmt.location);
            track->c_tx_begin_line = -1;
            break;
          }
          default:
            throw ex_invalid_stmt(stmt);
          }
          break;
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;
      }

// ---------- Structure Loading --------
      case static_hash("structure"):
        switch (hFunc) {
        case static_hash("load"): {
          stmt.assert_arg_count(1, 1);
          if (!(loadFlag & bmets::game::LOAD_SKIP_STRUCTURE)) {
            std::string structListFile;
            bmets::parser::BveDictionary structList;
            try {
              structListFile = path_to_abs(stmt.params[0].to_string(), data.source_files[stmt.file_index]);
              structList.load(structListFile);
            } catch (std::exception &ex) {
              throw FmtException("Cannot read '%s': %s", stmt.params[0].to_string().c_str(), ex.what());
            }
            structList.to_rel_path(0);
            for (auto &pair : structList.dict) {
              // BVE5 silently ignores this
              // if (pair.second.empty()) {
              //   loader_warn("No model assigned to key: " + pair.first, structListFile, -1);
              //   continue;
              // }
              try {
                bmets::render::model_manager.add_model(pair.first, pair.second.front());
              } catch (std::exception &ex) {
                loader_warn(ex.what(), data.source_files[stmt.file_index], stmt.line);
              }
            }
          }
          break;
        }
        }
        break;

      case static_hash("repeater"):
      case static_hash("section"):
      case static_hash("signal"):
      case static_hash("beacon"):
      case static_hash("speedlimit"):
      case static_hash("pretrain"):
      case static_hash("train"):
      case static_hash("sound"):
      case static_hash("sound3d"):
      case static_hash("station"):
      case static_hash("light"):
      case static_hash("fog"):
      case static_hash("background"):
      case static_hash("drawdistance"):
      case static_hash("cabilluminance"):
      case static_hash("irregularity"):
      case static_hash("adhesion"):
      case static_hash("rollingnoise"):
      case static_hash("flangenoise"):
      case static_hash("jointnoise"):
        break;
  // ---------- Invalid Class ----------
      default:
        throw ex_invalid_stmt(stmt);
      }
    } catch (std::exception &ex) {
      loader_warn(ex.what(), data.source_files[stmt.file_index], stmt.line);
    }
  }
}

static void parse_script_data_2(Map* map, bmets::parser::BveMapScript &data) {
  int processing = 0;
  for (auto &stmt : data.statements) {
    if (processing % 200 == 0) {
      bmets::game::loader_progress((boost::format("Calculating structure positions ( %d / %d ) ...") 
        % processing % data.statements.size()).str(), -1);
    }
    processing++;

#pragma warning (disable: 4307)
    hash_t hElem1 = strhash(stmt.elem1.c_str());
    hash_t hElem2 = stmt.elem2.empty() ? 0 : strhash(stmt.elem2.c_str());
    hash_t hFunc = strhash(stmt.function.c_str());

    try {
      switch (hElem1) {
  // ---------- Structure ----------
      case static_hash("structure"):
        switch (hFunc) {
        case static_hash("load"):
          break;
        case static_hash("put"): {
          stmt.assert_arg_count(9, 9);
          auto modelList = bmets::render::model_manager.get_model(stmt.key1);
          if (modelList == nullptr) {
            throw FmtException("Structure not loaded: %s", stmt.key1.c_str());
          }
          modelList->add_instance(
            find_track(map, stmt.params[0])->model_mat_at(
              stmt.location,
              stmt.params[1].to_double("x"), stmt.params[2].to_double("y"), stmt.params[3].to_double("z"),
              glm::radians(stmt.params[4].to_double("rx")), glm::radians(stmt.params[5].to_double("ry")), glm::radians(stmt.params[6].to_double("rz")),
              stmt.params[7].to_int("tilt"), stmt.params[8].to_double("span")
            ), stmt.location
          );
          break;
        }
        case static_hash("put0"): {
          stmt.assert_arg_count(3, 3);
          auto modelList = bmets::render::model_manager.get_model(stmt.key1);
          if (modelList == nullptr) {
            throw FmtException("Structure not loaded: %s", stmt.key1.c_str());
          }
          modelList->add_instance(
            find_track(map, stmt.params[0])->model_mat_at(
              stmt.location, 0, 0, 0, 0, 0, 0,
              stmt.params[1].to_int("tilt"), stmt.params[2].to_double("span")
            ), stmt.location
          );
          break;
        }
        case static_hash("putbetween"):
        // TODO: PutBetween
          break;
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;
      case static_hash("repeater"):
        // TODO: Don't put repeater before the first station

        switch (hFunc) {
        case static_hash("begin"): {
          stmt.assert_arg_count(11, 2147483647);
          std::string key = boost::algorithm::to_lower_copy(stmt.key1);
          auto it = map->repeaters.find(key);
          if (it == map->repeaters.end()) map->repeaters[key] = Repeater();

          std::vector<bmets::render::ModelList*> structures(stmt.params.size() - 10);
          for (int i = 10; i < stmt.params.size(); i++) {
            std::string crntStructName = stmt.params[i].to_string();
            if (crntStructName.empty()) {
              structures[i - 10] = nullptr;
            } else {
              auto crntStructList = bmets::render::model_manager.get_model(crntStructName);
              if (crntStructList == nullptr) {
                loader_warn("Structure not loaded: " + crntStructName, data.source_files[stmt.file_index], stmt.line);
                structures[i - 10] = nullptr;
              } else {
                structures[i - 10] = crntStructList;
              }
            }
          }

          map->repeaters[key].begin(
            map, stmt.location, find_track(map, stmt.params[0]),
            stmt.params[1].to_double("x"), stmt.params[2].to_double("y"), stmt.params[3].to_double("z"),
            glm::radians(stmt.params[4].to_double("rx")), glm::radians(stmt.params[5].to_double("ry")), glm::radians(stmt.params[6].to_double("rz")),
            stmt.params[7].to_int("tilt"), stmt.params[8].to_double("span"), 
            stmt.params[9].to_double("interval"), std::move(structures)
          );
          break;
        }
        case static_hash("begin0"): {
          stmt.assert_arg_count(5, 2147483647);
          std::string key = boost::algorithm::to_lower_copy(stmt.key1);
          auto it = map->repeaters.find(key);
          if (it == map->repeaters.end()) map->repeaters[key] = Repeater();

          std::vector<bmets::render::ModelList*> structures(stmt.params.size() - 4);
          for (int i = 4; i < stmt.params.size(); i++) {
            std::string crntStructName = stmt.params[i].to_string();
            if (crntStructName.empty()) {
              structures[i - 4] = nullptr;
            } else {
              auto crntStructList = bmets::render::model_manager.get_model(crntStructName);
              if (crntStructList == nullptr) {
                loader_warn("Structure not loaded: " + crntStructName, data.source_files[stmt.file_index], stmt.line);
                structures[i - 4] = nullptr;
              } else {
                structures[i - 4] = crntStructList;
              }
            }
          }

          map->repeaters[key].begin(
            map, stmt.location, find_track(map, stmt.params[0]),
            0, 0, 0, 0, 0, 0,
            stmt.params[1].to_int("tilt"), stmt.params[2].to_double("span"), 
            stmt.params[3].to_double("interval"), std::move(structures)
          );
          break;
        }
        case static_hash("end"): {
          stmt.assert_arg_count(0, 0);
          std::string key = boost::algorithm::to_lower_copy(stmt.key1);
          auto it = map->repeaters.find(key);
          if (it == map->repeaters.end()) {
            // BVE5 seems to ignore this silently
            // throw "Repeater not yet started: " + key;
            break;
          }

          map->repeaters[key].end(map, stmt.location);
          break;
        }
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;
      case static_hash("background"):
        switch (hFunc) {
        case static_hash("change"): {
          stmt.assert_arg_count(1, 1);
          std::string structKey = stmt.params[0].to_string();
          bmets::render::ModelList* modelList = bmets::render::model_manager.get_model(structKey);
          if (modelList == nullptr) {
            loader_warn("Structure not loaded: " + structKey, data.source_files[stmt.file_index], stmt.line);
            break;
          }
          map->track_main.bg_spline.push_back({ modelList->prefab.get() }, stmt.location);
          break;
        }
        default:
          throw ex_invalid_stmt(stmt);
        }
        break;
      }
    } catch (std::exception &ex) {
      loader_warn(ex.what(), data.source_files[stmt.file_index], stmt.line);
    }
  }
}

void Map::parse_script_data(bmets::parser::BveMapScript &data, int loadFlag) {
  // Loading, Main geometry
  parse_script_data_0(this, data, loadFlag);
  
  track_main.bake();
  for (auto &track : tracks) {
    track.second->bake();
  }

  // Put Structures
  parse_script_data_2(this, data);

  track_main.bg_spline.bake();

  if (data.statements.size() > 0) {
    double repeater_end = data.statements.back().location + REPEATER_END_EXTEND;
    for (auto &repeater : repeaters) {
      repeater.second.end(this, repeater_end);
    }
  }
  
}