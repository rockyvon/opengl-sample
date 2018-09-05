#include "stdafx.h"
#include "Shader.h"


ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

ShaderManager* ShaderManager::instance = NULL;
ShaderManager* ShaderManager::SingleInstance()
{
	if (instance == NULL) {
		instance = new ShaderManager();
	}
	return instance;
}

ShaderManager* ShaderManager::NewInstance()
{
	return new ShaderManager();
}

void ShaderManager::load(char* vertex_path, char* fragment_path) 
{
	cout << "before init:\n"
		<< "program:" << program
		<< ", vertex_shader:" << vertex_shader
		<< ", fragment_shader;" << fragment_shader
		<< endl;
	cout << "创建着色器前检查：";
	checkGLError();
	program = glCreateProgram();
	string src_content;
	char log[BUFFER_SIZE];

	//vertex shader
	
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	
	src_content = loadFile(vertex_path);
	const char* vertex_content = src_content.c_str();
	glShaderSource(vertex_shader, 1, &vertex_content, NULL);
	glCompileShader(vertex_shader);
	GLint success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << endl;
		LogUtils::createInstance()->write("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		LogUtils::createInstance()->write(log);
		LogUtils::createInstance()->write("\n");
	}

	//fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	src_content = loadFile(fragment_path);
	const char* fragment_content = src_content.c_str();
	glShaderSource(fragment_shader, 1, &fragment_content, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << endl;
		LogUtils::createInstance()->write( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		LogUtils::createInstance()->write(log);
		LogUtils::createInstance()->write("\n");
	}
	cout << "after init:\n" 
		<< "program:" << program 
		<< ", vertex_shader:" << vertex_shader 
		<< ", fragment_shader;" << fragment_shader 
		<< endl;
	
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, BUFFER_SIZE, NULL, log);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << endl;
	}
	cout << "创建程序后检查：";
	checkGLError();
	LogUtils::createInstance()->flush();
	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	//glDeleteShader(vertex_shader);
	//glDeleteShader(fragment_shader);
}

string ShaderManager::loadFile(char* path) {
	cout << "打开文件：" << path << endl;
	FILE* file;
	int length;
	string result = "";
	char buffer[BUFFER_SIZE];
	int fail = fopen_s(&file, path, "r");
	cout << "文件读取状态：" << fail << endl;
	if (fail) {
		cout << "文件不存在：" << path << endl;
		exit(1);
	}
	while (fgets(buffer, BUFFER_SIZE, file) != NULL)
	{
		
		length = strlen(buffer);
		//buffer[length - 1] = '\0';
		result.append(buffer);
	}
	fclose(file);
	return result;
	

}

void ShaderManager::use() {
	glUseProgram(program);
}

void ShaderManager::disable() {
	
}

void ShaderManager::checkGLError()
{
	GLenum GLerror;
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		switch (GLerror)
		{
		case GL_INVALID_ENUM:
			break;
		default:
			break;
		}
		//fprintf(stderr, "GL error: %x\n", GLerror);
		cout << "错误:" << gluErrorString(GLerror) << endl;
	}
	else {
		cout << "无错误" << endl;
	}
}

void ShaderManager::setUniform1i(const GLchar * name, GLint value)
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform1i(location, value);
}

void ShaderManager::setUniform1f(const GLchar * name, GLfloat value)
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform1f(location, value);
}

void ShaderManager::setUniform3fv(const GLchar * name, GLint count, GLfloat * values) {
	GLuint location = glGetUniformLocation(program, name);
	glUniform3fv(location, count, values);
}

void ShaderManager::setUniformMatrix4fv(const GLchar * name, GLint count, GLfloat * values)
{
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, count, GL_FALSE, values);
}

