//���Ա��˳��洢��˳���
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
//���Ա�Ļ�������

//���Ա�ĳ�ʼ��
/*�����Ա��ʼ��Ϊ�յ����Ա�ֻ��Ҫ�����Ա�ĳ���length��Ϊ0*/
void InitList(SeqList *L){
	L->length=0;
}

//�ж����Ա��Ƿ�Ϊ��
/*�ж����Ա��Ƿ�Ϊ�գ����Ա�Ϊ�շ���1�����򷵻�0*/
int ListEmpty(SeqList L){
	if(L.length==0)
		return 1;//Ϊ��
	else 
		return 0;//�ǿ�
}

//����Ų��Ҳ���
/*�������Ա��е�i��Ԫ�ء����ҳɹ�����ֵ���ظ�e��������1��ʾ�ɹ������򷵻�-1��ʾʧ�ܡ�*/
int GetElem(SeqList L,int i,DataType *e){
	if(i<1||i>L.length)
		return -1;//����ʧ��
	*e=L.list[i-1];//����i��Ԫ�ص�ֵ���ظ�e
	return 1;
}

//�����ݲ��Ҳ���
/*�������Ա���Ԫ��ֵΪe��Ԫ�أ����ҳɹ�����ӦԪ�ص���ŷ��أ����򷵻�0��ʾʧ�ܡ�*/
int LocateElem(SeqList L,DataType e){
	int i;
	for(i=0;i<L.length;i++){
		if(L.list[i]==e)
			return i+1;//���ص���e��λ��
	}
	return 0;//����ʧ��
}

//�������
/*��˳���ĵ�i��λ�ò���Ԫ��e������ɹ�����1���������λ�ò��Ϸ�����-1��˳���������0*/
int InsertList(SeqList* L,int i,DataType e){
	int j;
	if(i<1||i>L->length+1){
		printf("����λ��%d���Ϸ���\n",i);
		return -1;
	}else if(L->length>=ListSize){
		printf("˳������������ܲ���Ԫ�ء�\n");
		return 0;
	}else{
		for(j=L->length;j>=i;j--)
			L->list[j]=L->list[j-1];
		L->list[i-1]=e;
		L->length+=1;
		return 1;
	}
}

//ɾ������
int DeleteList(SeqList* L,int i,DataType *e){
	int j;
	if(L->length<=0){
		printf("˳����ѿղ��ܽ���ɾ��1\n");
		return 0;
	}else if(i<1||i>L->length){
		printf("ɾ��λ�ò�����!\n");
	}else{
		*e=L->list[i-1];
		for(j=i;j<L->length;j++)
			L->list[j-1]=L->list[j];
		L->length-=1;
		return 1;
	}
}

//�������Ա�ĳ��Ȳ���
int ListLength(SeqList L){
	return L.length;
}

//��ղ���
void ClearList(SeqList *L){
	L->length=0;
}
//#endif
//********************************************************************
//ɾ��A�г���B��Ԫ�صĺ���ʵ��
void DelElem(SeqList *A,SeqList B)
{
	int i,flag,pos;
	DataType e;
	for(i=0;i<B.length;i++)
	{
		flag=GetElem(B,i,&e);//���ΰ�B��ÿ��Ԫ��ȡ����
		if(flag==1)
		{
			pos=LocateElem(*A,e);//��A�в��Һ�B��ȡ����Ԫ��e��ȵ�Ԫ��
			if(pos>0)
				DeleteList(A,pos,&e);//����ҵ���Ԫ�أ������A��ɾ��
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
	for(i=1;i<=10;i++)				//��1-10���뵽˳���A��
	{
		if(InsertList(&A,i,i)==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	for(i=1,j=1;j<=6;i=i+2,j++)		//����˳���B��������
	{
		if(InsertList(&B,j,i*2)==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	printf("˳���A�е�Ԫ�أ�\n");
	for(i=1;i<=A.length;i++)		
	{
		flag=GetElem(A,i,&e);		//����˳���A�е�ÿ��Ԫ�ص�e��
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("˳���B�е�Ԫ�أ�\n");
	for(i=1;i<=B.length;i++)		//���˳���B�е�ÿ��Ԫ��
	{
		flag=GetElem(B,i,&e);		//����˳���B�е�ÿ��Ԫ�ص�e��
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	printf("����A�г���B��Ԫ��ɾ����A�е�Ԫ�أ�\n");
	DelElem(&A,B);					//����˳���A�г��ֵ�B��Ԫ��ɾ��
	for(i=1;i<=A.length;i++)		//��ʾ���ɾ����A������Ԫ��
	{
		flag=GetElem(A,i,&e);
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	system("pause");
}

//*******************************************************
/*�ϲ�˳���A��B��Ԫ�ص�C�У�������Ԫ�طǵݼ�����*/
void MergeList(SeqList a,SeqList b,SeqList *c)
{
	int i,j,k;
	i=1;
	j=1;
	k=1;
	DataType e1,e2;
	while(i<=a.length&&j<=b.length)
	{
		GetElem(a,i,&e1);//ȡ��˳���A�е�Ԫ��
		GetElem(b,j,&e2);//ȡ��˳���B�е�Ԫ��
		if(e1<=e2)	//�Ƚ�˳���A��˳���B�е�Ԫ��
		{
			InsertList(c,k,e1);	//����С��һ�����뵽C��
			i++;				//�����ƶ�һ��λ�ã�׼���Ƚ���һ��Ԫ��
			k++;
		}else{
			InsertList(c,k,e2);
			j++;
			k++;
		}
	}
	while(i<=a.length){		//���A��Ԫ�ػ���ʣ�࣬��ʱB���Ѿ�û��Ԫ��
		GetElem(a,i,&e1);
		InsertList(c,k,e1);	//��A��ʣ��Ԫ�ز��뵽C��
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
	SeqList A,B,C;					/*����˳���A��B��C*/
	InitList(&A);					/*��ʼ��˳���A*/
	InitList(&B);					/*��ʼ��˳���B*/
	InitList(&C);					/*��ʼ��˳���C*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)				/*������a�е�Ԫ�ز��뵽˳���A��*/
	{
		if(InsertList(&A,i,a[i-1])==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)				/*������b��Ԫ�ز��뵽˳���B��*/
	{
		if(InsertList(&B,i,b[i-1])==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	printf("˳���A�е�Ԫ�أ�\n");
	for(i=1;i<=A.length;i++)		/*���˳���A�е�ÿ��Ԫ��*/
	{
		flag=GetElem(A,i,&e);		/*����˳���A�е�ÿ��Ԫ�ص�e��*/
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("˳���B�е�Ԫ�أ�\n");
	for(i=1;i<=B.length;i++)		/*���˳���B�е�ÿ��Ԫ��*/
	{
		flag=GetElem(B,i,&e);		/*����˳���B�е�ÿ��Ԫ�ص�e��*/
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	printf("����A�г���B��Ԫ�غϲ���C�е�Ԫ�أ�\n");
	MergeList(A,B,&C);					/*����˳���A��B�е�Ԫ�غϲ�*/
	for(i=1;i<=C.length;i++)			/*��ʾ����ϲ���C������Ԫ��*/
	{
		flag=GetElem(C,i,&e);
		if(flag==1)
			printf("%4d",e);	
	}
	printf("\n");
	system("pause");
}
//*****************************************************
//����˳���L��ʹԪ�ص�����Ǵ��ڵ���0��Ԫ�أ��ұ���С��0��Ԫ��
void SplitSeqList(SeqList *L){
	int i,j;		//��������ָʾ��i��j
	DataType e;
	i=0;			//ָʾ��i��j�ֱ�ָʾ˳������˺��Ҷ�Ԫ��
	j=(*L).length-1;
	while(i<j){
		while(L->list[i]>=0)  //i�������ڵ���0��Ԫ���Թ�
			i++;
		while(L->list[j]<0)   //j����С��0��Ԫ���Թ�
			j--;
		if(i<j){			//����Ԫ�ص�i��jָʾ��Ԫ��λ��
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
	InitList(&L);					/*��ʼ��˳���L*/
	n=sizeof(a)/sizeof(a[0]);
	for(i=1;i<=n;i++)				/*������a��Ԫ�ز��뵽˳���L��*/
	{
		if(InsertList(&L,i,a[i-1])==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	printf("˳���L�е�Ԫ�أ�\n");
	for(i=1;i<=L.length;i++)		/*���˳���L�е�ÿ��Ԫ��*/
	{
		flag=GetElem(L,i,&e);		/*����˳���L�е�ÿ��Ԫ�ص�e��*/
		if(flag==1)
			printf("%4d",e);
	}
	printf("\n");
	printf("��˳���L���������Ԫ��>=0,�ұ�Ԫ��<0����\n");
	SplitSeqList(&L);					/*����˳���*/
	for(i=1;i<=L.length;i++)			/*���������˳���L������Ԫ��*/
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

