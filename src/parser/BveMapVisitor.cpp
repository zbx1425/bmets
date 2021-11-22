#include <boost/algorithm/string/case_conv.hpp>
#include "../util/Path.h"
#include "../util/FmtException.h"
#include "antlr4-runtime.h"
#include "BveMapVisitor.h"
#include "BveMapParser.h"
#include "BveMapValue.h"

using namespace bmets::parser;

antlrcpp::Any BveMapVisitor::visitRoot(BveMapParser::RootContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

antlrcpp::Any BveMapVisitor::visitStmt(BveMapParser::StmtContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

antlrcpp::Any BveMapVisitor::visitStmtList(BveMapParser::StmtListContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

BveMapValue BveMapVisitor::to_value_holder(antlrcpp::Any src) {
  if (src.is<BveMapValue>()) {
    return src.as<BveMapValue>();
  } else if (src.isNull()) {
    return BveMapValue(BveMapValue::TYPE_NULL);
  } else {
    throw FmtException("Invalid antlr any type");
  }
}

antlrcpp::Any BveMapVisitor::visitIncludeStmt(BveMapParser::IncludeStmtContext *ctx) {
  set_context(ctx);
  BveMapValue path = to_value_holder(visit(ctx->expr()));
  this->frame->script->load(path_to_abs(path.to_string(), frame->script->source_files[frame->file_index]));
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitDistStmt(BveMapParser::DistStmtContext *ctx) {
  set_context(ctx);
  BveMapValue distance = to_value_holder(visit(ctx->expr()));
  if (distance.type == BveMapValue::TYPE_NULL) return nullptr;
  this->frame->script->current_location = distance.to_double("Set Distance");
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitMapStmt(BveMapParser::MapStmtContext *ctx) {
  set_context(ctx);
  BveMapStatement stmt;
  stmt.location = frame->script->current_location;
#pragma warning (disable:4267)
  stmt.line = ctx->getStart()->getLine() + 1; // Header
  stmt.file_index = frame->file_index;
  stmt.type = 1 + (ctx->key1 != nullptr ? 2 : 0) + (ctx->elem2 != nullptr ? 4 : 0);
  stmt.elem1 = ctx->elem1->getText();
  boost::algorithm::to_lower(stmt.elem1);
  stmt.function = ctx->func->getText();
  boost::algorithm::to_lower(stmt.function);
  if (ctx->key1 != nullptr) {
    BveMapValue paramValue = to_value_holder(visit(ctx->key1));
    stmt.key1 = paramValue.to_string();
    boost::algorithm::to_lower(stmt.key1);
  }
  if (ctx->elem2 != nullptr) {
    stmt.elem2 = ctx->elem2->getText();
    boost::algorithm::to_lower(stmt.elem2);
  }

  if (!ctx->params->children.empty()) {
    stmt.params.resize(ctx->params->Comma().size() + 1);
    int paramId = 0;
    for (auto &param : ctx->params->children) {
      auto terminalNode = dynamic_cast<antlr4::tree::TerminalNodeImpl*>(param);
      if (terminalNode != nullptr && terminalNode->symbol->getType() == BveMapParser::Comma) {
        paramId++;
      } else {
        stmt.params[paramId] = to_value_holder(visit(param));
      }
    }
  }
  /*for (int i = 0; i < ctx->params->expr().size(); i++) {
    if (ctx->params->expr()[i] != nullptr) {
      stmt.params[i] = to_value_holder(visit(ctx->params->expr()[i]));
    } else {
      stmt.params[i] = BveMapValue(BveMapValue::TYPE_NULL);
    }
  }*/
  this->frame->script->statements.push_back(stmt);
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitAssignStmt(BveMapParser::AssignStmtContext *ctx) {
  // set_context(ctx);
  BveMapValue value = to_value_holder(visit(ctx->expr()));
  auto varName = ctx->Variable()->getText();
  if (varName[0] == '$') {
    this->frame->script->variables[varName] = value;
  } else {
    this->frame->variables[varName] = value;
  }
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitIfStmt(BveMapParser::IfStmtContext *ctx) {
  // set_context(ctx);
  for (int i = 0; i < ctx->cond.size(); ++i) {
    if (to_value_holder(visit(ctx->cond[i])).to_bool()) {
      visit(ctx->condCode[i]);
      return nullptr;
    }
  }
  if (ctx->elseCode != nullptr) visit(ctx->elseCode);
  return nullptr;
}

static const int LOOP_ITER_LIMIT = 50000;

antlrcpp::Any BveMapVisitor::visitForStmt(BveMapParser::ForStmtContext *ctx) {
  set_context(ctx);
  int loop_iter = 0;
  visit(ctx->initStmt);
  while (to_value_holder(visit(ctx->cond)).to_bool()) {
    ++loop_iter;
    if (ctx->Long() == nullptr && loop_iter > LOOP_ITER_LIMIT) {
      throw FmtException("Infinite loop suspected: this 'for' loop has ran more than %d iterations. "
        "If it is intentional, please use 'for long (...)'", LOOP_ITER_LIMIT);
    }
    visit(ctx->codeBlock());
    visit(ctx->stepStmt);
  }
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitWhileStmt(BveMapParser::WhileStmtContext *ctx) {
  set_context(ctx);
  int loop_iter = 0;
  while (to_value_holder(visit(ctx->expr())).to_bool()) {
    ++loop_iter;
    if (ctx->Long() == nullptr && loop_iter > LOOP_ITER_LIMIT) {
      throw FmtException("Infinite loop suspected: this 'while' loop has ran more than %d iterations. "
        "If it is intentional, please use 'while long (...)'", LOOP_ITER_LIMIT);
    }
    visit(ctx->codeBlock());
  }
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitFnDefStmt(BveMapParser::FnDefStmtContext *ctx) {
  set_context(ctx);
  std::vector<std::string> argNames;
  for (auto varCtx : ctx->paramDefList()->Variable()) {
    if (std::find(argNames.begin(), argNames.end(), varCtx->getText()) != argNames.end()) {
      throw FmtException("Duplicate argument name: %s", varCtx->getText().c_str());
    } else {
      argNames.push_back(varCtx->getText());
    }
  }
  frame->script->functions.emplace(
    ctx->fnName->getText(),
    BveMapFunction(ctx->fnName->getText(), ctx->codeBlock(), std::move(argNames), frame->file_index)
  );
  return nullptr;
}

antlrcpp::Any BveMapVisitor::visitParamList(BveMapParser::ParamListContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

antlrcpp::Any BveMapVisitor::visitParamDefList(BveMapParser::ParamDefListContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

antlrcpp::Any BveMapVisitor::visitCodeBlock(BveMapParser::CodeBlockContext *ctx) {
  // set_context(ctx);
  return visitChildren(ctx);
}

antlrcpp::Any BveMapVisitor::visitStringExpr(BveMapParser::StringExprContext *ctx) {
  // set_context(ctx);
  std::string strLiteral = ctx->StringLiteral()->getText();
  return BveMapValue(strLiteral.substr(1, strLiteral.length() - 2));
}

antlrcpp::Any BveMapVisitor::visitVarExpr(BveMapParser::VarExprContext *ctx) {
  set_context(ctx);
  auto varName = ctx->Variable()->getText();
  if (varName[0] == '$') {
    auto entry = frame->script->variables.find(varName);
    if (entry == frame->script->variables.end()) {
      throw FmtException("Usage of undefined global variable: %s", varName.c_str());
    } else {
      return entry->second;
    }
  } else {
    auto entry = frame->variables.find(varName);
    if (entry == frame->variables.end()) {
      throw FmtException("Usage of undefined local variable: %s", varName.c_str());
    } else {
      return entry->second;
    }
  }
}

antlrcpp::Any BveMapVisitor::visitInfixExpr(BveMapParser::InfixExprContext *ctx) {
  set_context(ctx);
  BveMapValue left = to_value_holder(visit(ctx->left));
  BveMapValue right = to_value_holder(visit(ctx->right));
  switch (ctx->op->getType()) {
  case BveMapParser::Plus:
    return left + right;
  case BveMapParser::Minus:
    return left - right;
  case BveMapParser::Star:
    return left * right;
  case BveMapParser::Div:
    return left / right;
  case BveMapParser::Mod:
    return left % right;
  case BveMapParser::Less:
    return left < right;
  case BveMapParser::LessEqual:
    return left <= right;
  case BveMapParser::Greater:
    return left > right;
  case BveMapParser::GreaterEqual:
    return left >= right;
  case BveMapParser::Equal:
    return left == right;
  case BveMapParser::NotEqual:
    return left != right;
  case BveMapParser::And:
  case BveMapParser::AndAnd:
    return left && right;
  case BveMapParser::Or:
  case BveMapParser::OrOr:
    return left || right;
  }
  throw FmtException("Invalid infix operator: %s", ctx->op->getText().c_str());
}

antlrcpp::Any BveMapVisitor::visitUnaryExpr(BveMapParser::UnaryExprContext *ctx) {
  set_context(ctx);
  BveMapValue value = to_value_holder(visit(ctx->expr()));
  switch (ctx->op->getType()) {
  case BveMapParser::Plus:
    return +value;
  case BveMapParser::Minus:
    return -value;
  case BveMapParser::Not:
    return !value;
  }
  throw FmtException("Invalid unary operator: %s", ctx->op->getText().c_str());
}

antlrcpp::Any BveMapVisitor::visitNullExpr(BveMapParser::NullExprContext *ctx) {
  // set_context(ctx);
  return BveMapValue(BveMapValue::TYPE_NULL);
}

antlrcpp::Any BveMapVisitor::visitNumberExpr(BveMapParser::NumberExprContext *ctx) {
  // set_context(ctx);
  // TODO: Ensure the numStr is always valid
  std::string numStr = ctx->Number()->getText();
  if (numStr.find('.') == std::string::npos) {
    return BveMapValue(std::stoi(ctx->Number()->getText()));
  } else {
    return BveMapValue(std::stod(ctx->Number()->getText()));
  }
}

antlrcpp::Any BveMapVisitor::visitParensExpr(BveMapParser::ParensExprContext *ctx) {
  // set_context(ctx);
  return to_value_holder(visit(ctx->expr()));
}

antlrcpp::Any BveMapVisitor::visitDistanceExpr(BveMapParser::DistanceExprContext *ctx) {
  // set_context(ctx);
  return BveMapValue(frame->script->current_location);
}

antlrcpp::Any BveMapVisitor::visitFnCallExpr(BveMapParser::FnCallExprContext *ctx) {
  set_context(ctx);
  auto fnName = ctx->func->getText();
  auto entry = frame->script->functions.find(fnName);
  if (entry == frame->script->functions.end()) {
    throw FmtException("Usage of undefined function: %s", fnName.c_str());
  } else {
    std::vector<BveMapValue> params;
    if (!ctx->params->children.empty()) {
      params.resize(ctx->params->Comma().size() + 1);
      int paramId = 0;
      for (auto &param : ctx->params->children) {
        auto terminalNode = dynamic_cast<antlr4::tree::TerminalNodeImpl*>(param);
        if (terminalNode != nullptr && terminalNode->symbol->getType() == BveMapParser::Comma) {
          paramId++;
        } else {
          params[paramId] = to_value_holder(visit(param));
        }
      }
    }
    return entry->second.call(frame->script, params);
  }
}