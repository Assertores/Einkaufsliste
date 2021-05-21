#include <functional>

#include <gtest/gtest.h>

#include "common/i_command.h"

class CommandMock : public common::ICommand
{
public:
	std::function<bool()> doExecute = []() {
		return false;
	};
	std::function<void()> doRevert = []() {
	};

	std::unique_ptr<ICommand> Clone() override
	{
		auto result = std::make_unique<CommandMock>();
		result->doExecute = doExecute;
		result->doRevert = doRevert;
		return result;
	}
	bool DoExecute() override { return doExecute(); }
	void DoRevert() override { doRevert(); };
};

TEST(Command, command_gets_executed) // NOLINT
{
	bool wasExecuted = false;
	CommandMock mockedCommand;
	mockedCommand.doExecute = [&]() {
		wasExecuted = true;
		return false;
	};

	common::ICommand::Execute(mockedCommand.Clone());

	EXPECT_TRUE(wasExecuted);

	common::ICommand::Clear();
}

TEST(Command, non_revertable_command_is_not_reverted) // NOLINT
{
	bool wasReversed = false;
	CommandMock mockedCommand;
	mockedCommand.doExecute = [&]() {
		return false;
	};
	mockedCommand.doRevert = [&]() {
		wasReversed = true;
	};

	common::ICommand::Execute(mockedCommand.Clone());
	common::ICommand::Revert();

	EXPECT_FALSE(wasReversed);

	common::ICommand::Clear();
}

TEST(Command, non_revertable_command_is_not_executed_again) // NOLINT
{
	int executeCount = 0;
	CommandMock mockedCommand;
	mockedCommand.doExecute = [&]() {
		executeCount++;
		return false;
	};

	common::ICommand::Execute(mockedCommand.Clone());
	common::ICommand::Revert();
	common::ICommand::ReExecute();

	EXPECT_EQ(executeCount, 1);

	common::ICommand::Clear();
}

TEST(Command, revertable_command_is_reverted) // NOLINT
{
	bool wasReversed = false;
	CommandMock mockedCommand;
	mockedCommand.doExecute = [&]() {
		return true;
	};
	mockedCommand.doRevert = [&]() {
		wasReversed = true;
	};

	common::ICommand::Execute(mockedCommand.Clone());
	common::ICommand::Revert();

	EXPECT_TRUE(wasReversed);

	common::ICommand::Clear();
}

TEST(Command, revertable_command_is_executed_again) // NOLINT
{
	int executeCount = 0;
	CommandMock mockedCommand;
	mockedCommand.doExecute = [&]() {
		executeCount++;
		return true;
	};

	common::ICommand::Execute(mockedCommand.Clone());
	common::ICommand::Revert();
	common::ICommand::ReExecute();

	EXPECT_EQ(executeCount, 2);

	common::ICommand::Clear();
}

TEST(Command, you_can_revert_and_reexecute_a_chain_of_commands) // NOLINT
{
	int executeCount1 = 0;
	CommandMock mockedCommand1;
	mockedCommand1.doExecute = [&]() {
		executeCount1++;
		return true;
	};
	int executeCount2 = 0;
	CommandMock mockedCommand2;
	mockedCommand2.doExecute = [&]() {
		executeCount2++;
		return true;
	};

	common::ICommand::Execute(mockedCommand1.Clone());
	common::ICommand::Execute(mockedCommand2.Clone());
	common::ICommand::Revert();
	common::ICommand::Revert();
	common::ICommand::ReExecute();

	EXPECT_EQ(executeCount1, 2);
	EXPECT_EQ(executeCount2, 1);

	common::ICommand::Clear();
}

TEST(Command, you_can_change_the_history_of_commands) // NOLINT
{
	int executeCount1 = 0;
	CommandMock mockedCommand1;
	mockedCommand1.doExecute = [&]() {
		executeCount1++;
		return true;
	};
	int executeCount2 = 0;
	CommandMock mockedCommand2;
	mockedCommand2.doExecute = [&]() {
		executeCount2++;
		return true;
	};
	int executeCount3 = 0;
	CommandMock mockedCommand3;
	mockedCommand3.doExecute = [&]() {
		executeCount3++;
		return true;
	};

	common::ICommand::Execute(mockedCommand1.Clone());
	common::ICommand::Execute(mockedCommand2.Clone());
	common::ICommand::Revert();
	common::ICommand::Revert();
	common::ICommand::ReExecute();
	common::ICommand::Execute(mockedCommand3.Clone());
	common::ICommand::Revert();
	common::ICommand::Revert();
	common::ICommand::ReExecute();
	common::ICommand::ReExecute();

	EXPECT_EQ(executeCount1, 3);
	EXPECT_EQ(executeCount2, 1);
	EXPECT_EQ(executeCount3, 2);

	common::ICommand::Clear();
}
