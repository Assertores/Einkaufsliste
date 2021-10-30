#pragma once

#include <functional>

namespace interface {
template <typename T>
class IObserver
{
public:
	virtual void OnChange(T aElement) = 0;
};

namespace fake {
template <typename T>
class Observer : public IObserver<T>
{
public:
	std::function<void(T)> onChange = [this](auto /*unused*/) {
		onChangeCount++;
	};

	void OnChange(T aElement) override { onChange(aElement); }

	int onChangeCount = 0;
};
} // namespace fake
}; // namespace interface
