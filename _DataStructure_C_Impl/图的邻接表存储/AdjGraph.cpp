#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ͼ���ڽӱ����Ͷ���
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 10000		//����һ�����޴��ֵ
#define MaxSize 50	 //��󶥵����
typedef enum{DG,DN,UG,UN}GraphKind;		//ͼ�����ͣ�����ͼ��������������ͼ��������
//�߽������Ͷ���
typedef struct ArcNode{
	int adjvex;	//�ڽӵ���,��ָ��Ķ����λ��
	InfoPtr *info;	//�뻡��ص���Ϣ
	struct ArcNode *nextarc;	//ָʾ��һ����ö������ڽӵĶ���
}ArcNode;
//ͷ�������Ͷ���
typedef struct VNode{
	VertexType data;	//���ڴ洢����
	ArcNode *firstarc;	//ָʾ��һ����ö����ڽӵĶ���
}VNode,AdjList[MaxSize];
//ͼ�����Ͷ���
typedef struct{
	AdjList vertex;
	int vexnum,arcnum;	//ͼ�Ķ�����Ŀ�뻡����Ŀ
	GraphKind kind;	//ͼ������
}AdjGraph;
//����ͼ�ж����Ӧ��λ��
int LocateVertex(AdjGraph G,VertexType v){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(G.vertex[i].data,v)==0)
			return i;
	return -1;
}
//�����ڽӱ�洢�ṹ����������ͼG
void CreateGraph(AdjGraph *G){
	int i,j,k;
	VertexType v1,v2;	//������������v1��v2
	ArcNode *p;
	printf("������ͼ�Ķ�����,����(���ŷָ�): ");
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
	printf("������%d�������ֵ:\n",G->vexnum);
	for(i=0;i<G->vexnum;i++){
		scanf("%s",G->vertex[i].data);
		G->vertex[i].firstarc=NULL;	//��������Ķ�����Ϊ��
	}
	printf("�����뻡β�ͻ�ͷ(�Կո���Ϊ���):\n");
	for(k=0;k<G->arcnum;k++){	//����������
		scanf("%s%s",v1,v2);
		i=LocateVertex(*G,v1);
		j=LocateVertex(*G,v2);
		//jΪ��ͷiΪ��β�����ڽӱ�
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->info=NULL;
		p->nextarc=G->vertex[i].firstarc;
		G->vertex[i].firstarc=p;
		//iΪ��ͷjΪ��β�����ڽӱ�
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=i;
		p->info=NULL;
		p->nextarc=G->vertex[j].firstarc;
		G->vertex[j].firstarc=p;
	}
	(*G).kind=UG;
}
//��������ͼG
void DestroyGraph(AdjGraph *G){
	int i;
	ArcNode *p,*q;
	for(i=0;i<(*G).vexnum;++i){	//�ͷ�ͼ�еı߱���
		p=G->vertex[i].firstarc;	//pָ��߱�ĵ�һ�����
		if(p!=NULL){	//����߱�Ϊ�գ����ͷű߱�Ľ��
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;	//����������Ϊ0
	(*G).arcnum=0;	//���ߵ���Ŀ��Ϊ0
}
//���ͼ���ڽӱ�
void DisplayGraph(AdjGraph G){
	int i;
	ArcNode *p;
	printf("%d�����㣺\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\n%d����:\n",2*G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertex[i].firstarc;
		while(p)
		{
			printf("%s��%s ",G.vertex[i].data,G.vertex[p->adjvex].data);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void main(){
	AdjGraph G;
	printf("�����ڽӱ�������ͼG��\n");
	CreateGraph(&G);
	printf("�������ͼG��");
	DisplayGraph(G);
	DestroyGraph(&G);
	system("pause");
}