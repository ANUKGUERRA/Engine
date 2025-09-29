#include "Window.h"

#ifdef WINDOWS_OS
	#include "WindowsOS/WindowsWindow.h"
#endif

std::unique_ptr<Window> Window::Create(const WindowSpecs& specs)
{
#ifdef WINDOWS_OS
	return std::make_unique<WindowsWindow>(specs);
#endif

#ifdef LINUX_OS
	return std::make_unique<LinuxWindow>(specs);
#endif

//Same for ps4-ps5-xbox-mac-switch-steamdeck...

}
