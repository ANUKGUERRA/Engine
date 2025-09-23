#include "Engine.h"
class Editor : public Application
{
public:
	Editor()
	{

	}
	~Editor()
	{

	}
};


Application* CreateApplication()
{
	return new Editor();
}