#include "TaskManager.h"
#include "HostTaskRunner.h"

TaskManager* TaskManager::Instance;

TaskManager::TaskManager(RunnerManager* runnerManager, MapperManager* mapperManager)
{
	TaskManager::Instance = this;

	this->Runners = runnerManager;
	this->Mappers = mapperManager;
}

TaskManager::~TaskManager()
{
	this->Tasks.clear();
}

void TaskManager::Stop()
{
	IsStopRequested = true;

	Log::Write(LogModule, "Stop is requested");
}

void TaskManager::StartPooling()
{
	Log::WriteThreadSafe(LogModule, "Is started pooling. Pres ENTER to quit.");

	while (!this->IsStopRequested)
	{
		if (std::cin.get() == '\n')
		{
			this->Stop();
		}
	}
}

void TaskManager::MapTaskResult(Task* task)
{
	CHECK_PTR(task);

	this->Mappers->MapTaskResult(task);
}

const TaskToken TaskManager::InsertTask(Task* task)
{
	Log::Write(LogModule, "Is creating a Task");

	const TaskToken token = this->MakeUniqueTaskToken();

	this->Tasks[token] = task;

	return token;
}

void TaskManager::RunTask(TaskToken token, RunnerToken runnerToken)
{
	Task* task = this->Tasks[token];

	CHECK_PTR(task);

	this->Runners->PushTaskToRunner(task, runnerToken);
}

const TaskToken TaskManager::MakeUniqueTaskToken()
{
	this->TokenCounter++;
	TaskToken token;
	token.Id = this->TokenCounter;

	return token;
}
