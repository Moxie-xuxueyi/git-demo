#include "stdio.h"
#include  "malloc.h"
#include "stdlib.h"

#define size 50
int password[50];

//定义循环链表的存储结构 
typedef struct node
{
	int data;	//存储节点序号
	int word; 	//存储密码
	struct node *next; 
}Node;

//定义线性表的存储结构
typedef struct list
{
	int data[size]; //数据域
	int word[size];
	int length; 
 }seqList;
 
 //循环链表创建
 Node *createCircular(int n)
 {
 	int i; 
 	Node *tail; 	//定义尾指针
	Node *temp;		//用于存储创建节点是返回的地址
	tail = (Node *)malloc(sizeof(Node)); //尾指针存储新建的节点地址
	tail->data = 1;
	tail->word = password[1];
	tail->next=	tail;
	for(i=2;i<=n;i++)
	{
		temp = (Node *)malloc(sizeof(Node));	 
		temp->data = i;
		temp->word = password[i];
		temp->next = tail->next;	//在头节点前插入节点 
		tail->next = temp;		   //将头指针指向新的节点 
		tail = temp;				//将新建节点的地址视为尾指针 
	  }  
	  return tail;
  } 

//循环链表解决约舍夫环问题
void circular(Node *tail)
{
	Node *pre = tail, *p = tail->next, *q;
	int count = 1;
	int newPassword = 20;
	printf("出环顺序:\t");
	while(p->next != p) //p指向第一个节点，当环中只剩下一个元素的时候退出循环
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
		 newPassword = p->word;				//更改密码 
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
	
	//用静态链表结局问题 
	void List_2(seqList *L)
	{
		int i;
		int p = 0; //p为数组中初始下标
		int newPassword = 20; 
		printf("出环顺序:\t");
		while(L->length != 0)
		{
			p = p + newPassword-1;
			p = p % L->length;
			printf("%-3d",L->data[p]);
			
			for(i=p;i<L->length-1;i++)
			{
				L->data[i] = L->data[i+1];//将数组下标i后移一位 
				L->word[i] = L->word[i+1];
			}
			L->length--;//线性表长度减一 
		 } 
	}
	
	void menu()
	{
		printf("*************约瑟夫问题***********\n\n");
		printf("1.用单循环链表实现约瑟夫环\n");
		printf("2.用顺序表实现约瑟夫环\n"); 
	}
	
	int getPassWord(int a){
	password[0] = 20;
	printf("\n请输入密码：\n"); 
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
		printf("请输入约瑟夫环的长度:\t");
		scanf("%d",&n);
		getPassWord(n);
		menu();
		do
		{
			printf("请输入约瑟夫环的长度:\t");
			scanf("%d",&n);
			getPassWord(n);
			menu();
			printf("\n请选择功能：\t");
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
			printf("\n是否继续？（y/n）\n");
			scanf(" %c", &ch);
		}while(ch =='y');
		return 0;
	 } 
