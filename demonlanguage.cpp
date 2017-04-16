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

///栈结构体
typedef struct
{
	selemtype *base;
	selemtype *top;
	int stacksize;
 } sqstack;
 
 //初始化栈
 status initStack(sqstack *stack)
 {
 	stack->base = (selemtype *) malloc (stack_init_size*sizeof(selemtype));
 	if(!stack->base) exit(OVERFLOW);
 	stack->top = stack->base;
 	stack->stacksize = stack_init_size;
 	return 1;
  } 
  
  //进栈
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
   
   //出栈
   status pop(sqstack *stack, selemtype *e)
   {
   	if(stack->top == stack->base) return -1;
   	*e=*(--(stack->top));
   	return 1;
	} 
	
	//队列结构(链表)
	typedef struct qNode{
		qelemtype data;
		struct qNode *next;
	}qNode,*queueptr;
	
	typedef struct
	{
		queueptr front;
		queueptr rear;	
	}linkqueue;
	
	//初始化队列
	status initQueue(linkqueue *queue)
	{
		queue->front = queue->rear = (queueptr)malloc(sizeof(qNode));
		if(!(queue->front)) exit(OVERFLOW);
		queue->front->next = NULL;
	 } 
	 
	 //入队
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
	  
	  //出队
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
	   
	//括号内元素入栈处理
	void tempStack(sqstack *temp)
	{
		int i=0;
		char t;
		char c;
		c=demon[i];
		for(i=0;c != '#';i++)
		{
			c=demon[i];
			if(c=='(') //遇到左括号 
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
			pop(temp,&t);		//将多余的首字母出栈 
			pop(temp,&t);		//将多余的）出栈 
		}
	 } 
}
	 
	 //特殊入队函数
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
	  	int flag=0; //判断大写字母
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
				printf("一个");
				i++;
				break;
			case 'e':
				printf("哈");
				i++;
				break;
			default :
				printf("一个一个");
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
	printf("\n\n\n\t\t\t魔王语言！\n");
	 printf("\t***************************************\n");
	 printf("\t输入魔王的语言：\n\t"); 
    printf("！请以‘#’作为结束 \n\t");
	printf("例子：B(ehnxgz)B\n") ;
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
    	 while(queue1.front!=queue1.rear) /*重写demon[i ]*/ 
            { 
            qPop(&queue1,&e); 
            demon[k]=e; 
            k++; 
            } 
        demon[k]='#'; 
        } 
        demon[k]='\0';
        printf("\n\t翻译成人话为:\n\t%s",demon); 
    printf("\n\n\t***************************************\n");
    if(!strcmp(demon,"tseadseaezegexenehetseadsea")){ printf("\t只鹅地上一只鹅鹅追鹅赶鹅下鹅蛋鹅恨鹅天上一只鹅地上一只鹅\n");} 
    print(demon);

    printf("\n\t\t\t欢迎使用!\n\t");
    printf("回车键退出！");
if(getchar()) exit(1);
	}
