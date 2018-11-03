#pragma once

#include <sstream>

template <typename T> std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}
