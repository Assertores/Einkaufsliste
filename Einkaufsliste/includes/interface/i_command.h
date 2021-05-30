#pragma once

#include <memory>
#include <vector>
#include <functional>

namespace interface {
class ICommand
{
public:
	static void Execute(std::unique_ptr<ICommand> aCommand);
	static void ReExecute();
	static void Revert();
	static void Clear();

	virtual ~ICommand() = default;

	virtual std::unique_ptr<ICommand> Clone() = 0;

protected:
	// returns wether or not this command is reversable
	virtual bool DoExecute() = 0;
	virtual void DoRevert() {};

private:
	static std::vector<std::unique_ptr<ICommand>> myCommandHistory;
	static size_t myBackOffset;
};

namespace fake {
class Command : public ICommand
{
public:
	std::function<bool()> doExecute = [this]() {
		doExecuteCount++;
		return false;
	};
	std::function<void()> doRevert = [this]() {
		doRevertCount++;
	};

	std::unique_ptr<ICommand> Clone() override
	{
		// TODO(andreas): don't clone lambdas if they are default
		auto result = std::make_unique<Command>();
		result->doExecute = doExecute;
		result->doRevert = doRevert;
		return result;
	}

	bool DoExecute() override { return doExecute(); }
	void DoRevert() override { doRevert(); };

	int doExecuteCount = 0;
	int doRevertCount = 0;
};
}
} // namespace interface
