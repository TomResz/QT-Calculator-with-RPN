#define _USE_MATH_DEFINES
#include "PostfixToResult.h"

PostfixToResult::PostfixToResult() : correctCheck("correct") {}
PostfixToResult::~PostfixToResult() { vec.clear(); }

double PostfixToResult::stringToDouble(const std::string& s)
{
	double number;
	std::istringstream stream(s);
	stream >> number;
	return number;
}

int PostfixToResult::whichOperator(const std::string& s) const
{
	const std::string operators[14] = { "+","-","*","/","sin","cos","tg","ctg","arctg","arcsin","sqrt","arccos","^","arcctg"};
	auto it = std::find_if(std::begin(operators), std::end(operators), [&s](const auto& element) 
	{ 
		return element == s; 
	});
	if (it != std::end(operators)) return std::distance(std::begin(operators), it) + 1;
	else return 0;
}

double PostfixToResult::operation(double b, double a, const std::string& s)
{
	double powerResult;
	switch (whichOperator(s))
	{
	case 1: // addition
		return a + b;
		break;
	case 2: // subtraction
		return b - a;
		break;
	case 3:
		return a * b; // multiplication
		break;
	case 4: // devision
		if (a == 0.0) {
			throw std::string("Divide by zero!");
		}
		else
		{
			return b / a;  
		}
		break;
	case 5:
		return std::sin(a); // sin
		break;
	case 6:
		return std::cos(a); // cos
		break;
	case 7:
		return std::tan(a); // tg
		break;
	case 8:
		if (a == 0.0)
		{
			throw std::string("Invalid number for ctg!");
		}
		else return std::tan(M_PI_2 - a); // ctg
		break;
	case 9: // arctg
		return std::atan(a);
		break;
	case 10: // arcsin
		if (a >= -1.0 && a <= 1.0) {
			return std::asin(a);
		}
		else throw std::string("Invalid number for arcsin function!");
		break;
	case 11: // sqrt
		if (a < 0.0) throw std::string("The number under the square root is negative!");
		else 
		{
			return std::sqrt(a);
		}
		break;
	case 12: // arccos
		if (a <= 1.0 && a >= -1.0) {
			return std::acos(a);
		}
		else {
			throw std::string("Invalid number for arccos function!");
		}
		break;
	case 13: // power
		powerResult = std::pow(b, a);
		if (isStringTheNumber(std::to_string(powerResult))) {
			return std::pow(b, a);
		}
		else throw std::string("Incorrect parameter for power function!");
		break;
	case 14: // arcctg
		if (a != 0.0) {
			return std::atan(1.0 / a);
		}
		else // arcctg(0)= PI/2
		{
			return M_PI_2;
		}
		break;
	default:
		break;
	}
	return -1;
}

double PostfixToResult::toResult(const std::vector<std::string>& vec) // finalny algorytm konwersji ONP do wyniku
{
	this->vec = vec;
	std::stack<double> stack;
	double a, b;
	try 
	{
		for (const auto& el : vec)
		{
			if (isStringTheNumber(el))
			{
				stack.push(stringToDouble(el));
			}
			else
			{
				if (isStringTheOperator(el))
				{
					a = stack.top();
					stack.pop();
					if (stack.size() >= 1) {
						b = stack.top();
						stack.pop();
						stack.push(operation(b, a, el));
					}
					else
					{
						stack.push(operation(0, a, el));
					}
				}
				else if (isStringTheFunction(el))
				{
					a = stack.top();
					stack.pop();
					stack.push(operation(0, a, el));

				}

			}
		}
		if (stack.size() == 1) {
			return stack.top();
		}
		else throw std::string("Syntax error!");
	}
	catch(std::string& correctCheck)
	{
		this->correctCheck = correctCheck;
		return -1;
	}
}

std::string PostfixToResult::resultToString(double a) const
{

	if (correctCheck == "correct")
	{
		std::ostringstream output;
		output << std::setprecision(10) << a;
		return output.str();
	}
	else
	{
		return correctCheck;
	}
}

void PostfixToResult::clear()
{
	vec.clear();
	correctCheck = "correct";
}
