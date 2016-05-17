#pragma once

#include "Common.h"
#include <ctime>

typedef std::clock_t Clock;

struct StopwatchResult
{
	Clock TotalTicks;
	double TotalSeconds;
};

class Stopwatch
{
private:
	const char* LogModule = CLASS_NAME;
	Clock StartTime;
	Clock EndTime;
	bool IsTicking : 1;

public:
	Stopwatch()
	{
		this->IsTicking = false;
	}

	void Start()
	{
		if (this->IsTicking)
		{
			Log::WriteThreadSafe(this->LogModule, "Starting already started stopwatch", Log::Severity::Warning);
		}

		this->IsTicking = true;
		this->StartTime = std::clock();
	}

	void Stop()
	{
		if (!this->IsTicking)
		{
			Log::WriteThreadSafe(this->LogModule, "Stopping not started stopwatch", Log::Severity::Warning);
		}

		this->IsTicking = false;
		this->EndTime = std::clock();
	}

	void Reset()
	{
		this->StartTime = 0;
		this->EndTime = 0;
		this->IsTicking = false;
	}

	StopwatchResult GetResult()
	{
		Clock total = this->EndTime - this->StartTime;

		return { total, double(total) / CLOCKS_PER_SEC };
	}
};