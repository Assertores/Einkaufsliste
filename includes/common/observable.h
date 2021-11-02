#pragma once

#include "interface/i_logger.h"
#include "interface/i_observer.h"

#include <memory>
#include <set>
#include <type_traits>

namespace common {
template <typename T>
class Observable {
public:
	Observable() = default;
	explicit Observable(T aValue)
		: myBackingValue(std::move(aValue)){};

	void Subscribe(std::weak_ptr<infas::IObserver<T>> aObserver) { myObservers.emplace(aObserver); }
	void Remove(std::weak_ptr<infas::IObserver<T>> aObserver) { myObservers.erase(aObserver); }
	void Set(T aValue) noexcept;
	[[nodiscard]] const T& Get() const noexcept { return myBackingValue; }

private:
	std::
		set<std::weak_ptr<infas::IObserver<T>>, std::owner_less<std::weak_ptr<infas::IObserver<T>>>>
			myObservers;

	T myBackingValue = T();
};

template <typename T>
void
Observable<T>::Set(T aValue) noexcept {
	if (myBackingValue == aValue) {
		return;
	}
	myBackingValue = aValue;
	std::
		set<std::weak_ptr<infas::IObserver<T>>, std::owner_less<std::weak_ptr<infas::IObserver<T>>>>
			removedObservers;
	for (const auto& it : myObservers) {
		auto ptr = it.lock();
		if (!ptr) {
			removedObservers.insert(it);

			infas::ILogger::Log(
				infas::LogLevel::Debug,
				infas::LogType::Observer,
				"a observer should have been notifyed but did not exist anymore.");
			continue;
		}
		ptr->OnChange(aValue);
	}
	for (const auto& it : removedObservers) {
		myObservers.erase(it);
	}
}
}  // namespace common
