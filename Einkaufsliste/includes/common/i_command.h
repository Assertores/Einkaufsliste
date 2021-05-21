#pragma once

#include <memory>
#include <vector>

namespace common {
class ICommand
{
public:
	virtual ~ICommand() = default;

	static void Execute(std::unique_ptr<ICommand> aCommand);
	static void ReExecute();
	static void Revert();
	static void Clear();

	virtual std::unique_ptr<ICommand> Clone() = 0;

protected:
	// returns wether or not this command is reversable
	virtual bool DoExecute() = 0;
	virtual void DoRevert() {};

private:
	static std::vector<std::unique_ptr<ICommand>> myCommandHistory;
	static size_t myBackOffset;
};
} // namespace common
