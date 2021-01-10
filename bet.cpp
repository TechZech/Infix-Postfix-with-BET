/*		BET.CPP
	Ben Zech	11/6/2020
	All work below was written by Benjamin Zech. Do not steal
*/

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include "bet.h"
using namespace std;

BET::BET()
// default zero-parameter constructor. Builds an empty tree
{
	root = nullptr;
}

BET::BET(const string& postfix)
// One-parameter constructor, where parameter "postfix" is string containing a postfix expression
// The tree should be built based on the postfix expression.
// Tokens in the postfix expression are separated by spaces.
// call buildfrompostfix
{
	root = nullptr;
	if(buildFromPostfix(postfix) == true)
		buildFromPostfix(postfix);
}

BET::BET(const BET& rhs) : root{ nullptr }
// copy constructor -- makes appropriate deep copy of the tree
{
	root = clone( rhs.root );
}

BET::~BET()
// destructor
{
	makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix)
// parameter "postfix" is string containing a postfix expression.
// The tree should be built based on the postfix expression. 
// Tokens in the postfix expression are separated by spaces.
// If the tree contains nodes before the function is called, first delete the existing nodes.
// Return true if the new tree is built successfully. Return false if an error is encountered.
{
	stack<BinaryNode*> theStack;
	stringstream ss(postfix);
	string token;
	
	if ( !empty() )	// if not empty, make it empty
		makeEmpty(root);
	
	while(ss >> token)
	{
		if ( isdigit(token.front()) != 0 || isalpha(token.front()) != 0 )	// operand
		{
			BinaryNode* tempBN = new BinaryNode(token);
			theStack.push(tempBN);
		}
		
		if ( token == "+" || token == "-" || token == "*" || token == "/" )	// operator
		{
			if( theStack.size() < 2 )
			{
				cout << "Wrong postfix expression" << endl;
				return false;
			}

			BinaryNode* opTemp = new BinaryNode(token, nullptr, theStack.top());
			theStack.pop();
			opTemp->leftChild = theStack.top();
			theStack.pop();
			theStack.push( opTemp );
		}
	}
	
	if ( theStack.size() != 1 )
	{
		cout << "Wrong postfix expression" << endl;
		return false;
	}
	else
	{
		root = theStack.top();
		theStack.pop();		// stack should be empty now
		return true;
	}
}

const BET& BET::operator= (const BET& rhs)
// assignment operator, deep copy
{
	makeEmpty(root);
	root = clone( rhs.root );
	return *this;
}

void BET::printInfixExpression() const
// Print out the infix expression. Should do this by making use of the private (recursive) version
{
	printInfixExpression(root);
	cout << endl;
}

void BET::printPostfixExpression() const
// Print the postfix form of the expression. Use the private recursive function to help
{	
	printPostfixExpression(root);
	cout << endl;
}

size_t BET::size() const
// Return the number of nodes in the tree (using the private recursive function)
{
	return size(root);
}

size_t BET::leaf_nodes() const
// Return the number of leaf nodes in the tree. (Use the private recursive function to help)
{
	return leaf_nodes(root);
}

bool BET::empty() const
// return true if the tree is empty. Return false otherwise.
{
	return (root == nullptr);
}

// ---------------- private helper functions below ----------------------
// ------------ all functions below should be RECURSIVE -----------------


void BET::printInfixExpression(BinaryNode *n) const
// print to the standard output the corresponding infix expression
// Note that you may need to add parentheses depending on the precedence of operators
// You should not have unnecessary parentheses.
{
	bool para = false;
	
	if ( n == nullptr )
		cout << "The BET is empty";
	else {

	if ( n->leftChild != nullptr )
	{
		if ( isOp(n->leftChild->data) && ( precedence(n->data) > precedence(n->leftChild->data)) )
		{
			cout << "( ";
			para = true;
		}

		printInfixExpression( n->leftChild );
		if (para == true)
		{
			cout << ") ";
			para = false;
		}
		
		cout << n->data << " ";

		if ( isOp(n->rightChild->data) && ( precedence(n->data) >= precedence(n->rightChild->data)) )
		{
			cout << "( ";
			para = true;
		}

		printInfixExpression( n->rightChild );
		if (para == true)
		{
			cout << ") ";
			para = false;
		}
	}
	else
		cout << n->data << " ";
	}
}

void BET::printPostfixExpression(BinaryNode *n) const
// print to the standard output the corresponding postfix expression.
{
	if ( n == nullptr )
		cout << "The BET is empty";
	else {

	if ( n->leftChild != nullptr )
	{
			printPostfixExpression( n->leftChild );
			printPostfixExpression( n->rightChild );
			cout << n->data << " ";
	}
	else
		cout << n->data << " ";	
	}
}

void BET::makeEmpty(BinaryNode* &t)
// delete all nodes in the subtree pointed to by t
{
	if (t != nullptr)
	{
		makeEmpty( t->leftChild );
		makeEmpty( t->rightChild );
		delete t;
	}
	t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode *t) const
// clone all nodes in the subtree pointed to by t
// Can be called by functions such as the assignment operator=
{
	if (t == nullptr)
		return nullptr;
	else
		return new BinaryNode{ t->data, clone( t->leftChild ), clone( t->rightChild ) };
}

size_t BET::size(BinaryNode *t) const
// return the number of nodes in the subtree pointed to by t
{
	if ( t == nullptr )
		return 0;
	else
		return 1 + size( t->leftChild ) + size( t->rightChild );
}

size_t BET::leaf_nodes(BinaryNode *t) const
// return the number of leaf nodes in the subtree pointed to by t
{
	if ( t == nullptr )
		return 0;	

	if ( t->leftChild == nullptr && t->rightChild == nullptr )
		return 1;
	else
		return 0 + leaf_nodes( t->leftChild ) + leaf_nodes( t->rightChild );	// is the 0 necessary? not sure and am too lazy to check
}

int BET::precedence(string op) const
// return int value for precedence of operators
{
	if ( op == "*" || op == "/" )
		return 5;		// arbitrary value
	else if ( op == "+" || op == "-" )
		return 4;
}

bool BET::isOp(string data) const
// return true if operator, false otherwise
{
	if ( data == "+" ||  data == "-" || data == "*" || data == "/" )
		return true;
	else
		return false;
}
