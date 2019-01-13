//�ؽþ˰����� ����� ��ȭ��ȣ��
#include <stdio.h>
#include <iostream>
#define MAX_HASH 100
#define HASH_KEY(key) key%MAX_HASH

using namespace std; //�ҽ������� .cpp�� �ٲ��ְ� �����ϸ� cout<<endl ��밡��(C++���� ���)

//����ó�� ���� �� ����ü ����
typedef struct info {
	int id; //Ű��
	char* name;
	int phoneNum;
	struct info* hashNext;
} info;

info* hashTable[MAX_HASH]; //�ؽ����̺��� ũ�⸦ 100���� ����

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
		printf("1_ ����ó �߰�\n");
		printf("2_ ����ó ����\n");
		printf("3_ ����ó ã��\n");
		printf("4_ ����ó ��ü����\n");
		printf("5_ ����\n");
		printf("\n�׸��� �����Ͽ� �ּ���: ");
		scanf_s("%d", &select, sizeof(select));
		printf("\n\n");

		if (select == 1)
		{
			printf("�̸��� �Է��Ͽ��ּ���: ");
			//gets(szName);
			scanf_s("%s", nm, sizeof(nm));
			fflush(stdin); //scanf�� �Է¹��۸� �����.(������ġ)
			printf("��ȭ��ȣ�� �Է��Ͽ��ּ���: ");
			scanf_s("%d", &pn, sizeof(pn));
			fflush(stdin);
			info* info1 = (info*)malloc(sizeof(info));
			info1->id = rand() % 5; //���ڸ� �������� �޾� 5�� ���� �������� key���� ����
			info1->name = nm; //�Է¹��� �̸��� ��ȭ��ȣ�� ����ü�� �����.
			info1->phoneNum = pn;
			info1->hashNext = NULL;
			printf("�߰��Ǿ����ϴ�.\n\n");
			AddHashData(info1, info1->id);
			saveidx[i] = info1->id;
			//i++;
		}
		else if (select == 2)
		{
			printf("��� ° �Դϱ�? ");
			scanf_s("%d", &seq1, sizeof(seq1));
			fflush(stdin);
			printf("������ �̸��� �Է��Ͽ��ּ���: ");
			scanf_s("%s", delnm, sizeof(delnm));
			fflush(stdin);
			DeleteHashData(delnm, seq1);
			printf("\n�����Ǿ����ϴ�.\n\n");
		}
		else if (select == 3)
		{
			printf("��� ° �Դϱ�? ");
			scanf_s("%d", &seq2, sizeof(seq2));
			fflush(stdin);
			printf("�˻��� �̸��� �Է��Ͽ��ּ���: ");
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
	printf("�߰��Ǿ����ϴ�.\n\n");
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
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.\n\n");
		return 0;
	}

	if (strcmp(hashTable[hash_key]->name, name) == 0)
	{
		printf("\n�˻��Ǿ����ϴ�.\n\n");
		printf("�˻����: %s / %d\n\n", name, hashTable[hash_key]->phoneNum);
		return hashTable[hash_key];
	}
	else
	{
		info* info1 = hashTable[hash_key];
		while (info1->hashNext)
		{
			if (strcmp(info1->hashNext->name, name) == 0)
			{
				printf("\n�˻��Ǿ����ϴ�.\n\n");
				printf("�˻����: %s / %d", name, hashTable[hash_key]->phoneNum);
				return info1->hashNext;
			}
			info1 = info1->hashNext;
		}
	}
	return 0;
}


void PrintAllHashData()
{
	cout << "###��ȭ��ȣ��###" << endl;
	for (int i = 1; i < MAX_HASH; i++)
	{
		cout << i << "��° ����:" << endl;
		if (hashTable[i] != NULL)
		{
			info* info1 = hashTable[i];
			while (info1->hashNext)
			{
				cout << info1->id << " ";
				info1 = info1->hashNext;
			}
			cout << "(�ؽð�: " << info1->id << ")" << endl;
			cout << info1->name << endl;
			cout << info1->phoneNum << endl;
		}
	}
	cout << endl << endl;;
}