#include "StarletSerializer/parser.hpp"
#include "StarletSerializer/utils/log.hpp"

#include "StarletScene/component/velocity.hpp"

bool Parser::parseVelocity(const unsigned char*& p, VelocityComponent& velocity) {
	PARSE_OR(return false, parseVec3, velocity.velocity, "velocity");
	return true;
}
