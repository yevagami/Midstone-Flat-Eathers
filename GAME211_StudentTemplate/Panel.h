#pragma once
#include <string>
#include <vector>

class Body;

namespace MATH {
	struct Vec2;
	struct Vec3;
}

enum class VariableType {
    INT,
    FLOAT,
    DOUBLE,
    STRING,
    CHAR,
    VEC3,
    VEC2,
    BODY,
};

//  brainstorming gone off track <3

class Panel {
public:
	class Window* windowPtr;

    Panel(std::string& panelName_) : name(panelName_)
	{}

    void addVariable(const std::string& variableName, VariableType variableType);

    void setValue(const std::string& variableName, int value);
    void setValue(const std::string& variableName, float value);
    void setValue(const std::string& variableName, double value);
    void setValue(const std::string& variableName, const std::string& value);
    void setValue(const std::string& variableName, char value);
    void setValue(const std::string& variableName, const MATH::Vec3& value);
    void setValue(const std::string& variableName, const MATH::Vec2& value);
    void setValue(const std::string& variableName, const Body& value);

    void printValues();

protected:
    std::string name;

    std::vector<void*> variableValues;
};