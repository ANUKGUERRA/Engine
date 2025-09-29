#pragma once
#include <sstream>

struct WindowSpecs {
	std::string Title;
	int Width;
	int Height;
	//std::filesystem::path IconPath;

	//bool WindowResizeable = true;

	//bool CustomTitlebar = false;

	//bool UseDockspace = false;

	//bool CenterWindow = false;
	WindowSpecs(const std::string& title = "Engine", int width = 1280, int height = 720) : Title(title), Width(width), Height(height)
	{
	}
};

class Window {
public:
	virtual ~Window() = default;

	virtual void OnUpdate() = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void* GetWindow() const = 0;

	static std::unique_ptr<Window> Create(const WindowSpecs& data = WindowSpecs());
};

