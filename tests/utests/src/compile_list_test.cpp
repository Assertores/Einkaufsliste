#include "biz/compile_list.h"

#include "common/recipe.h"
#include "common/unit.h"
#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

// TODO(andreas): remove this after Convertion rework
namespace {
void
SetupMockUnitConvertion() {
	auto mockingFileImpl = std::make_shared<infas::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) { return std::vector<std::string>{"1"}; };
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path>{"kg"};
	};
	common::UnitConversion conversion(mockingFileImpl);
	common::Unit::SetConversionFiles({conversion});
}
}  // namespace

TEST(CompileList, list_is_compiled)	 // NOLINT
{
	SetupMockUnitConvertion();
	const common::Unit unit(12, "kg", "wfndsauk");

	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));
	common::Recipe(mockList).AddIngredient(unit);
	common::List(mockList).AddRecipe(common::Recipe(mockList));

	auto subject = biz::CompileList::Create();
	subject->SetReferences(list);

	subject->Execute();

	infas::IFileImpl::Clear();

	// TODO(andreas): Silent Contract? find better way to test this.
	ASSERT_NE(mockList->myContent.find("List"), mockList->myContent.end());
	bool containsUnit = false;
	for (const auto& it : mockList->myContent["List"]) {
		const auto ingredients = common::Unit::FromString(it);
		if (std::find(ingredients.begin(), ingredients.end(), unit) != ingredients.end()) {
			containsUnit = true;
			break;
		}
	}
	EXPECT_TRUE(containsUnit);
}

TEST(CompileList, compiling_a_list_can_not_be_undone)  // NOLINT
{
	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));

	auto subject = biz::CompileList::Create();
	subject->SetReferences(list);

	auto memento = subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_EQ(memento, nullptr);
}
