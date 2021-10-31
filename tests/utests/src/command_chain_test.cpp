#include "common/command_chain.h"

#include "interface/i_command_memento.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>

using ::testing::InSequence;
using ::testing::NiceMock;

class CommandMementoMock : public interface::ICommandMemento {
public:
	MOCK_METHOD(void, ReExecute, (), (override));
	MOCK_METHOD(void, Revert, (), (override));
};

TEST(CommandChain, add_nullptr_is_ignored)	// NOLINT
{
	common::CommandChain subject;

	subject.AddCommand(nullptr);

	EXPECT_FALSE(subject.Undo());
	EXPECT_FALSE(subject.Redo());
}

TEST(CommandChain, revertable_command_is_reverted)	// NOLINT
{
	common::CommandChain subject;
	auto command1 = std::make_unique<NiceMock<CommandMementoMock>>();

	EXPECT_CALL(*command1, Revert);

	subject.AddCommand(std::move(command1));

	EXPECT_TRUE(subject.Undo());
}

TEST(CommandChain, revertable_command_is_executed_again)  // NOLINT
{
	common::CommandChain subject;
	auto command1 = std::make_unique<NiceMock<CommandMementoMock>>();

	EXPECT_CALL(*command1, ReExecute);

	subject.AddCommand(std::move(command1));

	subject.Undo();
	EXPECT_TRUE(subject.Redo());
}

TEST(CommandChain, you_can_revert_and_reexecute_a_chain_of_commands)  // NOLINT
{
	common::CommandChain subject;
	auto command1 = std::make_unique<NiceMock<CommandMementoMock>>();
	auto command2 = std::make_unique<NiceMock<CommandMementoMock>>();

	{
		InSequence s;
		EXPECT_CALL(*command2, Revert);
		EXPECT_CALL(*command1, Revert);
		EXPECT_CALL(*command1, ReExecute);
	}

	subject.AddCommand(std::move(command1));
	subject.AddCommand(std::move(command2));

	subject.Undo();
	subject.Undo();
	subject.Redo();
}

TEST(CommandChain, you_can_change_the_history_of_commands)	// NOLINT
{
	common::CommandChain subject;
	auto command1 = std::make_unique<NiceMock<CommandMementoMock>>();
	auto command2 = std::make_unique<NiceMock<CommandMementoMock>>();
	auto command3 = std::make_unique<NiceMock<CommandMementoMock>>();

	{
		InSequence s;
		EXPECT_CALL(*command2, Revert);
		EXPECT_CALL(*command1, Revert);
		EXPECT_CALL(*command1, ReExecute);
		EXPECT_CALL(*command3, Revert);
		EXPECT_CALL(*command1, Revert);
		EXPECT_CALL(*command1, ReExecute);
		EXPECT_CALL(*command3, ReExecute);
	}

	subject.AddCommand(std::move(command1));
	subject.AddCommand(std::move(command2));

	subject.Undo();
	subject.Undo();
	subject.Redo();

	subject.AddCommand(std::move(command3));

	subject.Undo();
	subject.Undo();
	subject.Redo();
	subject.Redo();
}

TEST(CommandChain, a_non_revertable_command_wont_clear_the_history)	 // NOLINT
{
	common::CommandChain subject;
	auto command1 = std::make_unique<NiceMock<CommandMementoMock>>();

	EXPECT_CALL(*command1, ReExecute);

	subject.AddCommand(std::move(command1));

	subject.Undo();

	subject.AddCommand(nullptr);

	subject.Redo();
}
