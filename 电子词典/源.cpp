
/************************************************************************/
/* 说明																	*/
/*编译环境 vs2013 如果其他编译器报错										*/
/*请删除#define _CRT_SECURE_NO_WARNINGS									*/
/************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEY_NUM 50
#define COMMENTATE_NUM 500

//创建Dict 结构体 保存字典单词和解释
struct Dict
{
	char key[50];
	char commentate[500];
	Dict *next;

};

//菜单的创建

int Menu(){
	int chooseNum;

	printf("-------------------------\n");
	puts("       欢迎使用电子词典      \n");
	puts("       1 查询               \n");
	puts("       2 添加新词汇或自定义单词的解释\n");
	puts("       3 退出                \n");
	printf("-------------------------\n");
	printf("请输入你的选择\n");
	scanf("%d", &chooseNum);
	system("cls");
	return chooseNum;
}

//创建文本缓存区
Dict* DictCache();
//搜索功能 
	//搜索本地词典
char* SearchDict(char *buf,Dict *head);
	//搜索用户词典
void SearchUserWord(char *keyWord, Dict *head, char *comment);
//输入功能
void Input_key(char *inputWord);
//展示功能
void Show(char *commentWord,char*commentWordUser);

//创建新单词本
Dict* UserDict();

//用户单词的搜索

char* SearchUserDict(char *buf, Dict *userhead);

//用户单词的添加

	//遍历->如果有 提示是否追加内容 如果没有 添加新的
//用户的添加
void UserAdd(Dict *userhead);

void AddNewWord(char *keyWord);

int main()
{
	
	Dict *head = DictCache();
	Dict *userhead = UserDict();
	char *commentWord;
	char commentWordUser[1024] = {" "};
	char inputkey[KEY_NUM];
	
	int i = Menu();

	do
	{
		if (i == 1)
		{
			Input_key(inputkey);
			commentWord = SearchDict(inputkey, head);
			SearchUserWord(inputkey, userhead, commentWordUser);
			Show(commentWord, commentWordUser);
			i = Menu();
		}
		else if (i==2)
		{
			UserAdd(userhead);
			printf("添加成功!\n");
			system("pause");
			system("cls");
			i = Menu();
		}
		else
		{
			puts("你输入的选择有误,请重新输入\n");
			system("pause");
			system("cls");
			i = Menu();
		}

	} while (i != 3);

	return 0;
}




//将单词读入到缓存
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




//搜索用户单词
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


//输入 :
void Input_key(char *inputWord)
{
	printf("请输入单词\n");
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
			printf("本地词典:%s\n", commentWord);
			printf("用户词典:没有你要查询的内容\n");
		}
		else if (commentWord==NULL){
			printf("本地词典:没有你要查询的内容\n");
			printf("用户词典:%s\n", commentWordUser);
		}
		else
		{
			printf("本地词典:%s\n", commentWord);
			printf("用户词典:%s\n", commentWordUser);
		}
		system("pause");
		system("cls");
	}
	//展示用户自己添加的单词

	//展示用户在原有单词添加的新解释
}

Dict* UserDict()
{
	Dict *head = NULL;
	Dict *current = NULL;
	Dict *prev = NULL;
	FILE *fp;
	if ((fp = fopen("UserDict.txt", "r")) == NULL)
	{
		perror("读取失败\n");
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
		printf("打开失败\n");

	}
	fputs(keyWord, fp);
	fputc('\n', fp);
	printf("请输入解释:\n");
	scanf("%s", commentWord);
	fputs(commentWord, fp);
	fputc('\n', fp);
	fclose(fp);

}

//查询用户的字符
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

	printf("请输入你要添加的单词\n");
	char keyWord[KEY_NUM];
	Input_key(keyWord);
	if ((SearchUserDict(keyWord,userhead))==NULL)
	{
		AddNewWord(keyWord);
	}
	else
	{
		int num;
		printf("该单词已经添加过了,是否追加解释\n");
		printf("1  是  2  否\n");
		
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



/*********************************************/ 
