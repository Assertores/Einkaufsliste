#include "common/i_command.h"

namespace common {
void
ICommand::Execute(std::unique_ptr<ICommand> aCommand)
{
	myCommandHistory.resize(myCommandHistory.size() - myBackOffset);
	if (aCommand->DoExecute())
	{
		myCommandHistory.emplace_back(std::move(aCommand));
	}
}

void
ICommand::ReExecute()
{
	if (myBackOffset == 0)
	{
		return;
	}
	myCommandHistory[myCommandHistory.size() - myBackOffset]->DoExecute();
	myBackOffset--;
}

void
ICommand::Revert()
{
	if (myBackOffset == myCommandHistory.size())
	{
		return;
	}
	myCommandHistory[myCommandHistory.size() - 1 - myBackOffset]->DoRevert();
	myBackOffset++;
}
} // namespace common
