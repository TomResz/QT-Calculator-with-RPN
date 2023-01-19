#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include "ErrorCheckFunctions.h"

class RPN : public ErrorCheckFunctions 
{

public:
	~RPN();
	void clear();
	void setter(const std::string& expression);
	std::vector<std::string> infixToPostfix();
	std::string resultToString(double a) const override;
private:
	std::vector<std::string> postfixVec;
	std::string expression;
	std::vector<std::string> tokenArray;
	void setExpression(const std::string& expression);
	void tokenization();
};