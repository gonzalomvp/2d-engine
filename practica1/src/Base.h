#pragma once
#include <sstream> 

const float PI = 3.14159265f;

template <typename T> std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}
