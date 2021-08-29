#pragma once

#include <functional>
#include <memory>

#include "interface/i_command_memento.h"

namespace interface {
class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual std::unique_ptr<ICommandMemento> Execute() = 0;
};

namespace fake {
class Command : public ICommand
{
public:
	std::function<std::unique_ptr<ICommandMemento>()> execute = [this]() {
		executeCount++;
		return nullptr;
	};
	std::unique_ptr<ICommandMemento> Execute() override { return execute(); }

	int executeCount = 0;
};
} // namespace fake
} // namespace interface
