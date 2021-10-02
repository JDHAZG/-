#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>


int outcome[50000],rem[50000];
typedef struct clause_elem{
	int elem;
	struct clause_elem *next_elem;
	bool is_delete;//判断文字是否被删除 
}clause_elem;
typedef struct rootclause{
	clause_elem *root;
	struct rootclause *next_root;
	bool is_delete;//判断子句是否被删除 
	int length;
}clause_root;



clause_elem* is_single_clause(clause_root *root_head)//判断是否为单子句的函数 
{
	int num=0;//统计文字数 
	clause_root *p1,*p2;
	clause_elem *p,*q,*temp;
	for(p1=root_head;p1->next_root!=NULL;p1=p1->next_root)
	{
		num=0;
		if(p1->is_delete==true)
		continue;
		p=p1->root;
		while(p->next_elem!=NULL)
		{
			if(p->is_delete!=true)
			{
				temp=p;
				num++;
			}	
			p=p->next_elem;
		}
		if(num==1)
		{
			if(temp->elem>0)
			outcome[temp->elem]=temp->elem;
			else if(temp->elem<0)
			outcome[-temp->elem]=temp->elem;
			//printf("%d ",temp->elem);
			return temp;
		}
	}
	return NULL;
}

 
bool dpll(clause_root *root_head,int bool_num)//dpll函数
{
	int num1=0,num2=0;//判断是否为空子句集和是否为空子句的计数器 
	int max,min,i,j,k;
	clause_root *p1,*q1,*p2,*q2,*root_head2;
	clause_elem *p,*q,*temp,*p0,*q0,*head2,*head;
	
/******    dpll核心结构     ******/ 
	while(temp=is_single_clause(root_head))//循环结构 
	{
		//根据单子句规则利用单子句简化cnf结构
	    for(p1=root_head;p1->next_root!=NULL;p1=p1->next_root)
	    {
	    	if(p1->is_delete==true)
	    	continue;
	    	for(p=p1->root;p->next_elem!=NULL;p=p->next_elem)
	    	{
	    		if(p->is_delete==true)
	    		continue;
	    		if(p->elem==temp->elem)
				{
					p1->is_delete=true;
					break;
				}
				else if(p->elem==-temp->elem)
				{
					p->is_delete=true;
				}
			}
		}
		
		
	/**    判断是否为空子句集和空子句     **/	
	num1=0;num2=0;
	for(p1=root_head;p1->next_root!=NULL;p1=p1->next_root)
	{
		if(p1->is_delete==true)
		continue;
		num1++;
		p=p1->root;
		num2=0;
		while(p->next_elem!=NULL)
		{
			if(p->is_delete!=true)
			num2++;
			p=p->next_elem;
		}
		if(num2==0)
	   	return false;
	}
	//printf("%d                       ",num1);
	if(num1==0)
	return true;
	/**    判断是否为空子句集和空子句     **/	
	}
	
	
/******选取最短子句里全局出现最多的文字作为策略******/ 
	
	//对统计文字次数的数组清零 
	for(i=1;i<=bool_num;i++)
	rem[i]=0;
	
	//统计cnf结构中所有文字出现的次数并选出最短子句 
	min=10000;
	for(p1=root_head;p1->next_root!=NULL;p1=p1->next_root)
	{
		if(p1->is_delete==true)
		continue;
		p=p1->root;
		while(p->next_elem!=NULL)
		{
			if(p->is_delete!=true)
			{
				p1->length++;
				if(p->elem>0)
				rem[p->elem]++;
				else rem[-p->elem]++;
			}
			p=p->next_elem;
		}
		if(p1->length<=min)
		{
			min=p1->length;
			q1=p1;
		}
	}
	
	//选取最短子句中全局出现最多的文字
	max=0;
	for(p=q1->root;p->next_elem!=NULL;p=p->next_elem)
	if(p->is_delete!=true)
	{
		if(p->elem>0)
		{
			if(rem[p->elem]>max)
	    	{
	    		max=rem[p->elem];
	    	    k=p->elem;
			}
		}
		else if(p->elem<0)
		{
			if(rem[-p->elem]>max)
	    	{
	    		max=rem[-p->elem];
	    	    k=p->elem;
			}
		}
	}
	
	//将选出的文字作为单子句合并到原来的cnf结构 
	q1=(clause_root*)malloc(sizeof(clause_root));
	q1->is_delete=false;
	q1->next_root=root_head;
	p=(clause_elem*)malloc(sizeof(clause_elem));
	q=(clause_elem*)malloc(sizeof(clause_elem));
	q->elem = k;
	q->is_delete=false;
	q->next_elem=p;
	p->next_elem=NULL;
	q1->root=q;
	root_head=q1;
	
/******选取最短子句里全局出现最多的文字作为策略******/ 
	
	
	//拷贝用于回溯 
	root_head2=(clause_root*)malloc(sizeof(clause_root));
	p2=(clause_root*)malloc(sizeof(clause_root));
	root_head2=p2;
	for(p1=root_head;p1->next_root!=NULL;p1=p1->next_root)
	    {
	    	p2->is_delete=p1->is_delete;
	    	p1->length=0;
	    	p2->length=0;
	    	p0=(clause_elem*)malloc(sizeof(clause_elem));
	    	head2=p0;
	    	for(p=p1->root;p->next_elem!=NULL;p=p->next_elem)
	    	{
	    		q0=(clause_elem*)malloc(sizeof(clause_elem));
			    p0->elem=p->elem;
			    p0->is_delete=p->is_delete;
			    p0->next_elem=q0;
			    p0=q0;
			}
			p0->next_elem=NULL;
			q2=(clause_root*)malloc(sizeof(clause_root));
			p2->root=head2;
			p2->is_delete=p1->is_delete;
			p2->next_root=q2;
	    	p2=q2;
		}
		p2->next_root=NULL;
	
	if(dpll(root_head,bool_num))
	return true;
	root_head2->root->elem = -k;
	return dpll(root_head2,bool_num);	
	
/******    dpll核心结构     ******/ 
	
}

#include"sudoku.h" 



int main()
{
	clock_t start, finish;     //定义第一次调用CPU时钟单位的实际，可以理解为定义一个计数器
	double Total_time;        //定义一个double类型的变量，用于存储时间单位
	char Filename[1000],ch,temp,ofilename[1000];
	int elem,i=0,j,k,clause_num,bool_elem[50000]={0},op,bool_num;
	clause_elem *head,*p,*q;
	clause_root *root_head,*p1,*q1;
	printf("1.cnf文件的求解              2.数独的求解\n");
	scanf("%d",&op);
	if(op==1) 
	{
		printf("请输入文件名\n");
		head=(clause_elem*)malloc(sizeof(clause_elem));
		scanf("%s",Filename);
		printf("请输入保存的文件名\n");
		scanf("%s",ofilename);
		FILE *fp,*fp1;
		fp=fopen(Filename,"r");
		fp1=fopen(ofilename,"w");
	
		while(1)
		{
			fscanf(fp,"%c",&ch);
			if(ch=='\n')
			{
				fscanf(fp,"%c",&temp);
				if(temp=='p')
				break;
			}
			else if(ch=='p')
			break;
		}
		while(ch!='f'){
			fscanf(fp,"%c",&ch);
		}
		fscanf(fp,"%d",&bool_num);
		fscanf(fp,"%d",&clause_num);//使输入时为正文 
	
/*****     构建以多重链表为结构的cnf公式      *****/	
	p1=(clause_root*)malloc(sizeof(clause_elem));
	root_head=p1;//获取多重链表的首结点 
	while(i<clause_num)
	{
		i++;
		p=(clause_elem*)malloc(sizeof(clause_elem));
		head=p;
		while(1)
		{
			q=(clause_elem*)malloc(sizeof(clause_elem));
			fscanf(fp,"%d",&elem);
			if(elem==0)
			break;
			p->elem=elem;
			p->next_elem=q;
			p=q;
		}
		p->next_elem=NULL;
		q1=(clause_root*)malloc(sizeof(clause_root));
		p1->root=head;
		p1->next_root=q1;
		p1->length=0;
		p1=q1;
	}
	p1->next_root=NULL;
/*****     构建以多重链表为结构的cnf公式      *****/
    p1=root_head;
	while(p1->next_root!=NULL)
	{
		p1->is_delete=false;
		p=p1->root;
		while(p->next_elem!=NULL)
		{
			p->is_delete=false;
			p=p->next_elem;
		}
		p1=p1->next_root;
	}
	start = clock();        //获取进入要测试执行时间代码段之前的CPU时间占用值
	if(dpll(root_head,bool_num)==true)
	{
		fprintf(fp1,"s 1\nv ");
		for(i=1;i<=bool_num;i++)
		if(outcome[i]!=0)
		fprintf(fp1,"%d ",outcome[i]);
	}
	else 
	{
		fprintf(fp1,"s -1");
	}
	finish = clock(); 
	Total_time = (double)(finish - start);
	fprintf(fp1,"\nt %.0f", Total_time);
  
	
  }
	if(op==2)
	{
		sudoku_generator(a);
		root_head=transfer(a);
	    printf("请输入保存的文件名\n");
		scanf("%s",ofilename);
		FILE *fp,*fp1;
		fp1=fopen(ofilename,"w");
	
		start = clock();  
		if(dpll(root_head,bool_num)==true)
		{
			fprintf(fp1,"s 1\nv ");
			for(i=1;i<=729;i++)
			if(outcome[i]!=0)
		    fprintf(fp1,"%d ",outcome[i]);
		    //printf("%d ",bool_num);

		}
		else 
		{
			fprintf(fp1,"s -1");
		}
		finish = clock(); 
		Total_time = (double)(finish - start);
		fprintf(fp1,"\nt %.0f", Total_time);		
  	}
}
