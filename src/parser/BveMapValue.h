#pragma once
#include <string>

namespace bmets::parser {

  class BveMapValue {
    public:
      char type;

      union {
        int value_int;
        double value_double;
        std::string value_string;
      };

      const static char TYPE_NULL = 0;
      const static char TYPE_INT = 1;
      const static char TYPE_DOUBLE = 2;
      const static char TYPE_STRING = 3;

      static const char* type_to_string(char value) {
        switch (value) {
        case TYPE_NULL:
          return "null";
        case TYPE_INT:
          return "number(integer)";
        case TYPE_DOUBLE:
          return "number(double)";
        case TYPE_STRING:
          return "string";
        default:
          return "error";
        }
      }
      const char* type_to_string() {
        return type_to_string(type);
      }

      BveMapValue() { type = TYPE_NULL; }
      BveMapValue(char t) { type = t; }
      BveMapValue(int value) { type = TYPE_INT; value_int = value; }
      BveMapValue(double value) { type = TYPE_DOUBLE; value_double = value; }
      BveMapValue(std::string value) { type = TYPE_STRING; new(&value_string)std::string(value); }

      BveMapValue(const BveMapValue& other) {
        type = other.type;
        switch (type) {
        case TYPE_STRING: new(&value_string)std::string(other.value_string); break;
        case TYPE_INT: value_int = other.value_int; break;
        case TYPE_DOUBLE: value_double = other.value_double; break;
        }
      }
      BveMapValue& operator= (const BveMapValue &other) {
        type = other.type;
        switch (type) {
          // TODO: Is there a memory leak possibility?
        case TYPE_STRING: new(&value_string)std::string(other.value_string); break;
        case TYPE_INT: value_int = other.value_int; break;
        case TYPE_DOUBLE: value_double = other.value_double; break;
        }
        return *this;
      }
      ~BveMapValue() {
        if (type == TYPE_STRING) value_string.~basic_string();
      }

      bool to_bool() const;
      int to_int(std::string location = "") const;
      double to_double(std::string location = "") const;
      float to_float(std::string location = "") const;
      std::string to_string() const;

      friend BveMapValue operator+ (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator- (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator* (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator/ (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator% (const BveMapValue &a, const BveMapValue &b);

      friend BveMapValue operator+ (const BveMapValue &a);
      friend BveMapValue operator- (const BveMapValue &a);
      friend BveMapValue operator! (const BveMapValue &a);

      friend BveMapValue operator&& (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator|| (const BveMapValue &a, const BveMapValue &b);

      friend BveMapValue operator== (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator!= (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator> (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator< (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator>= (const BveMapValue &a, const BveMapValue &b);
      friend BveMapValue operator<= (const BveMapValue &a, const BveMapValue &b);

  };
}