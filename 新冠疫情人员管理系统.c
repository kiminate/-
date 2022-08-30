#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#pragma warning(disable:4996)
void make_menu();//�����˵�
void input_information(); //��Ϣ¼��
void delete_information();//��Ϣɾ��
void modify_information();//��Ϣ�޸�
void browse_information();//��Ϣ���
void seek_information();//��Ϣ����

//��Ա��Ϣ�ṹ��
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
//����������ݽṹ
struct Node
{
	struct people data;
	struct Node* next;
};
//�����ʼ��
struct Node* list = NULL;
//����ͷ���
struct Node* create_headNode()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}
//�����½��
struct Node* create_newNode(struct people data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//�����㽨������
void link_Node(struct Node* headNode, struct people data)
{
	struct Node* newNode = create_newNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
//������������
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
//�������д����
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
//������
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
//�����˵�
void make_menu()
{
	int userkey = 0;

	printf("----------------�¹�����������Ա����ϵͳ1.0----------------\n");
	printf("\t\t\t0.�˳�ϵͳ\n");
	printf("\t\t\t1.��Ϣ¼��\n");
	printf("\t\t\t2.��Ϣ���\n");
	printf("\t\t\t3.��Ϣɾ��\n");
	printf("\t\t\t4.��Ϣ�޸�\n");
	printf("\t\t\t5.��Ϣ����\n");
	printf("-----------------------------------------------------------\n");
	printf("��������ѡ��0-5����");

	scanf_s("%d", &userkey);
	switch (userkey)
	{
	case 0:
		printf("�˳�ϵͳ�ɹ���\n");
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
//��Ϣ����
void seek_information()
{
	struct people data;
	printf("������Ҫ������Ա��������");
	scanf_s("%s",data.name,20 );
	struct Node* pMove = list->next;
	while (pMove != NULL && strcmp(pMove->data.name, data.name) != 0)
	{
		pMove = pMove->next;
	}
	if ( pMove != NULL)
	{
		printf("����\t����\t�绰\t\t¥��\t��Ԫ\t�����\t\t����ʱ��\t\t��ȥʱ��\n");
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
		printf("δ�ҵ������Ϣ��\n");
	}
}
//��Ϣ¼��
void input_information()
{
	struct people data;
	printf("��������Ա��Ϣ\n");
	printf("������"); scanf_s("%s", data.name, 20); 
	printf("���䣺"); scanf_s("%d", &data.age); 
	printf("�绰��"); scanf_s("%s", data.phone, 12); 
	printf("¥�ţ�"); scanf_s("%d", &data.building_num); 
	printf("��Ԫ��"); scanf_s("%d", &data.unit_num); 
	printf("����ţ�"); scanf_s("%d", &data.room_num); 
	printf("����ʱ�䣨��02.01_13:01)��"); scanf_s("%s", data.entry_time, 15); 
	printf("��ȥʱ�䣨��02.01_13:01)��"); scanf_s("%s", data.exit_time, 15); 
	link_Node(list, data);
	saveFile(list, "people.xls");
	printf("¼��ɹ���...\n");
}
//��Ϣɾ��
void delete_information()
{
	struct people data;
	printf("������Ҫɾ����Ա������\n");
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
		printf("ɾ���ɹ�\n");
	}
	saveFile(list, "people.xls");
}
//��Ϣ�޸�
void modify_information()
{
	struct people data;
	printf("������Ҫ�޸���Ա����:");
	scanf_s("%s",data.name,20);
	struct Node* pMove = list->next;
	while (pMove != NULL && strcmp(pMove->data.name , data.name) != 0 )
	{
		pMove = pMove->next;
	}
	if (pMove != NULL)
	{
		printf("0.����\t1.����\t2.�绰\t3.¥��\t4.��Ԫ\t5.�����\t6.����ʱ�䣨��02.01_13:01)\t7.��ȥʱ�䣨��02.01_13:01)");
		printf("��������Ҫ���ĵ���Ŀ��");
		int userkey = 0;
		scanf_s("%d", &userkey);
		switch (userkey)
		{
		case 0:
			printf("���������Ա������Ϣ\n");
			printf("������"); 
			scanf_s("%s", pMove->data.name, 20);
			break;
		case 1:
			printf("���������Ա������Ϣ\n");
			printf("���䣺");
			scanf_s("%d", &pMove->data.age);
			break;
		case 2:
			printf("���������Ա������Ϣ\n");
			printf("�绰��"); 
			scanf_s("%s", pMove->data.phone, 12);
			break;
		case 3:
			printf("���������Ա������Ϣ\n");
			printf("¥�ţ�");
			scanf_s("%d", &pMove->data.building_num);
			break;
		case 4:
			printf("���������Ա������Ϣ\n");
			printf("��Ԫ��");
			scanf_s("%d", &pMove->data.unit_num);
			break;
		case 5:
			printf("���������Ա������Ϣ\n");
			printf("����ţ�");
			scanf_s("%d", &pMove->data.room_num);
			break;
		case 6:
			printf("���������Ա������Ϣ\n");
			printf("����ʱ�䣨��02.01_13:01)��");
			scanf_s("%s", pMove->data.entry_time, 15);
			break;
		case 7:
			printf("���������Ա������Ϣ\n");
			printf("��ȥʱ�䣨��02.01_13:01)��");
			scanf_s("%s", pMove->data.exit_time, 15);
			printf("�޸ĳɹ�!\n");
			break;
		default:
			break;
		}
		saveFile(list, "people.xls");
		printf("�޸ĳɹ�!\n");
	}
	else
	{
		printf("δ�ҵ������Ϣ!�޷��޸�\n");
	}
}
//��Ϣ���
void browse_information()
{
	struct Node* pMove = list->next;
	printf("����\t����\t�绰\t\t¥��\t��Ԫ\t�����\t\t����ʱ��\t\t��ȥʱ��\n");
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
