#pragma once

#include "Rendering\RenderingApp.h"

class Game : public Rendering::RenderingApp
{
public: // constructors and destructors
	Game(Utils::CommandLine& commandLine);
	~Game(void);

public: // public member functions
	void Load();
	void GameLoop();

	void Update(float dt);
	void Draw();
	
	virtual void CloseWindowEvent();
	virtual void ResizeWindowEvent(int width, int height);
	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void CharEvent(unsigned int codepoint);
	virtual void MouseInputEvent(int button, int action, int mods);
};

