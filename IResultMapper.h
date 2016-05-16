#pragma once

#include "IPoolable.h"

class Task;

class IResultMapper : public IPoolable<Task*>
{
};