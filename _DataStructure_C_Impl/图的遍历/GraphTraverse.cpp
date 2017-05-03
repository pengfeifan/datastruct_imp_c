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

int visited[MaxSize];//���ʱ�־����
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
//���ض���v�ĵ�һ���ڽӶ�������
int FirstAdjVertex(AdjGraph G,VertexType v){
	ArcNode *p;
	int v1;
	v1=LocateVertex(G,v);	//v1Ϊ����v��ͼG�е����
	p=G.vertex[v1].firstarc;
	if(p)		//�������v�ĵ�һ���ڽӵ���ڣ������ڽӵ����ţ����򷵻�-1
		return p->adjvex;
	else
		return -1;
}
//����v�������w����һ���ڽӶ�������
int NextAdjVertex(AdjGraph G,VertexType v,VertexType w){
	ArcNode *p,*next;
	int v1,w1;
	v1=LocateVertex(G,v);	//v1Ϊ����v��ͼG�е����
	w1=LocateVertex(G,w);	//w1Ϊ����w��ͼG�е����
	for(next=G.vertex[v1].firstarc;next;)
		if(next->adjvex!=w1)
			next=next->nextarc;
	p=next;	//pָ�򶥵�v���ڽӶ���w�Ľ��
	if(!p||!p->nextarc)		//���w�����ڻ�w�����һ���ڽӵ㣬�򷵻�-1
		return -1;
	else
		return p->nextarc->adjvex;	//����v�������w����һ���ڽӵ�����
}
void Visit(VertexType v){
	printf("%s ",v);
}
//ͼ�ķǵݹ�������ȱ���
void DFSTraverse2(AdjGraph G,int v){
	int i,visited[MaxSize],top;
	ArcNode *stack[MaxSize],*p;
	for(i=0;i<G.vexnum;i++)	//�����ж��㶼���δ���ʱ�־
		visited[i]=0;
	Visit(G.vertex[v].data);	//���ʶ���v�������ʱ�־��Ϊ1����ʾ�Ѿ�����
	visited[v]=1;
	top=-1;	//��ʼ��ջ
	p=G.vertex[v].firstarc;	//pָ�򶥵�v�ĵ�һ���ڽӵ�
	while(top>-1||p!=NULL){
		while(p!=NULL)
			if(visited[p->adjvex]==1) //���pָ��Ķ����Ѿ����ʹ�����pָ����һ���ڽӵ�
				p=p->nextarc;
			else{
				Visit(G.vertex[p->adjvex].data);	//����pָ��Ķ���
				visited[p->adjvex]=1;
				stack[++top]=p;	//����pָ��Ķ���
				p=G.vertex[p->adjvex].firstarc;	//pָ��ǰ����ĵ�һ���ڽӵ�
			}
		if(top>-1){
			p=stack[top--];	//�����ǰ���㶼�Ѿ������ʣ�����ջ
			p=p->nextarc;	//pָ����һ���ڽӵ�
		}
	}
}
//�ӵ�1�������������������ȷǵݹ����ͼG
void BFSTraverse(AdjGraph G){
	int v,front,rear;
	ArcNode *p;
	int queue[MaxSize];	//����һ������Q
	front=rear=-1;	//��ʼ������Q
	for(v=0;v<G.vexnum;v++)	//��ʼ����־λ
		visited[v]=0;
	v=0;
	visited[v]=1;	//���÷��ʱ�־Ϊ1����ʾ�Ѿ������ʹ�
	Visit(G.vertex[v].data);
	rear=(rear+1)%MaxSize;
	queue[rear]=v;	//v�����
	while(front<rear){	//������в���
		front=(front+1)%MaxSize;
		v=queue[front];	//��ͷԪ�س��Ӹ�ֵ��v
		p=G.vertex[v].firstarc;
		while(p!=NULL){		//�������Ϊv�������ڽӵ�
			if(visited[p->adjvex]==0){	//����ö���δ�����ʹ�
				visited[p->adjvex]=1;
				Visit(G.vertex[p->adjvex].data);
				rear=(rear+1)%MaxSize;
				queue[rear]=p->adjvex;
			}
			p=p->nextarc;		//pָ����һ���ڽӵ�
		}
	}
}
//�Ӷ���v�����ݹ�������ȱ���ͼG
void DFS(AdjGraph G,int v){
	int w;
	visited[v]=1;
	Visit(G.vertex[v].data);
	for(w=FirstAdjVertex(G,G.vertex[v].data);w>=0;w=NextAdjVertex(G,G.vertex[v].data,G.vertex[w].data))
		if(!visited[w])
			DFS(G,w);		//�ݹ����DFS��v����δ���ʵ����Ϊw���ڽӶ���
}
//�ӵ�1��������������ȱ���ͼG
void DFSTraverse(AdjGraph G){
	int v;
	for(v=0;v<G.vexnum;v++)
		visited[v]=0;
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
			DFS(G,v);
	printf("\n");
}
void main(){
	AdjGraph G;
	printf("�����ڽӾ��󴴽�����ͼG��\n");
	CreateGraph(&G);
	printf("ͼG��������ȱ�����");
	DFSTraverse2(G,0);
	printf("\n");
	printf("ͼG�Ĺ�����ȱ�����");
	BFSTraverse(G);
	printf("\n");
	DestroyGraph(&G);
	system("pause");
}
