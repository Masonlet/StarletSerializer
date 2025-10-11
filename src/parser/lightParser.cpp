#include "StarletSerializer/parser.hpp"
#include "StarletSerializer/utils/log.hpp"

#include "StarletScene/component/light.hpp"
#include "StarletScene/component/transform.hpp"
#include "StarletScene/component/colour.hpp"

bool Parser::parseLightType(const unsigned char*& p, LightType& type) {
	p = skipWhitespace(p);
	if (!p || *p == '\0') return false;

	const unsigned char* original = p;

	unsigned int lightType;
	if (parseUInt(p, lightType)) {
		switch (lightType) {
		case 0: type = LightType::Point; break;
		case 1: type = LightType::Spot; break;
		case 2: type = LightType::Directional; break;
		default: return error("Parser", "parseLightType", "Unknown light type");
		}

		return true;
	}

	p = original;
	unsigned char typeName[64]{};
	if (!parseToken(p, typeName, sizeof(typeName)) || !p) {
		p = original;
		return false;
	}

	if (strcmp((char*)typeName, "Point") == 0) type = LightType::Point;
	else if (strcmp((char*)typeName, "Spot") == 0) type = LightType::Spot;
	else if (strcmp((char*)typeName, "Directional") == 0) type = LightType::Directional;
	else return error("Parser", "parseLightType", "Unknown light type");
	return true;
}

bool Parser::parseLight(const unsigned char*& p, Light& light, TransformComponent& transform, ColourComponent& colour) {
	PARSE_OR(return false, parseBool, light.enabled, "light enabled");
	PARSE_STRING_OR(return false, p, light.name, 64, "light name");
	PARSE_OR(return false, parseLightType, light.type, "light type");
	PARSE_OR(return false, parseVec3, transform.pos, "light position");
	PARSE_OR(return false, parseVec3, transform.rot, "light direction");
	PARSE_OR(return false, parseVec4, colour.colour, "light diffuse");
	PARSE_OR(return false, parseVec4, light.attenuation, "light attenuation");
	PARSE_OR(return false, parseVec2f, light.param1, "light param1");
	return true;
}