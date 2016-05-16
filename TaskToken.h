#pragma once

#include <stdint.h>

class TaskToken
{
public:
	uint16_t Id;

	inline const bool operator < (const TaskToken &right) const
	{
		return this->Id < right.Id;
	}
};