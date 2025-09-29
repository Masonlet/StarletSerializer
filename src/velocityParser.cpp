#include "StarletParsers/parser.hpp"
#include "StarletParsers/utils/log.hpp"

#include "StarletScene/components/velocity.hpp"

bool Parser::parseVelocity(const unsigned char*& p, VelocityComponent& velocity) {
	PARSE_OR(return false, parseVec3, velocity.velocity, "velocity");
	return true;
}
