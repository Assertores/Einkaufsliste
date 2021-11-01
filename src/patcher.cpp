#include "biz/patcher.h"

#include "interface/i_logger.h"

namespace biz {
void
Patch(const PatcherSettings& aSettings) {
	if (!aSettings.doPatching) {
		interface::ILogger::Log(
			interface::LogLevel::Debug,
			interface::LogType::StartUp,
			"asked to not patch");
		return;
	}

	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::StartUp,
		"patcher not implimented");
	// TODO(andreas): remove stuff from update
	// TODO(andreas): Translate data to new version
}
}  // namespace biz
