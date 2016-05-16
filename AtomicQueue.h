#pragma once

#include "Common.h"

template <typename T>
class AtomicQueue
{
private:
	uint32_t Size = 0;

public:
	T pop()
	{
		std::unique_lock<std::mutex> mlock(MainMutex);

		while (MainQueue.empty())
		{
			Condition.wait(mlock);
		}

		auto item = MainQueue.front();
		MainQueue.pop();

		Size--;

		return item;
	}

	void pop(T& item)
	{
		std::unique_lock<std::mutex> mlock(MainMutex);

		while (MainQueue.empty())
		{
			Condition.wait(mlock);
		}

		item = MainQueue.front();
		MainQueue.pop();

		Size--;
	}

	void push(const T& item)
	{
		std::unique_lock<std::mutex> mlock(MainMutex);

		MainQueue.push(item);
		mlock.unlock();
		Condition.notify_one();

		Size++;
	}

	void push(T&& item)
	{
		std::unique_lock<std::mutex> mlock(MainMutex);

		MainQueue.push(std::move(item));
		mlock.unlock();
		Condition.notify_one();

		Size++;
	}

	size_t size()
	{
		return this->Size;
	}

private:
	std::queue<T> MainQueue;
	Mutex MainMutex;
	std::condition_variable Condition;
};