#pragma once
#include "iostream"
// simple variadic print function for debugging purposes
// this is not recommended in practice! would
// drastically increase code size
template<typename T>
void println(T&& t) {
	std::cout << t << "\n";
}

template<typename T, typename... Args>
void println(T&& t, Args&&... args) {
	std::cout << t << "\n";
	println(args...);
}

template<typename T>
void printOneLine(T&& t) {
	std::cout << " " << t;
}

template<typename T, typename... Args>
void printOneLine(T&& t, Args&&... args) {
	std::cout << " " << t;
	printOneLine(args...);
}

template<typename T>
void print(T&& t) {
	std::cout << t << "\n";
}

template<typename T, typename... Args>
void print(T&& t, Args&&... args) {
	std::cout << t;
	printOneLine(args...);
	std::cout << "\n";
}

template<typename T>
void e_println(T&& t) {
	std::cerr << t << "\n";
}

template<typename T, typename... Args>
void e_println(T&& t, Args&&... args) {
	std::cerr << t << "\n";
	e_println(args...);
}

template<typename T>
void e_printOneLine(T&& t) {
	std::cerr << " " << t;
}

template<typename T, typename... Args>
void e_printOneLine(T&& t, Args&&... args) {
	std::cerr << " " << t;
	e_printOneLine(args...);
}

template<typename T>
void e_print(T&& t) {
	std::cerr << t << "\n";
}

template<typename T, typename... Args>
void e_print(T&& t, Args&&... args) {
	std::cerr << t;
	e_printOneLine(args...);
	std::cerr << "\n";
}

#ifdef K_DEBUG
#define kp(...) print(__VA_ARGS__)
#define kpln(...) println(__VA_ARGS__)
#define ekp(...) e_print(__VA_ARGS__)
#define ekpln(...) e_println(__VA_ARGS__)
#else
#define kp(...)
#define kpln(...)
#define ekp(...)
#define ekpln(...)
#endif