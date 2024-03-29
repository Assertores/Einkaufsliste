#include "common/observable.h"
#include "interface/i_observer.h"

#include <gtest/gtest.h>

TEST(Observer, observer_object_gets_notifyed) // NOLINT
{
	auto observer = std::make_shared<infas::fake::Observer<int>>();
	common::Observable<int> subject;

	subject.Subscribe(observer);

	subject.Set(2);

	EXPECT_EQ(observer->onChangeCount, 1);
}

TEST(Observer, observer_is_pased_the_correct_element) // NOLINT
{
	auto observer = std::make_shared<infas::fake::Observer<int>>();
	int number = 0;
	observer->onChange = [&](auto aElement) { number = aElement; };
	common::Observable<int> subject;

	subject.Subscribe(observer);

	subject.Set(2);

	EXPECT_EQ(number, 2);
}

TEST(Observer, observer_is_pased_a_copy) // NOLINT
{
	auto observer = std::make_shared<infas::fake::Observer<int>>();
	int* number = nullptr;
	observer->onChange = [&](auto aElement) { number = &aElement; };
	common::Observable<int> subject;

	subject.Subscribe(observer);

	int realNumber = 2;
	subject.Set(realNumber);

	EXPECT_NE(&realNumber, number);
}

TEST(Observer, notify_empty_observable_does_not_crash) // NOLINT
{
	common::Observable<int> subject;
	EXPECT_NO_THROW(subject.Set(2)); // NOLINT
}

TEST(Observer, unsubscribed_observer_is_not_called) // NOLINT
{
	auto observer = std::make_shared<infas::fake::Observer<int>>();
	common::Observable<int> subject;

	subject.Subscribe(observer);
	subject.Remove(observer);

	subject.Set(2);

	EXPECT_EQ(observer->onChangeCount, 0);
}
