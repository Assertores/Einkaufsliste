#pragma once

#include <memory>
#include <vector>

namespace interface {
class ICommandMemento;
};

namespace common {
class CommandChain {
public:
	bool Undo();
	bool Redo();
	void AddCommand(std::unique_ptr<interface::ICommandMemento> aCommand);

private:
	std::vector<std::unique_ptr<interface::ICommandMemento>> myCommandHistory;
	size_t myBackOffset = 0;
};
}  // namespace common
