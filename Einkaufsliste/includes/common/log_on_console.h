#pragma once

#include <iostream>

#include "interface/i_logger.h"

namespace common {
class LogOnConsole : public interface::ILogger
{
public:
	LogOnConsole(std::ostream& aOut)
		: myOut(aOut)
	{
	}
	void
	DoLog(interface::LogLevel aLevel, interface::LogType aType, std::string_view aLog) override;

private:
	std::ostream& myOut;
};
} // namespace common
