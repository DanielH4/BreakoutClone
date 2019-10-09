#pragma once

#include "Engine/Texture.h"
#include "Engine/Shader.h"

#include <string>

namespace Engine {
    static Texture loadTexture(const std::string &path) {
        return Texture(path);
    }

    static Shader createShader(const std::string &vPath, const std::string &fPath) {
        return Shader(vPath.c_str(), fPath.c_str());
    }
}