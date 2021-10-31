#pragma once

#include "interface/i_logger.h"

#include <iostream>

namespace common {
class LogOnConsole : public interface::ILogger {
public:
	explicit LogOnConsole(std::ostream& aOut)
		: myOut(aOut) {}
	void DoLog(
		interface::LogLevel aLevel, interface::LogType aType, std::string_view aLog) override;

private:
	std::ostream& myOut;
};
}  // namespace common
