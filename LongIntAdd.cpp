#include<stdio.h>
#include<stdlib.h>
#include<conio.h>


typedef struct node
{
    int data;
    struct node *pre;
    struct node *next;
}DataNode;

int CF;

DataNode* Input()
{
    char ch[50];
    DataNode  *temp,*node;
    int count=0,count1=0,i,j,n,sum=0;
    scanf("%s",ch);
    while(ch[count++]!='\0');
    count--;
    node=(DataNode*)malloc(sizeof(DataNode));
    temp=node;
    count1++;
        if(ch[0]=='-'||ch[0]=='+')
        {
       if((count-1)%2)
          count1+=(count-1)/2+1;
           else
          count1+=(count-1)/2;
        }
        else
        {
     if(count%2)
       count1+=count/2+1;
        else
        count1+=count/2;
        }

    count--;
    for(i=1;i<count1;i++)
    {
       temp->pre=(DataNode*)malloc(sizeof(DataNode));
       temp->pre->next=temp;
       temp=temp->pre;
       temp->data=0;
       for(j=0;j<2&&ch[count]!='-'&&ch[count]!='+';j++)
       {
           if(count<0) break;
           sum=ch[count--]-'0';
           for(n=0;n<j;n++)
           sum*=10;
           temp->data+=sum;
       }
    }
    temp->pre=node;
    node->next=temp;
    if(ch[0]=='-')
        count1=0-count1;
    node->data=count1;
        return node;
}
void Output(DataNode *node)
{
    int n,i;
    DataNode  *temp;
    n=node->data;
    temp=node->next;
    if(n<0)
    {
    printf("\n-");
    n=0-n;
    }
    for(i=0;i<n-1;i++)
    {
       if((n-1-i)%2==0&&i!=0)
       printf(",");
       if(n==1)
       {
       printf("%d",temp->data);
       break;
       }
       if(i==0)
       printf("%d",temp->data);
       else if(i==n-2)
        printf("%02d",temp->data);
            else
        printf("%02d",temp->data);
       temp=temp->next;
    }
}
int test(DataNode *node1,DataNode *node2)
{
    DataNode *temp1,*temp2;
    int i,count;
    temp1=node1;
    temp2=node2;
    if(abs(temp1->data)>abs(temp2->data))
        return 1;
    else if(abs(temp1->data)<abs(temp2->data))
         return 2;
         else
         {
         count=abs(temp1->data);
         for(i=1;i<count;i++)
         {
             temp1=temp1->next;
             temp2=temp2->next;
             if((temp1->data)>(temp2->data))
             return 1;
             if((temp1->data)>(temp2->data))
             return 2;
             if((temp1->data)==(temp2->data))
             if(i==count-1)
                 return 0;
         }
         }
}
DataNode* add(DataNode *node1,DataNode *node2)
{
    int i,flag,max,min;
    DataNode *temp1,*temp2;
    DataNode *result,*temp;
    result=(DataNode*)malloc(sizeof(DataNode));
    if((node1->data)*(node2->data)>0)
    {
        if(abs(node1->data)>abs(node2->data))
        {
            max=abs(node1->data);
            min=abs(node2->data);
            flag=1;
        }
        else
        {
            max=abs(node2->data);
            min=abs(node1->data);
            flag=2;
        }
    CF=0;
    temp1=node1->pre;
    temp2=node2->pre;
    temp=result;
    for(i=1;i<max;i++)
    {
        temp->pre=(DataNode*)malloc(sizeof(DataNode));
        temp->pre->next=temp;
        temp=temp->pre;
        if(i<min)
        {
        temp->data=(temp1->data+temp2->data+CF)%100;
        CF=(temp1->data+temp2->data+CF)/100;
                temp1=temp1->pre;
                temp2=temp2->pre;
        }
        else  if(flag==1)
          {
              temp->data=(temp1->data+CF)%100;
              CF=(temp1->data+CF)/100;
              temp1=temp1->pre;
          }
          else
          {
              temp->data=(temp2->data+CF)%100;
              CF=(temp2->data+CF)/100;
              temp2=temp2->pre;
          }
    }
    if(CF!=0)
    {
        max++;
        temp->pre=(DataNode*)malloc(sizeof(DataNode));
        temp->pre->next=temp;
        temp=temp->pre;
        temp->data=CF;
    }
    temp->pre=result;
    result->next=temp;
    if((node1->data)<0)
        max=0-max;
    result->data=max;
    return result;
    }
    else
    {
    switch(test(node1,node2))
    {
        case 0:result->data=2;
           result->next=(DataNode*)malloc(sizeof(DataNode));
           result->next->data=0;
           result->next->pre=result;
           result->pre=result->next;
           return result;
        case 1:CF=0;
           max=abs(node1->data);
           min=abs(node2->data);
           temp1=node1->pre;
           temp2=node2->pre;
           temp=result;
           for(i=1;i<max;i++)
           {
               temp->pre=(DataNode*)malloc(sizeof(DataNode));
               temp->pre->next=temp;
               temp=temp->pre;
               if(i<min)
               {
               if((temp1->data)>(temp2->data))
                   temp->data=(temp1->data)-(temp2->data)+CF;
               else if((temp1->data)<(temp2->data))
                {
                    temp->data=100+(temp1->data)-(temp2->data)+CF;
                    CF=-1;
                }
                else
                {
                    if(CF!=0)
                    {
                    temp->data=100+CF;
                    CF=-1;
                    }
                    else
                    temp->data=0;
                }
               }
               else
               {
               if(temp1->data==0)
               {
                   temp->data=(temp1->data)+CF+100;
                   CF=-1;
               }
               else
               {
                   temp->data=(temp1->data)+CF;
                   CF=0;
               }
               }
               temp1=temp1->pre;
               temp2=temp2->pre;
           }
           temp->pre=result;
           result->next=temp;
           result->data=node1->data;break;
             case 2:CF=0;
           max=abs(node2->data);
           min=abs(node1->data);
           temp1=node1->pre;
           temp2=node2->pre;
           temp=result;
           for(i=1;i<max;i++)
           {
               temp->pre=(DataNode*)malloc(sizeof(DataNode));
               temp->pre->next=temp;
               temp=temp->pre;
               if(i<min)
               {
               if((temp2->data)>(temp1->data))
                   temp->data=(temp2->data)-(temp1->data)+CF;
               else if((temp2->data)<(temp1->data))
                {
                    temp->data=100+(temp2->data)-(temp1->data)+CF;
                    CF=-1;
                }
                else
                {
                    if(CF!=0)
                    {
                    temp->data=100+CF;
                    CF=-1;
                    }
                    else
                    temp->data=0;

                }
               }
               else
               {
               if(temp2->data==0)
               {
                   temp->data=(temp2->data)+CF+100;
                   CF=-1;
               }
               else
               {
                   temp->data=(temp2->data)+CF;
                   CF=0;
               }
               }
               temp1=temp1->pre;
               temp2=temp2->pre;
           }
           temp->pre=result;
           result->next=temp;
           result->data=node2->data;break;
    }
    while((result->next->data)==0)
    {
        if(abs(result->data)==2)
        break;
        temp=result->next;
        result->next=temp->next;
        result->next->pre=result;
        if((result->data)>0)
        (result->data)--;
        else
        (result->data)++;
    }
    return result;
    }
}


int main()
{
    DataNode *data1,*data2,*result;
    char key;
    printf("请输入需要进行的操作：\n");
	printf("\t1.输入数据\n\t2.退出\n") ; 
    int i,flag=0;
   
    scanf("%c",&key);
    while(key!='3')
    {
    switch(key)
    {
        case '1':system("cls");
             printf("请输入第一个数据:");
             data1=Input();
             printf("\n请输入第二个数据:");
             data2=Input();
             flag=1;
             if(flag==0)
             {
             system("cls");
             printf("\n数据不存在");
             }
             else
             {
             system("cls");
             result=add(data1,data2);
             printf("\n结果是：");
             Output(result);
             getch();
         }
             break;
        case '2':if(flag==0)
             {
             system("cls");
             printf("\n数据不存在");
             }
             else
             {
             system("cls");
             result=add(data1,data2);
             printf("\n结果是：");
             Output(result);
             getch();
             }
             break;

    }
    system("cls");
    scanf("%c",&key);
    }
}

