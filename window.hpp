#ifndef _RK_WINDOW_HPP_
#define _RK_WINDOW_HPP_

#include "module/target_traits/target_traits.hpp"
#include <stdexcept>

using namespace std;
using namespace shy;

namespace rk
{
	struct Window
	{
		Window(const string &title, unsigned int width, unsigned int height);
		virtual ~Window();

		virtual bool swap();
	};

	namespace linux
	{
		struct Window
		{
			GLXContext context;
			::Window window;
			Display *display;
			Atom atom_delete;
			XVisualInfo *visual;
		};
	}

	namespace windows
	{
		struct Window
		{	
			HWND window;
			HDC device;
			HGLRC context;
			HINSTANCE instance;
		};
	}

	Window &CreateWindow(const string &title, unsigned int width, unsigned height)
	{
		if (target_system_is_linux<>::value)
			return linux::Window(title, width, height);
		else if (target_system_is_windows<>::value)
			return windows::Window(title, width, height);
		else
			throw runtime_error("Can't create window for current target system");
	}
}

#endif