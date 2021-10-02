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
	bool is_delete;//�ж������Ƿ�ɾ�� 
}clause_elem;
typedef struct rootclause{
	clause_elem *root;
	struct rootclause *next_root;
	bool is_delete;//�ж��Ӿ��Ƿ�ɾ�� 
	int length;
}clause_root;



clause_elem* is_single_clause(clause_root *root_head)//�ж��Ƿ�Ϊ���Ӿ�ĺ��� 
{
	int num=0;//ͳ�������� 
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

 
bool dpll(clause_root *root_head,int bool_num)//dpll����
{
	int num1=0,num2=0;//�ж��Ƿ�Ϊ���Ӿ伯���Ƿ�Ϊ���Ӿ�ļ����� 
	int max,min,i,j,k;
	clause_root *p1,*q1,*p2,*q2,*root_head2;
	clause_elem *p,*q,*temp,*p0,*q0,*head2,*head;
	
/******    dpll���Ľṹ     ******/ 
	while(temp=is_single_clause(root_head))//ѭ���ṹ 
	{
		//���ݵ��Ӿ�������õ��Ӿ��cnf�ṹ
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
		
		
	/**    �ж��Ƿ�Ϊ���Ӿ伯�Ϳ��Ӿ�     **/	
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
	/**    �ж��Ƿ�Ϊ���Ӿ伯�Ϳ��Ӿ�     **/	
	}
	
	
/******ѡȡ����Ӿ���ȫ�ֳ�������������Ϊ����******/ 
	
	//��ͳ�����ִ������������� 
	for(i=1;i<=bool_num;i++)
	rem[i]=0;
	
	//ͳ��cnf�ṹ���������ֳ��ֵĴ�����ѡ������Ӿ� 
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
	
	//ѡȡ����Ӿ���ȫ�ֳ�����������
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
	
	//��ѡ����������Ϊ���Ӿ�ϲ���ԭ����cnf�ṹ 
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
	
/******ѡȡ����Ӿ���ȫ�ֳ�������������Ϊ����******/ 
	
	
	//�������ڻ��� 
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
	
/******    dpll���Ľṹ     ******/ 
	
}

#include"sudoku.h" 



int main()
{
	clock_t start, finish;     //�����һ�ε���CPUʱ�ӵ�λ��ʵ�ʣ��������Ϊ����һ��������
	double Total_time;        //����һ��double���͵ı��������ڴ洢ʱ�䵥λ
	char Filename[1000],ch,temp,ofilename[1000];
	int elem,i=0,j,k,clause_num,bool_elem[50000]={0},op,bool_num;
	clause_elem *head,*p,*q;
	clause_root *root_head,*p1,*q1;
	printf("1.cnf�ļ������              2.���������\n");
	scanf("%d",&op);
	if(op==1) 
	{
		printf("�������ļ���\n");
		head=(clause_elem*)malloc(sizeof(clause_elem));
		scanf("%s",Filename);
		printf("�����뱣����ļ���\n");
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
		fscanf(fp,"%d",&clause_num);//ʹ����ʱΪ���� 
	
/*****     �����Զ�������Ϊ�ṹ��cnf��ʽ      *****/	
	p1=(clause_root*)malloc(sizeof(clause_elem));
	root_head=p1;//��ȡ����������׽�� 
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
/*****     �����Զ�������Ϊ�ṹ��cnf��ʽ      *****/
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
	start = clock();        //��ȡ����Ҫ����ִ��ʱ������֮ǰ��CPUʱ��ռ��ֵ
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
	    printf("�����뱣����ļ���\n");
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
