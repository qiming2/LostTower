#include <iostream>
#include <memory>
#include "KTEngine/Window.h"

int main() {
	Ref<Window> window = Window::getInstance();
	window->run();
	return EXIT_SUCCESS;
}