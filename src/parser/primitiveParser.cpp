#include "StarletParser/parser.hpp"

#include "StarletScene/components/primitive.hpp"
#include "StarletScene/components/transform.hpp"
#include "StarletScene/components/colour.hpp"

template<PrimitiveType T>
bool Parser::parsePrimitive(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour) {
  out.type = T;
  PARSE_STRING_OR(return false, p, out.name, 64, "primitive name");
  PARSE_OR(return false, parseVec3, transform.pos, "primitive position");
  PARSE_OR(return false, parseVec3, transform.rot, "primitive rotation");
  PARSE_OR(return false, parseVec3, transform.size, "triangle size");
  return parseColour(p, colour.colour);
}

bool Parser::parseTriangle(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour) {
  return parsePrimitive<PrimitiveType::Triangle>(p, out, transform, colour);
}
bool Parser::parseSquare(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour) {
  return parsePrimitive<PrimitiveType::Square>(p, out, transform, colour);
}
bool Parser::parseCube(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour) {
  return parsePrimitive<PrimitiveType::Cube>(p, out, transform, colour);
}