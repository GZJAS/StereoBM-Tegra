#pragma once

#include "Common.h"
#include "IPoolable.h"
#include "Task.h"

class DefaultResultsMapper : public IPoolable<Task*>
{
private:
	const char* LogModule = CLASS_NAME;

public:
	void StartPooling() override;

	void MapResult(Task* task);
};