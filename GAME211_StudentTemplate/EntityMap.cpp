#include "EntityMap.h"
#include <fstream>


void EntityMap::insertEntity(const std::string& entityName, const std::string& entityData) {
	entityMap[entityName] = entityData;
}

std::string EntityMap::getEntityData(const std::string& entityName) {
	auto it = entityMap.find(entityName);

	if (it != entityMap.end()) {
		return it->second;
	}
	return "";
}

bool EntityMap::removeEntity(const std::string& entityName) {
	auto it = entityMap.find(entityName);

	if (it != entityMap.end()) {
		entityMap.erase(it);
		return true;
	}
	return false;
}

bool EntityMap::saveEntityMapToFile(const char* fileDirectory_) const
{
	ofstream outputFile(fileDirectory_);
	if (outputFile.fail()) {
		return false;
	}

	//	for each entity in the map, add it to the file with the given formatting ("*first* : *second*")
	for (const auto& [first, second] : entityMap) {
		outputFile << first << " : " << second << std::endl;
	}

	outputFile.close();
	return true;

}

bool EntityMap::loadEntityMapFromFile(const char* fileDirectory_) {
	ifstream inputFile(fileDirectory_);
	if (inputFile.fail()) {
		return false;
	}

	entityMap.clear();

	//might not work, idk (how reassuring!)
	std::string line;
	while (std::getline(inputFile, line)) {
		size_t pos = line.find(" : ");
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 3); //maybe 2
			entityMap[key] = value;
		}
	}

	inputFile.close();
	return true;

}

bool EntityMap::hasEntity(const std::string& entityName_) {
	return entityMap.find(entityName_) != entityMap.end();
}

bool EntityMap::entityHasData(const std::string& entityName_, const std::string& searchData_) {
	auto it = entityMap.find(entityName_);
	if (it != entityMap.end()) {
		return it->second == searchData_;
	}
	return false;
}

void EntityMap::clearAllEntities() {
	entityMap.clear(); }

bool EntityMap::clearEntity(const std::string& entityName_) {
	if (const auto it = entityMap.find(entityName_); it != entityMap.end()) {
		entityMap.erase(it);
		return true;
	}

	return false;
}

int EntityMap::getEntityCount() const
{
	return static_cast<int>(entityMap.size());
}

bool EntityMap::updateEntityData(const std::string& entityName_, const std::string& newEntityData_) {
	if (const auto it = entityMap.find(entityName_); it != entityMap.end()) {
		it->second = newEntityData_;
		return true;
	}
	return false;
}

std::vector<std::string> EntityMap::findEntitiesByData(const std::string& searchData_) const
{
		//	by substring method, for more exact do the other one
	std::vector<std::string> matchingEntities;
	for (const auto& [first, second] : entityMap) {
		if (second.find(searchData_) != std::string::npos) {
			matchingEntities.push_back(first);
		}
	}
	return matchingEntities;
}


