#pragma once

#include "Common.h"
#include "ITaskRunner.h"
#include "HostTaskRunner.h"

typedef uint32_t RunnerToken;
typedef std::map<RunnerToken, ITaskRunner*> RunnersMap;
typedef std::map<RunnerToken, Thread*> RunnerThreadsMap;

class RunnerManager
{
private:
	const char* LogModule = CLASS_NAME;

	RunnerToken RunnerCounter = 0;
	RunnersMap Runners;
	RunnerThreadsMap RunnerThreads;

public:
	~RunnerManager();

	RunnerToken CreateRunner();

	void StartRunnerPooling(ITaskRunner* task) const;

	void DestroyRunner(const RunnerToken token);

	void PushTaskToRunner(Task* task, const RunnerToken token);
	void PushTaskToRunner(Task* task);
};