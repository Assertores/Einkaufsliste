#pragma once

#include <iostream>
#include <string_view>
#include <vector>

namespace biz {
int Entry(
	const std::vector<std::string_view>& aArgs,
	std::istream& aInput = std::cin,
	std::ostream& aOutput = std::cout);
} // namespace biz
