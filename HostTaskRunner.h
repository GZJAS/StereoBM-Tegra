#pragma once

#include "Common.h"
#include "ITaskRunner.h"
#include "Task.h"

class HostTaskRunner : public ITaskRunner
{
private:
	const char* LogModule = CLASS_NAME;

public:
	void StartPooling() override;

	void RunTask(Task* task);

	void Destroy() override;

	virtual ~HostTaskRunner();
};