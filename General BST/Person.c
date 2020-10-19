#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Person.h"


void initPerson(Person* pPer)
{
	printf("Please enter person name and  id:\n");
	scanf("%s %d", pPer->name, &pPer->age);
}

void showPerson(const void* p)
{
	const Person* pPer = (const Person*)p;
	printf("Person:\tname - %s\t id - %d\n", pPer->name, pPer->age);

}

void showPersonAge(const void* p)
{
	const Person* pPer = (const Person*)p;
	printf("%d\n", pPer->age);
}


int	comparePersonByAge(const void* p1, const void* p2)
{
	const Person* pS1 = (const Person*)p1;
	const Person* pS2 = (const Person*)p2;
	return pS1->age - pS2->age;
}