// _DataStructure_C_Impl:Sort
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
typedef int KeyType;
//����Ԫ�����Ͷ���
typedef struct{
	KeyType key;	//�ؼ���
}DataType;
//˳������Ͷ���
typedef struct{
	DataType data[MaxSize];
	int length;
}SqList;
//---------------------------------------------
//ֱ�Ӳ�������
void InsertSort(SqList *L){
	int i,j;
	DataType t;
	for(i=1;i<L->length;i++){		//ǰi��Ԫ���Ѿ����򣬴ӵ�i+1��Ԫ�ؿ�ʼ��ǰi��������Ĺؼ��ֱȽ�
		t=L->data[i+1];		//ȡ����ǰ�������Ԫ��
		j=i;
		while(j>-1&&t.key<L->data[j].key){		//�ҵ�ǰԪ�صĺ���λ��
			L->data[j+1]=L->data[j];
			j--;
		}
		L->data[j+1]=t;		//����ǰԪ�ز�����ʵ�λ��
	}
}
//---------------------------------------------
//�۰��������
void BinInsertSort(SqList *L){
	int i,j,mid,low,high;
	DataType t;
	for(i=1;i<L->length;i++){		//ǰi��Ԫ���Ѿ����򣬴ӵ�i+1��Ԫ�ؿ�ʼ��ǰi��������Ĺؼ��ֱȽ�
		t=L->data[i+1];		//ȡ����i+1��Ԫ�أ����������Ԫ��
		low=1;
		high=i;
		while(low<=high){		//�����۰����˼��Ѱ�ҵ�ǰԪ�صĺ���λ��
			mid=(low+high)/2;
			if(L->data[mid].key>t.key)
				high=mid-1;
			else
				low=mid+1;
		}
		for(j=i;j>=low;j--)		//�ƶ�Ԫ�أ��ճ�Ҫ�����λ��
			L->data[j+1]=L->data[j];
		L->data[low]=t;	//����ǰԪ�ز�����ʵ�λ��
	}
}
//---------------------------------------------
//��˳���L����һ��ϣ������delta������
void ShellInsert(SqList *L,int delta){
	int i,j;
	DataType t;
	for(i=delta+1;i<=L->length;i++){	//������Ϊdelta��Ԫ����Ϊһ�������н�������
		if(L->data[i].key<L->data[i-delta].key){	//�������С��ǰ�ߣ�����Ҫ�ƶ�Ԫ��
			t=L->data[i];
			for(j=i-delta;j>0&&t.key<L->data[j].key;j=j-delta)
				L->data[j+delta]=L->data[j];
			L->data[j+delta]=t;		//���ν�Ԫ�ز��뵽��ȷ��λ��
		}
	}
}
//ϣ������ÿ�ε����㷨ShellInsert,delta�Ǵ������������
void ShellInsertSort(SqList *L,int delta[],int m){
	int i;
	for(i=0;i<m;i++)	//����m��ϣ����������
		ShellInsert(L,delta[i]);
}
void ShellInsertSort2(SqList *L,int gap){
	while(gap>0){
		ShellInsert(L,gap);
		gap/=2;
	}
}
//---------------------------------------------
//��ѡ������
void SelectSort(SqList *L,int n){
	int i,j,k;
	DataType t;
	//����i��Ԫ�صĹؼ��������[i+1...n]��Ԫ�صĹؼ��ֱȽϣ����ؼ�����С�ĵ�Ԫ�ط��ڵ�i��λ��
	for(i=1;i<=n-1;i++){
		k=i;
		for(j=i+1;j<=n;j++)	//�ؼ�����С��Ԫ�ص����Ϊk
			if(L->data[j].key<L->data[k].key)
				k=j;
		if(k!=i){	//������i������k������Ҫ�����i�����k��Ԫ�ؽ���
			t=L->data[i];
			L->data[i]=L->data[k];
			L->data[k]=t;
		}
	}
}
//---------------------------------------------
//����H.data[s...m]�Ĺؼ��֣�ʹ���Ϊһ���󶥶�
void AdjustHeap(SqList *H,int s,int m){
	DataType t;
	int j;
	t=(*H).data[s];	//���������ʱ������t��
	for(j=2*s;j<=m;j*=2){	
		if(j<m&&(*H).data[j].key<(*H).data[j+1].key)	//�عؼ��ֽϴ�ĺ��ӽ������ɸѡ
			j++;		//jΪ�ؼ��ֽϴ�Ľ����±�
		if(t.key>(*H).data[j].key)	//������ӽ���ֵС�ڸ�����ֵ���򲻽��н���
			break;
		(*H).data[s]=(*H).data[j];
		s=j;
	}
	(*H).data[s]=t;	//��������ֵ���뵽��ȷλ��
}
//�����󶥶�
void CreateHeap(SqList *H,int n){
	int i;
	for(i=n/2;i>=1;i--)	//�����n/2��ʼ�����󶥶�
		AdjustHeap(H,i,n);
}
//��˳���H���ж�����
void HeapSort(SqList *H){
	DataType t;
	int i;
	CreateHeap(H,H->length);		//������
	for(i=(*H).length;i>1;i--){	//���Ѷ�Ԫ�������һ��Ԫ�ؽ��������µ�����
		t=(*H).data[1];
		(*H).data[1]=(*H).data[i];
		(*H).data[i]=t;
		AdjustHeap(H,1,i-1);		//��(*H).data[1..i-1]����Ϊ�󶥶�
	}
}
//---------------------------------------------
//������е�Ԫ��
void DispList3(SqList L,int count){
	int i;
	printf("��%d��������:",count);
	for(i=1;i<=L.length;i++)
		printf("%4d",L.data[i].key);
	printf("\n");
}
//ð������
void BubbleSort(SqList *L,int n){
	int i,j,flag=1;
	DataType t;
	static int count=1;
	for(i=1;i<=n-1&&flag;i++){		//��Ҫ����n-1������
		flag=0;		//��־λ���������򣬲���Ҫ�������������
		for(j=1;j<=n-i;j++)		//ÿһ��������Ҫ�Ƚ�n-i��
			if(L->data[j].key>L->data[j+1].key){	
				t=L->data[j];		
				L->data[j]=L->data[j+1];
				L->data[j+1]=t;
				flag=1;
			}
		DispList3(*L,count);
		count++;
	}
}
//---------------------------------------------
/*��˳���L.r[low..high]��Ԫ�ؽ���һ������ʹ����ǰ���Ԫ�عؼ���С��
����Ԫ�صĹؼ��֣���������Ԫ�عؼ��ִ��ڵ�������Ԫ�صĹؼ��֣�����������λ��*/
int Partition(SqList *L,int low,int high){
	DataType t;
	KeyType pivotkey;
	pivotkey=(*L).data[low].key;		//����ĵ�һ��Ԫ����Ϊ����Ԫ��
	t=(*L).data[low];
	while(low<high){		//�ӱ�����˽�������м�ɨ��
		while(low<high&&(*L).data[high].key>=pivotkey)	//�ӱ��ĩ����ǰɨ��
			high--;
		if(low<high){		//����ǰhighָ���Ԫ�ر�����lowλ��
			(*L).data[low]=(*L).data[high];
			low++;
		}
		while(low<high&&(*L).data[low].key<=pivotkey)	//�ӱ��ʼ�����ɨ��
			low++;
		if(low<high){		//����ǰlowָ���Ԫ�ر�����highλ��
			(*L).data[high]=(*L).data[low];
			high--;
		}
	}
	(*L).data[low]=t;	//������Ԫ�ر�����low=high��λ��
	return low;		//������������λ��
}
//
void DispList2(SqList L,int pivot,int count){
	int i;
	printf("��%d��������:[",count);
	for(i=1;i<pivot;i++)
		printf("%-4d",L.data[i].key);
	printf("]");
	printf("%3d ",L.data[pivot].key);
	printf("[");
	for(i=pivot+1;i<=L.length;i++)
		printf("%-4d",L.data[i].key);
	printf("]");
	printf("\n");
}
//��˳���L���п�������
void QSort(SqList *L,int low,int high){
	int pivot;
	static int count=1;
	if(low<high){		//���Ԫ�����еĳ��ȴ���1
		pivot=Partition(L,low,high);	//������������L.r[low..high]����Ϊ������
		DispList2(*L,pivot,count);	//���ÿ�λ��ֵĽ��
		count++;
		QSort(L,low,pivot-1);	//����ߵ��ӱ���еݹ�����pivot������λ��
		QSort(L,pivot+1,high);	//���ұߵ��ӱ���еݹ�����
	}
}
//��˳���L����������
void QuickSort(SqList *L){
	QSort(L,1,(*L).length);
}
//---------------------------------------------
//�������s[low...mid]��s[mid+1..high]�鲢Ϊ�����t[low..high]
void Merge(DataType s[],DataType t[],int low,int mid,int high){
	int i,j,k;
	i=low;
	j=mid+1;
	k=low;
	while(i<=mid&&j<=high){		//��s��Ԫ����С����غϲ���t
		if(s[i].key<=s[j].key)
			t[k]=s[i++];
		else
			t[k]=s[j++];
		k++;
	}
	while(i<=mid)		//��ʣ���s[i..mid]���Ƶ�t
		t[k++]=s[i++];
	while(j<=high)		//��ʣ���s[j..high]���Ƶ�t
		t[k++]=s[j++];
}
//2·�鲢���򣬽�s[low...high]�鲢���򲢴洢��t[low...high]��
void MergeSort(DataType s[],DataType t[],int low,int high){
	int mid;
	DataType t2[MaxSize];
	if(low==high)
		t[low]=s[low];
	else{
		mid=(low+high)/2;		//��s[low...high]ƽ��Ϊs[low...mid]��s[mid+1...high]
		MergeSort(s,t2,low,mid);	//��s[low...mid]�鲢Ϊ�����t2[low...mid]
		MergeSort(s,t2,mid+1,high);	//��s[mid+1...high]�鲢Ϊ�����t2[mid+1...high]
		Merge(t2,t,low,mid,high);	//��t2[low...mid]��t2[mid+1..high]�鲢��t[low...high]
	}
}
void InitSeqList1(SqList *L,DataType a[],int start,int n)
{
	int i,k;
	for(k=1,i=start;i<start+n;i++,k++)
	{
		L->data[k]=a[i];
	}
	L->length=n;

}
//---------------------------------------------
//˳���ĳ�ʼ��
void InitSeqList(SqList *L,DataType a[],int n){
	int i;
	for(i=1;i<=n;i++)
	{
		L->data[i]=a[i-1];
	}
	L->length=n;
}
//������е�Ԫ��
void DispList(SqList L){
	int i;
	for(i=1;i<=L.length;i++)
		printf("%4d",L.data[i].key);
	printf("\n");
}
void main(){
	DataType a[]={56,22,67,32,59,12,89,26,48,37};
	int delta[]={5,3,1};
	int gap=5;
	int i,n=10,m=3;
	SqList L;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*ֱ�Ӳ�������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	InsertSort(&L);
	printf("ֱ�Ӳ�����������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*�۰��������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	BinInsertSort(&L);
	printf("�۰������������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*ϣ������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	ShellInsertSort(&L,delta,m);
	printf("ϣ����������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*ϣ������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	ShellInsertSort2(&L,gap);
	printf("ϣ������2�����");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*��ѡ������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	SelectSort(&L,n);
	printf("��ѡ����������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*������*/
	InitSeqList(&L,a,n);
	printf("����ǰ��");
	DispList(L);
	HeapSort(&L);
	printf("����������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	DataType b[]={37,22,43,32,19,12,89,26,48,92};
	/*ð������*/
	InitSeqList(&L,b,n);
	printf("ð������ǰ��");
	DispList(L);
	BubbleSort(&L,n);
	printf("ð����������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*��������*/
	InitSeqList(&L,b,n);
	printf("��������ǰ��");
	DispList(L);
	QuickSort(&L);
	printf("������������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*�鲢����*/
	DataType c[MaxSize];
	InitSeqList(&L,b,n);	/*������a[0...n-1]��ʼ��Ϊ˳���L*/
	printf("�鲢����ǰ��");
	DispList(L);
	MergeSort(L.data,c,1,n);
	InitSeqList1(&L,c,1,n);	/*������c[1...n]��ʼ��Ϊ˳���L*/
	printf("�鲢��������");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	system("pause");
}