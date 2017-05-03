//��̬����
#include<stdio.h>
#include<stdlib.h>
#define ListSize 10
typedef char DataType;
//��̬���������Ͷ���
typedef struct{
	DataType data;//������
	int cur;// �α꣬����ָ����
}SListNode;
//��̬�������Ͷ���
typedef struct{
	SListNode list[ListSize];
	int av;//��������
}SLinkList;
//��̬�����ʼ��
void InitSList(SLinkList *L){
	int i;
	for(i=0;i<ListSize;i++){
		(*L).list[i].cur=i+1;
	}
	(*L).list[ListSize-1].cur=0;
	(*L).av=1;//
}
//�ӱ���������ȡ��һ�����ռ䣬�����Ҫ���������е�Ԫ��
int AssignNode(SLinkList L){
	int i;
	i=L.av;
	L.av=L.list[i].cur;
	return i;
}
//ʹ���н���Ϊ���������еĽ��
void FreeNode(SLinkList L,int pos){
	L.list[pos].cur=L.av;
	L.av=pos;
}
//�������
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
//ɾ������
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
//���˫��ѭ�������е�ÿһ��Ԫ��
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
	printf("��̬�����е�Ԫ��:");
	PrintDList(L,len);
	printf("����Ҫ�����Ԫ�ؼ�λ��:");
	scanf("%c",&e);
	getchar();
	scanf("%d",&pos);
	getchar();
	InsertSList(&L,pos,e);
	printf("����Ԫ�غ�̬�����е�Ԫ��:");
	PrintDList(L,len+1);

	printf("����Ҫɾ��Ԫ�ص�λ��:");
	scanf("%d",&pos);
	getchar();
	DeleteSList(&L,pos,&e);
	printf("ɾ����Ԫ����:");
	printf("%c\n",e);
	printf("ɾ��Ԫ�غ�̬�����е�Ԫ��:");
	PrintDList(L,len);
	system("pause");
}