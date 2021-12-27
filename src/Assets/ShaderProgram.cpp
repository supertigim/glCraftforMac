#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const std::string &name, const std::vector<VertexAttributeLocation> &attributes) {

  Shader vertexShader(name + ".vert", GL_VERTEX_SHADER);
  if (!vertexShader.isValid()) return;

  Shader fragmentShader(name + ".frag", GL_FRAGMENT_SHADER);
  if (!fragmentShader.isValid()) return;

  shaderProgram = glCreateProgram();
  for (const auto &[location, variableName]: attributes) {
    glBindAttribLocation(shaderProgram, location, variableName.c_str());
  }

  glAttachShader(shaderProgram, fragmentShader.getId());
  glAttachShader(shaderProgram, vertexShader.getId());

  glLinkProgram(shaderProgram);
}

int32_t ShaderProgram::getUniformLocation(const std::string &location) const {
  return glGetUniformLocation(shaderProgram, location.c_str());
}

void ShaderProgram::bind() const { glUseProgram(shaderProgram); }

void ShaderProgram::setInt(const std::string &location, int32_t value) {
  glProgramUniform1i(shaderProgram, getUniformLocation(location), value);
}

void ShaderProgram::setFloat(const std::string &location, float value) {
  glProgramUniform1f(shaderProgram, getUniformLocation(location), value);
}

void ShaderProgram::setVec3(const std::string &location, const glm::vec3 &value) {
  glProgramUniform3fv(shaderProgram, getUniformLocation(location), 1, &value.x);
}

void ShaderProgram::setMat4(const std::string &location, const glm::mat4 &value) {
  glProgramUniformMatrix4fv(shaderProgram, getUniformLocation(location), 1, GL_FALSE, &value[0][0]);
}

ShaderProgram::~ShaderProgram() {
  if (isValid()) { glDeleteShader(shaderProgram); }
}