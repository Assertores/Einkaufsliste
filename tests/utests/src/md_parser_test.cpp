#include "common/md_parser.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(MdParser, markdown_file_is_parset)	 // NOLINT
{
	std::stringstream input;
	input << "# a\n## b\n### c\nd\n- e\n## x\ny\n- u\n- v\n- w\n";

	common::MdParser subject;

	subject.Parse(input);

	ASSERT_EQ(subject.GetField("a/b/c/d").size(), 1);
	EXPECT_EQ(subject.GetField("a/b/c/d")[0], "e");

	ASSERT_EQ(subject.GetField("a/x/y").size(), 3);
	EXPECT_EQ(subject.GetField("a/x/y")[0], "u");
	EXPECT_EQ(subject.GetField("a/x/y")[1], "v");
	EXPECT_EQ(subject.GetField("a/x/y")[2], "w");
}

TEST(MdParser, markdown_is_correctly_serialised)  // NOLINT
{
	std::stringstream output;
	common::MdParser subject;

	subject.AddToKey("a/b/c/d", "e");
	subject.AddToKey("a/x/y", "u");
	subject.AddToKey("a/x/y", "v");
	subject.AddToKey("a/x/y", "w");

	subject.Serialize(output);

	EXPECT_EQ(output.str(), "# a\n## b\n### c\nd\n- e\n\n## x\ny\n- u\n- v\n- w\n\n");
}

TEST(MdParser, getting_a_nonexistent_field_wont_result_in_death)  // NOLINT
{
	common::MdParser subject;

	EXPECT_EQ(subject.GetField("vudsag").size(), 0);
}
