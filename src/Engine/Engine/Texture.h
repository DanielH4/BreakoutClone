#pragma once

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <bitset>
#include <iostream>

namespace Engine {
    class Texture {
    public:
        Texture(const std::string &path, GLint sWrap = GL_REPEAT, GLint tWrap = GL_REPEAT, 
                GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint maxFilter = GL_LINEAR)
        {
            static int s_textures = 0;
            std::cout << "s_textures value: " << s_textures << std::endl;
            m_textureNum = s_textures;
            std::cout << "m_textureNum value: " << m_textureNum << std::endl;
            s_textures++;
            glGenTextures(1, &m_ID);
            int width, height, nrComponents;
            //stbi_set_flip_vertically_on_load(true);     //flips orientation of image to be upright
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
            if(data) {
                GLenum format;
                if(nrComponents == 1)
                    format = GL_RED;
                else if(nrComponents == 3)
                    format = GL_RGB;
                else if(nrComponents == 4)
                    format = GL_RGBA;
                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, m_ID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
            }
            else {
                std::cout << "Failed to load texture at path: " << path << std::endl;
            }

            stbi_image_free(data);
        }

        //get ID (unsigned int) of texture object
        constexpr int getID() const {
            return m_ID;
        }

        constexpr int getNum() const {
            return m_textureNum;
        }

        void bind() const {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_ID);
        }

    private:
        unsigned int m_ID;
        int m_textureNum;
    };
}