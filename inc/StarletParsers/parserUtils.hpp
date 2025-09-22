#pragma once

#include "starletmath/vec2.hpp"
#include "starletmath/vec3.hpp"
#include "starletmath/vec4.hpp"

#ifndef PARSE_OR 
#define PARSE_OR(onFail, parser, target, errorMsg) \
do { \
  if (!(parser(p, target))) { \
      if((errorMsg) && *(errorMsg) != '\0') fprintf(stderr, "[Parser ERROR]: Failed to parse %s\n", errorMsg); \
      onFail; \
	} \
} while(0)
#endif

#ifndef PARSE_STRING_OR
#define PARSE_STRING_OR(onFail, p, target, size, label) \
  do {\
    char temp[size]{}; \
    if (!parseToken(p, reinterpret_cast<unsigned char*>(temp), size) || strlen(temp) == 0) { \
      fprintf(stderr, "[Parser ERROR] Failed to parse %s\n", label); \
      onFail; \
    } \
    target = temp; \
  } while (0)
#endif

const unsigned char* skipToNextLine(const unsigned char* p);
const unsigned char* skipWhitespace(const unsigned char* p, bool skipComma = true);
const unsigned char* trimEOL       (const unsigned char* p, const unsigned char* end);

bool parseUInt  (const unsigned char*& p, unsigned int& out);
bool parseBool  (const unsigned char*& p, bool& out);
bool parseFloat (const unsigned char*& p, float& out);
bool parseVec2f (const unsigned char*& p, Vec2<float>& out);
bool parseVec3  (const unsigned char*& p, Vec3<float>& out);
bool parseVec4  (const unsigned char*& p, Vec4<float>& out);
bool parseToken (const unsigned char*& p, unsigned char* out, const size_t maxLength);