#include <gtest/gtest.h>
#include <queue>

#include "ErrorHandler.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "LogExceptionCommand.h"
#include "RepeatCommand.h"
#include "RepeatCommandException.h"

// команда 1 сгенерировала исключение
TEST(HW3, Command1Exception)
{
	ASSERT_THROW(
		{
			Command1 cmd;
			cmd.Execute();
		},
		std::exception);
}
// команда 2 сгенерировала исключение
TEST(HW3, Command2Exception)
{
	ASSERT_THROW(
		{
			Command2 cmd;
			cmd.Execute();
		},
		std::bad_alloc);
}
// команда 3 сгенерировала исключение
TEST(HW3, Command3Exception)
{
	ASSERT_THROW(
		{
			Command3 cmd;
			cmd.Execute();
		},
		std::bad_exception);
}
TEST(HW3, TestHW3)
{
	std::queue<std::shared_ptr<ICommand>> queue;
	std::shared_ptr<ICommand> cmd1 = std::make_shared<Command1>();
	std::shared_ptr<ICommand> cmd2 = std::make_shared<Command2>();
	std::shared_ptr<ICommand> cmd3 = std::make_shared<Command3>();
	
	queue.push(cmd1);
	queue.push(cmd2);
	queue.push(cmd3);
	
	ErrorHandler errorHandler(&queue);
	// запись в лог при выбросе исключения команды 1
	errorHandler.RegisterHandler<Command1, std::exception>(
		std::make_shared<LogExceptionCommand<Command1, std::exception>>());
	
	// повтор команды, при выбросе исключения bad_alloc команды 2
	errorHandler.RegisterHandler<Command2, std::bad_alloc>(
		std::make_shared<RepeatCommand<Command2>>(1, cmd2));
	// запись в лог при повторном исключении той команды, которую нужно повторить
	errorHandler.RegisterHandler<RepeatCommand<Command2>, RepeatCommandException<Command2>>(
		std::make_shared<LogExceptionCommand<RepeatCommand<Command2>, RepeatCommandException<Command2>>>());
	
	// дважды повтор команды, при выбросе исключения runtime_error команды 3
	errorHandler.RegisterHandler<Command3, std::bad_exception>(
		std::make_shared<RepeatCommand<Command3>>(2, cmd3));
	// запись в лог в случае дважды невыполненной команды 3
	errorHandler.RegisterHandler<RepeatCommand<Command3>, RepeatCommandException<Command3>>(
		std::make_shared<LogExceptionCommand<RepeatCommand<Command3>, RepeatCommandException<Command3>>>());
	
	while (!queue.empty())
	{
		std::shared_ptr<ICommand> cmd = queue.front();
		queue.pop();
	
		try
		{
			cmd->Execute();
		}
		catch (const std::exception& ex)
		{
			errorHandler.Handle(cmd, ex);
		}
	}
}