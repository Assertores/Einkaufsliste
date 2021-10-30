#include <string_view>
#include <vector>

#include "biz/entry.h"

int
main(int argc, char** argv) // NOLINT
{
	std::vector<std::string_view> args;
	args.reserve(argc);
	for (int i = 0; i < argc; i++)
	{
		args.emplace_back(argv[i]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	}
	return biz::Entry(args);
}
