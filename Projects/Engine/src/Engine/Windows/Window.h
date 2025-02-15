#pragma once

#include "../Core.h"
#include "../Logger.h"

struct WindowData {
	std::string Title;
	int Width;
	int Height;

	WindowData(const std::string& title = "Engine", int width = 1280, int height = 720) : Title(title), Width(width), Height(height) {}
};



 class ENGINE_API Window {
public:
	virtual ~Window() = default;
	virtual void OnUpdate() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void* GetWindow() const = 0;

	static Window* Create(const WindowData& data = WindowData());
};