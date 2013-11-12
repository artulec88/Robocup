//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <ctime>
//
//#include <gl/glew.h>
//#include <GLFW/glfw3.h> // inlcude GLFW
//
//// Include GLM
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include "Controls.h"
//#include "Scene.h"
//
//#include "Maths\Vector.h"
////#include "Rendering\Renderer.h"
//
//// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
//// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
//static const GLfloat g_cube_vertex_buffer_data[] = {
//	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
//	-1.0f,-1.0f, 1.0f,
//	-1.0f, 1.0f, 1.0f, // triangle 1 : end
//	1.0f, 1.0f,-1.0f, // triangle 2 : begin
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f,-1.0f, // triangle 2 : end
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f
//};
//
//// One color for each vertex. They were generated randomly.
//static GLfloat g_cube_color_buffer_data[12*3*3];
//
//Scene::Scene(std::string windowTitle, int windowWidth /* = 1024 */, int windowHeight /* = 768 */) :
//	_windowTitle(windowTitle),
//	_windowWidth(windowWidth),
//	_windowHeight(windowHeight),
//	_window(NULL),
//	_programID(0),
//	_matrixID(0),
//	_controls(NULL)
//{
//	if ( !glfwInit() )
//	{
//		std::cerr << "Failed to initialize GLFW" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//
//	_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
//	if (!_window)
//	{
//		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible." << std::endl;
//		glfwTerminate();
//		exit(EXIT_FAILURE);
//	}
//
//	glfwMakeContextCurrent(_window);
//
//	// Initialize GLEW
//	glewExperimental = true; // Needed for core profile
//	GLenum err = glewInit();
//	if (err != GLEW_OK) {
//		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
//		exit(EXIT_FAILURE);
//	}
//
//	glfwSetKeyCallback(_window, KeyCallback);
//
//	// Enable depth test
//	glEnable(GL_DEPTH_TEST);
//	// Accept fragment if it closer to the camera than the former one
//	glDepthFunc(GL_LESS); 
//
//	glGenVertexArrays(1, &_vertexArrayID);
//	glBindVertexArray(_vertexArrayID);
//
//	// Cull triangles which normal is not towards the camera
//	glEnable(GL_CULL_FACE);
//
//	// TODO: Remove in the future
//	glGenBuffers(1, &_cubeVertexBuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
//	glBindBuffer(GL_ARRAY_BUFFER, _cubeVertexBuffer); // The following commands will talk about our 'vertexbuffer' buffer
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.
//
//	srand(static_cast<unsigned int>(time(NULL)));
//	for (int v = 0; v < 12*3; ++v)
//	{
//		g_cube_color_buffer_data[3*v + 0] = static_cast<float>(rand()) / RAND_MAX;
//		g_cube_color_buffer_data[3*v + 1] = static_cast<float>(rand()) / RAND_MAX;
//		g_cube_color_buffer_data[3*v + 2] = static_cast<float>(rand()) / RAND_MAX;
//	}
//
//	glGenBuffers(1, &_cubeColorBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, _cubeColorBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_color_buffer_data), g_cube_color_buffer_data, GL_STATIC_DRAW);
//}
//
//
//Scene::~Scene(void)
//{
//	glDeleteBuffers(1, &_cubeVertexBuffer);
//	glDeleteBuffers(1, &_cubeColorBuffer);
//	glDeleteProgram(GetProgramID());
//	glDeleteVertexArrays(1, &_vertexArrayID);
//
//	glfwDestroyWindow(_window);
//
//	glfwTerminate(); // Close OpenGL window and terminate GLFW
//
//	if (_controls != NULL)
//	{
//		delete _controls;
//		_controls = NULL;
//	}
//}
//
//void Scene::SetClearColor(const Color& color)
//{
//	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
//}
//
//void Scene::LoadShaders(std::string vertexShaderPath, std::string fragmentShaderPath)
//{
//	// Create the shaders
//	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// Read the Vertex Shader code from the file
//	std::string VertexShaderCode;
//	std::ifstream VertexShaderStream(vertexShaderPath.c_str(), std::ios::in);
//	if (VertexShaderStream.is_open())
//	{
//		std::string Line = "";
//		while(getline(VertexShaderStream, Line))
//			VertexShaderCode += "\n" + Line;
//		VertexShaderStream.close();
//	}
//	else
//	{
//		std::cerr << "Impossible to open" << vertexShaderPath << ". Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
//		return;
//	}
//
//	// Read the Fragment Shader code from the file
//	std::string FragmentShaderCode;
//	std::ifstream FragmentShaderStream(fragmentShaderPath.c_str(), std::ios::in);
//	if(FragmentShaderStream.is_open())
//	{
//		std::string Line = "";
//		while(getline(FragmentShaderStream, Line))
//			FragmentShaderCode += "\n" + Line;
//		FragmentShaderStream.close();
//	}
//
//
//
//	GLint Result = GL_FALSE;
//	int InfoLogLength;
//
//
//
//	// Compile Vertex Shader
//	std::cout << "Compiling shader : " << vertexShaderPath << std::endl;
//	char const * VertexSourcePointer = VertexShaderCode.c_str();
//	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
//	glCompileShader(VertexShaderID);
//
//	// Check Vertex Shader
//	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if ( InfoLogLength > 0 )
//	{
//		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
//		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//		std::cout << &VertexShaderErrorMessage[0] << std::endl;
//	}
//
//
//
//	// Compile Fragment Shader
//	std::cout << "Compiling shader : " << fragmentShaderPath << std::endl;
//	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
//	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
//	glCompileShader(FragmentShaderID);
//
//	// Check Fragment Shader
//	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if ( InfoLogLength > 0 )
//	{
//		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
//		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
//		std::cout << &FragmentShaderErrorMessage[0] << std::endl;
//	}
//
//
//
//	// Link the program
//	std::cout << "Linking program" << std::endl;
//	GLuint programID = glCreateProgram();
//	glAttachShader(programID, VertexShaderID);
//	glAttachShader(programID, FragmentShaderID);
//	glLinkProgram(programID);
//
//	// Check the program
//	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
//	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if ( InfoLogLength > 0 )
//	{
//		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
//		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//		std::cout << &ProgramErrorMessage[0] << std::endl;
//	}
//
//	glDeleteShader(VertexShaderID);
//	glDeleteShader(FragmentShaderID);
//
//	SetProgramID(programID);
//
//	// TODO: Move MatrixID initialization somewhere else
//	// Get a handle for our "MVP" uniform.
//	// Only at initialisation time.
//	SetMatrixID(glGetUniformLocation(programID, "MVP"));
//}
//
//void Scene::Start()
//{
//	//Rendering::Renderer renderer;
//	//Maths::PointF lower(-300.0f, 2.0f, 2.0f);
//	//Maths::PointF upper(400.0f, 4.0f, 4.0f);
//	//const float density = 0.1f;
//	while (!glfwWindowShouldClose(_window))
//	{
//		glfwPollEvents();
//		// Keep running
//		DrawFrame();
//		//renderer.RenderGrid(lower, upper, density);
//	}
//}
//
//void Scene::DrawFrame()
//{
//	#ifdef  FRAME_GENERATION_TIME
//		ptime start(microsec_clock::local_time());
//		if(last!=not_a_date_time) acc((start-last).total_nanoseconds()/10e9);
//		last=start;
//	#endif
//
//	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	// Use our shader
//	glUseProgram(GetProgramID());
//
//	//// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//	glm::mat4 projectionMatrix = glm::perspective(GetFoV(), GetAspect(), GetZNear(), GetZFar());
//	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
//	glm::mat4 modelMatrix = glm::mat4(1.0f);
//	glm::mat4 MVPmatrix = projectionMatrix * viewMatrix * modelMatrix;
//
//	// Send our transformation to the currently bound shader,
//	// in the "MVP" uniform
//	// For each model you render, since the MVP will be different (at least the M part)
//	glUniformMatrix4fv(GetMatrixID(), 1, GL_FALSE, &MVPmatrix[0][0]);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, _cubeVertexBuffer);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, _cubeColorBuffer);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle;
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//
//	#ifdef  FRAME_GENERATION_TIME
//
//	clog << "Generation time:\t" << (microsec_clock::local_time()-start).total_nanoseconds()/10e9 ;
//	clog << '\t' << "FPS:" << 1/rolling_mean(acc);
//	clog << endl;
//
//	#endif
//
//	// Swap buffers
//	glfwSwapBuffers(_window);
//}
//
//void Scene::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}