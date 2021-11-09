#pragma once

#include <string>

namespace common {
struct UpdaterSettings {
	bool doUpdate;
	bool getPrerelease;
	std::string url;
};

class UpdaterTemplateMethode {
public:
	virtual ~UpdaterTemplateMethode() = default;

	bool Execute(const UpdaterSettings& aSettings);

protected:
	virtual bool RetraveMetaData() = 0;
	virtual bool IsPatchUpdate() = 0;
	virtual bool RetreavePatchLocation() = 0;
	virtual bool DownloadPatch() = 0;
	virtual bool ExtractPatch() = 0;
	virtual bool ApplyPatch() = 0;
	virtual void CleanUp() = 0;
};
}  // namespace common