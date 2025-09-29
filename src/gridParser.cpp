#include "StarletParsers/parser.hpp"

#include "StarletScene/components/grid.hpp"
#include "StarletScene/components/transform.hpp"

template <GridType T>
bool Parser::parseGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform) {
  grid.type = T;
  PARSE_STRING_OR(return false, p, grid.name, 64, "grid name");
  PARSE_OR(return false, parseUInt, grid.count, "grid count");
  PARSE_OR(return false, parseFloat, grid.spacing, "grid spacing");
  PARSE_OR(return false, parseVec3, transform.pos, "grid start position");
  PARSE_OR(return false, parseVec3, transform.rot, "grid rotation");
  PARSE_OR(return false, parseVec3, transform.size, "grid scale");
  return parseColour(p, grid.colour, grid.colourMode);
}

bool Parser::parseSquareGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform) {
  return parseGrid<GridType::Square>(p, grid, transform);
}
bool Parser::parseCubeGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform) {
  return parseGrid<GridType::Cube>(p, grid, transform);
}
