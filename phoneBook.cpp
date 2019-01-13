//해시알고리즘을 사용한 전화번호부
#include <stdio.h>
#include <iostream>
#define MAX_HASH 100
#define HASH_KEY(key) key%MAX_HASH

using namespace std; //소스파일을 .cpp로 바꿔주고 선언하면 cout<<endl 사용가능(C++에서 사용)

//연락처에 들어가야 할 구조체 정보
typedef struct info {
	int id; //키값
	char* name;
	int phoneNum;
	struct info* hashNext;
} info;

info* hashTable[MAX_HASH]; //해시테이블의 크기를 100으로 설정

//void SelectOne(char name[10], int phoneNumber);
void AddHashData(info* info1, int key);
void DeleteHashData(char* name, int id);
info* FindHashData(char* name, int id);
void PrintAllHashData();

int main() {
	char nm[10];
	int pn;
	int select;
	int i = 0;
	char delnm[10];
	char findnm[10];
	int seq1;
	int seq2;
	int saveidx[101] = { 0, };
	char szName[20] = { 0, };

	do {
		printf("1_ 연락처 추가\n");
		printf("2_ 연락처 삭제\n");
		printf("3_ 연락처 찾기\n");
		printf("4_ 연락처 전체보기\n");
		printf("5_ 종료\n");
		printf("\n항목을 선택하여 주세요: ");
		scanf_s("%d", &select, sizeof(select));
		printf("\n\n");

		if (select == 1)
		{
			printf("이름을 입력하여주세요: ");
			//gets(szName);
			scanf_s("%s", nm, sizeof(nm));
			fflush(stdin); //scanf의 입력버퍼를 지운다.(안전장치)
			printf("전화번호를 입력하여주세요: ");
			scanf_s("%d", &pn, sizeof(pn));
			fflush(stdin);
			info* info1 = (info*)malloc(sizeof(info));
			info1->id = rand() % 5; //숫자를 랜덤으로 받아 5로 나눈 나머지를 key값에 저장
			info1->name = nm; //입력받은 이름과 전화번호가 구조체에 저장됨.
			info1->phoneNum = pn;
			info1->hashNext = NULL;
			printf("추가되었습니다.\n\n");
			AddHashData(info1, info1->id);
			saveidx[i] = info1->id;
			//i++;
		}
		else if (select == 2)
		{
			printf("몇번 째 입니까? ");
			scanf_s("%d", &seq1, sizeof(seq1));
			fflush(stdin);
			printf("삭제할 이름을 입력하여주세요: ");
			scanf_s("%s", delnm, sizeof(delnm));
			fflush(stdin);
			DeleteHashData(delnm, seq1);
			printf("\n삭제되었습니다.\n\n");
		}
		else if (select == 3)
		{
			printf("몇번 째 입니까? ");
			scanf_s("%d", &seq2, sizeof(seq2));
			fflush(stdin);
			printf("검색할 이름을 입력하여주세요: ");
			scanf_s("%s", findnm, sizeof(findnm));
			fflush(stdin);
			FindHashData(findnm, seq2);
		}
		else if (select == 4)
		{
			PrintAllHashData();
		}
	} while (select != 5);
	return 0;
}

/*
void SelectOne(char name[10], int phoneNumber) {
	int i = 0;
	int saveidx[101] = { 0, };
	info* info1 = (info*)malloc(sizeof(info));
	info1->id = rand() % 5;
	info1->name = name;
	info1->phoneNum = phoneNumber;
	info1->hashNext = NULL;
	printf("추가되었습니다.\n\n");
	AddHashData(info1, info1->id);
	saveidx[i] = info1->id;
}
*/
void AddHashData(info* info1, int key)
{
	int hash_key = HASH_KEY(key);
	if (hashTable[hash_key] == NULL)
	{
		hashTable[hash_key] = info1;
	}
	else
	{
		info1->hashNext = hashTable[hash_key];
		hashTable[hash_key] = info1;
	}
}

void DeleteHashData(char* name, int id)
{
	int hash_key = HASH_KEY(id);
	if (hashTable[hash_key] == NULL)
		return;

	info* delInfo = NULL;
	
	if (strcmp(hashTable[hash_key]->name, name) == 0)
	{
		delInfo = hashTable[hash_key];
		hashTable[hash_key] = hashTable[hash_key]->hashNext;
	}
	else
	{
		info* info1 = hashTable[hash_key];
		info* next = info1->hashNext;
		while (next)
		{
			if (strcmp(next->name, name) == 0)
			{
				info1->hashNext = next->hashNext;
				delInfo = next;
				break;
			}
			info1 = next;
			next = info1->hashNext;
		}
	}
	free(delInfo);
}
info* FindHashData(char* name, int id) {
	int hash_key = HASH_KEY(id);
	if (hashTable[hash_key] == NULL) {
		printf("해당 데이터가 존재하지 않습니다.\n\n");
		return 0;
	}

	if (strcmp(hashTable[hash_key]->name, name) == 0)
	{
		printf("\n검색되었습니다.\n\n");
		printf("검색결과: %s / %d\n\n", name, hashTable[hash_key]->phoneNum);
		return hashTable[hash_key];
	}
	else
	{
		info* info1 = hashTable[hash_key];
		while (info1->hashNext)
		{
			if (strcmp(info1->hashNext->name, name) == 0)
			{
				printf("\n검색되었습니다.\n\n");
				printf("검색결과: %s / %d", name, hashTable[hash_key]->phoneNum);
				return info1->hashNext;
			}
			info1 = info1->hashNext;
		}
	}
	return 0;
}


void PrintAllHashData()
{
	cout << "###전화번호부###" << endl;
	for (int i = 1; i < MAX_HASH; i++)
	{
		cout << i << "번째 정보:" << endl;
		if (hashTable[i] != NULL)
		{
			info* info1 = hashTable[i];
			while (info1->hashNext)
			{
				cout << info1->id << " ";
				info1 = info1->hashNext;
			}
			cout << "(해시값: " << info1->id << ")" << endl;
			cout << info1->name << endl;
			cout << info1->phoneNum << endl;
		}
	}
	cout << endl << endl;;
}