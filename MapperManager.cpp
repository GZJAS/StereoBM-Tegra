#include "MapperManager.h"

MapperManager::~MapperManager()
{
	this->MapperThreads.clear();
	this->Mappers.clear();
}

MapperToken MapperManager::CreateResultMapper()
{
	Log::Write(LogModule, "Is creating a result mapper");

	ResultMapperCounter++;

	IResultMapper* mapper = new DefaultResultsMapper();
	CHECK_PTR(mapper);

	Thread* mapperThread = new Thread(&MapperManager::StartMapperPooling, this, mapper);
	CHECK_PTR(mapperThread);

	this->Mappers[ResultMapperCounter] = mapper;
	this->MapperThreads[ResultMapperCounter] = mapperThread;

	return ResultMapperCounter;
}

void MapperManager::StartMapperPooling(IResultMapper* mapper) const
{
	mapper->StartPooling();
}

void MapperManager::MapTaskResult(Task* task)
{
	IResultMapper* mapper = this->Mappers[task->TargetResultMapper];
	CHECK_PTR(mapper);

	mapper->Insert(task);
}

void MapperManager::DestroyMapper(const MapperToken token)
{
	// NOTE: This method is nearly the same as in RunnerManager and etc.
	Log::WriteThreadSafe(LogModule, "Is destroying a Mapper");

	IResultMapper* mapper = this->Mappers[token];

	CHECK_PTR(mapper);
	CHECK_MAP_ERASE(this->Mappers.erase(token));
	SAFE_DELETE(mapper);

	Thread* thread = this->MapperThreads[token];
	CHECK_PTR(thread);
	CHECK_MAP_ERASE(this->MapperThreads.erase(token));

	thread->join();

	SAFE_DELETE(thread);
}
