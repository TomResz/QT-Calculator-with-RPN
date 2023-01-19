#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class ErrorCheckFunctions
{
public:
	virtual std::string resultToString(double a) const = 0;
protected:
	bool isStringTheOperator(const std::string& s) const;
	bool isStringTheNumber(const std::string& s) const;
	bool isStringTheFunction(const std::string& s) const;
	bool isCharTheNumber(char c) const;
	bool unknownSign(char c) const;
	bool isCharTheOperator(char c) const;
	bool isCharTheFunction(char c) const;
};
