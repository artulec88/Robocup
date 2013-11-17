#include "Game.h"
#include "Utils\Log.h"
#include "Maths\Vector.h"

using namespace Rendering;
using namespace Utils;

Game::Game(Utils::CommandLine& commandLine)
	: RenderingApp(commandLine)
{
	stdlog(Debug, LOGPLACE, "Game construction started");
	stdlog(Debug, LOGPLACE, "Game construction finished");
}


Game::~Game(void)
{
	stdlog(Debug, LOGPLACE, "Game destruction started");
	stdlog(Debug, LOGPLACE, "Game destruction finished");
}

void Game::Load()
{
	stdlog(Critical, LOGPLACE, "Function not yet implemented");
}

void Game::GameLoop()
{
	stdlog(Notice, LOGPLACE, "Main game loop started");

	if (GetApp() == NULL)
	{
		stdlog(Error, LOGPLACE, "Rendering application is NULL before Game Loop even started");
		return;
	}

	float previousTime = 0.0f;
	float currentTime = GetApp()->GetTime();
	while (true)
	{
		if (GetApp() == NULL)
		{
			stdlog(Critical, LOGPLACE, "Rendering application is NULL");
			break;
		}
		previousTime = currentTime;
		currentTime = GetApp()->GetTime();

		float dt = currentTime - previousTime;
		if (dt > 0.15f)
		{
			stdlog(Warning, LOGPLACE, "dt timespan equals %f", dt);
			dt = 0.15f;
		}

		Update(dt);
		Draw();
	}

	stdlog(Notice, LOGPLACE, "Main game loop finished");
}

void Game::Update(float dt)
{
	//stdlog(Info, LOGPLACE, "Function not yet implemented");
}

void Game::Draw()
{
	//stdlog(Info, LOGPLACE, "Function not yet implemented");

	GetRenderer()->RenderGrid(Maths::Point3Df(0.0f, 0.0f, 0.0f), Maths::Point3Df(15.0f, 15.0f, 15.0f), 0.01f);
	GetRenderer()->RenderTriangle(Maths::Point3Df(0.0f, 0.0f, 0.0f), Maths::Point3Df(1.0f, 1.0f, 1.0f), Maths::Point3Df(2.0f, 2.0f, 2.0f));

	GetApp()->SwapBuffers();
}

void Game::CloseWindowEvent()
{
	RenderingApp::CloseWindowEvent();
}

void Game::ResizeWindowEvent(int width, int height)
{
	RenderingApp::ResizeWindowEvent(width, height);
}

void Game::KeyEvent(int key, int scancode, int action, int mods)
{
	RenderingApp::KeyEvent(key, scancode, action, mods);
}

void Game::CharEvent(unsigned int codepoint)
{
	RenderingApp::CharEvent(codepoint);
}

void Game::MouseInputEvent(int button, int action, int mods)
{
	RenderingApp::MouseInputEvent(button, action, mods);
}