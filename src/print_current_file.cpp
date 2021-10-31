#include "biz/print_current_file.h"

namespace common {
void
PrintCurrentFile::SetReferences(
	std::ostream* aOut,
	std::weak_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe,
	std::weak_ptr<Observable<std::optional<Week>>> aCurrentWeek)
{
	myOut = aOut;
	myCurrentRecipe = std::move(aCurrentRecipe);
	myCurrentWeek = std::move(aCurrentWeek);

	auto recipe = myCurrentRecipe.lock();
	if (!recipe)
	{
		return;
	}
	recipe->Subscribe(weak_from_this());

	auto week = myCurrentWeek.lock();
	if (!week)
	{
		return;
	}
	week->Subscribe(weak_from_this());
};

PrintCurrentFile::~PrintCurrentFile()
{
	auto recipe = myCurrentRecipe.lock();
	if (recipe)
	{
		recipe->Remove(weak_from_this());
	}
	auto week = myCurrentWeek.lock();
	if (week)
	{
		week->Remove(weak_from_this());
	}
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
PrintCurrentFile::OnChange(std::optional<Recipe> aElement)
{
	if (!aElement.has_value())
	{
		return;
	}
	myCurrentFile = std::make_shared<Recipe>(std::move(aElement.value()));
}

void
PrintCurrentFile::OnChange(std::optional<Week> aElement)
{
	if (!aElement.has_value())
	{
		return;
	}
	myCurrentFile = std::make_shared<Week>(std::move(aElement.value()));
}
} // namespace common
