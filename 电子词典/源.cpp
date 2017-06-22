#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEY_NUM 50
#define COMMENTATE_NUM 500




struct Dict
{
	char key[50];
	char commentate[500];
	Dict *next;

};


//�����ı�������
Dict* DictCache();
//��������
char* SearchDict(char *buf,Dict *head);
//���빦��
void Input_key(char *inputWord);
//չʾ����
void Show(char *commentWord,char*commentWordUser);

//�����µ��ʱ�
Dict* UserDict();

//�û����ʵ�����

char* SearchUserDict(char *buf, Dict *userhead);

//�û����ʵ����

	//����->����� ��ʾ�Ƿ�׷������ ���û�� ����µ�
//�û������
void UserAdd(Dict *userhead);

void AddNewWord(char *keyWord);

//char *SearchUserWord(char *keyWord,Dict *head);
void SearchUserWord(char *keyWord, Dict *head, char *comment);
int main()
{
	
	
		printf("-------------------------\n");
		puts("       ��ӭʹ�õ��Ӵʵ�      \n");
		puts("       1 ��ѯ               \n");
		puts("       2 ����´ʻ�          \n");
		puts("       3 �˳�                \n");
		system("cls");
	
	
	
	Dict *head = DictCache();
	Dict *userhead = UserDict();
	char *commentWord;
	char commentWordUser[1024] = {" "};
	char inputkey[KEY_NUM];
	
	Input_key(inputkey);
	commentWord = SearchDict(inputkey, head);
	//commentWordUser = SearchUserDict(inputkey, userhead);
	//commentWordUser = SearchUserWord(inputkey, userhead);
	SearchUserWord(inputkey, userhead, commentWordUser);

	
	Show(commentWord,commentWordUser);

	UserAdd(userhead);

	system("pause");
	return 0;
}





Dict* DictCache()
{
	Dict *head=NULL;
	Dict *current = NULL;
	Dict *prev = NULL;
	FILE *fp;
	if ((fp = fopen("dict2.txt", "r")) == NULL)
	{
		perror("fail to read");
		exit(1);
	}
	char buf[KEY_NUM];
	char keybuf[KEY_NUM];
	char comment[COMMENTATE_NUM];
	while (fgets(buf, KEY_NUM, fp) != NULL)
	{
		current = (Dict *)malloc(sizeof(Dict));
		int len = strlen(buf);
		buf[len - 1] = '\0';
		for (int i = 1; i < len; i++)
		{
			char temp = buf[i];
			buf[i - 1] = buf[i];

		}
		strcpy(current->key, buf);
		fgets(comment, COMMENTATE_NUM, fp);
		len=strlen(comment);
		comment[len - 1] = '\0';
		for (int i = 6; i < len; i++)
		{
			comment[i - 6] = comment[i];
		}
		strcpy(current->commentate, comment);
		if (head==NULL)
		{
			head = current;
			prev = head;
			head->next = NULL;
		}
		else
		{
			prev->next = current;
			current->next = NULL;
			prev = current;
		}

	}
	fclose(fp);
	return head;
}





char* SearchDict(char *buf, Dict *head)
{
	Dict *cunrrent=head;

	while (cunrrent!=NULL)
	{
		if ((strcmp(buf,cunrrent->key))==0)
		{

			return cunrrent->commentate;
		}
		else
		{
			cunrrent = cunrrent->next;
		}
		
	}
	return NULL;
}

void Input_key(char *inputWord)
{
	printf("��������Ҫ��ѯ�ĵ��ʻ��ߺ���\n");
	scanf("%s", inputWord);
}



void Show(char *commentWord,char *commentWordUser)
{
	if (commentWord == NULL&&commentWordUser==NULL)
	{
		printf("NOFind\n");
	}
	else
	{
		if (commentWordUser==NULL)
		{
			printf("���شʵ�:%s\n", commentWord);
			printf("�û��ʵ�:û����Ҫ��ѯ������\n");
		}
		else if (commentWord==NULL){
			printf("���شʵ�:û����Ҫ��ѯ������\n");
			printf("�û��ʵ�:%s\n", commentWordUser);
		}
		else
		{
			printf("���شʵ�:%s\n", commentWord);
			printf("�û��ʵ�:%s\n", commentWordUser);
		}
		
	}
	//չʾ�û��Լ���ӵĵ���

	//չʾ�û���ԭ�е�����ӵ��½���
}

Dict* UserDict()
{
	Dict *head = NULL;
	Dict *current = NULL;
	Dict *prev = NULL;
	FILE *fp;
	if ((fp = fopen("UserDict.txt", "r")) == NULL)
	{
		perror("��ȡʧ��\n");
		exit(1);
	}
	char buf[KEY_NUM];
	char keybuf[KEY_NUM];
	char comment[COMMENTATE_NUM];
	while (fgets(buf, KEY_NUM, fp) != NULL)
	{
		current = (Dict *)malloc(sizeof(Dict));
		int len = strlen(buf);
		buf[len - 1] = '\0';
	
		strcpy(current->key, buf);
		fgets(current->commentate, COMMENTATE_NUM, fp);
		
		if (head == NULL)
		{
			head = current;
			prev = head;
			head->next = NULL;
		}
		else
		{
			prev->next = current;
			current->next = NULL;
			prev = current;
		}

	}
	fclose(fp);
	return head;
}

char* SearchUserDict(char *buf, Dict *userhead)
{
	Dict *cunrrent = userhead;

	while (cunrrent != NULL)
	{
		if ((strcmp(buf, cunrrent->key)) == 0)
		{
			return cunrrent->commentate;
		}
		else
		{
			cunrrent = cunrrent->next;
		}

	}
	return NULL;
}

void AddNewWord(char *keyWord)
{
	char commentWord[COMMENTATE_NUM];
	FILE *fp;
	fp = fopen("UserDict.txt", "ab+");
	if (fp==NULL)
	{
		printf("��ʧ��\n");

	}
	fputs(keyWord, fp);
	fputc('\n', fp);
	printf("���������:\n");
	scanf("%s", commentWord);
	fputs(commentWord, fp);
	fputc('\n', fp);
	fclose(fp);

}

//��ѯ�û����ַ�
char * SearchUserWord(char *keyWord, Dict *head)
{
	Dict *current = head;
	char Key[1024] = {" "};
	while (current!=NULL)
	{
		if ((strcmp(keyWord,current->key))==0)
		{
			strcat(Key, current->commentate);
		}

		current = current->next;
	}
	return Key;

}

void SearchUserWord(char *keyWord, Dict *head, char *comment)
{
	Dict *current = head;
	
	while (current != NULL)
	{
		if ((strcmp(keyWord, current->key)) == 0)
		{
			strcat(comment, current->commentate);
		}

		current = current->next;
	}

}

void UserAdd(Dict *userhead)
{

	printf("��������Ҫ��ӵĵ���\n");
	char keyWord[KEY_NUM];
	Input_key(keyWord);
	if ((SearchUserDict(keyWord,userhead))==NULL)
	{
		AddNewWord(keyWord);
	}
	else
	{
		int num;
		printf("�õ����Ѿ���ӹ���,�Ƿ�׷�ӽ���\n");
		printf("1  ��  2  ��\n");
		
		scanf("%d", &num);
		system("cls");
		if (num==1)
		{
			AddNewWord(keyWord);
		}
		else
		{
			return;
		}

	}

}




