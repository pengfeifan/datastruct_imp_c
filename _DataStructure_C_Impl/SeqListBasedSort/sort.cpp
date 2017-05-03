// _DataStructure_C_Impl:Sort
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
typedef int KeyType;
//数据元素类型定义
typedef struct{
	KeyType key;	//关键字
}DataType;
//顺序表类型定义
typedef struct{
	DataType data[MaxSize];
	int length;
}SqList;
//---------------------------------------------
//直接插入排序
void InsertSort(SqList *L){
	int i,j;
	DataType t;
	for(i=1;i<L->length;i++){		//前i个元素已经有序，从第i+1个元素开始与前i个的有序的关键字比较
		t=L->data[i+1];		//取出当前待排序的元素
		j=i;
		while(j>-1&&t.key<L->data[j].key){		//找当前元素的合适位置
			L->data[j+1]=L->data[j];
			j--;
		}
		L->data[j+1]=t;		//将当前元素插入合适的位置
	}
}
//---------------------------------------------
//折半插入排序
void BinInsertSort(SqList *L){
	int i,j,mid,low,high;
	DataType t;
	for(i=1;i<L->length;i++){		//前i个元素已经有序，从第i+1个元素开始与前i个的有序的关键字比较
		t=L->data[i+1];		//取出第i+1个元素，即待排序的元素
		low=1;
		high=i;
		while(low<=high){		//利用折半查找思想寻找当前元素的合适位置
			mid=(low+high)/2;
			if(L->data[mid].key>t.key)
				high=mid-1;
			else
				low=mid+1;
		}
		for(j=i;j>=low;j--)		//移动元素，空出要插入的位置
			L->data[j+1]=L->data[j];
		L->data[low]=t;	//将当前元素插入合适的位置
	}
}
//---------------------------------------------
//对顺序表L进行一次希尔排序，delta是增量
void ShellInsert(SqList *L,int delta){
	int i,j;
	DataType t;
	for(i=delta+1;i<=L->length;i++){	//将距离为delta的元素作为一个子序列进行排序
		if(L->data[i].key<L->data[i-delta].key){	//如果后者小于前者，则需要移动元素
			t=L->data[i];
			for(j=i-delta;j>0&&t.key<L->data[j].key;j=j-delta)
				L->data[j+delta]=L->data[j];
			L->data[j+delta]=t;		//依次将元素插入到正确的位置
		}
	}
}
//希尔排序，每次调用算法ShellInsert,delta是存放增量的数组
void ShellInsertSort(SqList *L,int delta[],int m){
	int i;
	for(i=0;i<m;i++)	//进行m次希尔插入排序
		ShellInsert(L,delta[i]);
}
void ShellInsertSort2(SqList *L,int gap){
	while(gap>0){
		ShellInsert(L,gap);
		gap/=2;
	}
}
//---------------------------------------------
//简单选择排序
void SelectSort(SqList *L,int n){
	int i,j,k;
	DataType t;
	//将第i个元素的关键字与后面[i+1...n]个元素的关键字比较，将关键字最小的的元素放在第i个位置
	for(i=1;i<=n-1;i++){
		k=i;
		for(j=i+1;j<=n;j++)	//关键字最小的元素的序号为k
			if(L->data[j].key<L->data[k].key)
				k=j;
		if(k!=i){	//如果序号i不等于k，则需要将序号i和序号k的元素交换
			t=L->data[i];
			L->data[i]=L->data[k];
			L->data[k]=t;
		}
	}
}
//---------------------------------------------
//调整H.data[s...m]的关键字，使其成为一个大顶堆
void AdjustHeap(SqList *H,int s,int m){
	DataType t;
	int j;
	t=(*H).data[s];	//将根结点暂时保存在t中
	for(j=2*s;j<=m;j*=2){	
		if(j<m&&(*H).data[j].key<(*H).data[j+1].key)	//沿关键字较大的孩子结点向下筛选
			j++;		//j为关键字较大的结点的下标
		if(t.key>(*H).data[j].key)	//如果孩子结点的值小于根结点的值，则不进行交换
			break;
		(*H).data[s]=(*H).data[j];
		s=j;
	}
	(*H).data[s]=t;	//将根结点的值插入到正确位置
}
//建立大顶堆
void CreateHeap(SqList *H,int n){
	int i;
	for(i=n/2;i>=1;i--)	//从序号n/2开始建立大顶堆
		AdjustHeap(H,i,n);
}
//对顺序表H进行堆排序
void HeapSort(SqList *H){
	DataType t;
	int i;
	CreateHeap(H,H->length);		//创建堆
	for(i=(*H).length;i>1;i--){	//将堆顶元素与最后一个元素交换，重新调整堆
		t=(*H).data[1];
		(*H).data[1]=(*H).data[i];
		(*H).data[i]=t;
		AdjustHeap(H,1,i-1);		//将(*H).data[1..i-1]调整为大顶堆
	}
}
//---------------------------------------------
//输出表中的元素
void DispList3(SqList L,int count){
	int i;
	printf("第%d趟排序结果:",count);
	for(i=1;i<=L.length;i++)
		printf("%4d",L.data[i].key);
	printf("\n");
}
//冒泡排序
void BubbleSort(SqList *L,int n){
	int i,j,flag=1;
	DataType t;
	static int count=1;
	for(i=1;i<=n-1&&flag;i++){		//需要进行n-1趟排序
		flag=0;		//标志位，若以有序，不需要进行下面的排序
		for(j=1;j<=n-i;j++)		//每一趟排序需要比较n-i次
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
/*对顺序表L.r[low..high]的元素进行一趟排序，使枢轴前面的元素关键字小于
枢轴元素的关键字，枢轴后面的元素关键字大于等于枢轴元素的关键字，并返回枢轴位置*/
int Partition(SqList *L,int low,int high){
	DataType t;
	KeyType pivotkey;
	pivotkey=(*L).data[low].key;		//将表的第一个元素作为枢轴元素
	t=(*L).data[low];
	while(low<high){		//从表的两端交替地向中间扫描
		while(low<high&&(*L).data[high].key>=pivotkey)	//从表的末端向前扫描
			high--;
		if(low<high){		//将当前high指向的元素保存在low位置
			(*L).data[low]=(*L).data[high];
			low++;
		}
		while(low<high&&(*L).data[low].key<=pivotkey)	//从表的始端向后扫描
			low++;
		if(low<high){		//将当前low指向的元素保存在high位置
			(*L).data[high]=(*L).data[low];
			high--;
		}
	}
	(*L).data[low]=t;	//将枢轴元素保存在low=high的位置
	return low;		//返回枢轴所在位置
}
//
void DispList2(SqList L,int pivot,int count){
	int i;
	printf("第%d趟排序结果:[",count);
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
//对顺序表L进行快速排序
void QSort(SqList *L,int low,int high){
	int pivot;
	static int count=1;
	if(low<high){		//如果元素序列的长度大于1
		pivot=Partition(L,low,high);	//将待排序序列L.r[low..high]划分为两部分
		DispList2(*L,pivot,count);	//输出每次划分的结果
		count++;
		QSort(L,low,pivot-1);	//对左边的子表进行递归排序，pivot是枢轴位置
		QSort(L,pivot+1,high);	//对右边的子表进行递归排序
	}
}
//对顺序表L作快速排序
void QuickSort(SqList *L){
	QSort(L,1,(*L).length);
}
//---------------------------------------------
//将有序的s[low...mid]和s[mid+1..high]归并为有序的t[low..high]
void Merge(DataType s[],DataType t[],int low,int mid,int high){
	int i,j,k;
	i=low;
	j=mid+1;
	k=low;
	while(i<=mid&&j<=high){		//将s中元素由小到大地合并到t
		if(s[i].key<=s[j].key)
			t[k]=s[i++];
		else
			t[k]=s[j++];
		k++;
	}
	while(i<=mid)		//将剩余的s[i..mid]复制到t
		t[k++]=s[i++];
	while(j<=high)		//将剩余的s[j..high]复制到t
		t[k++]=s[j++];
}
//2路归并排序，将s[low...high]归并排序并存储到t[low...high]中
void MergeSort(DataType s[],DataType t[],int low,int high){
	int mid;
	DataType t2[MaxSize];
	if(low==high)
		t[low]=s[low];
	else{
		mid=(low+high)/2;		//将s[low...high]平分为s[low...mid]和s[mid+1...high]
		MergeSort(s,t2,low,mid);	//将s[low...mid]归并为有序的t2[low...mid]
		MergeSort(s,t2,mid+1,high);	//将s[mid+1...high]归并为有序的t2[mid+1...high]
		Merge(t2,t,low,mid,high);	//将t2[low...mid]和t2[mid+1..high]归并到t[low...high]
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
//顺序表的初始化
void InitSeqList(SqList *L,DataType a[],int n){
	int i;
	for(i=1;i<=n;i++)
	{
		L->data[i]=a[i-1];
	}
	L->length=n;
}
//输出表中的元素
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
	/*直接插入排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	InsertSort(&L);
	printf("直接插入排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*折半插入排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	BinInsertSort(&L);
	printf("折半插入排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*希尔排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	ShellInsertSort(&L,delta,m);
	printf("希尔排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*希尔排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	ShellInsertSort2(&L,gap);
	printf("希尔排序2结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*简单选择排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	SelectSort(&L,n);
	printf("简单选择排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*堆排序*/
	InitSeqList(&L,a,n);
	printf("排序前：");
	DispList(L);
	HeapSort(&L);
	printf("堆排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	DataType b[]={37,22,43,32,19,12,89,26,48,92};
	/*冒泡排序*/
	InitSeqList(&L,b,n);
	printf("冒泡排序前：");
	DispList(L);
	BubbleSort(&L,n);
	printf("冒泡排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*快速排序*/
	InitSeqList(&L,b,n);
	printf("快速排序前：");
	DispList(L);
	QuickSort(&L);
	printf("快速排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	/*归并排序*/
	DataType c[MaxSize];
	InitSeqList(&L,b,n);	/*将数组a[0...n-1]初始化为顺序表L*/
	printf("归并排序前：");
	DispList(L);
	MergeSort(L.data,c,1,n);
	InitSeqList1(&L,c,1,n);	/*将数组c[1...n]初始化为顺序表L*/
	printf("归并排序结果：");
	DispList(L);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	system("pause");
}