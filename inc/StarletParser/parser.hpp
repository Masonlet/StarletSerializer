#pragma once

template <typename T> struct Vec2;
template <typename T> struct Vec3;
template <typename T> struct Vec4;

enum class ColourMode;
enum class PrimitiveType;
enum class GridType;
enum class LightType;

struct Camera;
struct Primitive;
struct Model;
struct Light;
struct Grid;
struct TextureData;
struct TextureConnection;

struct TextureCPU;
struct MeshCPU;

struct TransformComponent;
struct VelocityComponent;
struct ColourComponent;

class Scene;

#include <string>
#include <vector>

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

class Parser {
public:
	const size_t MAX_SIZE = static_cast<size_t>(200 * 1024) * 1024; //200MB Limit

	bool loadFile(std::string& out, const std::string& path);
	bool loadBinaryFile(std::vector<unsigned char>& dataOut, const std::string& path);

	bool parseColour(const unsigned char*& p, Vec4<float>& colourOut);
	bool parseSpecialColour(const unsigned char*& p, ColourMode& mode);

	bool parseTriangle(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour);
	bool parseSquare(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour);
	bool parseCube(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour);

	bool parseCamera(const unsigned char*& p, Camera& out, TransformComponent& transform);

  bool parsePlyMesh(const std::string& path, MeshCPU& drawInfo);
	bool parseModel(const unsigned char*& p, Model& out, TransformComponent& transform, ColourComponent& colour);

	bool parseBMP(const std::string& path, TextureCPU& out);
	bool parseTexture(const unsigned char*& p, TextureData& out);
	bool parseCubeTexture(const unsigned char*& p, TextureData& out);

	bool parseLight(const unsigned char*& p, Light& light, TransformComponent& transform, ColourComponent& colour);

	bool parseSquareGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform, ColourComponent& colour);
	bool parseCubeGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform, ColourComponent& colour);

	bool parseVelocity(const unsigned char*& p, VelocityComponent& velocity);

	bool parseScene(Scene& scene, const std::string& path);

private:
	bool getFileSize(FILE* file, size_t& sizeOut);

	bool isDelim(unsigned char c, bool comma = true);

	const unsigned char* skipToNextLine(const unsigned char* p);
	const unsigned char* skipWhitespace(const unsigned char* p, bool skipComma = true);
	const unsigned char* trimEOL(const unsigned char* p, const unsigned char* end);

	bool parseUInt(const unsigned char*& p, unsigned int& out);
	bool parseBool(const unsigned char*& p, bool& out);
	bool parseFloat(const unsigned char*& p, float& out);
	bool parseVec2f(const unsigned char*& p, Vec2<float>& out);
	bool parseVec3(const unsigned char*& p, Vec3<float>& out);
	bool parseVec4(const unsigned char*& p, Vec4<float>& out);
	bool parseToken(const unsigned char*& p, unsigned char* out, const size_t maxLength);

	bool parseNamedColour(const unsigned char*& p, Vec4<float>& colour);
	bool parseNumericColour(const unsigned char*& p, Vec4<float>& out);

	template <PrimitiveType T>
	bool parsePrimitive(const unsigned char*& p, Primitive& out, TransformComponent& transform, ColourComponent& colour);

	bool parsePlyElementLine(const unsigned char*& p, unsigned int& verticesOut, unsigned int& trianglesOut);
	bool parsePlyPropertyLine(const unsigned char*& p, bool& hasNx, bool& hasNy, bool& hasNz, bool& hasR, bool& hasG, bool& hasB, bool& hasU, bool& hasV);
	bool parsePlyHeader(const unsigned char*& p, unsigned int& numVerticesOut, unsigned int& numTrianglesOut, bool& hasNormalsOut, bool& hasColoursOut, bool& hasTexCoordsOut);

	bool parseVertices(const unsigned char*& p, MeshCPU& drawInfo);
	bool parseIndices(const unsigned char*& p, MeshCPU& drawInfo);

	bool parseLightType(const unsigned char*& p, LightType& type);

	template <GridType T>
	bool parseGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform, ColourComponent& colour);

	bool parseBmpHeader(const unsigned char* p, size_t fileSize, int32_t& height, int32_t& width, uint32_t& dataOffset);

	bool parseSceneLine(const unsigned char* p, Scene& scene);
};