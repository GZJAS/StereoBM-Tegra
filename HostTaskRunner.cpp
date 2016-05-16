#include "HostTaskRunner.h"
#include "TaskManager.h"

void HostTaskRunner::StartPooling()
{
	this->IsRunning = true;

	while (IsRunning)
	{
		if (this->Queue.size() > 0)
		{
			Task* task = this->Queue.pop();

			this->RunTask(task);
			continue;
		}
	}
}

void HostTaskRunner::RunTask(Task* task)
{
	// TODO: Run the task on CUDA kernel
	//       When task is done, pass it to result mapper

	TaskManager::Instance->MapTaskResult(task);
}

void HostTaskRunner::Destroy()
{
	this->IsRunning = false;
}

HostTaskRunner::~HostTaskRunner()
{

}
