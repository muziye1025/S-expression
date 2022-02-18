#include "BoolParser.h"
#include <string>
#include <stack>
using namespace std;

namespace Parser
{
	#define INIT_VALUE	-1

	BoolParserSexpr* BoolParserSexpr::getInstance()
	{
		static BoolParserSexpr m_instance;
		return &m_instance;
	}

	bool BoolParserSexpr::cacluteExpressionResult(TreeNode* treeInfo)
	{
		bool ret = false;
		if (nullptr == treeInfo)
		{
			printf("Error: the expression is null.");
			return ret;
		}

		if (treeInfo->isSymble)
		{
			switch (treeInfo->character[0])
			{
			case '|':
				ret = cacluteExpressionResult(treeInfo->left) || cacluteExpressionResult(treeInfo->right);
				if (ret)
				{
					treeInfo->character[0] = 'T';
				}
				else
				{
					treeInfo->character[0] = 'F';
				}
				if (m_sExpression[0] != 0)
				{
					sprintf_s(m_sExpression, BUFFER_SIZE, "(%s | %s)", m_sExpression, "S");
				}
				else
				{
					strcat_s(m_sExpression, BUFFER_SIZE, "(S | S)");
				}
				break;
			case '&':
				ret = cacluteExpressionResult(treeInfo->left) && cacluteExpressionResult(treeInfo->right);
				if (ret)
				{
					treeInfo->character[0] = 'T';
				}
				else
				{
					treeInfo->character[0] = 'F';
				}
				if (m_sExpression[0] != 0)
				{
					sprintf_s(m_sExpression, BUFFER_SIZE, "(%s & %s)", m_sExpression, "S");
				}
				else
				{
					strcat_s(m_sExpression, BUFFER_SIZE, "(S & S)");
				}
				break;
			default:
				break;
			}
		}
		if (!treeInfo->isSymble)
		{
			switch (treeInfo->character[0])
			{
			case 'T':
				ret = true;
				if (m_isOnlyOneSymbol)
				{
					strcat_s(m_sExpression, BUFFER_SIZE, "(S)");
				}
				break;
			case 'F':
				ret = false;
				if (m_isOnlyOneSymbol)
				{
					strcat_s(m_sExpression, BUFFER_SIZE, "(S)");
				}
				break;
			default:
				break;
			}
		}

		return ret;
	}

	TreeNode* BoolParserSexpr::generateBinaryTree(const char* inputStr, int start, int end)
	{
		if (start >= end)
		{
			return nullptr;
		}
		TreeNode* tempNode = new TreeNode;
		int splitId = INIT_VALUE;
		int bracketsMark = 0;
		if (end - start == 1)   //If there is only one valid character in the string, it should return only one node without calculation.
	    {
			tempNode->character[0] = inputStr[start];
			if ('T' == tempNode->character[0])
			{
				tempNode->flag = true;
			}
			else if ('F' == tempNode->character[0])
			{
				tempNode->flag = false;
			}
			return tempNode;
	     }
	
		int idx = 0;
		for (idx = start; idx < end; idx++)   // Find the root of the node, from the string's right to left.
	     {
			 if (inputStr[idx] == '(')
			 {
				 bracketsMark++;
			 }
			 if (inputStr[idx] == ')')
			 {
				 bracketsMark--;
			 }
			 if ((inputStr[idx] == '|' || inputStr[idx] == '&'))
			 {
				 // Use the brackets to split the string in different level in the binary tree structure.
				 if (!bracketsMark)
				 {
					 splitId = idx;
				 }
			 }
	     }
		 if (splitId < 0)
		 {
			 // The current expression is in a couple of brackets.
			 return generateBinaryTree(inputStr, start + 1, end - 1);
		 }     
		 // Store the character's value in node.
		 tempNode->character[0] = inputStr[splitId];
		 // Assume that the input string only contains '|',  '&',  'T',  'F'.
		 if ('|' == tempNode->character[0] || '&' == tempNode->character[0])
		 {
			 tempNode->isSymble = true;
		 }
		 else
		 {
			 tempNode->isSymble = false;
		 }
		 m_isOnlyOneSymbol = false;
		 tempNode->left = generateBinaryTree(inputStr, start, splitId);
		 tempNode->right = generateBinaryTree(inputStr, splitId + 1, end);
		 return tempNode;
	}

	void BoolParserSexpr::outputResultExpression()
	{
		printf("S-expression:%s\n", m_sExpression);
	}

	void BoolParserSexpr::destroyTreeNode(TreeNode* tNode)
	{
		if (nullptr == tNode)
		{
			printf("The TreeNode is null!");
			return;
		}
		if (tNode)
		{
			if (nullptr == tNode->left && nullptr == tNode->right)
			{
				printf("%s is released!\n", tNode->character);
				delete(tNode);
				tNode = nullptr;
			}
		}
		if (tNode)
		{
			destroyTreeNode(tNode->left);
			destroyTreeNode(tNode->right);
		}
		if (tNode)
		{
			printf("%s is released!\n", tNode->character);
			delete(tNode);
			tNode = nullptr;
		}
	}

	void BoolParserSexpr::clearExpresionBuffer()
	{
		memset(m_sExpression, 0x00, sizeof(m_sExpression));
	}

	BoolParserSexpr::BoolParserSexpr()
	{
		m_isOnlyOneSymbol = true;
		memset(m_sExpression, 0x00, sizeof(m_sExpression));
	}

	BoolParserSexpr::~BoolParserSexpr()
	{

	}
}