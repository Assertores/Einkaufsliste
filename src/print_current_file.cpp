#include "biz/print_current_file.h"

namespace biz {
void
PrintCurrentFile::SetReferences(
	std::ostream* aOut,
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe,
	std::weak_ptr<common::Observable<std::optional<common::Week>>> aCurrentWeek,
	std::weak_ptr<common::Observable<std::optional<common::List>>> aCurrentList) {
	myOut = aOut;
	myCurrentRecipe = std::move(aCurrentRecipe);
	myCurrentWeek = std::move(aCurrentWeek);
	myCurrentList = std::move(aCurrentList);

	auto recipe = myCurrentRecipe.lock();
	if (!recipe) {
		return;
	}
	recipe->Subscribe(weak_from_this());

	auto week = myCurrentWeek.lock();
	if (!week) {
		return;
	}
	week->Subscribe(weak_from_this());

	auto list = myCurrentList.lock();
	if (!list) {
		return;
	}
	list->Subscribe(weak_from_this());
};

PrintCurrentFile::~PrintCurrentFile() {
	auto recipe = myCurrentRecipe.lock();
	if (recipe) {
		recipe->Remove(weak_from_this());
	}
	auto week = myCurrentWeek.lock();
	if (week) {
		week->Remove(weak_from_this());
	}
	auto list = myCurrentList.lock();
	if (list) {
		list->Remove(weak_from_this());
	}
}

std::unique_ptr<infas::ICommandMemento>
PrintCurrentFile::Execute() {
	if (!myCurrentFile) {
		*myOut << "no file to print\n";
		return nullptr;
	}
	*myOut << myCurrentFile->Print();
	return nullptr;
}

void
PrintCurrentFile::OnChange(std::optional<common::Recipe> aElement) {
	if (!aElement.has_value()) {
		return;
	}
	myCurrentFile = std::make_shared<common::Recipe>(std::move(aElement.value()));
}

void
PrintCurrentFile::OnChange(std::optional<common::Week> aElement) {
	if (!aElement.has_value()) {
		return;
	}
	myCurrentFile = std::make_shared<common::Week>(std::move(aElement.value()));
}

void
PrintCurrentFile::OnChange(std::optional<common::List> aElement) {
	if (!aElement.has_value()) {
		return;
	}
	myCurrentFile = std::make_shared<common::List>(std::move(aElement.value()));
}
} // namespace biz
