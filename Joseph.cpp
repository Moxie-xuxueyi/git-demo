#include "stdio.h"
#include  "malloc.h"
#include "stdlib.h"

#define size 50
int password[50];

//����ѭ������Ĵ洢�ṹ 
typedef struct node
{
	int data;	//�洢�ڵ����
	int word; 	//�洢����
	struct node *next; 
}Node;

//�������Ա�Ĵ洢�ṹ
typedef struct list
{
	int data[size]; //������
	int word[size];
	int length; 
 }seqList;
 
 //ѭ��������
 Node *createCircular(int n)
 {
 	int i; 
 	Node *tail; 	//����βָ��
	Node *temp;		//���ڴ洢�����ڵ��Ƿ��صĵ�ַ
	tail = (Node *)malloc(sizeof(Node)); //βָ��洢�½��Ľڵ��ַ
	tail->data = 1;
	tail->word = password[1];
	tail->next=	tail;
	for(i=2;i<=n;i++)
	{
		temp = (Node *)malloc(sizeof(Node));	 
		temp->data = i;
		temp->word = password[i];
		temp->next = tail->next;	//��ͷ�ڵ�ǰ����ڵ� 
		tail->next = temp;		   //��ͷָ��ָ���µĽڵ� 
		tail = temp;				//���½��ڵ�ĵ�ַ��Ϊβָ�� 
	  }  
	  return tail;
  } 

//ѭ��������Լ�������
void circular(Node *tail)
{
	Node *pre = tail, *p = tail->next, *q;
	int count = 1;
	int newPassword = 20;
	printf("����˳��:\t");
	while(p->next != p) //pָ���һ���ڵ㣬������ֻʣ��һ��Ԫ�ص�ʱ���˳�ѭ��
	{
		if(count < newPassword)
		{
			pre = p;
			p = p->next;
			count++; 
		 }
		 else
		 {
		 printf("%-3d",p->data);
		 q = p;
		 newPassword = p->word;				//�������� 
		 pre->next = p->next;
		 p = pre->next;
		 free(q);
		 count = 1;
		 }
		 } 
		 printf("%-3d\n",p->data);
		 free(p);
		 return;
	} 
	
	void Creat_2(seqList *L, int n)
	{
		int i;
		for(i=0;i<n;i++)
		{
			L->data[i] = i+1; 
			L->word[i] = password[i+1];
		}
		L->length = n;
	}
	
	//�þ�̬���������� 
	void List_2(seqList *L)
	{
		int i;
		int p = 0; //pΪ�����г�ʼ�±�
		int newPassword = 20; 
		printf("����˳��:\t");
		while(L->length != 0)
		{
			p = p + newPassword-1;
			p = p % L->length;
			printf("%-3d",L->data[p]);
			
			for(i=p;i<L->length-1;i++)
			{
				L->data[i] = L->data[i+1];//�������±�i����һλ 
				L->word[i] = L->word[i+1];
			}
			L->length--;//���Ա��ȼ�һ 
		 } 
	}
	
	void menu()
	{
		printf("*************Լɪ������***********\n\n");
		printf("1.�õ�ѭ������ʵ��Լɪ��\n");
		printf("2.��˳���ʵ��Լɪ��\n"); 
	}
	
	int getPassWord(int a){
	password[0] = 20;
	printf("\n���������룺\n"); 
	for(int j=1;j<a+1;j++)
	{
		scanf("%d",password+j);
	 }
	 return 1; 
	
	/*for(int k=0;k<a+1;k++)
	{
	printf("%d",password[k]);
	printf("  ");
	}	
	getchar();*/
	}
	
	int main()
	{
		int n,m,choose;
		char ch;
		Node *tail = NULL;
		seqList L;
		printf("������Լɪ�򻷵ĳ���:\t");
		scanf("%d",&n);
		getPassWord(n);
		menu();
		do
		{
			printf("������Լɪ�򻷵ĳ���:\t");
			scanf("%d",&n);
			getPassWord(n);
			menu();
			printf("\n��ѡ���ܣ�\t");
			scanf("%d",&choose);
			switch(choose)
			{
				case 1:
					{
						tail = createCircular(n);
						circular(tail);
						break;
					}
				case 2:
				{
					Creat_2(&L,n);
					List_2(&L);
					break;
				}
				default:printf("error\n");
			}
			printf("\n�Ƿ��������y/n��\n");
			scanf(" %c", &ch);
		}while(ch =='y');
		return 0;
	 } 
