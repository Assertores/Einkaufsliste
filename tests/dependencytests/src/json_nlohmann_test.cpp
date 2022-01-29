#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

TEST(Json, can_deal_with_array_on_root_level)  // NOLINT
{
	const auto* const json = R"json([{"sasaskd": "asdfsa"}])json";
	const auto subject = nlohmann::json::parse(json);

	EXPECT_TRUE(subject.is_array());
}

TEST(Json, can_retreave_elements_with_array_opperator)	// NOLINT
{
	const auto* const json = R"json([{"sasaskd": "asdfsa"}])json";
	const auto subject = nlohmann::json::parse(json)[0];

	EXPECT_TRUE(subject.is_object());
}

TEST(Json, can_find_field_in_object)  // NOLINT
{
	const std::string key = "sasaskd";

	const auto json = R"json({")json" + key + R"json(": "asdfsa"})json";
	const auto subject = nlohmann::json::parse(json);

	EXPECT_TRUE(subject.contains(key));
}

TEST(Json, can_deal_with_string_field_types)  // NOLINT
{
	const std::string key = "sasaskd";

	const auto json = R"json({")json" + key + R"json(": "asdfsa"})json";
	const auto subject = nlohmann::json::parse(json);

	EXPECT_TRUE(subject[key].is_string());
}

TEST(Json, can_retreave_string_value_from_field)  // NOLINT
{
	const std::string key = "sasaskd";
	const std::string value = "asdfsa";

	const auto json = R"json({")json" + key + R"json(": ")json" + value + R"json("})json";
	const auto subject = nlohmann::json::parse(json);

	EXPECT_EQ(subject[key].get<std::string>(), value);
}

TEST(Json, can_iterate_over_array)	// NOLINT
{
	const std::string first = "afzukaesub";
	const std::string second = "sauneksae";
	const std::string third = "qwrew";
	const auto json = R"json([")json" + first + R"json(", ")json" + second + R"json(", ")json"
					  + third + R"json("])json";
	const auto subject = nlohmann::json::parse(json);

	int iterationCount = 0;
	bool hadFirst = false;
	bool hadSecond = false;
	bool hadThird = false;
	for (const auto& it : subject) {
		iterationCount++;
		if (it == first) {
			hadFirst = true;
		}
		if (it == second) {
			hadSecond = true;
		}
		if (it == third) {
			hadThird = true;
		}
	}
	EXPECT_EQ(iterationCount, 3);
	EXPECT_TRUE(hadFirst);
	EXPECT_TRUE(hadSecond);
	EXPECT_TRUE(hadThird);
}