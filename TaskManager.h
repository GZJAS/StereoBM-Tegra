#pragma once

#include "Common.h"
#include "TaskToken.h"
#include "Task.h"

#include "RunnerManager.h"
#include "MapperManager.h"

typedef std::map<const TaskToken, Task*> TasksMap;

class TaskManager
{
public:
	static TaskManager* Instance;

private:
	MapperManager* Mappers;
	RunnerManager* Runners;

	TasksMap Tasks;

	uint16_t TokenCounter = 0;

	bool IsStopRequested = false;
	const char* LogModule = CLASS_NAME;

public:
	TaskManager(RunnerManager* runnerManager, MapperManager* mapperManager);
	~TaskManager();

	void StartPooling();

	void Stop();

	void MapTaskResult(Task* task);

	const TaskToken InsertTask(Task* task);

	void RunTask(TaskToken token, RunnerToken runnerToken);

private:
	const TaskToken MakeUniqueTaskToken();
};
