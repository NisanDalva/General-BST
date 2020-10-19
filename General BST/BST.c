#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "BST.h"
#include "Person.h"


/*
create new binary search tree
input: pointer to BST
output: True if success, False if not
*/
BOOL initBTree(BST** pTree)
{
	if (!pTree)
		return False;

	*pTree = (BST*)malloc(1 * sizeof(BST));
	if (!(*pTree))
		return False;

	(*pTree)->data = NULL;
	(*pTree)->left = NULL;
	(*pTree)->right = NULL;
	return True;
}

/*
insert new DATA into an exist BST
input: pointer to BST want to add to, DATA will insert, and function can compare between two diffrent type of DATA
output: True if success, False if not
*/
BOOL insert(BST* pTree, DATA value, int(*compare)(const void*, const void*))
{
	if (!pTree)
		return False;

	BST* new;
	BST* parent;
	BST** tmp;

	//insert first value into tree
	if (!pTree->data)
	{
		pTree->data = value;
		return True;
	}

	//decide to where insert new DATA
	parent = find_parent(pTree, value, compare);
	tmp = compare(value, parent->data) > 0 ? &parent->right : &parent->left;
	if ((*tmp)) //value already in tree
		return False;

	//create new node
	new = (BST*)malloc(1 * sizeof(BST));
	if (!new)
		return False;
	new->data = value;
	new->left = NULL;
	new->right = NULL;

	*tmp = new; //connect to tree
	return True;
}

/*
delete exist DATA into an exist BST
input: pointer to BST want to delete from, DATA will deleted, and function can compare between two diffrent type of DATA
output: True if success, False if not
*/
BOOL delete(BST* pTree, DATA value, int(*compare)(const void*, const void*))
{
	if (!pTree)
		return False;

	BST* node;
	BST* parent;
	BST** tmp;

	parent = find_parent(pTree, value, compare);

	//if parent == NULL --- to do

	if (!parent) //is head of tree
		tmp = &pTree;
	else
		tmp = compare(value, parent->data) > 0 ? &parent->right : &parent->left;

	node = *tmp;
	if (!node)
		return False; //x doesn't exist, no deletion

	if (node->left && node->right)
	{
		tmp = &node->right;
		while ((*tmp)->left)
		{
			tmp = &(*tmp)->left;
		}
		node->data = (*tmp)->data;

		node = *tmp;
	}

	*tmp = node->left ? node->left : node->right;

	free(node);


	return True;
}

/*
find an element
input: pointer to BST, DATA will search for, function can compare between two different type of DATA
output: BST who pointed to DATA, NULL if not found
*/
BST* find(BST* pTree, DATA value, int(*compare)(const void*, const void*))
{
	if (!pTree)
		return NULL;

	if (compare(value, pTree->data) > 0)
		return find(pTree->right, value, compare);

	if (compare(value, pTree->data) < 0)
		return find(pTree->left, value, compare);

	return pTree;
}

/*
check if BST is leaf
input: pointer to BST
output: True if is leaf, False if isn't
*/
BOOL isLeaf(BST* pTree)
{
	if (!pTree)
		return False;

	if (!pTree->left && !pTree->right)
		return True;
	return False;
}

/*
free all elements from memory
input: pointer to BST
*/
void freeTree(BST* pTree)
{
	if (!pTree)
		return;
	freeTree(pTree->left);
	freeTree(pTree->right);
	free(pTree);
}



/*
find a parent of exsit node
input: pointer to BST, DATA , function can compare between two different type of DATA
*/
BST* find_parent(BST* pTree, DATA value, int(*compare)(const void*, const void*))
{
	if (!pTree)
		return NULL;

	BST* tmp;
	if ((isLeaf(pTree) && !pTree->data) || compare(value, pTree->data) == 0)
		return NULL;

	tmp = compare(value, pTree->data) > 0 ? pTree->right : pTree->left;

	if (tmp == NULL || compare(value, tmp->data) == 0)
		return pTree;

	return find_parent(tmp, value, compare);
}

/*
find minimum value of tree
input: pointer to BST
output: BST who pointed to the minimum value
*/
BST* find_min(BST* pTree)
{
	if (!pTree)
		return NULL;

	if (pTree->left)
		return find_min(pTree->left);
	else
		return pTree;
}

/*
find maximum value of tree
input: pointer to BST
output: BST who pointed to the maximum value
*/
BST* find_max(BST* pTree)
{
	if (!pTree)
		return NULL;

	if (pTree->right)
		return find_max(pTree->right);
	else
		return pTree;
}

/*
find the follower of DATA, according to given function
input: pointer to BST, DATA, function can compare between two different type of DATA
output: BST who pointed to the follower
*/
BST* find_follower(BST* pTree, DATA value, int(*compare)(const void*, const void*))
{
	if (!pTree)
		return NULL;

	BST* node = find(pTree, value, compare);

	if (node->right)
		return find_min(node->right);

	BST* p = find_parent(pTree, value, compare);
	if (compare(value, p->data) > 0)
	{
		BST* pp = find_parent(pTree, p->data, compare);
		if (compare(value, pp->data) < 0)
			return pp;
	}
	else if (compare(value, p->data) < 0)
		return p;

	return NULL; //no follower
}

/*
calculate the height of tree
input: pointer to BST
*/
int height(BST* pTree)
{
	if (!pTree)
		return 0;

	//height of subtrees
	int leftHeight = height(pTree->left);
	int rightHeight = height(pTree->right);

	if (leftHeight > rightHeight)
		return(leftHeight + 1);
	return(rightHeight + 1);
}

/*
check if given BST is full tree
input: pointer to BST
output: True if is full, False if isn't
*/
BOOL isFull(BST* pTree)
{
	if (!pTree)
		return False;

	if (isLeaf(pTree))
		return True;

	if (pTree->left && pTree->right)
		return isFull(pTree->left) && isFull(pTree->right);

	return False;

}

/*
claculate the number of nodes in tree
input: pointer to BST
output: the number of nodes
*/
int numOfNodes(BST* pTree)
{
	if (!pTree)
		return 0;

	int numLeft = numOfNodes(pTree->left);
	int numRight = numOfNodes(pTree->right);

	return numLeft + numRight + 1;
}

/*
store BST into sorted array
input: pointer to BST, pointer to array of BSTs, pointer to start index in array
*/
void storeTreeIntoSortedArr(BST* pTree, BST*** arr, int* i)
{
	if (!pTree)
		return;

	storeTreeIntoSortedArr(pTree->left, arr, i);

	(*arr)[*i] = pTree;
	(*i)++;

	storeTreeIntoSortedArr(pTree->right, arr, i);
}

/*
build a balanced tree from given BST
input: pointer to BST
output: balanced BST
*/
BST* buildBalancedTree(BST* pTree)
{
	if (!pTree)
		return NULL;

	int numNodes = numOfNodes(pTree);
	//first, build sorted array of original BST
	BST** arr = (BST**)malloc(numNodes * sizeof(BST*));
	if (!arr)
		return NULL;

	int i = 0;
	storeTreeIntoSortedArr(pTree, &arr, &i);
	BST* balancedBST = buildBalancedTreeHelper(arr, 0, numNodes - 1);
	free(arr);
	return balancedBST;
}

/*
utility function to 'buileBalancedTree'
*/
BST* buildBalancedTreeHelper(BST** arr, int left, int right)
{
	if (left > right)
		return NULL;

	//pick the middle of array and make it root
	int mid = (left + right) / 2;
	BST* root = arr[mid];

	root->left = buildBalancedTreeHelper(arr, left, mid - 1);
	root->right = buildBalancedTreeHelper(arr, mid + 1, right);

	return root;
}




/*
print tree as pre-order operation
input: pointer to BST, function can print type of DATA
*/
void preOrder(BST* pTree, void(*print)(const void*))
{
	if (!pTree)
		return;

	print(pTree->data);
	preOrder(pTree->left, print);
	preOrder(pTree->right, print);
}

/*
print tree as in-order operation
input: pointer to BST, function can print type of DATA
*/
void inOrder(BST* pTree, void(*print)(const void*))
{
	if (!pTree)
		return;

	inOrder(pTree->left, print);
	print(pTree->data);
	inOrder(pTree->right, print);
}

/*
print tree as post-order operation
input: pointer to BST, function can print type of DATA
*/
void postOrder(BST* pTree, void(*print)(const void*))
{
	if (!pTree)
		return;

	postOrder(pTree->left, print);
	postOrder(pTree->right, print);
	print(pTree->data);
}

/*
print the tree
input: pointer to BST. function can print the ONLY value (not the entire DATA)

			  5								8
for BST:     / \		will print:     5
			3   8							3
*/
void prettyPrint(BST* pTree, void(*print)(const void*))
{
	prettyPrintHelper(pTree, 0, print);
}

/*
utility function to 'prettyPrint'
*/
void prettyPrintHelper(BST* pTree, int space, void(*print)(const void*))
{
	const int INCREASE = 5;
	if (!pTree)
		return;

	// increase distance between levels 
	space += INCREASE;

	prettyPrintHelper(pTree->right, space, print);

	printf("\n");
	for (int i = INCREASE; i < space; i++)
		printf(" ");

	//print current DATA
	print(pTree->data);

	prettyPrintHelper(pTree->left, space, print);
}
