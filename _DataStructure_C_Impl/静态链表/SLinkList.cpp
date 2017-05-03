//静态链表
#include<stdio.h>
#include<stdlib.h>
#define ListSize 10
typedef char DataType;
//静态链表结点类型定义
typedef struct{
	DataType data;//数据域
	int cur;// 游标，类似指针域
}SListNode;
//静态链表类型定义
typedef struct{
	SListNode list[ListSize];
	int av;//备用链表
}SLinkList;
//静态链表初始化
void InitSList(SLinkList *L){
	int i;
	for(i=0;i<ListSize;i++){
		(*L).list[i].cur=i+1;
	}
	(*L).list[ListSize-1].cur=0;
	(*L).av=1;//
}
//从备用链表中取下一个结点空间，分配给要插入链表中的元素
int AssignNode(SLinkList L){
	int i;
	i=L.av;
	L.av=L.list[i].cur;
	return i;
}
//使空闲结点成为备用链表中的结点
void FreeNode(SLinkList L,int pos){
	L.list[pos].cur=L.av;
	L.av=pos;
}
//插入操作
void InsertSList(SLinkList *L,int i,DataType e){
	int j,k,x;
	k=(*L).av;
	(*L).av=(*L).list[k].cur;
	(*L).list[k].data=e;
	j=(*L).list[0].cur;
	for(x=1;x<i-1;x++)
		j=(*L).list[j].cur;
	(*L).list[k].cur=(*L).list[j].cur;
	(*L).list[j].cur=k;
}
//删除操作
void DeleteSList(SLinkList *L,int i,DataType *e){
	int j,k,x;
	j=(*L).list[0].cur;
	for(x=1;x<i-1;x++)
		j=(*L).list[j].cur;
	k=(*L).list[j].cur;
	(*L).list[j].cur=(*L).list[k].cur;
	(*L).list[k].cur=(*L).av;
	*e=(*L).list[k].data;
	(*L).av=k;
}
//输出双向循环链表中的每一个元素
void PrintDList(SLinkList L,int n){
	int j,k;
	k=L.list[0].cur;
	for(j=1;j<=n;j++){
		printf("%4c",L.list[k].data);
		k=L.list[k].cur;
	}
	printf("\n");
}
void main(){
	SLinkList L;
	int i,len;
	int pos;
	char e;
	DataType a[]={'A','B','C','D','E','F','H'};
	//DataType a1[]={1,2,3,4,5,6,7,8};
	len=sizeof(a)/sizeof(a[0]);
	InitSList(&L);
	for(i=1;i<=len;i++)
		InsertSList(&L,i,a[i-1]);
	printf("静态链表中的元素:");
	PrintDList(L,len);
	printf("输入要插入的元素及位置:");
	scanf("%c",&e);
	getchar();
	scanf("%d",&pos);
	getchar();
	InsertSList(&L,pos,e);
	printf("插入元素后静态链表中的元素:");
	PrintDList(L,len+1);

	printf("输入要删除元素的位置:");
	scanf("%d",&pos);
	getchar();
	DeleteSList(&L,pos,&e);
	printf("删除的元素是:");
	printf("%c\n",e);
	printf("删除元素后静态链表中的元素:");
	PrintDList(L,len);
	system("pause");
}