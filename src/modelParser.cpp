#include "StarletParser/parser.hpp"

#include "StarletScene/components/model.hpp"
#include "StarletScene/components/transform.hpp"

bool Parser::parseModel(const unsigned char*& p, Model& model, TransformComponent& transform, ColourComponent& colour) {
  PARSE_OR(return false, parseBool, model.isVisible, "model enabled");
  PARSE_OR(return false, parseBool, model.isLighted, "model lighting");
  PARSE_STRING_OR(return false, p, model.name, 64, "model name");
  PARSE_STRING_OR(return false, p, model.meshPath, 128, "model path");
  PARSE_OR(return false, parseVec3, transform.pos, "model position");
  PARSE_OR(return false, parseVec3, transform.rot, "model rotation");
  PARSE_OR(return false, parseVec3, transform.size, "model scale");
  if (!parseColour(p, colour.colour) && !parseSpecialColour(p, model.mode))
			return false;
  PARSE_OR(return false, parseVec4, colour.specular, "model specular");
  return true;
}
