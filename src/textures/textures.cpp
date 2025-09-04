#include "starletparsers/textures/texture.hpp"
#include <glad/glad.h>

Texture::~Texture() { 
	if (pixels) { delete[] pixels; pixels = nullptr; } 
	if (id) { glDeleteTextures(1, &id); id = 0; }
}
