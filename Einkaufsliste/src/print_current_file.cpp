#include "common/print_current_file.h"

namespace common {
void
PrintCurrentFile::SetReferences(
	std::ostream* aOut,
	std::weak_ptr<Observable<Recipe>> aCurrentRecipe)
{
	myOut = aOut;
	myCurrentRecipe = std::move(aCurrentRecipe);

	auto recipe = myCurrentRecipe.lock();
	if (!recipe)
	{
		return;
	}
	recipe->Subscribe(weak_from_this());
};

PrintCurrentFile::~PrintCurrentFile()
{
	auto recipe = myCurrentRecipe.lock();
	if (!recipe)
	{
		return;
	}
	recipe->Remove(weak_from_this());
}

std::unique_ptr<interface::ICommandMemento>
PrintCurrentFile::Execute()
{
	if (!myCurrentFile)
	{
		*myOut << "no file to print\n";
		return nullptr;
	}
	*myOut << myCurrentFile->Print();
	return nullptr;
}

void
PrintCurrentFile::OnChange(Recipe aElement)
{
	myCurrentFile = std::make_shared<Recipe>(std::move(aElement));
}
} // namespace common
