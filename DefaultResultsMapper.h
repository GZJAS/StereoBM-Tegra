#pragma once

#include "Common.h"
#include "Task.h"
#include "IResultMapper.h"

class DefaultResultsMapper : public IResultMapper
{
private:
	const char* LogModule = CLASS_NAME;

public:
	void StartPooling() override;

	void Destroy() override;

	void MapResult(Task* task);
};