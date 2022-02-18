#ifndef _BOOL_PARSER_H_
#define _BOOL_PARSER_H_

#include <string.h>

namespace Parser
{
	#define BUFFER_SIZE	1024
	#define BOOL_PARSER_SEXPR() BoolParserSexpr::getInstance()

	struct TreeNode
	{
		char			character[2];	// Store the character which is parsed from the string.
		bool			flag;			// Mark matches to indicate true or false of symbol.
		bool			isSymble;		// Whether the character is symbol, such as:'|' and '&'.
		TreeNode*		left;			// Left child node.
		TreeNode*		right;			// Right child node.
		TreeNode()
		{
			flag = false;
			isSymble = false;
			memset(character, 0x00, sizeof(character));
			left = nullptr;
			right = nullptr;
		}
	};

	class BoolParserSexpr
	{
	public:
		static BoolParserSexpr* getInstance();

		/*
		* @brief
		*   Generate the binary tree structure with string.
		* @return
		*   TreeNode*: The root node of binary tree.
		* @param
		*   [in] int start: The start id.
		*   [in] int end: The end id.
		*/
		TreeNode* generateBinaryTree(const char* inputStr, int start, int end);

		/*
		* @brief
		*   Calculate the result of the boolean expression.
		* @return
		*   bool: result: true or false.
		* @param
		*   [in] TreeNode* treeInfo: The root node of binary tree.
		*/
		bool cacluteExpressionResult(TreeNode* treeInfo);

		/*
		* @brief
		*   Print the S-expression for the string .
		* @return
		*   void
		* @param
		*   None
		*/
		void outputResultExpression();

		/*
		* @brief
		*   Release the binary node's buffer.
		* @return
		*   void
		* @param
		*   [in] TreeNode* treeInfo: The root node of binary tree.
		*/
		void destroyTreeNode(TreeNode* tNode);

		/*
		* @brief
		*   Clear the S-expression's buffer to avoid the error messages.
		* @return
		*   void
		* @param
		*   None
		*/
		void clearExpresionBuffer();

	private:
		BoolParserSexpr();
		~BoolParserSexpr();

	private:
		char m_sExpression[BUFFER_SIZE] ;
		bool m_isOnlyOneSymbol;
	};
}

#endif // _BOOL_PARSER_H_
