#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 10000		//����һ�����޴��ֵ
#define MaxSize 50	 //��󶥵����
typedef enum{DG,DN,UG,UN}GraphKind;		//ͼ�����ͣ�����ͼ��������������ͼ��������

typedef struct{
	VRType adj;		//������Ȩͼ����1��ʾ���ڣ�0��ʾ�����ڣ����ڴ�Ȩͼ���洢Ȩֵ
	InfoPtr *info;	//�뻡��ߵ������Ϣ
}ArcNode,AdjMatrix[MaxSize][MaxSize];
//ͼ�����Ͷ���
typedef struct{
	VertexType vex[MaxSize];	//���ڴ洢����
	AdjMatrix arc;		//�ڽӾ��󣬴洢�߻򻡵���Ϣ
	int vexnum,arcnum;	//�������ͱߣ���������Ŀ
	GraphKind kind;		//ͼ������
}MGraph;
//��¼�Ӷ��㼯��U��V-U�Ĵ�����С�ıߵ����鶨��
typedef struct{
	VertexType adjvex;
	VRType lowcost;
}closeedge[MaxSize];
//�ڶ��������в��Ҷ���v���ҵ���������������ţ����򷵻�-1
int LocateVertex(MGraph N,VertexType v){
	int i;
	for(i=0;i<N.vexnum;++i)
		if(strcmp(N.vex[i],v)==0)
			return i;
	return -1;
}
//�����ڽӾ����ʾ������������N
void CreateGraph(MGraph *N){
	int i,j,k,w,InfoFlag,len;
	char s[MaxSize];
	VertexType v1,v2;
	printf("������������N�Ķ�����,����,������Ϣ(��:1,��:0): ");
	scanf("%d,%d,%d",&(*N).vexnum,&(*N).arcnum,&InfoFlag);
	printf("������%d�������ֵ(<%d���ַ�):\n",N->vexnum,MaxSize);
	for(i=0;i<N->vexnum;++i)	//�������ĸ�������
		scanf("%s",N->vex[i]);
	for(i=0;i<N->vexnum;i++)	//��ʼ���ڽӾ���
		for(j=0;j<N->vexnum;j++){
			N->arc[i][j].adj=INFINITY;
			N->arc[i][j].info=NULL;	//������Ϣ��ʼ��Ϊ��
		}
		printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",N->arcnum);
		for(k=0;k<N->arcnum;k++){
			scanf("%s%s%d",v1,v2,&w);	//������������ͻ���Ȩֵ
			i=LocateVertex(*N,v1);
			j=LocateVertex(*N,v2);
			N->arc[i][j].adj=w;
			if(InfoFlag){		//���������������Ϣ
				printf("�����뻡�������Ϣ: ");
				gets(s);
				len=strlen(s);
				if(len){
					N->arc[i][j].info=(char *)malloc((len+1)*sizeof(char));
					strcpy(N->arc[i][j].info,s);
				}
			}
		}
		N->kind=DN;		//ͼ������Ϊ������
}
//������N
void DestroyGraph(MGraph *N){
	int i,j;
	for(i=0;i<N->vexnum;i++)		//�ͷŻ��������Ϣ
		for(j=0;j<N->vexnum;j++)
			if(N->arc[i][j].adj!=INFINITY)	//������ڻ�
				if(N->arc[i][j].info!=NULL){	//������������Ϣ���ͷŸ���Ϣ��ռ�ÿռ�
					free(N->arc[i][j].info);
					N->arc[i][j].info=NULL;
				}
				N->vexnum=0;	//�����Ķ�������Ϊ0
				N->arcnum=0;	//�����Ļ�����Ŀ��Ϊ0
}
//
void DisplayGraph(MGraph N){
	int i,j;
	printf("����������%d������%d����������������: ",N.vexnum,N.arcnum);
	for(i=0;i<N.vexnum;++i)		//������Ķ���
		printf("%s ",N.vex[i]);
	printf("\n������N��:\n");			//�����N�Ļ�
	printf("���i=");
	for(i=0;i<N.vexnum;i++)
		printf("%8d",i);
	printf("\n");
	for(i=0;i<N.vexnum;i++)
	{
		printf("%8d",i);
		for(j=0;j<N.vexnum;j++)
			printf("%8d",N.arc[i][j].adj);
		printf("\n"); 
	}
}
//��lowcost����Сֵ����ŷ���
int MiniNum(closeedge edge,MGraph G){
	int i=0,j,k,min;
	while(!edge[i].lowcost)
		i++;
	min=edge[i].lowcost;//��һ����Ϊ0��ֵ
	k=i;
	for(j=i+1;j<G.vexnum;j++)
		if(edge[j].lowcost>0&&edge[j].lowcost<min){	//����Сֵ��Ӧ����Ÿ�ֵ��k
			min=edge[j].lowcost;
			k=j;
		}
	return k;
}
//��������ķ�㷨��ӵ�u���������������G����С������T
void Prim(MGraph G,VertexType u){
	int i,j,k;
	closeedge closedge;
	k=LocateVertex(G,u);	//kΪ����u��Ӧ�����
	for(j=0;j<G.vexnum;j++){	//�����ʼ��
		strcpy(closedge[j].adjvex,u);
		closedge[j].lowcost=G.arc[k][j].adj;
	}
	closedge[k].lowcost=0;		//��ʼʱ����Uֻ��������u
	printf("����������С�������ĸ����߷ֱ���:\n");
	for(i=1;i<G.vexnum;++i){	//ѡ��ʣ�µ�G.vexnum-1������
		k=MiniNum(closedge,G);	//kΪ��U�ж������ڽӵ���һ����������
		printf("(%s-%s)\n",closedge[k].adjvex,G.vex[k]); //����������ı�
		closedge[k].lowcost=0;	//��k���㲢��U��
		for(j=0;j<G.vexnum;++j)
			if(G.arc[k][j].adj<closedge[j].lowcost){	//�¶������U�������½���С�ߴ��뵽����
				strcpy(closedge[j].adjvex,G.vex[k]);
				closedge[j].lowcost=G.arc[k][j].adj;
			}
	}
}
void main(){
	MGraph N;
	printf("����һ����������\n");
	CreateGraph(&N);
	DisplayGraph(N);
	Prim(N,"A");	
	DestroyGraph(&N);
	system("pause");
}