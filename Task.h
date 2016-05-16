#pragma once

#include "Common.h"

typedef uint32_t MapperToken;

struct TaskPayload
{
	RawData* InputData;
	size_t InputDataSize;

	RawData* OutputData;
	size_t OutputDataSize;
};

typedef void (*TaskCompletionHandler)(TaskPayload*);

class Task
{
public:
	const char* Name;
	const TaskPayload Payload;
	const MapperToken TargetResultMapper;
	TaskCompletionHandler OnCompleted;

public:
	Task(const char* name, TaskPayload payload, MapperToken mapperToken) : Name(name), Payload(payload), OnCompleted(nullptr), TargetResultMapper(mapperToken)
	{}
};