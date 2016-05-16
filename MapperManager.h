#pragma once

#include "Common.h"
#include "DefaultResultsMapper.h"

typedef DefaultResultsMapper IResultMapper; // TODO: Hack, create interface for this
typedef uint32_t MapperToken;

typedef std::map<MapperToken, IResultMapper*> ResultMappersMap;
typedef std::map<MapperToken, Thread*> ResultMapperThreadsMap;

class MapperManager
{
private:
	const char* LogModule = CLASS_NAME;
	ResultMappersMap Mappers;
	ResultMapperThreadsMap MapperThreads;

	MapperToken ResultMapperCounter = 0;

public:
	~MapperManager();

	MapperToken CreateResultMapper();
	
	void MapTaskResult(Task* task);

	void DestroyMapper(const MapperToken token);

private:
	void StartMapperPooling(IResultMapper* mapper) const;
};