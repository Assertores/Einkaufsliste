#include "common/command_chain.h"

#include "interface/i_command_memento.h"

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

bool
CommandChain::Undo()
{
	if (myBackOffset == myCommandHistory.size())
	{
		return false;
	}
	myCommandHistory[myCommandHistory.size() - 1 - myBackOffset]->Revert();
	myBackOffset++;
	return true;
}

bool
CommandChain::Redo()
{
	if (myBackOffset == 0)
	{
		return false;
	}
	myCommandHistory[myCommandHistory.size() - myBackOffset]->ReExecute();
	myBackOffset--;
	return true;
}
} // namespace common
