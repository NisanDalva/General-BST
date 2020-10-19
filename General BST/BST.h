#include "def.h"

/* definition */

typedef struct NODE
{
	DATA			 data;
	struct NODE* right;
	struct NODE* left;
} BST;



/* prototypes */

//basic operations
BOOL initBTree(BST** pTree);
BOOL insert(BST* pTree, DATA value, int(*compare)(const void*, const void*));
BOOL delete(BST* pTree, DATA value, int(*compare)(const void*, const void*));
BST* find(BST* pTree, DATA value, int(*compare)(const void*, const void*));
BOOL isLeaf(BST* pTree);
void freeTree(BST* pTree);


//additional operations
BST* find_parent(BST* pTree, DATA value, int(*compare)(const void*, const void*));
BST* find_min(BST* pTree);
BST* find_max(BST* pTree);
BST* find_follower(BST* pTree, DATA value, int(*compare)(const void*, const void*));
int height(BST* pTree);
BOOL isFull(BST* pTree);
int numOfNodes(BST* pTree);
void storeTreeIntoSortedArr(BST* pTree, BST*** arr, int* i);
BST* buildBalancedTree(BST* pTree);
BST* buildBalancedTreeHelper(BST** arr, int left, int right);


//print operations
void preOrder(BST* pTree, void(*print)(const void*));
void inOrder(BST* pTree, void(*print)(const void*));
void postOrder(BST* pTree, void(*print)(const void*));
void prettyPrint(BST* pTree, void(*print)(const void*));
void prettyPrintHelper(BST* root, int space, void(*print)(const void*));
