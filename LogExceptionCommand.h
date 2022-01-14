#pragma once
#include "ICommand.h"
#include <iostream>

template <typename T, typename E>
class LogExceptionCommand : public ICommand
{
public:
	LogExceptionCommand()
	{
		
	}
	void Execute() override
	{
		printf("%s: %s\n", typeid(T).name(), E().what());
	}
	
};