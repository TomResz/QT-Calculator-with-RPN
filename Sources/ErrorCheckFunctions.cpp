#include "ErrorCheckFunctions.h"


bool ErrorCheckFunctions::isCharTheFunction(char c) const
{
	if (c >= 'a' and c <= 'z') return 1;
	else return 0;
}


bool ErrorCheckFunctions::isCharTheNumber(char c) const
{
	if ((c >= '0' && c <= '9') || c == '.') return 1;
	else {
		return 0;
	}
}

bool ErrorCheckFunctions::isCharTheOperator(char c) const
{
	return (c == '*' || c == '+' || c == '/' || c == '^' || c == '(' || c == ')' || c == '-');
}


bool ErrorCheckFunctions::unknownSign(char c) const
{
	if (!isCharTheOperator(c) and !isCharTheNumber(c) and !isCharTheFunction(c)) return 1;
	else return 0;
}



bool ErrorCheckFunctions::isStringTheFunction(const std::string& s) const
{
	return s == "cos" || s == "sin" || s == "tg" || s == "ctg" || s == "arcos" || s == "arcsin" || s == "arctg" || s == "arcctg" || s == "sqrt" || s == "arccos";
}


bool ErrorCheckFunctions::isStringTheNumber(const std::string& s) const
{
	auto result = double();
	auto i = std::istringstream(s);
	i >> result;
	return !i.fail() && i.eof();
}


bool ErrorCheckFunctions::isStringTheOperator(const std::string& s) const
{
	return (s == "*" || s == "+" || s == "/" || s == "^" || s == "-");
}