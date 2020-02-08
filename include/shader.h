/*
    Copyright 2019 Carson Clarke-Magrab

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include <common.h>
#include <matrix.h>
#include <texture.h>

enum ShaderType {
    VERTEX, FRAGMENT, GEOMETRY, COMPUTE
};
class Shader {
private:
    GLuint program;
    GLuint shaders[4];

    static std::stack<Shader*> m_shader_stack;
public:
    /**
     * Constructs a new Shader object.
     */
    Shader();

    /**
     * Destroys a Shader object
     */
    ~Shader();

    /**
     * Loads and attaches a shader from text.
     *
     * @param type      Type of shader to attach.
     * @param src       The text of the shader.
     * @return  CODE_SUCCESS if success, else a relevant error code.
     */
    int load_text(enum ShaderType type, const char* src);

    /**
     * Loads and attaches a shader from a file.
     *
     * @param type      Type of shader to attach.
     * @param file      File path of the file to open and read.
     * @return  CODE_SUCCESS if success, else a relevant error code.
     */
    int load_file(enum ShaderType type, const char* file);

    /**
     * Attempts to compiles all attached shaders. To prevent memory
     * leakages, make sure to call dispose() when you're done using the
     * shader.
     *
     * @return  CODE_SUCCESS if success, else a relevant error code.
     */
    int compile();

    /**
     * Updates a shader's mat4 uniform.
     *
     * @param name      Name of uniform to update.
     * @param data      mat4 data to update with.
     */
    void uniform_mat4(const char* name, const mat4 data);

    /**
     * Updates a shader's vec2 uniform.
     *
     * @param name      Name of uniform to update.
     * @param data      vec2 data to update with.
     */
    void uniform_vec2(const char* name, const vec2 data);

    /**
     * Updates a shader's vec3 uniform.
     *
     * @param name      Name of uniform to update.
     * @param data      vec3 data to update with.
     */
    void uniform_vec3(const char* name, const vec3 data);

    /**
     * Updates a shader's float uniform.
     *
     * @param name      Name of uniform to update.
     * @param data      float data to update with.
     */
    void uniform_float(const char* name, float data);

    /**
     * Updates a shader's int uniform.
     *
     * @param name      Name of uniform to update.
     * @param data      int data to update with.
     */
    void uniform_int(const char* name, int data);

    /**
     * Binds a uniform buffer object to a Shader by slot number.
     *
     * @param name      Name of uniform buffer
     * @param slot      Slot where the uniform buffer is bound.
     */
    void bind_ubo(const char* name, uint32_t slot);

    /**
     * Registers a texture to the shader
     *
     * @param texture   The texture to register
     * @param slot      The slot number to register it to
     */
    void register_texture(Texture* texture, unsigned int slot);

    /**
     * Binds the shader by making it the active shader. Does
     * not affect the shader stack.
     */
    void bind();

    /**
     * Unbinds shaders. Does not affect the shader stack.
     */
    void unbind();


    /**
     * Adds a shader to the stack and binds it.
     * 
     * @param shader    Pointer to shader to bind 
     */
    static void push(Shader* shader);

    /**
     *  Pops the current shader from the stack and binds the top of 
     *  the stack. If there is nothing on the stack, it unbinds all 
     *  shaders.
     */
    static void pop();
};

#endif
