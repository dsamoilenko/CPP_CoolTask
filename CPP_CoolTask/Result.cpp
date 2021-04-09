#include "Result.h"

Result::Result(void* dict, Types type, unsigned executionTime) {
	cout << "Constr" << endl;
	this->dict = dict;
	this->type = type;
	this->executionTime = executionTime;
}

Result::~Result() {
	delete this->dict;
}

unsigned Result::getExecutionTime() {
	return this->executionTime;
}

void Result::save(const char* fileName) {
	std::ofstream stream(fileName);

	if (stream.is_open()) {
		switch (this->type) {
			case MAP: {
				auto* tmp = static_cast<std::map<std::string, int>*>(this->dict);
				for (const auto& item : *tmp) {
					stream << item.first << " " << item.second << "\n\r";
				}

				break;
			}
			case UNMAP: {
				auto* tmp = static_cast<std::unordered_map<std::string, int>*>(this->dict);
				for (const auto& item : *tmp) {
					stream << item.first << " " << item.second << "\n\r";
				}

				break;
			}
			case VECTOR: {
				auto* tmp = static_cast<std::vector<std::pair<std::string, int>>*>(this->dict);
				for (const auto& item : *tmp) {
					stream << item.first << " " << item.second << "\n\r";
				}

				break;
			}
			case LIST: {
				auto* tmp = static_cast<std::list<std::pair<std::string, int>>*>(this->dict);
				for (const auto& item : *tmp) {
					stream << item.first << " " << item.second << "\n\r";
				}

				break;
			}
		}

		stream.close();
	}
}
