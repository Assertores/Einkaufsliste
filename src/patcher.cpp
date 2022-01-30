#include "biz/patcher.h"

#include "interface/i_logger.h"

namespace biz {
void
Patch(const PatcherSettings& aSettings) {
	if (!aSettings.doPatching) {
		infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::StartUp, "asked to not patch");
		return;
	}

	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::StartUp, "patcher not implemented");
	// TODO(andreas): remove stuff from update
	// TODO(andreas): Translate data to new version
}
} // namespace biz
