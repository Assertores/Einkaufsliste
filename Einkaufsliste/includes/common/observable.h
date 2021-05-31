#pragma once

#include <memory>
#include <set>

#include "interface/i_logger.h"
#include "interface/i_observer.h"

namespace common {
template <typename T>
class Observable
{
public:
	void Subscribe(std::weak_ptr<interface::IObserver<T>> aObserver)
	{
		myObservers.emplace(std::move(aObserver));
	}
	void Remove(std::weak_ptr<interface::IObserver<T>> aObserver) { myObservers.erase(aObserver); }
	void Notify(T aValue);

private:
	std::set<
		std::weak_ptr<interface::IObserver<T>>,
		std::owner_less<std::weak_ptr<interface::IObserver<T>>>>
		myObservers;
};

template <typename T>
void
Observable<T>::Notify(T aValue)
{
	for (const auto& it : myObservers)
	{
		auto ptr = it.lock();
		if (!ptr)
		{
			interface::ILogger::Log(
				interface::LogLevel::Debug,
				interface::LogType::Observer,
				"a observer should have been notifyed but did not exist anymore.");
			continue;
		}
		ptr->OnChange(aValue);
	}
}
} // namespace common