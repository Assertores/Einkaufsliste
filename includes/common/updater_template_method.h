#pragma once

#include <string>

namespace common {
struct UpdaterSettings {
	bool doUpdate;
	bool getPrerelease;
	std::string url;
};

class UpdaterTemplateMethod {
public:
	virtual ~UpdaterTemplateMethod() = default;

	bool Execute(const UpdaterSettings& aSettings);

protected:
	virtual bool RetrieveMetaData() = 0;
	virtual bool IsPatchUpdate() = 0;
	virtual bool RetrievePatchLocation() = 0;
	virtual bool DownloadPatch() = 0;
	virtual bool ExtractPatch() = 0;
	virtual bool ApplyPatch() = 0;
	virtual void CleanUp() = 0;
};
}  // namespace common

