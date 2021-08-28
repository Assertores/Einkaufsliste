#pragma once

#include <memory>

namespace interface {
class ICommandMemento;
};

namespace common {
class CommandChain
{
public:
	void Undo();
	void Redo();
	void AddCommand(std::unique_ptr<interface::ICommandMemento> aCommand);

private:
	std::vector<std::unique_ptr<interface::ICommandMemento>> myCommandHistory;
	size_t myBackOffset = 0;
};
}