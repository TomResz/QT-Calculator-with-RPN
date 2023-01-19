#define _USE_MATH_DEFINES
#include "RPN.h"

RPN::~RPN() {
	clear();
}

void RPN::setter(const std::string& expression)
{
	setExpression(expression);
	tokenization();
}

void RPN::setExpression(const std::string& expression)
{
	this->expression = expression;
}

void RPN::tokenization() // podzial stringa na wektor pojedynczych elementow
{
	std::string liczba = "";
	int i = 0;
	while (i != expression.size())
	{
		if (isCharTheNumber(expression[i]))
		{
			while (isCharTheNumber(expression[i]))
			{
				liczba += expression[i];
				i++;
			}
			tokenArray.push_back(liczba);
			liczba = "";
		}
		else if (expression[i] == ' ')
		{
			i++;
		}
		else if (isCharTheOperator(expression[i]))
		{
			liczba += expression[i];
			tokenArray.push_back(liczba);
			liczba = "";
			i++;
		}
		else if (isCharTheFunction(expression[i]))
		{
			while (isCharTheFunction(expression[i]))
			{
				liczba += expression[i];
				i++;
			}
			tokenArray.push_back(liczba);
			liczba = "";
		}
		else if (unknownSign(expression[i]))
		{
			liczba += expression[i];
			i++;
			tokenArray.push_back(liczba);
			liczba = "";
		}

	}

	for (int i = 0; i < tokenArray.size(); ++i) 
	{
		if (i == 0 && tokenArray[i] == "-" && isStringTheNumber(tokenArray[i + 1]) && tokenArray.size() >= 2)
		{
			tokenArray[i + 1] = "-" + tokenArray[i + 1];
			tokenArray.erase(tokenArray.begin());
		}
		else if (tokenArray[i] == "(" && tokenArray[i + 1] == "-" && isStringTheNumber(tokenArray[i + 2]) && i < tokenArray.size() - 3)
		{
			tokenArray[i + 2] = "-" + tokenArray[i + 2];
			tokenArray.erase(tokenArray.begin() + i + 1);
		}
	}
}

void RPN::clear()
{
	tokenArray.clear();
	expression.clear();
}



std::vector<std::string> RPN::infixToPostfix()
{
	std::vector<std::string> postfix; 
	std::stack<std::string> stack;
	stack.push("(");
	tokenArray.push_back(")");
	postfix.reserve(tokenArray.size()); 

	std::map<std::string, int> mapOfOperators = 
	{
		{"+",1},
		{"-",1},
		{"*",2},
		{"^",3},
		{"/",2},
		{"(",0},
		{")",1},
		{"cos",4},
		{"sin",4},
		{"tg",4},
		{"ctg",4},
		{"arccos",4},
		{"arcsin",4},
		{"arctg",4},
		{"arcctg",4},
		{"sqrt",4}
	};

	for (const auto& token : tokenArray)
	{
		if (mapOfOperators.find(token) == mapOfOperators.end())
		{
			postfix.push_back(token);
		}
		else if (token == "(")
		{
			stack.push(token);
		}
		else if (token == ")")
		{
			while (stack.top() != "(")
			{
				postfix.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else
		{
			while (stack.size() > 0 && mapOfOperators[token] <= mapOfOperators[stack.top()])
			{
				postfix.push_back(stack.top());
				stack.pop();
			}
			stack.push(token);
		}
	}
	return postfix;
}

std::string RPN::resultToString(double a) const
{
	int bracketsCorrect = 0;
	try
	{
		if (isStringTheOperator(tokenArray[0])  )
		{
			throw std::string("Operator at the beginning of the expression!");
		}
		else if (isStringTheOperator(tokenArray[tokenArray.size() - 1]))
		{
			throw std::string("Operator at the end of the expression!");
		}

		for (int i = 0; i < tokenArray.size(); ++i)
		{

			if (tokenArray[i] == "(")
			{
				bracketsCorrect++;
				if (i > 0 && isStringTheNumber(tokenArray[i-1]))
				{
					throw std::string("Number before ( !");
				}
				int k = 0;
				for (int j = i+1; j < tokenArray.size(); ++j)
				{

					if (isStringTheNumber(tokenArray[j])) {
						k++;
					}
					else if (tokenArray[j] == ")")
					{
						if (k == 0)  throw std::string("Syntax error!");
					}
				}

				if (tokenArray[i] == "(" && isStringTheOperator(tokenArray[i + 1]) && i < tokenArray.size() - 2)
				{
					throw std::string("Operator after ( !");
				}
			}
			else if (tokenArray[i] == ")")
			{
				if (bracketsCorrect == 0) {
					throw std::string("Syntax error !");
				}
				bracketsCorrect--;
	
			}
			else if (isStringTheOperator(tokenArray[i]) && isStringTheOperator(tokenArray[i + 1]) && i < tokenArray.size() - 2)
			{
				throw std::string("Two operators side by side!");
			}
			else if (!isStringTheNumber(tokenArray[i]) && !isStringTheFunction(tokenArray[i]) && !isStringTheOperator(tokenArray[i]) && tokenArray[i] != "(" && tokenArray[i] != ")")
			{
				throw std::string("Invalid number!");
			}
			else if (tokenArray[i] == ")" && isStringTheOperator(tokenArray[i - 1]) && i > 0)
			{
				throw std::string("Operator before )!");
			}
			else if (isStringTheNumber(tokenArray[i]) && i > 0 && tokenArray[i-1]==")")
			{
				throw std::string("Number after )!");
			}
		}

		if (bracketsCorrect != 0)
		{
			throw std::string("Syntax error!");
		}
	}
	catch (std::string& exceptionMessage)
	{
		return exceptionMessage;
	}
	return "correct";
}