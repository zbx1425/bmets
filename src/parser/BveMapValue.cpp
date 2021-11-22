#include "BveMapValue.h"
#include <cmath>
#include "../util/FmtException.h"

namespace bmets::parser {

static FmtException exception_value_type(std::string place, std::string expected, int type) {
  return FmtException("Type mismatch at '%s' where (%s) is expected but (%s) is encountered", 
    place.c_str(), expected.c_str(), BveMapValue::type_to_string(type));
}

static FmtException exception_value_type(std::string place, std::string expected, BveMapValue a) {
  return FmtException("Type mismatch at '%s' where (%s) is expected but (%s) is encountered",
    place.c_str(), expected.c_str(), a.type_to_string());
}

static FmtException exception_value_type(std::string place, std::string expected, BveMapValue a, BveMapValue b) {
  return FmtException("Type mismatch at '%s' where (%s) is expected but (%s, %s) is encountered",
    place.c_str(), expected.c_str(), a.type_to_string(), b.type_to_string());
}

bool BveMapValue::to_bool() const {
  switch(type) {
  case BveMapValue::TYPE_NULL: return false;
  case BveMapValue::TYPE_INT: return value_int != 0;
  case BveMapValue::TYPE_DOUBLE: return value_double != 0.0;
  case BveMapValue::TYPE_STRING: return !value_string.empty();
  }
  return false;
}

int BveMapValue::to_int(std::string location) const {
  switch(type) {
  case BveMapValue::TYPE_NULL: return 0;
  case BveMapValue::TYPE_INT: return value_int;
  case BveMapValue::TYPE_DOUBLE: return static_cast<int>(value_double);
  }
  throw exception_value_type(location, "number", type);
}

double BveMapValue::to_double(std::string location) const {
  switch(type) {
  case BveMapValue::TYPE_NULL: return 0.0;
  case BveMapValue::TYPE_INT: return static_cast<double>(value_int);
  case BveMapValue::TYPE_DOUBLE: return value_double;
  }
  throw exception_value_type(location, "number", type);
}

float BveMapValue::to_float(std::string location) const {
  switch(type) {
  case BveMapValue::TYPE_NULL: return 0.0f;
  case BveMapValue::TYPE_INT: return static_cast<float>(value_int);
  case BveMapValue::TYPE_DOUBLE: return static_cast<float>(value_double);
  }
  throw exception_value_type(location, "number", type);
}

std::string BveMapValue::to_string() const {
  switch(type) {
  case BveMapValue::TYPE_NULL: return "";
  case BveMapValue::TYPE_INT: return std::to_string(value_int);
  case BveMapValue::TYPE_DOUBLE: return std::to_string(value_double);
  case BveMapValue::TYPE_STRING: return value_string;
  }
  return "";
}

BveMapValue operator+ (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int + b.value_int);
  case 0b0110: return BveMapValue(a.value_int + b.value_double);
  case 0b1001: return BveMapValue(a.value_double + b.value_int);
  case 0b1010: return BveMapValue(a.value_double + b.value_double);
  case 0b0111: return BveMapValue(std::to_string(a.value_int) + b.value_string);
  case 0b1011: return BveMapValue(std::to_string(a.value_double) + b.value_string);
  case 0b1101: return BveMapValue(a.value_string + std::to_string(b.value_int));
  case 0b1110: return BveMapValue(a.value_string + std::to_string(b.value_double));
  case 0b1111: return BveMapValue(a.value_string + b.value_string);
  }
  throw exception_value_type("infix +", "number/string, number/string", a, b);
}

BveMapValue operator- (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int - b.value_int);
  case 0b0110: return BveMapValue(a.value_int - b.value_double);
  case 0b1001: return BveMapValue(a.value_double - b.value_int);
  case 0b1010: return BveMapValue(a.value_double - b.value_double);
  }
  throw exception_value_type("infix -", "number, number", a, b);
}

BveMapValue operator* (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int * b.value_int);
  case 0b0110: return BveMapValue(a.value_int * b.value_double);
  case 0b1001: return BveMapValue(a.value_double * b.value_int);
  case 0b1010: return BveMapValue(a.value_double * b.value_double);
  }
  throw exception_value_type("infix *", "number, number", a, b);
}

BveMapValue operator/ (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: 
    if (a.value_int % b.value_int == 0) {
      return BveMapValue(a.value_int / b.value_int);
    } else {
      return BveMapValue(static_cast<double>(a.value_int) / b.value_int);
    }
  case 0b0110: return BveMapValue(a.value_int / b.value_double);
  case 0b1001: return BveMapValue(a.value_double / b.value_int);
  case 0b1010: return BveMapValue(a.value_double / b.value_double);
  }
  throw exception_value_type("infix /", "number, number", a, b);
}

BveMapValue operator% (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int % b.value_int);
  case 0b0110: return BveMapValue(std::fmod(a.value_int, b.value_double));
  case 0b1001: return BveMapValue(std::fmod(a.value_double, b.value_int));
  case 0b1010: return BveMapValue(std::fmod(a.value_double, b.value_double));
  }
  throw exception_value_type("infix %", "number, number", a, b);
}

BveMapValue operator+ (const BveMapValue &a) {
  switch (a.type) {
  case 0b01: return a;
  case 0b10: return a;
  }
  throw exception_value_type("unary +", "number", a);
}

BveMapValue operator- (const BveMapValue &a) {
  switch (a.type) {
  case 0b01: return BveMapValue(-a.value_int);
  case 0b10: return BveMapValue(-a.value_double);
  }
  throw exception_value_type("unary -", "number", a);
}

BveMapValue operator! (const BveMapValue &a) {
  switch (a.type) {
  case 0b01: return BveMapValue(a.value_int == 0 ? 1 : 0);
  case 0b10: return BveMapValue(a.value_double == 0.0 ? 1.0 : 0.0);
  }
  throw exception_value_type("unary !", "number", a);
}

BveMapValue operator&& (const BveMapValue &a, const BveMapValue &b) {
  return BveMapValue(a.to_bool() && b.to_bool());
}

BveMapValue operator|| (const BveMapValue &a, const BveMapValue &b) {
  return BveMapValue(a.to_bool() || b.to_bool());
}

BveMapValue operator== (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int == b.value_int);
  case 0b0110: return BveMapValue(a.value_int == b.value_double);
  case 0b1001: return BveMapValue(a.value_double == b.value_int);
  case 0b1010: return BveMapValue(a.value_double == b.value_double);
  case 0b0111: return BveMapValue(std::to_string(a.value_int) == b.value_string);
  case 0b1011: return BveMapValue(std::to_string(a.value_double) == b.value_string);
  case 0b1101: return BveMapValue(a.value_string == std::to_string(b.value_int));
  case 0b1110: return BveMapValue(a.value_string == std::to_string(b.value_double));
  case 0b1111: return BveMapValue(a.value_string == b.value_string);
  }
  throw exception_value_type("infix ==", "number/string, number/string", a, b);
}

BveMapValue operator!= (const BveMapValue &a, const BveMapValue &b) {
  return !(a == b);
}

BveMapValue operator> (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int > b.value_int);
  case 0b0110: return BveMapValue(a.value_int > b.value_double);
  case 0b1001: return BveMapValue(a.value_double > b.value_int);
  case 0b1010: return BveMapValue(a.value_double > b.value_double);
  case 0b0111: return BveMapValue(std::to_string(a.value_int) > b.value_string);
  case 0b1011: return BveMapValue(std::to_string(a.value_double) > b.value_string);
  case 0b1101: return BveMapValue(a.value_string > std::to_string(b.value_int));
  case 0b1110: return BveMapValue(a.value_string > std::to_string(b.value_double));
  case 0b1111: return BveMapValue(a.value_string > b.value_string);
  }
  throw exception_value_type("infix >", "number/string, number/string", a, b);
}

BveMapValue operator< (const BveMapValue &a, const BveMapValue &b) {
  switch ((a.type << 2) + b.type) {
  case 0b0101: return BveMapValue(a.value_int < b.value_int);
  case 0b0110: return BveMapValue(a.value_int < b.value_double);
  case 0b1001: return BveMapValue(a.value_double < b.value_int);
  case 0b1010: return BveMapValue(a.value_double < b.value_double);
  case 0b0111: return BveMapValue(std::to_string(a.value_int) < b.value_string);
  case 0b1011: return BveMapValue(std::to_string(a.value_double) < b.value_string);
  case 0b1101: return BveMapValue(a.value_string < std::to_string(b.value_int));
  case 0b1110: return BveMapValue(a.value_string < std::to_string(b.value_double));
  case 0b1111: return BveMapValue(a.value_string < b.value_string);
  }
  throw exception_value_type("infix <", "number/string, number/string", a, b);
}

BveMapValue operator>= (const BveMapValue &a, const BveMapValue &b) {
  return (a > b) || (a == b);
}

BveMapValue operator<= (const BveMapValue &a, const BveMapValue &b) {
  return (a < b) || (a == b);
}

}