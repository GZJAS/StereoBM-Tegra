#pragma once

#include "Common.h"

template<typename T>
class IPoolable
{
protected:
	AtomicQueue<T> Queue;
	volatile bool IsRunning : 1;

public:
	IPoolable() { this->IsRunning = false; }
	virtual ~IPoolable() {};

	void Insert(T item) { this->Queue.push(item); }
	virtual void StartPooling() { this->IsRunning = true; };
	virtual void Destroy() { this->IsRunning = false; };
};