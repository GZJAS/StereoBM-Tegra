#include "RunnerManager.h"

RunnerManager::~RunnerManager()
{
	this->RunnerThreads.clear();
	this->Runners.clear();
}

RunnerToken RunnerManager::CreateRunner()
{
	Log::Write(LogModule, "Is creating a runner");

	RunnerCounter++;

	ITaskRunner* runner = new HostTaskRunner();
	CHECK_PTR(runner);

	Thread* runnerThread = new Thread(&RunnerManager::StartRunnerPooling, this, runner);
	CHECK_PTR(runnerThread);

	this->Runners[RunnerCounter] = runner;
	this->RunnerThreads[RunnerCounter] = runnerThread;

	return RunnerCounter;
}

void RunnerManager::StartRunnerPooling(ITaskRunner* task) const
{
	task->StartPooling();
}

void RunnerManager::DestroyRunner(const RunnerToken token)
{
	Log::WriteThreadSafe(LogModule, "Is destroying a Runner");

	ITaskRunner* runner = this->Runners[token];

	CHECK_PTR(runner);

	runner->Destroy();

	CHECK_MAP_ERASE(this->Runners.erase(token));
	SAFE_DELETE(runner);

	Thread* thread = this->RunnerThreads[token];
	CHECK_PTR(thread);
	CHECK_MAP_ERASE(this->RunnerThreads.erase(token));

	// NOTE: We must join thread before deleting it!!!
	thread->join();

	SAFE_DELETE(thread);
}

void RunnerManager::PushTaskToRunner(Task* task, const RunnerToken token)
{
	CHECK_PTR(task);

	ITaskRunner* runner = this->Runners[token];
	CHECK_PTR(runner);

	runner->Insert(task);
}

void RunnerManager::PushTaskToRunner(Task* task)
{
	if (this->Runners.size() == 0)
	{
		Log::WriteThreadSafe(LogModule, "Trying to push task to runner, but none runner is created yet!", Log::Severity::Critical);
	}

	const RunnerToken token = 1; // NOTE: Hardcoded one as runner token.

	this->PushTaskToRunner(task, token);
}