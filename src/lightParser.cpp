#include "StarletParser/parser.hpp"
#include "StarletParser/utils/log.hpp"

#include "StarletScene/components/light.hpp"
#include "StarletScene/components/transform.hpp"
#include "StarletScene/components/colour.hpp"

bool Parser::parseLightType(const unsigned char*& p, unsigned int& typeOut) {
	p = skipWhitespace(p);
	if (!p || *p == '\0') return false;
	if (*p == '0') { ++p; typeOut = 0; return true; }
	if (*p == '1') { ++p; typeOut = 1; return true; }
	if (*p == '2') { ++p; typeOut = 2; return true; }

	const unsigned char* original = p;
	if (parseUInt(p, typeOut)) return true;

	p = original;
	unsigned char typeName[64]{};
	if (!parseToken(p, typeName, sizeof(typeName)) || !p) {
		p = original;
		return false;
	}

	if (strcmp((char*)typeName, "Point") == 0)       typeOut = 0;
	else if (strcmp((char*)typeName, "Spot") == 0)        typeOut = 1;
	else if (strcmp((char*)typeName, "Directional") == 0) typeOut = 2;
	else return error("Parser", "parseLightType", "Unknown light type");
	return true;
}

bool Parser::parseLight(const unsigned char*& p, Light& light, TransformComponent& transform, ColourComponent& colour) {
	PARSE_OR(return false, parseBool, light.enabled, "light enabled");
	PARSE_STRING_OR(return false, p, light.name, 64, "light name");
	PARSE_OR(return false, parseLightType, light.type, "light type");
	PARSE_OR(return false, parseVec3, transform.pos, "light position");
	PARSE_OR(return false, parseVec4, colour.colour, "light diffuse");
	PARSE_OR(return false, parseVec4, light.attenuation, "light attenuation");
	PARSE_OR(return false, parseVec3, transform.rot, "light direction");
	PARSE_OR(return false, parseVec2f, light.param1, "light param1");
	return true;
}