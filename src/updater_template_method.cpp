#include "common/updater_template_method.h"

#include "interface/i_logger.h"

namespace common {
bool
UpdaterTemplateMethod::Execute(const UpdaterSettings& aSettings) {
	if (!aSettings.doUpdate) {
		infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::StartUp, "asked to not update");
		return false;
	}
	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::StartUp,
		"retreaving meta data ...");
	if (!RetrieveMetaData(aSettings.getPrerelease)) {
		return false;
	}
	infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "checking version ...");
	if (!IsPatchUpdate()) {
		infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::StartUp, "nothing to update");
		return false;
	}

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::StartUp,
		"retreaving patch location ...");
	if (!RetrievePatchLocation()) {
		return false;
	}

	infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "downloading patch ...");
	if (!DownloadPatch()) {
		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "cleaning up ...");
		CleanUp();
		return false;
	}
	infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "extracting patch ...");
	if (!ExtractPatch()) {
		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "cleaning up ...");
		CleanUp();
		return false;
	}
	infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "applying patch ...");
	const bool isPatched = ApplyPatch();
	infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "cleaning up ...");
	CleanUp();
	return isPatched;
}
}  // namespace common
