/*		BET.H
	Ben Zech	11/6/2020
	All work below was written by Benjamin Zech. Do not steal
*/

#include <iostream>
#include <string>
using namespace std;

class BET
{
	private: // Nested BinaryNode class
	struct BinaryNode {
		string data;
		BinaryNode* leftChild;
		BinaryNode* rightChild;

		BinaryNode(const string & d, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
			: data{d}, leftChild{l}, rightChild{r} {}
		BinaryNode(string && d, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
			: data{std::move(d)}, leftChild{l}, rightChild{r} {}
		
	
	};
	public:
		BET();				// default zero-parameter constructor. Builds an empty tree.
		BET(const string& postfix);	// One-parameter constructor
		BET(const BET&);		// copy constructor -- makes appropriate deep copy of the tree
		~BET();				// destructor
		bool buildFromPostfix(const string& postfix);
		const BET & operator= (const BET &);	// assignment operator, deep copy
		void printInfixExpression() const;	// print infix
		void printPostfixExpression() const;	// print postfix
		size_t size() const;	// return the num nodes
		size_t leaf_nodes() const;	// return num leaves
		bool empty() const;	// is tree empty?

	private:
		BinaryNode* root;
		
		void printInfixExpression(BinaryNode *n) const;	// print to std out
		void printPostfixExpression(BinaryNode *n) const;	// print to std out
		void makeEmpty(BinaryNode* &t);			// delete all nodes in subtree t
		BinaryNode* clone(BinaryNode *t) const;		// clone subtree t (hint: use in assignment operator)
		size_t size(BinaryNode *t) const;		// return num nodes of subtree t
		size_t leaf_nodes(BinaryNode *t) const;		// return leaves of subtree t
		int precedence(string op) const;		// helper function with precedence of operators
		bool isOp(string data) const;			// helper function determines is or isnt operator
};
