#include "common/updater_template_methode.h"

#include "interface/i_logger.h"

namespace common {
bool
UpdaterTemplateMethode::Execute(const UpdaterSettings& aSettings) {
	if (!aSettings.doUpdate) {
		infas::ILogger::Log(
			infas::LogLevel::Debug,
			infas::LogType::StartUp,
			"asked to not updater");
		return false;
	}
	if (!RetraveMetaData()) {
		return false;
	}
	if (!IsPatchUpdate()) {
		return false;
	}
	if (!RetreavePatchLocation()) {
		return false;
	}
	if (!DownloadPatch()) {
		CleanUp();
		return false;
	}
	if (!ExtractPatch()) {
		CleanUp();
		return false;
	}
	const bool isPatched = ApplyPatch();
	CleanUp();
	return isPatched;
}
}  // namespace common