#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Result.h"

char* copyStr(const char* str, const unsigned& strLength) {
	char* tmp = new char[strLength + 1];
	memcpy(tmp, str, sizeof(char) * strLength);
	tmp[strLength] = 0;

	return tmp;
}

Result* checkMapSpeed(const char* str, const unsigned& strLength) {
	char* tmp = copyStr(str, strLength);

	auto* dict = new std::map<std::string, int>();

	std::map<int, int> a;
	a[2] = 2;

	unsigned startTime = clock(), endTime;

	char* token = strtok(tmp, ",.!?:;-()'[] \t\n\r\"");
	while (token != nullptr) {
		std::string tmpToken = token;

		(*dict)[tmpToken] += 1;

		token = strtok(nullptr, ",.!?:;-()'[] \t\n\r\"");
	}

	endTime = clock();

	delete[] tmp;

	return new Result(dict, Result::Types::MAP, endTime - startTime);
}

Result* checkUnorderedMapSpeed(const char* str, const unsigned& strLength) {
	char* tmp = copyStr(str, strLength);

	std::unordered_map<std::string, int>* dict = new std::unordered_map<std::string, int>();

	unsigned startTime = clock(), endTime;

	char* token = strtok(tmp, ",.!?:;-()'[] \t\n\r\"");
	while (token != nullptr) {
		std::string tmpToken = token;

		(*dict)[tmpToken] += 1;

		token = strtok(nullptr, ",.!?:;-()'[] \t\n\r\"");
	}

	endTime = clock();

	delete[] tmp;

	return new Result(dict, Result::Types::UNMAP, endTime - startTime);
}

Result* checkVectorSpeed(const char* str, const unsigned& strLength) {
	char* tmp = copyStr(str, strLength);

	std::vector<std::pair<std::string, int>> *dict = new std::vector<std::pair<std::string, int>>();

	bool isFoundToken;

	unsigned startTime = clock(), endTime;

	char* token = strtok(tmp, ",.!?:;-()'[] \t\n\r\"");
	while (token != nullptr) {
		isFoundToken = false;

		std::string tmpToken = token;

		for (int i = 0; i < dict->size(); ++i) {
			if ((*dict)[i].first == tmpToken) {
				(*dict)[i].second += 1;
				isFoundToken = true;

				break;
			}
		}

		if (!isFoundToken) dict->push_back(std::make_pair(tmpToken, 1));

		token = strtok(nullptr, ",.!?:;-()'[] \t\n\r\"");
	}

	endTime = clock();

	delete[] tmp;

	return new Result(dict, Result::Types::VECTOR, endTime - startTime);
}

Result* checkListSpeed(const char* str, const unsigned& strLength) {
	char* tmp = copyStr(str, strLength);

	std::list<std::pair<std::string, int>> *dict = new std::list<std::pair<std::string, int>>();

	bool isFoundToken;

	unsigned startTime = clock(), endTime;

	char* token = strtok(tmp, ",.!?:;-()'[] \t\n\r\"");
	while (token != nullptr) {
		isFoundToken = false;

		std::string tmpToken = token;

		for (auto& item : *dict) {
			if (item.first == tmpToken) {
				item.second += 1;
				isFoundToken = true;

				break;
			}
		}

		if (!isFoundToken) dict->push_back(std::make_pair(tmpToken, 1));

		token = strtok(nullptr, ",.!?:;-()'[] \t\n\r\"");
	}

	endTime = clock();

	delete[] tmp;

	return new Result(dict, Result::Types::LIST, endTime - startTime);
}

int main() {
	std::ifstream stream("C:\\Temp\\eng_text.txt", std::ios_base::binary);

	if (stream.is_open()) {
		stream.seekg(0, std::ios::end);
		unsigned length = stream.tellg();
		stream.seekg(0, std::ios::beg);

		char* buffer = new char[length];
		stream.read(buffer, length);

		stream.close();

		auto res1 = checkMapSpeed(buffer, length);
		std::cout << "Map: " << res1->getExecutionTime() << std::endl;
		res1->save("C:\\Temp\\res1.txt");

		delete res1;

		auto res2 = checkUnorderedMapSpeed(buffer, length);
		std::cout << "Unordered map: " << res2->getExecutionTime() << std::endl;
		res2->save("C:\\Temp\\res2.txt");

		delete res2;

		auto res3 = checkVectorSpeed(buffer, length);
		std::cout << "Vector: " << res3->getExecutionTime() << std::endl;
		res3->save("C:\\Temp\\res3.txt");

		delete res3;

		auto res4 = checkListSpeed(buffer, length);
		std::cout << "List: " << res4->getExecutionTime() << std::endl;
		res4->save("C:\\Temp\\res4.txt");

		delete res4;

		delete[] buffer;
	}

	return 0;
}
