#include "BoolParser.h"
#include <string>
#include <iostream>

using namespace std;
using namespace Parser;

int main()
{
	int count = 10;
	printf("Please input the boolean expression, such as T&(T|F)&T, please don't input other characters which are not included in the boolean expression, you can test ten times in the softzare life circle, thanks!.\n");
	while (count--)
	{
		string inputStr;
		BoolParserSexpr* ins = BOOL_PARSER_SEXPR()->getInstance();
		// Input the string.
		getline(cin, inputStr);
		// Generate the binary tree structure with the string.
		TreeNode* tNode = ins->generateBinaryTree(inputStr.c_str(), 0, strlen(inputStr.c_str()));
		// Calculate the result of boolean expression.
		bool ret = ins->cacluteExpressionResult(tNode);
		// Print the S-expression.
		ins->outputResultExpression();
		printf("Result is : %s\n", ret ? "true" : "false");
		// delete the buffer which is applied by in the program.
		ins->destroyTreeNode(tNode);
		// Clear the S-expression buffer for next test.
		ins->clearExpresionBuffer();
		printf("Next one, please! \n\n");
	}
	system("pause");
}