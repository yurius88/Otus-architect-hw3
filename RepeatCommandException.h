#pragma once
#include <exception>
#include <string>

template<typename T>
class RepeatCommandException : public std::exception
{
public:
	char const* what() const override
	{
		return "Repeat command failed";
	}

};
