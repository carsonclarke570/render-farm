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

#include <shader.h>


extern const char *texture_type_map[4];

std::stack<Shader*> Shader::m_shader_stack = std::stack<Shader*>();

Shader::Shader() {
    this->program = 0;
    this->shaders[VERTEX] = 0;
    this->shaders[FRAGMENT] = 0;
    this->shaders[GEOMETRY] = 0;
    this->shaders[COMPUTE] = 0;
}

Shader::~Shader() {
    glDeleteProgram(this->program);
    this->program = 0;
}

int Shader::load_text(enum ShaderType type, const char *src) {
    // Create shader
    GLenum gl_type;
    switch(type) {
        case VERTEX:
            gl_type = GL_VERTEX_SHADER;
            break;
        case GEOMETRY:
            gl_type = GL_GEOMETRY_SHADER;
            break;
        case FRAGMENT:
            gl_type = GL_FRAGMENT_SHADER;
            break;
        case COMPUTE:
            gl_type = GL_COMPUTE_SHADER;
            break;
        default:
            fprintf(stderr, "ERROR: Invalid ShaderType!\n");
            return CODE_INVALID_SHADER_TYPE;
    }

    GLuint gl_shader = glCreateShader(gl_type);
    glShaderSource(gl_shader, 1, &src, NULL);

    // Compile + error check
    int status;
    glCompileShader(gl_shader);
    glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        // Get error and print
        int32_t log_size;
        glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &log_size);
        char* log = (char*) malloc(log_size * sizeof(char));
        glGetShaderInfoLog(gl_shader, log_size, NULL, log);
        fprintf(stderr, "ERROR: Failed to compile shader! Message follows:\n%s", log);

        // Clean up
        free(log);
        glDeleteShader(gl_shader);

        //return code
        return CODE_SHADER_COMPILE_ERROR;
    }

    this->shaders[type] = gl_shader;
    return CODE_SUCCESS;
}

int Shader::load_file(enum ShaderType type, const char* file) {
    FILE* fp = fopen(file, "rb");
    if (!fp) {
        fprintf(stderr, "ERROR: Failed to open file %s\n", file);
        return CODE_INVALID_FILENAME;
    }
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    char* data = (char*) malloc((size + 1) * sizeof(char));
    fread(data, sizeof(char), size, fp);
    data[size] = 0;
    fclose(fp);

    int error_code = this->load_text(type, data);
    free(data);
    return error_code;
}

int Shader::compile() {
    // Create and attach shaders
    this->program = glCreateProgram();
    for (int i = 0; i < 4; i ++) {
        if (this->shaders[i]) {
            glAttachShader(this->program, this->shaders[i]);
        }
    }

    // Link
    int32_t status;
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &status);
    if (!status) {
        // Get error and print
        int32_t log_size;
        glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &log_size);
        char* log = (char*) malloc(log_size * sizeof(char));
        glGetProgramInfoLog(this->program, log_size, NULL, log);
        fprintf(stderr, "ERROR: Failed to link shader! Message follows:\n%s", log);

        // Clean up
        free(log);
        glDeleteProgram(this->program);

        //return code
        return CODE_SHADER_LINK_ERROR;
    }

    for (int i = 0; i < 4; i ++) {
        if (this->shaders[i]) {
            glDetachShader(this->program, this->shaders[i]);
            glDeleteShader(this->shaders[i]);
        }
    }
    return CODE_SUCCESS;
}

void Shader::uniform_mat4(const char* name, const mat4 data) {
    GLuint loc = glGetUniformLocation(this->program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void Shader::uniform_vec2(const char* name, const vec2 data) {
    GLuint loc = glGetUniformLocation(this->program, name);
    glUniform2fv(loc, 1, data);
}

void Shader::uniform_vec3(const char* name, const vec3 data) {
    GLuint loc = glGetUniformLocation(this->program, name);
    glUniform3fv(loc, 1, data);
}

void Shader::uniform_float(const char* name, float data) {
    GLuint loc = glGetUniformLocation(this->program, name);
    glUniform1f(loc, data);
}

void Shader::uniform_int(const char* name, int data) {
    GLuint loc = glGetUniformLocation(this->program, name);
    glUniform1i(loc, data);
}

void Shader::bind_ubo(const char* name, uint32_t slot) {
    GLuint loc = glGetUniformBlockIndex(this->program, name);
    glUniformBlockBinding(this->program, loc, slot);
}

void Shader::register_texture(Texture *texture, unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glUniform1i(glGetUniformLocation(this->program, texture_type_map[texture->type]), slot);
}

void Shader::bind() {
    glUseProgram(this->program);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::push(Shader* shader) {
    m_shader_stack.push(shader);
    shader->bind();
}

void Shader::pop() {
    if (m_shader_stack.empty()) 
        glUseProgram(0);

    Shader* shader = m_shader_stack.top();
    m_shader_stack.pop();

    shader->bind();
}