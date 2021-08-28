#include <functional>

#include <gtest/gtest.h>

#include "interface/i_command.h"

TEST(Command, command_gets_executed) // NOLINT
{
	bool wasExecuted = false;
	interface::fake::Command mockedCommand;
	mockedCommand.doExecute = [&]() {
		wasExecuted = true;
		return false;
	};

	interface::ICommand::Execute(mockedCommand.Clone());

	EXPECT_TRUE(wasExecuted);

	interface::ICommand::Clear();
}

TEST(Command, non_revertable_command_is_not_reverted) // NOLINT
{
	bool wasReversed = false;
	interface::fake::Command mockedCommand;
	mockedCommand.doExecute = [&]() {
		return false;
	};
	mockedCommand.doRevert = [&]() {
		wasReversed = true;
	};

	interface::ICommand::Execute(mockedCommand.Clone());
	interface::ICommand::Revert();

	EXPECT_FALSE(wasReversed);

	interface::ICommand::Clear();
}

TEST(Command, non_revertable_command_is_not_executed_again) // NOLINT
{
	int executeCount = 0;
	interface::fake::Command mockedCommand;
	mockedCommand.doExecute = [&]() {
		executeCount++;
		return false;
	};

	interface::ICommand::Execute(mockedCommand.Clone());
	interface::ICommand::Revert();
	interface::ICommand::ReExecute();

	EXPECT_EQ(executeCount, 1);

	interface::ICommand::Clear();
}

TEST(Command, revertable_command_is_reverted) // NOLINT
{
	bool wasReversed = false;
	interface::fake::Command mockedCommand;
	mockedCommand.doExecute = [&]() {
		return true;
	};
	mockedCommand.doRevert = [&]() {
		wasReversed = true;
	};

	interface::ICommand::Execute(mockedCommand.Clone());
	interface::ICommand::Revert();

	EXPECT_TRUE(wasReversed);

	interface::ICommand::Clear();
}

TEST(Command, revertable_command_is_executed_again) // NOLINT
{
	int executeCount = 0;
	interface::fake::Command mockedCommand;
	mockedCommand.doExecute = [&]() {
		executeCount++;
		return true;
	};

	interface::ICommand::Execute(mockedCommand.Clone());
	interface::ICommand::Revert();
	interface::ICommand::ReExecute();

	EXPECT_EQ(executeCount, 2);

	interface::ICommand::Clear();
}

TEST(Command, you_can_revert_and_reexecute_a_chain_of_commands) // NOLINT
{
	int executeCount1 = 0;
	interface::fake::Command mockedCommand1;
	mockedCommand1.doExecute = [&]() {
		executeCount1++;
		return true;
	};
	int executeCount2 = 0;
	interface::fake::Command mockedCommand2;
	mockedCommand2.doExecute = [&]() {
		executeCount2++;
		return true;
	};

	interface::ICommand::Execute(mockedCommand1.Clone());
	interface::ICommand::Execute(mockedCommand2.Clone());
	interface::ICommand::Revert();
	interface::ICommand::Revert();
	interface::ICommand::ReExecute();

	EXPECT_EQ(executeCount1, 2);
	EXPECT_EQ(executeCount2, 1);

	interface::ICommand::Clear();
}

TEST(Command, you_can_change_the_history_of_commands) // NOLINT
{
	int executeCount1 = 0;
	interface::fake::Command mockedCommand1;
	mockedCommand1.doExecute = [&]() {
		executeCount1++;
		return true;
	};
	int executeCount2 = 0;
	interface::fake::Command mockedCommand2;
	mockedCommand2.doExecute = [&]() {
		executeCount2++;
		return true;
	};
	int executeCount3 = 0;
	interface::fake::Command mockedCommand3;
	mockedCommand3.doExecute = [&]() {
		executeCount3++;
		return true;
	};

	interface::ICommand::Execute(mockedCommand1.Clone());
	interface::ICommand::Execute(mockedCommand2.Clone());
	interface::ICommand::Revert();
	interface::ICommand::Revert();
	interface::ICommand::ReExecute();
	interface::ICommand::Execute(mockedCommand3.Clone());
	interface::ICommand::Revert();
	interface::ICommand::Revert();
	interface::ICommand::ReExecute();
	interface::ICommand::ReExecute();

	EXPECT_EQ(executeCount1, 3);
	EXPECT_EQ(executeCount2, 1);
	EXPECT_EQ(executeCount3, 2);

	interface::ICommand::Clear();
}
