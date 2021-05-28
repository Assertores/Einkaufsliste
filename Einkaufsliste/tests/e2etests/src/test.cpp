#include "biz/entry.h"

#include <gtest/gtest.h>

TEST(test, test) // NOLINT
{
	std::stringstream out;
	biz::Entry(std::vector<std::string_view> { "", "--log-level", "verbose", "-something" }, out);

	EXPECT_FALSE(out.str().empty());
}