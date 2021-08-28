#pragma once

#include <functional>

namespace interface {
class ICommandNode
{
public:
	virtual ~ICommandNode() = default;

	virtual void ReExecute() = 0;
	virtual void Revert() = 0;
};

namespace fake {
class Command : public ICommandMemento
{
public:
	std::function<bool()> reExecute = [this]() {
		reExecuteCount++;
		return false;
	};
	std::function<void()> revert = [this]() {
		revertCount++;
	};

	bool ReExecute() override { return reExecute(); }
	void Revert() override { revert(); };

	int reExecuteCount = 0;
	int revertCount = 0;
};
} // namespace fake
} // namespace interface
