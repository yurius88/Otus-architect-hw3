#pragma once
#include "ICommand.h"
#include <exception>

class Command2 : public ICommand
{
public:
	void Execute() override
	{
		printf("Execute Command2\n");
		throw std::bad_alloc();
	}
};