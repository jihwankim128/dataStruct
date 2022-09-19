#include <stdio.h>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool Is_In(vector<int> set, int n) {
	for(int i = 0; i<set.size(); i++)
		if(set[i]==n) return true;
	return false;
}
vector<int> Union(vector<int> set1, vector<int> set2) {
	for(int i=0; i<set2.size();i++)
		if(!Is_In(set1, set2[i]))
			set1.push_back(set2[i]);
	return set1;
}
vector<int> Difference(vector<int> base, vector<int> set){
	vector<int> diff;
	for(int i = 0; i<base.size();i++)
		if (!Is_In(set, base[i]))
			diff.push_back(base[i]);
	return diff;
}
vector<int> Intersection(vector<int> set1, vector<int> set2){
	vector<int> insec;
	for(int i = 0; i<set1.size();i++)
		if(Is_In(set2,set1[i]))
			insec.push_back(set1[i]);
	return insec;
}
vector<int> Create(vector<int> arr)
{
	vector<int> set;
	for (int i = 0; i < arr.size(); i++) {
		if(Is_In(set, arr[i])) continue;
		else set.push_back(arr[i]);
	}
	return set;
}

void Insert(vector<int> &arr, int n) {
	if (Is_In(arr, n)) printf("이미 존재하는 원소입니다.\n");
	else arr.push_back(n);
}

void Remove(vector<int> &arr, int n) {
	if(Is_In(arr, n))
		arr.erase(remove(arr.begin(), arr.end(), n), arr.end());
	else
		printf("존재하지 않는 원소 입니다.\n");
}

void print(vector<int> arr, char *name) {
  	int size = arr.size();
  	printf("%s : ",name);
  	if(arr.empty()) {
  		printf("empty\n");
		return;
	}
	printf("[");
	for (int i = 0; i < size - 1; ++i)
		printf("%d, ", arr[i]);
	printf("%d]\n",arr[size-1]);
}

int main(){
	srand(time(NULL));
	vector<int> A;
	vector<int> B;
	for (int i = 0; i < 10; i++)
	    A.push_back(rand() % 10);
	for (int i = 0; i < 10; i++)
	    B.push_back(rand() % 10);
	
	printf("임의의 배열 생성\n");
	print(A,"A");
	print(B,"B");
	
	vector<int> set_A = Create(A);
	vector<int> set_B = Create(B);
	
	printf("\n배열을 토대로 집합 생성\n");
	print(set_A, "SET_A");
	print(set_B, "SET_B");
	
	printf("\n합집합, 차집합, 교집합\n"); 
	print(Union(set_A, set_B),"UNION");
	print(Difference(set_A, set_B),"Difference");
	print(Intersection(set_A, set_B), "Intersection");
	
	printf("\nINSERT, SET_A에 11삽입\n");
	Insert(set_A, 11);
	print(set_A, "SET_A");
	printf("INSERT, SET_A에 11삽입\n");
	Insert(set_A, 11);
	
	printf("\nIS_IN, SET_A에 11이 존재하는가? ");
	if(Is_In(set_A, 11)) printf("YES\n");
	else printf("NO\n");
	printf("IS_IN, SET_A에 12가 존재하는가? ");
	if(Is_In(set_A, 12)) printf("YES\n");
	else printf("NO\n");

	printf("\nREMOVE, SET_A에 11제거\n");
	Remove(set_A, 11);
	print(set_A, "SET_A");
	printf("REMOVE, SET_A에 11제거\n");
	Remove(set_A, 11);

}
