#pragma once

#include <memory>

#include "common/observable.h"
#include "common/recipe.h"

namespace interface {
class IHub
{
public:
	common::Observable<common::Recipe> currentRecipe;
};
}; // namespace interface
