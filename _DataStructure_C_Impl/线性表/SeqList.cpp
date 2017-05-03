//线性表的顺序存储：顺序表
//#pragma once
//#ifndef SeqList_H
//#define SeqList_H

#include<stdio.h>
#include<stdlib.h>
#define ListSize 100
typedef int DataType;
typedef struct{
	DataType list[ListSize];
	int length;
}SeqList;
//线性表的基本运算

//线性表的初始化
/*将线性表初始化为空的线性表只需要把线性表的长度length置为0*/
void InitList(SeqList *L){
	L->length=0;
}

//判断线性表是否为空
/*判断线性表是否为空，线性表为空返回1，否则返回0*/
int ListEmpty(SeqList L){
	if(L.length==0)
		return 1;//为空
	else 
		return 0;//非空
}

//按序号查找操作
/*查找线性表中第i个元素。查找成功将该值返回给e，并返回1表示成功；否则返回-1表示失败。*/
int GetElem(SeqList L,int i,DataType *e){
	if(i<1||i>L.length)
		return -1;//查找失败
	*e=L.list[i-1];//将第i个元素的值返回给e
	return 1;
}

//按内容查找操作
/*查找线性表中元素值为e的元素，查找成功将对应元素的序号返回，否则返回0表示失败。*/
int LocateElem(SeqList L,DataType e){
	int i;
	for(i=0;i<L.length;i++){
		if(L.list[i]==e)
			return i+1;//返回等于e的位置
	}
	return 0;//查找失败
}

//插入操作
/*在顺序表的第i个位置插入元素e，插入成功返回1，如果插入位置不合法返回-1，顺序表满返回0*/
int InsertList(SeqList* L,int i,DataType e){
	int j;
	if(i<1||i>L->length+1){
		printf("插入位置%d不合法！\n",i);
		return -1;
	}else if(L->length>=ListSize){
		printf("顺序表已满，不能插入元素。\n");
		return 0;
	}else{
		for(j=L->length;j>=i;j--)
			L->list[j]=L->list[j-1];
		L->list[i-1]=e;
		L->length+=1;
		return 1;
	}
}

//删除操作
int DeleteList(SeqList* L,int i,DataType *e){
	int j;
	if(L->length<=0){
		printf("顺序表已空不能进行删除1\n");
		return 0;
	}else if(i<1||i>L->length){
		printf("删除位置不合适!\n");
	}else{
		*e=L->list[i-1];
		for(j=i;j<L->length;j++)
			L->list[j-1]=L->list[j];
		L->length-=1;
		return 1;
	}
}

//返回线性表的长度操作
int ListLength(SeqList L){
	return L.length;
}

//清空操作
void ClearList(SeqList *L){
	L->length=0;
}
//#endif
//********************************************************************
//删除A中出现B的元素的函数实现
void DelElem(SeqList *A,SeqList B)
{
	int i,flag,pos;
	DataType e;
	for(i=0;i<B.length;i++)
	{
		flag=GetElem(B,i,&e);//依次把B中每个元素取出给
		if(flag==1)
		{
			pos=LocateElem(*A,e);//在A中查找和B中取出的元素e相等的元素
			if(pos>0)
				DeleteList(A,pos,&e);//如果找到该元素，将其从A中删除
		}
	}
}
void main_DelElem()
{
	int i,j,flag;
	DataType e;
	SeqList A,B;					
	InitList(&A);					
	InitList(&B);					
	for(i=1;i<=10;i++)				//将1-10插入到顺序表A中
	{
		if(InsertList(&A,i,i)==0)
		{
			printf("位置不合法");
			return;
		}
	}
	for(i=1,j=1;j<=6;i=i+2,j++)		//插入顺序表B中六个数
	{
		if(InsertList(&B,j,i*2)==0)
		{
			printf("位置不合法");
			return;
		}
	}
	printf("顺序表A中的元素：\n");
	for(i=1;i<=A.length;i++)		
	{
		flag=GetElem(A,i,&e);		//返回顺序表A中的每个元素到e中
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("顺序表B中的元素：\n");
	for(i=1;i<=B.length;i++)		//输出顺序表B中的每个元素
	{
		flag=GetElem(B,i,&e);		//返回顺序表B中的每个元素到e中
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	printf("将在A中出现B的元素删除后A中的元素：\n");
	DelElem(&A,B);					//将在顺序表A中出现的B的元素删除
	for(i=1;i<=A.length;i++)		//显示输出删除后A中所有元素
	{
		flag=GetElem(A,i,&e);
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	system("pause");
}

//*******************************************************
/*合并顺序表A和B的元素到C中，并保持元素非递减排序*/
void MergeList(SeqList a,SeqList b,SeqList *c)
{
	int i,j,k;
	i=1;
	j=1;
	k=1;
	DataType e1,e2;
	while(i<=a.length&&j<=b.length)
	{
		GetElem(a,i,&e1);//取出顺序表A中的元素
		GetElem(b,j,&e2);//取出顺序表B中的元素
		if(e1<=e2)	//比较顺序表A和顺序表B中的元素
		{
			InsertList(c,k,e1);	//将较小的一个插入到C中
			i++;				//往后移动一个位置，准备比较下一个元素
			k++;
		}else{
			InsertList(c,k,e2);
			j++;
			k++;
		}
	}
	while(i<=a.length){		//如果A中元素还有剩余，这时B中已经没有元素
		GetElem(a,i,&e1);
		InsertList(c,k,e1);	//将A中剩余元素插入到C中
		i++;
		k++;
	}
	while(j<=b.length){
		GetElem(b,j,&e2);
		InsertList(c,k,e2);
		j++;
		k++;
	}
}
void main_MergeList()
{
	int i,flag;
	DataType a[]={6,11,11,23};
	DataType b[]={2,10,12,12,21};
	DataType e;
	SeqList A,B,C;					/*声明顺序表A，B和C*/
	InitList(&A);					/*初始化顺序表A*/
	InitList(&B);					/*初始化顺序表B*/
	InitList(&C);					/*初始化顺序表C*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)				/*将数组a中的元素插入到顺序表A中*/
	{
		if(InsertList(&A,i,a[i-1])==0)
		{
			printf("位置不合法");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)				/*将数组b中元素插入到顺序表B中*/
	{
		if(InsertList(&B,i,b[i-1])==0)
		{
			printf("位置不合法");
			return;
		}
	}
	printf("顺序表A中的元素：\n");
	for(i=1;i<=A.length;i++)		/*输出顺序表A中的每个元素*/
	{
		flag=GetElem(A,i,&e);		/*返回顺序表A中的每个元素到e中*/
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("顺序表B中的元素：\n");
	for(i=1;i<=B.length;i++)		/*输出顺序表B中的每个元素*/
	{
		flag=GetElem(B,i,&e);		/*返回顺序表B中的每个元素到e中*/
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	printf("将在A中出现B的元素合并后C中的元素：\n");
	MergeList(A,B,&C);					/*将在顺序表A和B中的元素合并*/
	for(i=1;i<=C.length;i++)			/*显示输出合并后C中所有元素*/
	{
		flag=GetElem(C,i,&e);
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	system("pause");
}
//*****************************************************
//调整顺序表L，使元素的左边是大于等于0的元素，右边是小于0的元素
void SplitSeqList(SeqList *L){
	int i,j;		//定义两个指示器i和j
	DataType e;
	i=0;			//指示器i和j分别指示顺序表的左端和右端元素
	j=(*L).length-1;
	while(i<j){
		while(L->list[i]>=0)  //i遇到大于等于0的元素略过
			i++;
		while(L->list[j]<0)   //j遇到小于0的元素略过
			j--;
		if(i<j){			//调整元素的i和j指示的元素位置
			e=L->list[i];
			L->list[i]=L->list[j];
			L->list[j]=e;
		}
	}
}
void main_SplitSeqList(){
	int i,flag,n;
	DataType e;
	SeqList L;				
	int a[]={-7,0,5,-8,9,-4,3,-2};
	InitList(&L);					/*初始化顺序表L*/
	n=sizeof(a)/sizeof(a[0]);
	for(i=1;i<=n;i++)				/*将数组a的元素插入到顺序表L中*/
	{
		if(InsertList(&L,i,a[i-1])==0)
		{
			printf("位置不合法");
			return;
		}
	}
	printf("顺序表L中的元素：\n");
	for(i=1;i<=L.length;i++)		/*输出顺序表L中的每个元素*/
	{
		flag=GetElem(L,i,&e);		/*返回顺序表L中的每个元素到e中*/
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("将顺序表L调整后（左边元素>=0,右边元素<0）：\n");
	SplitSeqList(&L);					/*调整顺序表*/
	for(i=1;i<=L.length;i++)			/*输出调整后顺序表L中所有元素*/
	{
		flag=GetElem(L,i,&e);
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");	
	system("pause");
}
void main(){
	main_DelElem();
	main_MergeList();
	main_SplitSeqList();
}

