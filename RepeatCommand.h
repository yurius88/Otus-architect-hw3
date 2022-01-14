#pragma once
#include "ICommand.h"
#include <memory>
#include "RepeatCommandException.h"

template<typename T>
class RepeatCommand : public ICommand
{
public:
	// repeatAttempt - максимальное кол-во повторений команды
	RepeatCommand(unsigned repeatAttempt, std::shared_ptr<ICommand> cmd)
		: _repeatAttempt(repeatAttempt),
		_cmd(cmd)
	{
		
	}

	void Execute() override
	{
		for (unsigned attempt = 0; attempt < _repeatAttempt; ++attempt)
		{
			try
			{
				_cmd->Execute();
			}
			catch (const std::exception& ex)
			{
				if ((attempt+1) == _repeatAttempt)
					throw (RepeatCommandException<T>());
			}
		}
	}

private:
	unsigned _repeatAttempt;
	std::shared_ptr<ICommand> _cmd;
};