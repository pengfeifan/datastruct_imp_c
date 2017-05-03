#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define MaxSize 50	//��󶥵����
typedef enum{DG,DN,UG,UN}GraphKind;
//�߽������Ͷ���
typedef struct ArcNode{
	int adjvex;		//��ָ��Ķ����λ��
	InfoPtr *info;	//����Ȩֵ
	struct ArcNode *nextarc;	//ָʾ��һ����ö������ڽӵĶ���
}ArcNode;
//ͷ�������Ͷ���
typedef struct VNode{
	VertexType data;	//���ڴ洢����
	ArcNode *firstarc;	//ָʾ��һ����ö����ڽӵĶ���
}VNode,AdjList[MaxSize];
//ͼ�����Ͷ���
typedef struct{
	AdjList vertex;	 //ͷ���
	int vexnum,arcnum;	//ͼ�Ķ�����Ŀ�뻡����Ŀ
	GraphKind kind;	//ͼ������
}AdjGraph;
//��ͼG�У�����붥��v0���·��Ϊk�����ж���
void BsfLevel(AdjGraph G,int v0,int k){
	int visited[MaxSize];	//һ��������ʱ�־���飬0��ʾδ���ʣ�1��ʾ�Ѿ�����
	int queue[MaxSize][2];	//����queue[][0]�洢�������ţ�queue[][1]�洢��ǰ�������v0��·������
	int front=0,rear=-1,v,i,level,yes=0;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)		//��ʼ����־����
		visited[i]=0;
	rear=(rear+1)%MaxSize;	//����v0�����
	queue[rear][0]=v0;
	queue[rear][1]=1;
	visited[v0]=1;	//���������־��Ϊ1
	level=1;	//���õ�ǰ���
	do{
		v=queue[front][0];		//ȡ�������ж���
		level=queue[front][1];
		front=(front+1)%MaxSize;
		p=G.vertex[v].firstarc;	//pָ��v�ĵ�һ���ڽӵ�
		while(p!=NULL){
			if(visited[p->adjvex]==0){	//������ڽӵ�δ������
				if(level==k){	//������ڽӵ����v0�����·��Ϊk���������
					if(yes==0)
						printf("����%s�����·��Ϊ%2d�Ķ����У�%s ",
						G.vertex[v0].data,k,G.vertex[p->adjvex].data);
					else
						printf(",%s",G.vertex[p->adjvex].data);
					yes=1;
				}
				visited[p->adjvex]=1;	//���ʱ�־��Ϊ1
				rear=(rear+1)%MaxSize;	//�����ö������
				queue[rear][0]=p->adjvex;
				queue[rear][1]=level+1;
			}
			p=p->nextarc;	//�����ǰ�����Ѿ������ʣ���p������һ���ڽӵ�
		}
	}while(front!=rear&&level<k+1);
	printf("\n");
}
//����ͼ�ж����Ӧ��λ��
int LocateVertex(AdjGraph G,VertexType v){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(G.vertex[i].data,v)==0)
			return i;
	return -1;
}
//�����ڽӱ�洢�ṹ����������ͼN
void CreateGraph(AdjGraph *G){
	int i,j,k,w;
	VertexType v1,v2;					/*������������v1��v2*/
	ArcNode *p;
	printf("������ͼ�Ķ�����,����(�Զ��ŷָ�): ");
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
	printf("������%d�������ֵ:",G->vexnum);
	for(i=0;i<G->vexnum;i++)			/*������洢��ͷ�����*/
	{
		scanf("%s",G->vertex[i].data);
		G->vertex[i].firstarc=NULL;		/*��������Ķ�����Ϊ��*/
	}
	printf("������ߵ���������(�Կո���Ϊ�ָ�):\n");
	for(k=0;k<G->arcnum;k++)			/*����������*/
	{
		scanf("%s%s",v1,v2);
		i=LocateVertex(*G,v1);
		j=LocateVertex(*G,v2);
		/*jΪ���iΪ���ߴ����ڽӱ�*/
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
		/*��pָ��Ľ����뵽�߱���*/
		p->nextarc=G->vertex[i].firstarc;
		G->vertex[i].firstarc=p;
		/*iΪ���jΪ���ߴ����ڽӱ�*/
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
	for(i=0;i<G->vexnum;++i)		/*�ͷ�ͼ�еı߱���*/
	{
		p=G->vertex[i].firstarc;	/*pָ��߱�ĵ�һ�����*/
		if(p!=NULL)					/*����߱�Ϊ�գ����ͷű߱�Ľ��*/
		{
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;					/*����������Ϊ0*/
	(*G).arcnum=0;					/*���ߵ���Ŀ��Ϊ0*/
}
//ͼG���ڽӱ�����
void DisplayGraph(AdjGraph G){
	int i;
	ArcNode *p;
	printf("��ͼ����%d�����㣺",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\nͼ�й���%d����:\n",2*G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertex[i].firstarc;
		while(p)
		{
			printf("(%s,%s) ",G.vertex[i].data,G.vertex[p->adjvex].data);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void main(){
	AdjGraph G;
	CreateGraph(&G);		/*�����ڽӱ�洢�ṹ����ͼG*/
	DisplayGraph(G);		/*�������ͼG*/
	BsfLevel(G,0,2);		/*��ͼG�о��붥��v0���·��Ϊ2�Ķ���*/
	DestroyGraph(&G);		/*����ͼG*/
	system("pause");
}