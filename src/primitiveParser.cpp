#include "StarletParser/parser.hpp"

#include "StarletScene/components/primitive.hpp"
#include "StarletScene/components/transform.hpp"

template<PrimitiveType T>
bool Parser::parsePrimitive(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  out.type = T;
  PARSE_STRING_OR(return false, p, out.name, 64, "primitive name");
  PARSE_OR(return false, parseVec3, transform.pos, "primitive position");
  PARSE_OR(return false, parseVec3, transform.rot, "primitive rotation");
  PARSE_OR(return false, parseVec3, transform.size, "triangle size");
  return parseColour(p, out.colour, out.colourMode);
}

bool Parser::parseTriangle(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Triangle>(p, out, transform);
}
bool Parser::parseSquare(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Square>(p, out, transform);
}
bool Parser::parseCube(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Cube>(p, out, transform);
}