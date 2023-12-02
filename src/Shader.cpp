#include <Shader.hpp>

std::string Shader::loadShaderFile(std::string& filePath) {
  std::ifstream sourceFile(filePath);
  std::string source = "";
  std::string tmp;

  if (sourceFile.is_open()) {
    while (std::getline(sourceFile, tmp)) {
      source += tmp + '\n';
    }
    sourceFile.close();
  } else {
    std::cerr << "ERROR LOADING SOURCE" << std::endl
              << std::strerror(errno) << std::endl;
  }

  std::cout << "SOURCE LOADED" << std::endl << source << std::endl;
  return source;
}

GLuint Shader::compileShader(GLuint type, const GLchar* source) {
  GLuint shader = glCreateShader(type);

  std::string typeString =
      type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER" : "GL_FAGMENT_SHADER";

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint shaderCompiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

  if (!shaderCompiled) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(shader, 1024, &log_length, message);

    std::cout << "ERROR COMPILING SHADER" << std::endl
              << typeString << std::endl
              << message << std::endl;
    std::cout << "SHADER SOURCE" << std::endl << source << std::endl;
  }
  return shader;
}

Shader::Shader(std::string& vertexPath, std::string& fragmentPath) {
  std::string vSource = loadShaderFile(vertexPath);
  std::string fSource = loadShaderFile(fragmentPath);

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vSource.c_str());
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fSource.c_str());

  ID = glCreateProgram();

  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  GLint programLinked;
  glGetProgramiv(ID, GL_LINK_STATUS, &programLinked);

  if (!programLinked) {
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetProgramInfoLog(ID, 1024, &logLength, message);
    std::cout << "ERROR SHADER PROGRAM LINKING" << std::endl
              << message << std::endl;
  }

  glDetachShader(ID, vertexShader);
  glDetachShader(ID, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
  GLuint location = glGetUniformLocation(ID, name.c_str());
  glUniform1f(location, value);
}
