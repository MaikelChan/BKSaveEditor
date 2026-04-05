#include "Window.h"

Window::Window(const WindowParams& params) : params(params)
{

}

Window::~Window()
{

}

void Window::Terminate()
{
	isRunning = false;
}