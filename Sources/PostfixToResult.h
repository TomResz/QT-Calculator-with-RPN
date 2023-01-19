#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>
#include <cmath>
#include <iomanip>
#include "ErrorCheckFunctions.h"

class PostfixToResult : public ErrorCheckFunctions
{
	std::vector<std::string> vec;
	double stringToDouble(const std::string& s);
	double operation(double b, double a, const std::string& s);
	int whichOperator(const std::string& s) const;
	std::string correctCheck;


public:
	PostfixToResult();
	~PostfixToResult();
	void clear();
	double toResult(const std::vector<std::string>& vec);
	std::string resultToString(double a) const override;
};