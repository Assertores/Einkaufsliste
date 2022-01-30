#pragma once

#include "interface/i_command_memento.h"

#include <functional>
#include <memory>

namespace infas {
class ICommand {
public:
	virtual ~ICommand() = default;

	virtual std::unique_ptr<ICommandMemento> Execute() = 0;
};

namespace fake {
class Command : public ICommand {
public:
	std::function<std::unique_ptr<ICommandMemento>()> execute = [this]() {
		executeCount++;
		return std::make_unique<CommandMemento>();
	};
	std::unique_ptr<ICommandMemento> Execute() override { return execute(); }

	int executeCount = 0;
};
} // namespace fake
} // namespace infas
