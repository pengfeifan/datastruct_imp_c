#include<stdio.h>
#include<stdlib.h>
typedef struct{
	char *str;
	int length;
}HeapString;
//���ĸ�ֵ����
void StrAssign(HeapString *S,char cstr[]){
	int i=0,len;
	if(S->str)
		free(S->str);
	for(i=0;cstr[i]!='\0';i++);	//��cstr�ַ����ĳ���
	len=i;
	if(!i){
		S->str=NULL;
		S->length=0;
	}else{
		S->str=(char *)malloc((len+1)*sizeof(char));
		if(!S->str)
			exit(-1);
		for(i=0;i<len;i++)
			S->str[i]=cstr[i];
		S->length=len;
	}
}
//�жϴ��Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0
int StrEmpty(HeapString S){
	if(S.length==0)
		return 1;
	else
		return 0;
}
//�󴮵ĳ��Ȳ���
int StrLength(HeapString S){
	return S.length;
}
//���ĸ��Ʋ���
void StrCopy(HeapString *T,HeapString S){
	int i;
	T->str=(char *)malloc(S.length*sizeof(char));
	if(!T->str)
		exit(-1);
	for(i=0;i<S.length;i++)	//����S���ַ���ֵ����T
		T->str[i]=S.str[i];
	T->length=S.length;	//����S�ĳ��ȸ�ֵ����T
}
//���ıȽϲ���
int StrCompare(HeapString S,HeapString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++)	//�Ƚ��������е��ַ�
		if(S.str[i]!=T.str[i])	//��������ַ���ͬ���򷵻������ַ��Ĳ�ֵ
			return (S.str[i]-T.str[i]);
	return (S.length-T.length);	//����Ƚ���ϣ������������ĳ��ȵĲ�ֵ
}
//���Ĳ����������S�е�pos��λ�ò���T
int StrInsert(HeapString *S,int pos,HeapString T){
	int i;
	if(pos<0||pos-1>S->length){		//����λ�ò���ȷ������0
		printf("����λ�ò���ȷ");
		return 0;
	}
	S->str=(char *)realloc(S->str,(S->length+T.length)*sizeof(char));
	if(!S->str){
		printf("�ڴ����ʧ��");
		exit(-1);
	}
	for(i=S->length-1;i>=pos-1;i--)
		S->str[i+T.length]=S->str[i];
	for(i=0;i<T.length;i++)
		S->str[pos+i-1]=T.str[i];
	S->length=S->length+T.length;
	return 1;
}
//�ڴ�S��ɾ��pos��ʼ��len���ַ�
int StrDelete(HeapString *S,int pos,int len){
	int i;
	char *p;
	if(pos<0||len<0||pos+len-1>S->length){
		printf("ɾ��λ�ò���ȷ������len���Ϸ�");
		return 0;
	}
	p=(char *)malloc((S->length-len)*sizeof(char));	//pָ��̬������ڴ浥Ԫ
	if(!p)
		exit(-1);
	for(i=0;i<pos-1;i++)	//������posλ��֮ǰ���ַ����Ƶ�p��
		p[i]=S->str[i];
	for(i=pos-1;i<S->length-len;i++)	//������pos+lenλ���Ժ���ַ����Ƶ�p��
		p[i]=S->str[i+len];
	S->length=S->length-len;	//�޸Ĵ��ĳ���
	free(S->str);		//�ͷ�ԭ���Ĵ�S���ڴ�ռ�
	S->str=p;	//������strָ��p�ַ���
	return 1;
}
//����S�����ڴ�T�ĺ���
int StrCat(HeapString *T,HeapString S){
	int i;
	T->str=(char *)realloc(T->str,(T->length+S.length)*sizeof(char));
	if(!T->str){
		printf("����ռ�ʧ��");
		exit(-1);
	}else{
		for(i=T->length;i<T->length+S.length;i++)
			T->str[i]=S.str[i-T->length];	//��Sֱ��������T��ĩβ
		T->length+=S.length;	//�޸Ĵ�T�ĳ���
	}
	return 1;
}
//���Ӵ�S�еĵ�pos��λ�ý�ȡ����Ϊlen���Ӵ���ֵ��Sub
int SubString(HeapString *Sub,HeapString S,int pos,int len){
	int i;
	if(Sub->str)
		free(Sub->str);
	if(pos<0||len<0||pos+len-1>S.length){
		printf("����pos��len���Ϸ�");
		return 0;
	}else{
		Sub->str=(char *)malloc(len*sizeof(char));
		if(!Sub->str){
			printf("�洢����ʧ��");
			exit(-1);
		}
		for(i=0;i<len;i++)	//����S�ĵ�pos��λ�ó���Ϊlen���ַ���ֵ��Sub
			Sub->str[i]=S.str[pos+i-1];
		Sub->length=len;
		return 1;
	}
}
//������S�еĵ�pos��λ�ÿ�ʼ�����Ӵ�T������ҵ������Ӵ���������λ�ã����򣬷���0
int StrIndex(HeapString S,int pos,HeapString T){
	int i,j;
	if(StrEmpty(T))	//�����TΪ�գ��򷵻�0
		return 0;
	i=pos;
	j=0;
	while(i<S.length&&j<T.length){
		if(S.str[i]==T.str[j]){	//�����S�ʹ�T�ж�Ӧλ���ַ���ȣ�������Ƚ���һ���ַ�
			i++;
			j++;
		}else{	//�����ǰ��Ӧλ�õ��ַ�����ȣ���Ӵ�S����һ���ַ���ʼ��T�ĵ�0���ַ���ʼ�Ƚ�
			i=i-j+1;
			j=0;
		}
	}
	if(j>=T.length)
		return i-j+1;	//�����S���ҵ���T���򷵻��Ӵ�T������S��λ��
	else
		return 0;
}
//����S�е������Ӵ�T��V�滻
int StrReplace(HeapString *S,HeapString T,HeapString V){
	int i=0;
	int flag;
	if(StrEmpty(T))
		return 0;
	do{
		i=StrIndex(*S,i,T);	//���ô��Ķ�λ�����ڴ�S�в���T��λ��
		if(i){
			StrDelete(S,i,StrLength(T));	//����ҵ��Ӵ�T����S�еĴ�Tɾ��
			flag=StrInsert(S,i,V);		//���Ӵ�V���뵽ԭ��ɾ��T��λ��
			if(!flag)		//���û�в���ɹ����򷵻�0
				return 0;
			i+=StrLength(V);		//�ڴ�S�У������Ӵ�V���ȸ��ַ�����������T
		}
	}while(i);
	return 1;
}
//��մ���ֻ��Ҫ�����ĳ�����Ϊ0����
void StrClear(HeapString *S){
	S->str='\0';
	S->length=0;
}
//���ĳ�ʼ������
void InitString(HeapString *S){
	S->length=0;
	S->str='\0';
}
//���ٴ�
void StrDestroy(HeapString *S){
	if(S->str)
		free(S->str);
}
void StrPrint(HeapString S){
	int i;
	for(i=0;i<S.length;i++){
		printf("%c",S.str[i]);
	}
	printf("\n");
}
void main(){
	HeapString S1,S2,Sub;
	char *p;
	char ch[50];
	/*��ʼ����S1��S2��Sub*/	
	InitString(&S1);
	InitString(&S2);
	InitString(&Sub);
	printf("�������һ���ַ�����");
	gets(ch);
	StrAssign(&S1,ch);				/*ͨ�����뽫��S1��ֵ*/
	printf("������ֵ������Ĵ�S1��\n");
	StrPrint(S1);
	printf("������ڶ����ַ�����");
	gets(ch);
	StrAssign(&S2,ch);				/*ͨ�����뽫��S2��ֵ*/
	printf("������ֵ������Ĵ�S2��\n");
	StrPrint(S2);
	printf("�Ѵ�S2�����ڴ�S1��ĩβ��S1��Ϊ��\n");
	StrCat(&S1,S2);					/*����S2�����ڴ�S1��ĩβ*/
	StrPrint(S1);
	printf("������ֵ������Ĵ�Sub��\n");
	StrAssign(&Sub,"Everyone");		/*����Sub��ֵ*/
	StrPrint(Sub);
	printf("����S2���뵽��S1�ĵ�һλ�ã�\n");
	StrInsert(&S1,1,Sub);			/*����Sub���뵽��S1�ĵ�һλ��*/
	StrPrint(S1);
	printf("�Ѵ�S1�ĵ�1��λ��֮���8���ַ�ɾ����\n");
	StrDelete(&S1,1,8);				/*����S1�ĵ�һλ�ú��8���ַ�ɾ��*/
	StrPrint(S1);
	printf("����S1�е�S2�û�ΪSub��\n");
	StrAssign(&Sub,"Xi'an");		/*����Sub���¸�ֵ*/
	StrReplace(&S1,S2,Sub);			/*�ô�Subȡ����S1�е�S2*/
	StrPrint(S1);
	/*����S1��S2��Sub���ڴ浥Ԫ�ͷ�*/
	StrDestroy(&S1);
	StrDestroy(&S2);
	StrDestroy(&Sub);
	system("pause");
}