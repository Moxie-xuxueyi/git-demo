#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2
#define MAXSIZE 100
#define stack_init_size  100 
#define stackincrement   10 

typedef char selemtype;
typedef char qelemtype;
typedef char elemtype;
typedef int status;

char  e;
char demon[MAXSIZE];

///ջ�ṹ��
typedef struct
{
	selemtype *base;
	selemtype *top;
	int stacksize;
 } sqstack;
 
 //��ʼ��ջ
 status initStack(sqstack *stack)
 {
 	stack->base = (selemtype *) malloc (stack_init_size*sizeof(selemtype));
 	if(!stack->base) exit(OVERFLOW);
 	stack->top = stack->base;
 	stack->stacksize = stack_init_size;
 	return 1;
  } 
  
  //��ջ
  status push(sqstack *stack, selemtype e)
  {
  	if(stack->top - stack->base == stack->stacksize)
  	{
  		stack->base =(selemtype *) realloc(stack->base,(stack->stacksize+stackincrement)*sizeof(selemtype));
  		if(!stack->base) exit(OVERFLOW);
  		stack->top = stack->base + stack->stacksize;
  		stack->stacksize+=stackincrement; 
	}
	*(stack->top++)=e;
	return 1;
   } 
   
   //��ջ
   status pop(sqstack *stack, selemtype *e)
   {
   	if(stack->top == stack->base) return -1;
   	*e=*(--(stack->top));
   	return 1;
	} 
	
	//���нṹ(����)
	typedef struct qNode{
		qelemtype data;
		struct qNode *next;
	}qNode,*queueptr;
	
	typedef struct
	{
		queueptr front;
		queueptr rear;	
	}linkqueue;
	
	//��ʼ������
	status initQueue(linkqueue *queue)
	{
		queue->front = queue->rear = (queueptr)malloc(sizeof(qNode));
		if(!(queue->front)) exit(OVERFLOW);
		queue->front->next = NULL;
	 } 
	 
	 //���
	 status qPush(linkqueue *queue, qelemtype e)
	 {
	 	if(!queue->front) exit(OVERFLOW);
	 	queueptr p;
	 	p = (queueptr)malloc(sizeof(qNode));
	 	if(!p) exit(OVERFLOW);
	 	p->data = e;
	 	p->next = NULL;
	 	queue->rear->next = p;
	 	queue->rear=p;
	 	return 1;
	  } 
	  
	  //����
	  status qPop(linkqueue *queue,qelemtype *e)
	  {
	  	queueptr p;
	  	if(queue->front == queue->rear) return -1;
	  	p = queue->front->next;
	  	*e = p->data;
	  	queue->front->next = p->next;
	  	if(queue->rear == p) queue->rear = queue->front;
	  	free(p);
	  	return 1;
	   } 
	   
	//������Ԫ����ջ����
	void tempStack(sqstack *temp)
	{
		int i=0;
		char t;
		char c;
		c=demon[i];
		for(i=0;c != '#';i++)
		{
			c=demon[i];
			if(c=='(') //���������� 
			{
				t=demon[i+1];
				push(temp,t);
				i++;
			
			do
			{
				i++;
				c=demon[i];
				push(temp,c);
				push(temp,t);
			}while(c != ')');
			pop(temp,&t);		//�����������ĸ��ջ 
			pop(temp,&t);		//������ģ���ջ 
		}
	 } 
}
	 
	 //������Ӻ���
	 void spenqueue(linkqueue *queue, char key)
	 {
	 	int j = 0;
	 	char a[5];
	 	switch(key)
	 	{
	 		case 'A':strcpy(a,"sea"); break;
	 		case 'B':strcpy(a,"tAdA"); break;
	 		case 'C':strcpy(a,"abc"); break;
			case 'D':strcpy(a,"def"); break;
			default:strcpy(a,"???"); 
		 }
		 while(a[j]!='\0')
		 {
		 	qPush(queue,a[j]);
		 	j++;
		 }
	  } 
	  
	  status sort(sqstack *stack, linkqueue *queue)
	  {
	  	qNode b;
	  	int flag=0; //�жϴ�д��ĸ
		int i;
		for(i=0;demon[i]!='#';i++)
		{
			b.data=demon[i];
			if(('a'<=b.data&&b.data<='z') || b.data=='?') qPush(queue,b.data);
			else
			{
				if('A'<=b.data && b.data<='Z')
				{
					spenqueue(queue,b.data);
					flag=1;
				}
				else{
					if(b.data=='(')
					{
						do{
							pop(stack,&e);
							qPush(queue,e);
						}while(!(stack->top==stack->base));
						while(b.data!=')'){
							i++;
							b.data=demon[i];
						}
					}
				}
			}
		 } 
		 return flag;
	  }

void print(char word[100]){
	int i=0;
	while(word[i] != NULL )
	{
		switch(word[i])
		{
			case 'a':
				printf("һ��");
				i++;
				break;
			case 'e':
				printf("��");
				i++;
				break;
			default :
				printf("һ��һ��");
				i++;
				break; 
		}
	}
}

status main(){
	sqstack stack1;
	linkqueue queue1;
	int k=0;
	int flag=1;
	printf("\n\n\n\t\t\tħ�����ԣ�\n");
	 printf("\t***************************************\n");
	 printf("\t����ħ�������ԣ�\n\t"); 
    printf("�����ԡ�#����Ϊ���� \n\t");
	printf("���ӣ�B(ehnxgz)B\n") ;
    printf("\t***************************************\n\t");
    scanf("%s",demon); 
    printf("\n\t***************************************"); 
    initStack(&stack1);
    initQueue(&queue1);
    tempStack(&stack1);
    while(flag==1)
    {
    	k=0;
    	flag=sort(&stack1,&queue1);
    	 while(queue1.front!=queue1.rear) /*��дdemon[i ]*/ 
            { 
            qPop(&queue1,&e); 
            demon[k]=e; 
            k++; 
            } 
        demon[k]='#'; 
        } 
        demon[k]='\0';
        printf("\n\t������˻�Ϊ:\n\t%s",demon); 
    printf("\n\n\t***************************************\n");
    if(!strcmp(demon,"tseadseaezegexenehetseadsea")){ printf("\tֻ�����һֻ���׷��϶��¶쵰��޶�����һֻ�����һֻ��\n");} 
    print(demon);

    printf("\n\t\t\t��ӭʹ��!\n\t");
    printf("�س����˳���");
if(getchar()) exit(1);
	}
