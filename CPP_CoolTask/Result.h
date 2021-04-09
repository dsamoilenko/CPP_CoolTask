#pragma once

#include <fstream>
#include <string>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>

class Result {
public:
	static enum Types { MAP = 1, UNMAP = 2, VECTOR = 3, LIST = 4 };

private:
	void* dict;
	Types type;
	unsigned executionTime;

public:
	Result(void* dict, Types type, unsigned executionTime);

	~Result();

	unsigned getExecutionTime();

	void save(const char* fileName);
};

