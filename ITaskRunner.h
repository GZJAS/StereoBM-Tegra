#pragma once

#include "IPoolable.h"

class Task;

class ITaskRunner : public IPoolable<Task*>
{
};