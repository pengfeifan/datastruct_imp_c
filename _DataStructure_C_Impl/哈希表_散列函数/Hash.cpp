#include<stdlib.h>
#include<stdio.h>
typedef int KeyType;
//Ԫ�����Ͷ���
typedef struct{
	KeyType key;	//�ؼ���
	int hi;			//��ͻ����
}DataType;
//��ϣ�����Ͷ���
typedef struct{
	DataType *data;
	int tableSize;	//��ϣ��ĳ���
	int curSize;	//���йؼ��ָ���
}HashTable;
//����һ����ϣ���������ͻ
void CreateHashTable(HashTable *H,int m,int p,int hash[],int n){
	int i,sum,addr,di,k=1;
	(*H).data=(DataType *)malloc(m*sizeof(DataType));	//Ϊ��ϣ�����洢�ռ�
	if(!(*H).data)
		exit(-1);
	for(i=0;i<m;i++){	//��ʼ����ϣ��
		(*H).data[i].key=-1;
		(*H).data[i].hi=0;
	}
	for(i=0;i<n;i++){		//���ϣ������ַ�������ͻ
		sum=0;		//��ͻ�Ĵ���
		addr=hash[i]%p;		//���ó������������ϣ������ַ
		di=addr;
		if((*H).data[addr].key==-1){	//�������ͻ��Ԫ�ش洢�ڱ���
			(*H).data[addr].key=hash[i];
			(*H).data[addr].hi=1;
		}else{				//������̽����ɢ�з������ͻ
			do{
				di=(di+k)%m;
				sum+=1;
			}while((*H).data[di].key!=-1);
			(*H).data[di].key=hash[i];
			(*H).data[di].hi=sum+1;
		}
	}
	(*H).curSize=n;	//��ϣ���йؼ��ָ���Ϊn
	(*H).tableSize=m;	//��ϣ��ĳ���
}
//�ڹ�ϣ��H�в��ҹؼ���k��Ԫ��
int SearchHash(HashTable H,KeyType k){
	int d,d1,m;
	m=H.tableSize;
	d=d1=k%m;		//��k�Ĺ�ϣ��ַ
	while(H.data[d].key!=-1){
		if(H.data[d].key==k)	//�����Ҫ���ҵĹؼ���k���򷵻�k��λ��
			return d;
		else				//�����������
			d=(d+1)%m;
		if(d==d1)		//��������˹�ϣ���е�����λ�ã�û���ҵ�����0
			return 0;
	}
	return 0;			//��λ�ò����ڹؼ���k
}
//�����ϣ��
void DisplayHash(HashTable H,int m){
	int i;
	printf("��ϣ���ַ��");
	for(i=0;i<m;i++)
		printf("%-5d",i);
	printf("\n");
	printf("�ؼ���key:  ");
	for(i=0;i<m;i++)
		printf("%-5d",H.data[i].key);
	printf("\n");
	printf("��ͻ������  ");
	for(i=0;i<m;i++)
		printf("%-5d",H.data[i].hi);
	printf("\n");
}
//���ϣ���ƽ�����ҳ���
void HashASL(HashTable H,int m){
	float average=0;
	int i;
	for(i=0;i<m;i++)
		average=average+H.data[i].hi;
	average=average/H.curSize;
	printf("ƽ�����ҳ���ASL=%.2f",average);
	printf("\n"); 
}
void main(){
	int hash[]={23,35,12,56,123,39,342,90};
	int m=11,p=11,n=8,pos;
	KeyType k;
	HashTable H;
	CreateHashTable(&H,m,p,hash,n);
	DisplayHash(H,m);
	k=123;
	pos=SearchHash(H,k);
	printf("�ؼ���%d�ڹ�ϣ���е�λ��Ϊ��%d\n",k,pos);
	HashASL(H,m);
	system("pause");
}