#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "common/recipe.h"
#include "common/week.h"
#include "interface/i_command.h"
#include "interface/i_observer.h"

#include <memory>
#include <optional>
#include <ostream>

namespace biz {
class PrintCurrentFile final
	: public infas::ICommand
	, public infas::IObserver<std::optional<common::Recipe>>
	, public infas::IObserver<std::optional<common::Week>>
	, public infas::IObserver<std::optional<common::List>>
	, public std::enable_shared_from_this<PrintCurrentFile> {
public:
	static std::shared_ptr<PrintCurrentFile> Create() {
		return std::make_shared<PrintCurrentFile>();
	}

	~PrintCurrentFile() override;
	void SetReferences(
		std::ostream* aOut,
		std::weak_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe,
		std::weak_ptr<common::Observable<std::optional<common::Week>>> aCurrentWeek,
		std::weak_ptr<common::Observable<std::optional<common::List>>> aCurrentList);

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void OnChange(std::optional<common::Recipe> aElement) override;
	void OnChange(std::optional<common::Week> aElement) override;
	void OnChange(std::optional<common::List> aElement) override;

	// protected:
	PrintCurrentFile() = default;
	PrintCurrentFile(const PrintCurrentFile&) = default;
	PrintCurrentFile(PrintCurrentFile&&) = default;
	PrintCurrentFile& operator=(const PrintCurrentFile&) = default;
	PrintCurrentFile& operator=(PrintCurrentFile&&) = default;

private:
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myCurrentRecipe;
	std::weak_ptr<common::Observable<std::optional<common::Week>>> myCurrentWeek;
	std::weak_ptr<common::Observable<std::optional<common::List>>> myCurrentList;
	std::ostream* myOut = nullptr;

	std::shared_ptr<infas::IFile> myCurrentFile;
};
} // namespace biz
