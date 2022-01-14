#pragma once
#include "ICommand.h"
#include <iostream>

class Command1 : public ICommand
{
public:
	void Execute() override
	{
		printf("Execute Command1\n");
		throw std::exception();
	}
};