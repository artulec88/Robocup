//#pragma once
//#include <iostream>
//#include <string>
//
//#include "Controls.h"
//#include "Color.h"
//
//class Scene
//{
//public:
//	Scene(std::string windowTitle, int windowWidth = 1024, int windowHeight = 768);
//	~Scene(void);
//
//public:
//	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//public:
//	void SetClearColor(const Color& color);
//	void LoadShaders(std::string vertexShaderPath, std::string fragmentShaderPath);
//	void DrawFrame();
//
//	void Start();
//public:
//	void SetProgramID(GLuint programID) { _programID = programID; };
//	GLuint GetProgramID() const { return _programID; };
//
//	void SetMatrixID(GLuint matrixID) { _matrixID = matrixID; };
//	GLuint GetMatrixID() const { return _matrixID; };
//
//	float GetFoV() const { return _fov; };
//	float GetAspect() const { return _aspect; };
//	float GetZNear() const { return _zNear; };
//	float GetZFar() const { return _zFar; };
//protected:
//	int _windowWidth;
//	int _windowHeight;
//	std::string _windowTitle;
//
//	GLFWwindow* _window;
//	GLuint _programID;
//	GLuint _matrixID;
//
//	Inputs::Controls* _controls;
//
//	float _fov; // TODO: Think where fov, aspect, zNear and zFar should be put
//	float _aspect;
//	float _zNear;
//	float _zFar;
//
//	GLuint _vertexArrayID;
//	GLuint _cubeVertexBuffer;
//	GLuint _cubeColorBuffer;
//};
//
