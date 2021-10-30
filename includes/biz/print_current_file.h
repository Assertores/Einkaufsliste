#pragma once

#include <memory>
#include <ostream>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_observer.h"

namespace common {
class PrintCurrentFile final
	: public interface::ICommand
	, public interface::IObserver<std::optional<Recipe>>
	, public std::enable_shared_from_this<PrintCurrentFile>
{
public:
	static std::shared_ptr<PrintCurrentFile> Create()
	{
		return std::make_shared<PrintCurrentFile>();
	}

	~PrintCurrentFile() override;
	void SetReferences(
		std::ostream* aOut,
		std::weak_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe);

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void OnChange(std::optional<Recipe> aElement) override;

	// protected:
	PrintCurrentFile() = default;
	PrintCurrentFile(const PrintCurrentFile&) = default;
	PrintCurrentFile(PrintCurrentFile&&) = default;
	PrintCurrentFile& operator=(const PrintCurrentFile&) = default;
	PrintCurrentFile& operator=(PrintCurrentFile&&) = default;

private:
	std::weak_ptr<Observable<std::optional<Recipe>>> myCurrentRecipe;
	std::ostream* myOut = nullptr;

	std::shared_ptr<interface::IFile> myCurrentFile;
};
} // namespace common
