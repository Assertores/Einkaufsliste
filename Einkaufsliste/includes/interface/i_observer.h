#pragma once

#include <memory>
#include <set>

namespace interface {
template <typename T>
class IObserver
{
public:
	virtual void OnChange(T element) = 0;
};
}; // namespace interface
