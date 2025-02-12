#include "Engine.h"

class Editor : public Engine::Application
{
public:
	Editor()
	{

	}
	~Editor()
	{

	}
};


Engine::Application* Engine::CreateApplication()
{
	return new Editor();
}