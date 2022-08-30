#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#pragma warning(disable:4996)
void make_menu();//建立菜单
void input_information(); //信息录入
void delete_information();//信息删除
void modify_information();//信息修改
void browse_information();//信息浏览
void seek_information();//信息查找

//人员信息结构体
struct people
{
	char name[20];
	int age;
	char phone[12];
	int building_num;
	int unit_num;
	int room_num;
	char entry_time[15];
	char exit_time[15];
	//......
};
//定义结点的数据结构
struct Node
{
	struct people data;
	struct Node* next;
};
//链表初始化
struct Node* list = NULL;
//建立头结点
struct Node* create_headNode()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}
//建立新结点
struct Node* create_newNode(struct people data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//插入结点建立链表
void link_Node(struct Node* headNode, struct people data)
{
	struct Node* newNode = create_newNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
//针对链表读操作
void readFile(struct Node* headnode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if (fp == NULL)
	{
		fp = fopen(fileURL, "w+");
		fclose(fp);
		return;
	}
	struct people data;
	while (fscanf(fp, "%s\t%d\t%s\t%d\t%d\t%d\t%s\t%s\n", 
		data.name, &data.age, &data.phone,
		&data.building_num,&data.unit_num,&data.room_num,
		data.entry_time,data.exit_time) != EOF)
	{
		link_Node(list, data);
	}
	fclose(fp);
}
//针对链表写操作
void saveFile(struct Node* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "w");
	struct Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		fprintf(fp, "%s\t%d\t%s\t%d\t%d\t%d\t%s\t%s\n",
			pMove->data.name,
			pMove->data.age,
			pMove->data.phone,
			pMove->data.building_num,
			pMove->data.unit_num,
			pMove->data.room_num,
			pMove->data.entry_time,
			pMove->data.exit_time);
		pMove = pMove->next;
	}
}
//主函数
int main()
{
	list = create_headNode();
	readFile(list, "people.xls");
	while (1)
	{
		make_menu();
		system("pause");
		system("cls");
	}
	return 0;
}
//建立菜单
void make_menu()
{
	int userkey = 0;

	printf("----------------新冠疫情社区人员管理系统1.0----------------\n");
	printf("\t\t\t0.退出系统\n");
	printf("\t\t\t1.信息录入\n");
	printf("\t\t\t2.信息浏览\n");
	printf("\t\t\t3.信息删除\n");
	printf("\t\t\t4.信息修改\n");
	printf("\t\t\t5.信息查找\n");
	printf("-----------------------------------------------------------\n");
	printf("请输入你选择（0-5）：");

	scanf_s("%d", &userkey);
	switch (userkey)
	{
	case 0:
		printf("退出系统成功！\n");
		system("pause");
		exit(0);
		break;
	case 1:
		input_information();
		break;
	case 2:
		browse_information();
		break;
	case 3:
		delete_information();
		break;
	case 4:
		modify_information();
		break;
	case 5:
		seek_information();
		break;
	default:
		break;
	}
}
//信息查找
void seek_information()
{
	struct people data;
	printf("请输入要查找人员的姓名：");
	scanf_s("%s",data.name,20 );
	struct Node* pMove = list->next;
	while (pMove != NULL && strcmp(pMove->data.name, data.name) != 0)
	{
		pMove = pMove->next;
	}
	if ( pMove != NULL)
	{
		printf("姓名\t年龄\t电话\t\t楼号\t单元\t房间号\t\t进入时间\t\t出去时间\n");
		printf("%s\t%d\t%s\t%d\t%d\t%d\t\t%s\t\t%s\n",
			pMove->data.name,
			pMove->data.age,
			pMove->data.phone,
			pMove->data.building_num,
			pMove->data.unit_num,
			pMove->data.room_num,
			pMove->data.entry_time,
			pMove->data.exit_time);
	}
	else
	{
		printf("未找到相关信息！\n");
	}
}
//信息录入
void input_information()
{
	struct people data;
	printf("请输入人员信息\n");
	printf("姓名："); scanf_s("%s", data.name, 20); 
	printf("年龄："); scanf_s("%d", &data.age); 
	printf("电话："); scanf_s("%s", data.phone, 12); 
	printf("楼号："); scanf_s("%d", &data.building_num); 
	printf("单元："); scanf_s("%d", &data.unit_num); 
	printf("房间号："); scanf_s("%d", &data.room_num); 
	printf("进入时间（例02.01_13:01)："); scanf_s("%s", data.entry_time, 15); 
	printf("出去时间（例02.01_13:01)："); scanf_s("%s", data.exit_time, 15); 
	link_Node(list, data);
	saveFile(list, "people.xls");
	printf("录入成功！...\n");
}
//信息删除
void delete_information()
{
	struct people data;
	printf("请输入要删除人员姓名：\n");
	scanf_s("%s", data.name,20);
	struct Node* preNode = list;
	struct Node* posNode = list->next;
	while (posNode != NULL && strcmp(posNode->data.name,data.name ) != 0)
	{
		preNode = posNode;
		posNode = preNode->next;
	}
	if (posNode != NULL)
	{
		preNode->next = posNode->next;
		free(posNode);
		printf("删除成功\n");
	}
	saveFile(list, "people.xls");
}
//信息修改
void modify_information()
{
	struct people data;
	printf("请输入要修改人员姓名:");
	scanf_s("%s",data.name,20);
	struct Node* pMove = list->next;
	while (pMove != NULL && strcmp(pMove->data.name , data.name) != 0 )
	{
		pMove = pMove->next;
	}
	if (pMove != NULL)
	{
		printf("0.姓名\t1.年龄\t2.电话\t3.楼号\t4.单元\t5.房间号\t6.进入时间（例02.01_13:01)\t7.出去时间（例02.01_13:01)");
		printf("请输入需要更改的项目：");
		int userkey = 0;
		scanf_s("%d", &userkey);
		switch (userkey)
		{
		case 0:
			printf("请输入该人员的新信息\n");
			printf("姓名："); 
			scanf_s("%s", pMove->data.name, 20);
			break;
		case 1:
			printf("请输入该人员的新信息\n");
			printf("年龄：");
			scanf_s("%d", &pMove->data.age);
			break;
		case 2:
			printf("请输入该人员的新信息\n");
			printf("电话："); 
			scanf_s("%s", pMove->data.phone, 12);
			break;
		case 3:
			printf("请输入该人员的新信息\n");
			printf("楼号：");
			scanf_s("%d", &pMove->data.building_num);
			break;
		case 4:
			printf("请输入该人员的新信息\n");
			printf("单元：");
			scanf_s("%d", &pMove->data.unit_num);
			break;
		case 5:
			printf("请输入该人员的新信息\n");
			printf("房间号：");
			scanf_s("%d", &pMove->data.room_num);
			break;
		case 6:
			printf("请输入该人员的新信息\n");
			printf("进入时间（例02.01_13:01)：");
			scanf_s("%s", pMove->data.entry_time, 15);
			break;
		case 7:
			printf("请输入该人员的新信息\n");
			printf("出去时间（例02.01_13:01)：");
			scanf_s("%s", pMove->data.exit_time, 15);
			printf("修改成功!\n");
			break;
		default:
			break;
		}
		saveFile(list, "people.xls");
		printf("修改成功!\n");
	}
	else
	{
		printf("未找到相关信息!无法修改\n");
	}
}
//信息浏览
void browse_information()
{
	struct Node* pMove = list->next;
	printf("姓名\t年龄\t电话\t\t楼号\t单元\t房间号\t\t进入时间\t\t出去时间\n");
	while (pMove != NULL)
	{
		printf("%s\t%d\t%s\t%d\t%d\t%d\t\t%s\t\t%s\n",
			pMove->data.name,
			pMove->data.age,
			pMove->data.phone,
			pMove->data.building_num,
			pMove->data.unit_num,
			pMove->data.room_num,
			pMove->data.entry_time,
			pMove->data.exit_time);
		pMove = pMove->next;
	}
	printf("\n");
}
