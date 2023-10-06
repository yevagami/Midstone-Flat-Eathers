#pragma once
#include "FileManager.h"
#include <unordered_map>

/// <summary>
/// Entity Maps Class
/// 
/// Entity Maps are unordered_maps (glorified lists) with:
	/// a key (thing 1), and
	/// a value (thing 2). looks like this:
		/// :::
		///	 unordered_map <type, type> unordered_mapName;
		///	 map <type,type> mapName;
		///	 std::unordered_map<std::string, std::string> string_stringMap;
		/// :::
/// wow thats scary...
/// dw, this class will do the scary work with them. just think of them like this:
/// Mock Entity Map (visualized):
/// 
///			 a map of animals and what i hate ab them
/// :::
///		{Cow : they smell, didn't friend me back on discord, touches grass daily },
///		{Cat : nothing. I hate nothing. }
///		{Worms : no i wouldnt love u if u were a worm, slimey, worm-like }
///		{Dragons : aren't real...}
/// :::
/// its a key, and a value (or multiple in some cases)
/// 
/// </summary>

class EntityMap : private FileManager {
public:
	//	return a string containing the entity data for the given entity
	std::string getEntityData(const std::string& entityName);
	//	inserts the given entity into the map
	void insertEntity(const std::string& entityName, const std::string& entityData);
	//	removes the given entity from the map
	bool removeEntity(const std::string& entityName);

	//	saves the map to a provided file
	bool saveEntityMapToFile(const char* fileDirectory_) const;
	//	loads the map from a provided file
	bool loadEntityMapFromFile(const char* fileDirectory_);


	//	TO DO
	bool hasEntity(const std::string& entityName_);
	bool entityHasData(const std::string& entityName_, const std::string& searchData_);

	void clearAllEntities();
	bool clearEntity(const std::string& entityName_);
	int getEntityCount() const;
	bool updateEntityData(const std::string& entityName_, const std::string& newEntityData_);
	
	std::vector<std::string> findEntitiesByData(const std::string& searchData_) const;

public:
	std::unordered_map<std::string, std::string> getEntityMap() { return entityMap; }

protected:
	std::unordered_map <std::string, std::string> entityMap;		//	frick getters and setters. they're ugly. this variable is special.

};

