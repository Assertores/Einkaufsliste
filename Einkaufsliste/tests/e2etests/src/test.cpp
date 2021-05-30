#include <gtest/gtest.h>

#include "biz/entry.h"

TEST(test, test) // NOLINT
{
	std::stringstream out;
	biz::Entry(
		std::vector<std::string_view> { "exe",
										"--no-patch",
										"--no-update",
										"--log-level",
										"verbose",
										"-something" },
		out);

	EXPECT_FALSE(out.str().empty());
}