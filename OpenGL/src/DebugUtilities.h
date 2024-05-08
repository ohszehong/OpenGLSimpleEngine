#pragma once

#include <GL/glew.h>
#include <iostream>
#include <cmath>

#define ASSERT(x) if (!(x)) __debugbreak()
#ifdef _DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else 
#define GLCall(x) x
#endif

//FUNCTIONS
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

// Define a tolerance for floating-point comparison
static const float epsilon = 0.0001f;

// Check if the difference between two floating-point numbers is within a tolerance
bool isEqual(float a, float b);
