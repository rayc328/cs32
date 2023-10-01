#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

//helper functions
bool isValidInfix(string infix); //check if infix string is valid 
int operatorPrecedence(char op); //establishes operator precedence
bool evalOperand(char operand); //converts 'T' and 'F' to booleans

int evaluate(string infix, string& postfix, bool& result)
{
	if (isValidInfix(infix) == false)
		return 1; 

	//infix to postfix conversion 

	postfix = "";
	stack <char> operatorStack; 
	for (int i = 0; i < infix.size(); i++)
	{
		switch (infix[i])
		{
			case 'T':
			case 'F':
			{
				postfix += infix[i];
				break;
			}

			case '(':
			{
				operatorStack.push(infix[i]);
				break;
			}

			case ')':
			{
				while (!operatorStack.empty() && operatorStack.top() != '(')
				{
					postfix += operatorStack.top();
					operatorStack.pop(); 
				}
				operatorStack.pop(); //top of stack will be '('
				break; 
			}

			case '!':
			case '&':
			case '^':
			{
				while (!operatorStack.empty() && operatorStack.top() != '(' && operatorPrecedence(infix[i]) <= operatorPrecedence(operatorStack.top()))
				{
					postfix += operatorStack.top(); 
					operatorStack.pop();
				}
				operatorStack.push(infix[i]);
				break;
			}
		}
	}

	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	//evaluation of postfix expression 
	stack <bool> operandStack;
	bool operand2; 
	bool operand1; 
	bool operationResult; 
	for (int j = 0; j < postfix.size(); j++)
	{
		if (postfix[j] == 'T' || postfix[j] == 'F')
		{
			operandStack.push(evalOperand(postfix[j]));
		}
		else //ch is a binary operator 
		{
			if (operandStack.size() >= 2)
			{
				operand2 = operandStack.top();
				operandStack.pop();
			}

			if (!operandStack.empty())
			{
				operand1 = operandStack.top();
				operandStack.pop();
			}
			
			if (postfix[j] == '&')
			{
				if (operand2 == true && operand1 == true)
				{
					operationResult = true;
				}
				else
					operationResult = false; // T&F is false
			}

			if (postfix[j] == '^')
			{
				if (operand2 != operand1) //only returns true for ^ if they are different 
					operationResult = true;
				else
					operationResult = false;
			}

			if (postfix[j] == '!')
			{
				operationResult = !operand1;
			}

			operandStack.push(operationResult); 
		}	
	}

	if (!operandStack.empty())
	{
		result = operandStack.top();
	}

	return 0; 
}

bool isValidInfix(string infix)
{
	if (infix.size() == 0)
		return false;

	for (int k = 0; k < infix.size(); k++) //deleting whitespaces from infix string 
	{
		if (infix[k] == ' ')
		{
			for (int n = k; n < infix.size() - 1; n++)
			{
				infix[n] = infix[n + 1];
			}
			infix.resize(infix.size() - 1);
			k--; //ensures we don't skip over any indexes after shifting everything over 
		}
	}

	if (infix[0] != 'T' && infix[0] != 'F' && infix[0] != '(' && infix[0] != '!') //checking the beginning of infix string 
		return false;

	if (infix[infix.size() - 1] != 'T' && infix[infix.size() - 1] != 'F' && infix[infix.size() - 1] != ')') //checking end of infix string 
		return false;

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] != '!' && infix[i] != '^' && infix[i] != '&' && infix[i] != 'T' && infix[i] != 'F' && infix[i] != '(' && infix[i] != ')') //checking for valid characters in the string
		{
			return false;
		}

		if (infix[i] == 'T' || infix[i] == 'F')  //infix expression cannot have consecutive operands
		{
			if (i + 1 < infix.size())
			{
				if (infix[i + 1] == 'F' || infix[i + 1] == 'T' || infix[i + 1] == '(')
					return false;
			}
		}

		if (infix[i] == '^')
		{
			if (infix[i - 1] == '(' || infix[i - 1] == '!' || infix[i - 1] == '^' || infix[i - 1] == '&')
				return false;

			if (infix[i + 1] == '&' || infix[i + 1] == ')' || infix[i + 1] == '^')
				return false;
		}

		if (infix[i] == '!') //can be followed by ! ( T F  //last index in the string will never be !
		{
			if (infix[i + 1] != '!' && infix[i + 1] != '(' && infix[i + 1] != 'T' && infix[i + 1] != 'F')
				return false;
		}

		if (infix[i] == '&') //can be followed by ! ( T F, last index in string will never be &
		{
			if (infix[i + 1] != '!' && infix[i + 1] != '(' && infix[i + 1] != 'T' && infix[i + 1] != 'F')
				return false;
		}

		if (infix[i] == '(') // ! T F 
		{
			if (infix[i + 1] != '!' && infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '(')
				return false;
		}

		if (infix[i] == ')')
		{
			if (i + 1 < infix.size())
			{
				if (infix[i + 1] != '^' && infix[i + 1] != '&' && infix[i + 1] != ')')
					return false;
			}
		}
	}

	stack <char> paranthesesStack;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
		{
			paranthesesStack.push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			if (paranthesesStack.empty() || paranthesesStack.top() != '(')
			{
				return false; 
			}
			paranthesesStack.pop();
			
			//pop when we find closing parantheses to match opening parantheses 
		}
	}

	if (!paranthesesStack.empty())
	{
		return false;
	}

	return true;
}

int operatorPrecedence(char op)
{
	if (op == '!') //! has greater precedence than & which has greater precedence than ^
		return 3;

	if (op == '&')
		return 2;

	if (op == '^')
		return 1;

	return 0;
}

bool evalOperand(char operand)
{
	if (operand == 'T')
		return true;

	if (operand == 'F')
		return false;

	else
		return true;
}

int main()
{

	/*assert(isValidInfix("T") == true);
	assert(isValidInfix("(F)") == true);
	assert(isValidInfix("T^(F)") == true);
	assert(isValidInfix("T ^ !F") == true);
	assert(isValidInfix("!(T&F)") == true);
	assert(isValidInfix("!T&F") == true);
	assert(isValidInfix("T^F&F") == true);
	assert(isValidInfix("T&!(F^T&T^F)^!!!(F&T&F)") == true);
	assert(isValidInfix("") == false);
	assert(isValidInfix("T&!(F^T&T^F)^!!!(F&T&F)(") == false);
	assert(isValidInfix(")T&!(F^T&T^F)^!!!(F&T&F)") == false);
	assert(isValidInfix("^T&!(F^T&T^F)^!!!(F&T&F)") == false);
	assert(isValidInfix("!T&!(F^T&T^F)^!!!(F&T&F)") == true);
	assert(isValidInfix("bruh") == false);*/

	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}

