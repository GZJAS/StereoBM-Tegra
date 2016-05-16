#include "DefaultResultsMapper.h"

void DefaultResultsMapper::StartPooling()
{
	this->IsRunning = true;

	while (IsRunning)
	{
		if (this->Queue.size() > 0)
		{
			Task* task = this->Queue.pop();

			this->MapResult(task);
		}
	}
}

void DefaultResultsMapper::MapResult(Task* task)
{
	TaskPayload payload = task->Payload;

	CHECK_PTR(task->OnCompleted);

	task->OnCompleted(&payload);
}
