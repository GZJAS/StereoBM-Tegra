#pragma once

#include "Common.h"

template<typename T>
class IPoolable
{
protected:
	AtomicQueue<T> Queue;
	volatile bool IsRunning = false;

public:
	void Insert(T item) { this->Queue.push(item); }
	virtual void StartPooling() {};
	virtual void Destroy() {};
	virtual ~IPoolable() {};
};