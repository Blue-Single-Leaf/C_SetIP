/*************************�������뺯������*************************/

/*********

����������get+���ͣ���               ->�����������ĸ��д������������ֵ
		  gets+����(char *s)         ->�����char *s�����ݣ��ٷ�������ֵ
���⣺getStr()��getsStr(char *s)	 ->���ýṹ�壬ʹ��ʱ�ں�߼���.c	�磺char * string1 = getsStr("please Enter a string").c;

*********/
//��������ֵ����
int getInt(){
	int a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
int getsInt(char *c){
	int a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//����short��ֵ����
short getShort(){
	short a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
short getsShort(char *c){
	short a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//���س�����ֵ����
long getLong(){
	long a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
long getsLong(char *c){
	long a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//����double��ֵ����
double getDouble(){
	double a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
double getsDouble(char *c){
	double a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//����float��ֵ����
float getFloat(){
	float a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
float getsFloat(char *c){
	float a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//�����ַ���ֵ����
char getChar(){
	char a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
char getsChar(char *c){
	char a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//�����ַ�����ֵ����
struct str {
	char c[100];
};
struct	str getStr(){
	struct str a;
	gets(a.c);			//the value you should input and then return;
	return a;
}
struct	str getsStr(char *c){
	struct str a;
	printf("%s",c);
	gets(a.c);				//the value you should input and then return;
	return a;
}