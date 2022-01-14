#pragma once
#include "ICommand.h"
#include <exception>

class Command3 : public ICommand
{
public:
	void Execute() override
	{
		printf("Execute Command3\n");
		throw std::bad_exception();
	}
};