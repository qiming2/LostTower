#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "k_print.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/include/glfw3.h"
#include "GLAD/include/glad/glad.h"
#define Ref std::shared_ptr
#define BIT(x, y) ((x) & (1 << y))
#define SET(x, y) ((x) | (1 << y))
#define KEPSILON 0.0001
