#ifndef PERSON_H_
#define PERSON_H_

#define MAX_LEN 20
typedef struct
{
	int 	age;
	char	name[MAX_LEN];
}Person;

void 	initPerson(Person* pPer);
void	showPerson(const void* pPer);
int		comparePersonByAge(const void* p1, const void* p2);
void showPersonAge(const void* p);

#endif /* PERSON_H_ */