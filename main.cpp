#include "TaskManager.h"
#include "Task.h"
#include "RunnerManager.h"
#include "MapperManager.h"
#include "Stopwatch.h"

int main()
{
	RunnerManager runnerManager;
	MapperManager mapperManager;
	TaskManager taskManager(&runnerManager, &mapperManager);

	RunnerToken mainRunnerToken = runnerManager.CreateRunner();
	MapperToken mapperToken = mapperManager.CreateResultMapper();

	// Test task
	const TaskPayload data = { 0 };
	Task task("Test task", data, mapperToken);

	task.OnCompleted = [](TaskPayload* task)
	{
		Log::WriteThreadSafe("main", "Task is completed, mapping result");
	};

	const TaskToken token = taskManager.InsertTask(&task);
	taskManager.RunTask(token, mainRunnerToken);

	// Endless loop of task manager
	taskManager.StartPooling();

	// Delete all
	runnerManager.DestroyRunner(mainRunnerToken);
	mapperManager.DestroyMapper(mapperToken);

	return 0;
}