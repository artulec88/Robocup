//#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>

#include "Game.h"

/* MATHS begin */
#include "Maths\Maths.h"
#include "Maths\Vector.h"
/* MATHS end */

/* RENDERING begin */
#include "Rendering\RenderingApp.h"
//#include "Rendering\Renderer.h"
/* RENDERING end */

/* UTILS begin */
#include "Utils\Utils.h"
#include "Utils\Log.h"
#include "Utils\Config.h"
#include "Utils\Time.h"
#include "Utils\CommandLine.h"
/* UTILS end */

//#define TESTING_ENABLED

using namespace std;
using namespace Utils;
using namespace Rendering;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void PrintHelp()
{
	cout << "usage: Robocup.exe [OPTIONS]" << endl;
	cout << "\t-log [Critical, Emergency, Error, Warning, Notice, Info, Debug, Delocust]" << endl;
	cout << "\t-config ConfigFilePath" << endl;
	cout << endl;
}

void PrintTable(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		cout << argv[i] << endl << endl;
	}
}

//std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // tolower function

int main(int argc, char* argv[])
{
#ifdef TESTING_ENABLED
	CommandLine commands(argc, argv);
	if (commands.IsPresent("-help"))
	{
		PrintHelp();
		system("pause");
		return 0;
	}
	stdlog.Fill(commands.Get("-log", ""), Debug);
	Config::LoadFromFile(commands.Get("-config", "C:\\Users\\Artur\\Documents\\Visual Studio 2010\\Projects\\Robocup\\x64\\Debug\\Config.cfg"));
	/* Testing Maths DLL begin */
	Maths::Vector3D<int> vector(3, 4, 5);
	cout << vector.ToString() << " " << vector.Length() << endl;
	stdlog(Notice, LOGPLACE, "This is a NOTICE message");
	/* Testing Maths DLL end */

	/* Testing Utils DLL begin */
	Utils::Time t = Utils::Time::Now();
	cout << "\"" << t.ToString() << "\"" << endl;
	/* Testing Utils DLL end */

	/* Testing Utils::Utility::ListAllFilesInDir(...) function begin */
	std::vector<std::string> asShaders;
	Utils::Utility::ListAllFilesInDir("C:\\Users\\Artur\\Documents\\Visual Studio 2010\\Projects\\Robocup\\Shaders", asShaders);
	/* Testing Utils::Utility::ListAllFilesInDir(...) function end */

	/* Testing begin */
	float camera_near = Utils::Config::GetValue("camera_near", 0.005f);
	//int camera_near = Utils::Config::GetValue(1);
	cout << "camera_near = " << camera_near << endl;
	system("PAUSE");
	return 0;
	/* Testing end */
#else
	/* ==================== Initialization begin ==================== */
	// TODO: Create AppManager class (singleton) which has Init(argc, argv) method. This class will be the manager of the whole application.
	CommandLine commands(argc, argv);
	if (commands.IsPresent("-help"))
	{
		PrintHelp();
		system("pause");
		return 0;
	}
	stdlog.Fill(commands.Get("-log", ""), Debug);
	Game game(commands);
	//Game game2(commands);
	game.ReadConfigFile();
	game.OpenWindow("Window title");
	game.SetMouseCursorEnabled(Config::GetValue("Cursor_input_mode", GLFW_CURSOR_HIDDEN));

	game.Load();
	/* ==================== Initialization end ==================== */

	/* ==================== Main loop begin ==================== */
	game.GameLoop();
	/* ==================== Main loop end ==================== */

	system("PAUSE");
	return 0;

	unsigned int seed = static_cast<unsigned int>(time(NULL));
	srand(seed);

	/* ========================================================== */
	//Scene* scene = new Scene("RoboCup");
	//scene->SetClearColor(Color(0.0f, 0.0f, 0.4f, 0.0f));
	//scene->LoadShaders(vertexShaderPath, fragmentShaderPath);
	//scene->Start();

	//delete scene;
	//scene = NULL;
	//return 0;
	/* ========================================================== */


    //GLFWwindow* window;

    //glfwSetErrorCallback(error_callback);

    //if (!glfwInit())
    //    exit(EXIT_FAILURE);

    //window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    //if (!window)
    //{
    //    glfwTerminate();
    //    exit(EXIT_FAILURE);
    //}

    //glfwMakeContextCurrent(window);

    //glfwSetKeyCallback(window, key_callback);

    //while (!glfwWindowShouldClose(window))
    //{
    //    float ratio;
    //    int width, height;

    //    glfwGetFramebufferSize(window, &width, &height);
    //    ratio = width / (float) height;

    //    glViewport(0, 0, width, height);
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    //    glMatrixMode(GL_MODELVIEW);

    //    glLoadIdentity();
    //    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    //    glBegin(GL_TRIANGLES);
    //    glColor3f(1.f, 0.f, 0.f);
    //    glVertex3f(-0.6f, -0.4f, 0.f);
    //    glColor3f(0.f, 1.f, 0.f);
    //    glVertex3f(0.6f, -0.4f, 0.f);
    //    glColor3f(0.f, 0.f, 1.f);
    //    glVertex3f(0.f, 0.6f, 0.f);
    //    glEnd();

    //    glfwSwapBuffers(window);
    //    glfwPollEvents();
    //}

    //glfwDestroyWindow(window);

    //glfwTerminate();
    //exit(EXIT_SUCCESS);
#endif
}

//! [code]
