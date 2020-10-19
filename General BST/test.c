#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "BST.h"
#include "Person.h"


int main()
{

	Person persons[8] = {
							{ 15, "aaa" }, //persons[0]
							{ 20, "bbb" }, //persons[1]
							{ 18, "ccc" }, //persons[2]
							{ 10, "ddd" }, //persons[3]
							{ 11, "eee" }, //persons[4]
							{ 9, "fff" },  //persons[5]
							{ 19, "ggg" }, //persons[6]
							{ 22, "hhh" }  //persons[7]
	};


	printf("all persons in array:\n");
	for (int i = 0; i < 8; i++)
		showPerson(&persons[i]);


	BST* tree = NULL;
	initBTree(&tree);

	for (int i = 0; i < 5; i++)
		insert(tree, &persons[i], comparePersonByAge);

	//------------------------------------

	printf("\npre-order:\n");
	preOrder(tree, showPerson);

	printf("\nin-order:\n");
	inOrder(tree, showPerson);

	printf("\npost-order:\n");
	postOrder(tree, showPerson);

	//------------------------------------

	printf("\n\nfind person by age:\n");
	Person tmp = { 15, "ee" };
	BST* isFound = find(tree, &tmp, comparePersonByAge);

	if (isFound)
		showPerson(isFound->data);
	else
		printf("not found\n");
	printf("\n");

	//------------------------------------

	printf("\n\npretty print:\n");
	prettyPrint(tree, showPersonAge);

	//------------------------------------

	delete(tree, &persons[6], comparePersonByAge);
	printf("\n\none node deleted - pretty print:\n");
	prettyPrint(tree, showPersonAge);

	//------------------------------------

	printf("\n\nminimum in tree:\n");
	BST* min = find_min(tree);
	showPerson(min->data);


	printf("maximum in tree:\n");
	BST* max = find_max(tree);
	showPerson(max->data);

	//------------------------------------

	printf("\n\nheight of tree:\n");
	int h = height(tree);
	printf("h = %d\n", h);

	//------------------------------------

	printf("\n\nis full tree?\n");
	BOOL isFullTree = isFull(tree);
	printf("isFullTree = %d\t\t(0 - false, 1 - true)\n", isFullTree);

	//------------------------------------

	printf("\n\nfind follower:\t");
	BST* follower = find_follower(tree, &persons[4], comparePersonByAge);
	if (follower)
		showPerson(follower->data);
	else
		printf("no follower, is max number\n");

	//------------------------------------

	printf("\n\nnum of nodes:\n");
	int num = numOfNodes(tree);
	printf("num = %d\n", num);

	//------------------------------------

	printf("\n\nsorted array:\n");
	BST** arr = (BST**)malloc(numOfNodes(tree) * sizeof(BST*));
	if (!arr)
		return -1;

	int i = 0;
	storeTreeIntoSortedArr(tree, &arr, &i);

	for (int i = 0; i < numOfNodes(tree); i++)
		showPerson(arr[i]->data);
	free(arr);
	//------------------------------------

	//another tree - for test buildTree function
	Person persons2[8] = {
						{ 78, "aaa" }, //persons[0]
						{ 20, "bbb" }, //persons[1]
						{ 18, "ccc" }, //persons[2]
						{ 10, "ddd" }, //persons[3]
						{ 11, "eee" }, //persons[4]
						{ 9, "fff" },  //persons[5]
						{ 19, "ggg" }, //persons[6]
						{ 22, "hhh" }  //persons[7]
	};

	BST* tree2 = NULL;
	initBTree(&tree2);

	for (int i = 0; i < 5; i++)
		insert(tree2, &persons2[i], comparePersonByAge);

	printf("\n\nbefore build balanced BST - pretty print of another tree:\n");
	prettyPrint(tree2, showPersonAge);

	printf("\nafter build balanced BST - pretty print:\n");
	BST* balanced = buildBalancedTree(tree2);
	prettyPrint(balanced, showPersonAge);

	//------------------------------------

	freeTree(tree);
	printf("\n\nfree success\n");
	return 0;

}
