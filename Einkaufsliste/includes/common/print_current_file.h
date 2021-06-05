#pragma once

#include <memory>
#include <ostream>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_observer.h"

namespace common {
class PrintCurrentFile final
	: public interface::ICommand
	, public interface::IObserver<Recipe>
	, public std::enable_shared_from_this<PrintCurrentFile>
{
public:
	PrintCurrentFile() = default;
	PrintCurrentFile(const PrintCurrentFile&) = default;
	PrintCurrentFile(PrintCurrentFile&&) = default;
	PrintCurrentFile& operator=(const PrintCurrentFile&) = default;
	PrintCurrentFile& operator=(PrintCurrentFile&&) = default;

	~PrintCurrentFile() override;
	void SetReferences(std::ostream* aOut, std::weak_ptr<Observable<Recipe>> aCurrentRecipe);

	std::unique_ptr<ICommand> Clone() override;
	bool DoExecute() override;

	void OnChange(Recipe aElement) override;

private:
	std::weak_ptr<Observable<Recipe>> myCurrentRecipe;
	std::ostream* myOut = nullptr;

	std::shared_ptr<interface::IFile> myCurrentFile;
};
} // namespace common
