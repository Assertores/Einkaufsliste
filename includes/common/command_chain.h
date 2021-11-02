#pragma once

#include <memory>
#include <vector>

namespace infas {
class ICommandMemento;
};

namespace common {
class CommandChain {
public:
	bool Undo();
	bool Redo();
	void AddCommand(std::unique_ptr<infas::ICommandMemento> aCommand);

private:
	std::vector<std::unique_ptr<infas::ICommandMemento>> myCommandHistory;
	size_t myBackOffset = 0;
};
}  // namespace common
