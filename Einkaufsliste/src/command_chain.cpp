#include "common/command_chain.h"

#include "interface/i_command_memento"

namespace common {

void
CommandChain::AddCommand(std::unique_ptr<interface::ICommandMemento> aCommand)
{
	if (aCommand == nullptr)
	{
		return;
	}
	myCommandHistory.resize(myCommandHistory.size() - myBackOffset);
	myCommandHistory.emplace_back(std::move(aCommand));
}

void
CommandChain::Undo()
{
	if (myBackOffset == myCommandHistory.size())
	{
		return;
	}
	myCommandHistory[myCommandHistory.size() - 1 - myBackOffset]->DoRevert();
	myBackOffset++;
}

void
CommandChain::Redo()
{
	if (myBackOffset == 0)
	{
		return;
	}
	myCommandHistory[myCommandHistory.size() - myBackOffset]->DoExecute();
	myBackOffset--;
}
} // namespace common
