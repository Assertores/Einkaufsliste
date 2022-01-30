#pragma once

#include <functional>

namespace infas {
class ICommandMemento {
public:
	virtual ~ICommandMemento() = default;

	virtual void ReExecute() = 0;
	virtual void Revert() = 0;
};

namespace fake {
class CommandMemento : public ICommandMemento {
public:
	std::function<void()> reExecute = [this]() { reExecuteCount++; };
	std::function<void()> revert = [this]() { revertCount++; };

	void ReExecute() override { return reExecute(); }
	void Revert() override { revert(); };

	int reExecuteCount = 0;
	int revertCount = 0;
};
} // namespace fake
} // namespace infas
