#pragma once

#include <memory>

#include "interface/i_hub.h"
#include "interface/i_frontend.h"

namespace biz {
struct AppSettings
{
};

class Application : public interface::IHub
{
public:
	Application(const AppSettings& aSettings);

	void Run();

private:
	std::shared_ptr<interface::IFrontend> myFrontend;
};
} // namespace biz
