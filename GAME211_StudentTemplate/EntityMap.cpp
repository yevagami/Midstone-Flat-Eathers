#include "EntityMap.h"


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

bool EntityMap::saveEntityMapToFile(const char* fileDirectory) {
	ofstream outputFile(fileDirectory);
	if (outputFile.fail()) {
		return false;
	}

	//	for each entity in the map, add it to the file with the given formatting ("*first* : *second*")
	for (const auto& pair : entityMap) {
		outputFile << pair.first << " : " << pair.second << std::endl;
	}

	outputFile.close();
	return true;

}

bool EntityMap::loadEntityMapFromFile(const char* fileDirectory) {
	ifstream inputFile(fileDirectory);
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

bool EntityMap::hasEntity(const std::string& entityName) {
	return entityMap.find(entityName) != entityMap.end();
}

bool EntityMap::entityHasData(const std::string& entityName, const std::string& searchData) {
	auto it = entityMap.find(entityName);
	if (it != entityMap.end()) {
		return it->second == searchData;
	}
	return false;
}

void EntityMap::clearAllEntities() {
	entityMap.clear(); }

bool EntityMap::clearEntity(const std::string& entityName) {
	auto it = entityMap.find(entityName);
	if (it != entityMap.end()) {
		entityMap.erase(it);
		return true;
	}
	return false;
}

int EntityMap::getEntityCount() {
	return static_cast<int>(entityMap.size());
}

bool EntityMap::updateEntityData(const std::string& entityName, const std::string newEntityData) {
	auto it = entityMap.find(entityName);
	if (it != entityMap.end()) {
		it->second = newEntityData;
		return true;
	}
	return false;
}

std::vector<std::string> EntityMap::findEntitiesByData(std::string searchData) {
		//	by substring method, for more exact do the other one
	std::vector<std::string> matchingEntities;
	for (const auto& pair : entityMap) {
		if (pair.second.find(searchData) != std::string::npos) {
			matchingEntities.push_back(pair.first);
		}
	}
	return matchingEntities;
}


