#include<stdio.h>
#include<stdlib.h>
typedef struct{
	char *str;
	int length;
}HeapString;
//串的赋值操作
void StrAssign(HeapString *S,char cstr[]){
	int i=0,len;
	if(S->str)
		free(S->str);
	for(i=0;cstr[i]!='\0';i++);	//求cstr字符串的长度
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
//判断串是否为空，串为空返回1，否则返回0
int StrEmpty(HeapString S){
	if(S.length==0)
		return 1;
	else
		return 0;
}
//求串的长度操作
int StrLength(HeapString S){
	return S.length;
}
//串的复制操作
void StrCopy(HeapString *T,HeapString S){
	int i;
	T->str=(char *)malloc(S.length*sizeof(char));
	if(!T->str)
		exit(-1);
	for(i=0;i<S.length;i++)	//将串S的字符赋值给串T
		T->str[i]=S.str[i];
	T->length=S.length;	//将串S的长度赋值给串T
}
//串的比较操作
int StrCompare(HeapString S,HeapString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++)	//比较两个串中的字符
		if(S.str[i]!=T.str[i])	//如果出现字符不同，则返回两个字符的差值
			return (S.str[i]-T.str[i]);
	return (S.length-T.length);	//如果比较完毕，返回两个串的长度的差值
}
//串的插入操作。在S中第pos个位置插入T
int StrInsert(HeapString *S,int pos,HeapString T){
	int i;
	if(pos<0||pos-1>S->length){		//插入位置不正确，返回0
		printf("插入位置不正确");
		return 0;
	}
	S->str=(char *)realloc(S->str,(S->length+T.length)*sizeof(char));
	if(!S->str){
		printf("内存分配失败");
		exit(-1);
	}
	for(i=S->length-1;i>=pos-1;i--)
		S->str[i+T.length]=S->str[i];
	for(i=0;i<T.length;i++)
		S->str[pos+i-1]=T.str[i];
	S->length=S->length+T.length;
	return 1;
}
//在串S中删除pos开始的len个字符
int StrDelete(HeapString *S,int pos,int len){
	int i;
	char *p;
	if(pos<0||len<0||pos+len-1>S->length){
		printf("删除位置不正确，参数len不合法");
		return 0;
	}
	p=(char *)malloc((S->length-len)*sizeof(char));	//p指向动态分配的内存单元
	if(!p)
		exit(-1);
	for(i=0;i<pos-1;i++)	//将串第pos位置之前的字符复制到p中
		p[i]=S->str[i];
	for(i=pos-1;i<S->length-len;i++)	//将串第pos+len位置以后的字符复制到p中
		p[i]=S->str[i+len];
	S->length=S->length-len;	//修改串的长度
	free(S->str);		//释放原来的串S的内存空间
	S->str=p;	//将串的str指向p字符串
	return 1;
}
//将串S连接在串T的后面
int StrCat(HeapString *T,HeapString S){
	int i;
	T->str=(char *)realloc(T->str,(T->length+S.length)*sizeof(char));
	if(!T->str){
		printf("分配空间失败");
		exit(-1);
	}else{
		for(i=T->length;i<T->length+S.length;i++)
			T->str[i]=S.str[i-T->length];	//串S直接连接在T的末尾
		T->length+=S.length;	//修改串T的长度
	}
	return 1;
}
//将从串S中的第pos个位置截取长度为len的子串赋值给Sub
int SubString(HeapString *Sub,HeapString S,int pos,int len){
	int i;
	if(Sub->str)
		free(Sub->str);
	if(pos<0||len<0||pos+len-1>S.length){
		printf("参数pos和len不合法");
		return 0;
	}else{
		Sub->str=(char *)malloc(len*sizeof(char));
		if(!Sub->str){
			printf("存储分配失败");
			exit(-1);
		}
		for(i=0;i<len;i++)	//将串S的第pos个位置长度为len的字符赋值给Sub
			Sub->str[i]=S.str[pos+i-1];
		Sub->length=len;
		return 1;
	}
}
//在主串S中的第pos个位置开始查找子串T，如果找到返回子串在主串的位置；否则，返回0
int StrIndex(HeapString S,int pos,HeapString T){
	int i,j;
	if(StrEmpty(T))	//如果串T为空，则返回0
		return 0;
	i=pos;
	j=0;
	while(i<S.length&&j<T.length){
		if(S.str[i]==T.str[j]){	//如果串S和串T中对应位置字符相等，则继续比较下一个字符
			i++;
			j++;
		}else{	//如果当前对应位置的字符不相等，则从串S的下一个字符开始，T的第0个字符开始比较
			i=i-j+1;
			j=0;
		}
	}
	if(j>=T.length)
		return i-j+1;	//如果在S中找到串T，则返回子串T在主串S的位置
	else
		return 0;
}
//将串S中的所有子串T用V替换
int StrReplace(HeapString *S,HeapString T,HeapString V){
	int i=0;
	int flag;
	if(StrEmpty(T))
		return 0;
	do{
		i=StrIndex(*S,i,T);	//利用串的定位函数在串S中查找T的位置
		if(i){
			StrDelete(S,i,StrLength(T));	//如果找到子串T，则将S中的串T删除
			flag=StrInsert(S,i,V);		//将子串V插入到原来删除T的位置
			if(!flag)		//如果没有插入成功，则返回0
				return 0;
			i+=StrLength(V);		//在串S中，跳过子串V长度个字符，继续查找T
		}
	}while(i);
	return 1;
}
//清空串，只需要将串的长度置为0即可
void StrClear(HeapString *S){
	S->str='\0';
	S->length=0;
}
//串的初始化操作
void InitString(HeapString *S){
	S->length=0;
	S->str='\0';
}
//销毁串
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
	/*初始化串S1，S2和Sub*/	
	InitString(&S1);
	InitString(&S2);
	InitString(&Sub);
	printf("请输入第一个字符串：");
	gets(ch);
	StrAssign(&S1,ch);				/*通过输入将串S1赋值*/
	printf("经过赋值操作后的串S1：\n");
	StrPrint(S1);
	printf("请输入第二个字符串：");
	gets(ch);
	StrAssign(&S2,ch);				/*通过输入将串S2赋值*/
	printf("经过赋值操作后的串S2：\n");
	StrPrint(S2);
	printf("把串S2连接在串S1的末尾，S1串为：\n");
	StrCat(&S1,S2);					/*将串S2连接在串S1的末尾*/
	StrPrint(S1);
	printf("经过赋值操作后的串Sub：\n");
	StrAssign(&Sub,"Everyone");		/*将串Sub赋值*/
	StrPrint(Sub);
	printf("将串S2插入到串S1的第一位置：\n");
	StrInsert(&S1,1,Sub);			/*将串Sub插入到串S1的第一位置*/
	StrPrint(S1);
	printf("把串S1的第1个位置之后的8个字符删除：\n");
	StrDelete(&S1,1,8);				/*将串S1的第一位置后的8个字符删除*/
	StrPrint(S1);
	printf("将串S1中的S2置换为Sub：\n");
	StrAssign(&Sub,"Xi'an");		/*将串Sub重新赋值*/
	StrReplace(&S1,S2,Sub);			/*用串Sub取代串S1中的S2*/
	StrPrint(S1);
	/*将串S1，S2和Sub的内存单元释放*/
	StrDestroy(&S1);
	StrDestroy(&S2);
	StrDestroy(&Sub);
	system("pause");
}