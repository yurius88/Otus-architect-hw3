#pragma once
#include "ICommand.h"
#include "LogExceptionCommand.h"

#include <queue>
#include <exception>
#include <memory>
#include <map>

struct ErrorHandlerValueParams
{
	std::string Exception;
	std::shared_ptr<ICommand> HandlerCmd;
};

class ErrorHandler
{
public:
	ErrorHandler(std::queue<std::shared_ptr<ICommand>>* cmds) : _cmds(cmds)
	{
	
	}

	void Handle(std::shared_ptr<ICommand> cmd, const std::exception& ex)
	{
		// найти в обработчике стратегию обработки ошибки
		std::string exceptionName = typeid(ex).name();
		auto result = _handlers.equal_range(typeid(*cmd.get()).name());
		for (MMAPIterator it = result.first; it != result.second; it++)
		{
			if (exceptionName == it->second.Exception)
			{
				_cmds->push(it->second.HandlerCmd);
				break;
			}
		}
	}

	template<typename T, typename E>
	void RegisterHandler(std::shared_ptr<ICommand> cmd)
	{
		ErrorHandlerValueParams p;
		p.Exception = typeid(E).name();
		p.HandlerCmd = cmd;

		_handlers.insert({ typeid(T).name(), p });
	}

private:
	std::queue<std::shared_ptr<ICommand>>* _cmds;
	std::multimap<std::string, ErrorHandlerValueParams> _handlers;
	typedef std::multimap<std::string, ErrorHandlerValueParams>::iterator MMAPIterator;
};
