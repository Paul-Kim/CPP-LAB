#pragma once
#include "main.h"

class Tree
{
public:
	struct Node
	{
		int value = -INF;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int value) : value(value) {}

		void insert(Node*  node);
	};

	static int CountNode(Node* root);
	static int CountLeafNode(Node* root);
};