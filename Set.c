#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int v;
	struct Node* next;
} Node;

typedef struct Set {
	Node* head;
	bool (*Is_In) (struct Set* list, int n);
	void (*Create) (struct Set* list, int v);
	void (*Insert) (struct Set* list, int v);
	bool (*Remove) (struct Set* list, int v);
} Set;

void printSet(Set* list);
void init(Set* list);
Set Union(Set* A, Set* B);
Set Intersection(Set* A, Set* B);
Set Difference(Set* A, Set* B);

int main() {
	srand(time(NULL));
	int A[10], B[10];
	int i;

	Set set_A, set_B;
	init(&set_A), init(&set_B);

	printf("======= Random Array A =======\n");
	for (i = 0;i < 10;i++) {
		A[i] = rand() % 10;
		B[i] = rand() % 10;
		i < 9 ? printf("%d, ", A[i]) : printf("%d\n", A[i]);
	}
	printf("======= Random Array B =======\n");
	for (i = 0;i < 10;i++) {
		i < 9 ? printf("%d, ", B[i]) : printf("%d\n\n", B[i]);
		set_A.Create(&set_A, A[i]);
		set_B.Create(&set_B, B[i]);
	}


	Set set_Union = Union(&set_A, &set_B);
	Set set_Intersection = Intersection(&set_A, &set_B);
	Set set_Diff_AB = Difference(&set_A, &set_B);
	Set set_Diff_BA = Difference(&set_B, &set_A);

	printf("============ SET A ===========\n");
	printSet(&set_A);
	printf("============ SET B ===========\n");
	printSet(&set_B);
	printf("\n");

	printf("== INSERT 10 to setA 2 loop ==\n");
	for (i = 0; i != 2; i++) {
		if (set_A.Is_In(&set_A, 10)) printf("이미 존재하는 값\n");
		else {
			set_A.Insert(&set_A, 10);
			printSet(&set_A);
		}
	}
	printf("\n");

	printf("== REMOVE 10 to setA 2 loop ==\n");
	for (i = 0; i != 2; i++) {
		if (set_A.Is_In(&set_A, 10)) {
			set_A.Remove(&set_A, 10);
			printSet(&set_A);
		}
		else printf("존재하지 않는 값\n");
	}
	printf("\n");

	printf("============ UNION ===========\n");
	printSet(&set_Union);
	printf("\n");

	printf("======== Intersection ========\n");
	printSet(&set_Intersection);
	printf("\n");

	printf("======= Difference A-B =======\n");
	printSet(&set_Diff_AB);
	printf("======= Difference B-A =======\n");
	printSet(&set_Diff_BA);
	printf("\n");

	return 0;
}

void printSet(Set* list) {
	if (list -> head == NULL) printf("empty\n");
	else {
		Node* ptr = list->head;
		if (ptr != NULL) printf("%d", ptr->v);
		ptr = ptr->next;
		while (ptr != NULL) {
			printf(", %d", ptr->v);
			ptr = ptr->next;
		}
		printf("\n");
	}
}
bool Set_Is_In(Set* list, int n) {
	Node* ptr = list->head;
	while (ptr != NULL) {
		if (ptr->v == n) {
			return true; 
		}
		ptr = ptr->next;
	}
	return false;
}
void push(Set* list, int v) {
	if (Set_Is_In(list, v)) return;
	Node* ptr = list->head;
	Node* node = (Node*)malloc(sizeof(Node));
	node->v = v;
	node->next = NULL;

	if (ptr == NULL) list->head = node;
	else {
		while (ptr->next != NULL) ptr = ptr->next;
		ptr->next = node;
	}
}

Set Intersection(Set* A, Set* B) {
	Set set;
	init(&set);
	Node* ptr = B->head;
	while (ptr != NULL) {
		if (A->Is_In(A, ptr->v)) set.Create(&set, ptr->v);
		ptr = ptr->next;
	}
	return set;
}
Set Difference(Set* A, Set* B) {
	Set set;
	init(&set);
	Node* ptr = A->head;
	while (ptr != NULL) {
		if (!(B->Is_In(B,ptr->v))) set.Create(&set, ptr->v);
		ptr = ptr->next;
	}
	return set;
}
Set Union(Set* A, Set* B) {
	Set set;
	init(&set);
	Node* ptr = A->head;
	while (ptr != NULL) {
		set.Create(&set, ptr->v);
		ptr = ptr->next;
	}
	ptr = B->head;
	while (ptr != NULL) {
		set.Create(&set, ptr->v);
		ptr = ptr->next;
	}
	return set;
}
bool pop(Set* list, int v) {
	Node* ptr = list->head;
	Node* next = ptr->next;
	if (ptr == NULL) return false;
	if (ptr->v == v) {
		list->head = ptr->next;
		return true;
	}
	while (next != NULL) {
		if (next->v == v) {
			ptr->next = next->next;
			return true;
		}
		ptr = ptr->next;
		next = next->next;
	}
	return false;
}
void init(Set* list) {
	list->head = NULL;
	list->Is_In = Set_Is_In;
	list->Create = push;
	list->Insert = push;
	list->Remove = pop;
}