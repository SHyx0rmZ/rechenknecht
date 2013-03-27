#ifndef _RK_WINDOW_HPP_
#define _RK_WINDOW_HPP_

#include "module/target_traits/target_traits.hpp"
#include <stdexcept>
#include <string>

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

	#if defined(SHY_TARGET_SYSTEM_LINUX)
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
	#endif

	#if defined(SHY_TARGET_SYSTEM_WINDOWS)
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
	#endif

	Window &CreateWindow(const string &title, unsigned int width, unsigned height)
	{
		#if defined(SHY_TARGET_SYSTEM_LINUX)
		return linux::Window(title, width, height);
		#elif defined(SHY_TARGET_SYSTEM_WINDOWS)
		return windows::Window(title, width, height);
		#else
		throw runtime_error("Can't create window for current target system");
		#endif
	}
}

#endif