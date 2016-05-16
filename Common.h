#pragma once

#ifndef __COMMON_H
#define __COMMON_H

#if _WIN32
#include <windows.h>

#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>

#define SLEEP(ms) usleep(ms * 1000)
#endif

#include <iostream>
#include <thread>
#include <map>
#include <atomic>
#include <stdint.h>
#include <queue>
#include <mutex>
#include <condition_variable>

typedef std::thread Thread;
typedef float RawData;
typedef std::atomic<bool> AtomicBool;
typedef std::mutex Mutex;

#include "AtomicQueue.h"

#define IS_DEBUG 1

#include "Log.h"

#if IS_DEBUG
#if _WIN32
#define BREAK_APP DebugBreak()
#else
#define BREAK_APP 
#endif
#endif

#if IS_DEBUG
#define CHECK_MAP_ERASE(X) if((X) != 1) { Log::Write("CheckMapErase", "Erase not returned 1", Log::Severity::Critical); BREAK_APP; exit(-1); } 
#define CHECK_PTR(X) if( (X) == 0 ) { Log::Write("CheckPtr", "Pointer is invalid", Log::Severity::Critical); BREAK_APP; exit(-1); }
#else
#define CHECK_MAP_ERASE(X) 
#define CHECK_PTR(X) 
#endif

#define CLASS_NAME typeid(*this).name()
#define SAFE_DELETE(X) delete (X); (X) = nullptr;

#endif