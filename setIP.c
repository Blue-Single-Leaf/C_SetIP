#include<stdlib.h>							//调用命令行的类库
#include<string.h>							//字符串类库
#include<stdio.h>
#include "../myinput.c"						//个人喜欢的输入格式，如下文的getsInt()等等均在此定义
#include "../myfile.c"

/*重命名结构体类型为ipSet，用来存储ip等信息*/
typedef struct {
	char mask[32];			//子网掩码
	char dns[32];			//dns
	char alt_dns[32];		//备用dns
	char ip[32];			//本机Ip
	char gateway[32];		//默认网关
}ipSet;

//main()函数部分
int main(int argc,char *argv[]){
	char *ip,*s_ip;			//s_ip为源ip，输入之后存在，用来保留母本防止操作中被更改;ip为s_ip赋值产生，存放在c[100]中，用来操作
	char c[100]={'\0'};
	void come_on(char *c,char *s_ip,char *ip);
	void show_info();
	show_info();
	s_ip = "127.0.0.1";			//此处为s_ip初始化，无意义，下文重新更改
	ip = c;
	come_on(getsStr("请输入指令：").c,s_ip,ip);
	return 0;
}
/*信息展示*/
void show_info(){
	printf("\n**********************自动开网小程序*************************\n");
	printf("\n此程序为吉大开网小白和小懒专用，提供主dns:10.10.10.10;和备用dns:202.98.18.3\n");
	printf("\n开网一般有以下两步：\n\t1.查本机mac地址\t查完之后上学校网站 ip.jlu.edu.cn/pay 获得ip\n");
	printf("\n\t2.配置本机ip,掩码,网关，DNS");
	printf("\n\n温馨提示：开网请在校园卡里准备好一百元储备\n\n\t  以管理员身份打开  ->鼠标右击此程序在列表里可看到该项\n");
	printf("***************************************************************\n\n");
	printf("本程序使用如下：\n\n");
	printf("\t1.输入 mac ->查本机mac地址\n");
	printf("\n\t2.输入 ip ->进入ip配置步骤\t!请确保你已有ip\n\n你只需将之前获得的ip输入即可(确保以管理员权限运行此程序）\n");
	printf("\n\t3.输入 auto ->设置自动获取IP\n");
	printf("\n\t4.输入 over ->退出\n");
	printf("\n\t5.输入 me ->设置我本人的IP\n");
	printf("\n***************************************************************\n\n");
}
/*程序主体*/
//char *c为指令记录，判断执行查询mac、配置ip还是结束程序over
void come_on(char *c,char *s_ip,char *ip){
	void getMac();
	int i = 0;		//在checkip()中记录输入ip的正确性，1为合理ip，-1为不合理ip;在最后做普通变量，切割ip获得网关
	int *is_ok;	//is_ok指向i,传值给checkip(),记录ip正确性
	is_ok = &i;
	strlwr(c);
	if(strcmp(c,"mac") == 0){
		getMac();										//调用函数获取Mac地址
		printf("将mac记下到  ip.jlu.edu.cn/pay 上去获取ip,然后再以管理员身份打开这个程序输入指令: ip ,再输入你所获得的ip即可\n\n");

		come_on(getsStr("请输入指令：").c,s_ip,ip);		//回调函数
	}
	else if(strcmp(c,"ip") == 0){
		void  checkip(char *v,char *p,int *is_ok);
		char *p_ip[5];										//切割ip时记录用
		char set_ip[200],set_dns[200],set_alt_dns[200];		//三条命令行指令存放
		ipSet myData = {"255.255.255.0","10.10.10.10","202.98.18.3","\0","\0"};		//调用结构体 ipSet类型
		s_ip = getsStr("请输入ip地址:").c;
		strcpy(ip,s_ip);									//备份ip
		checkip(s_ip,ip,is_ok);								//检验ip合理性函数
		while(*is_ok == -1)									//ip不合理则再次输入、检验
		{
			s_ip = getStr().c;
			checkip(s_ip,ip,is_ok);
		}
		strcpy(ip,s_ip);									//重赋ip
		p_ip[0] = strtok(ip,".");							//切割ip
		i = 0;												//****
		while(p_ip[i] != NULL){								
			i++;											//切割ip,注意strtok()的用法
			p_ip[i] = strtok(NULL,".");
		}													//*
		sprintf(myData.ip,s_ip);							//sprintf()字符串输出函数，用来得到ip,和下方的网关，以及三条cmd命令行
		sprintf(myData.gateway,"%s.%s.%s.254",p_ip[0],p_ip[1],p_ip[2]);
		sprintf(set_ip,"netsh interface ip set address \"以太网\" static %s %s %s",myData.ip,myData.mask,myData.gateway);
		sprintf(set_dns,"netsh interface ip set dns \"以太网\" static %s",myData.dns);
		sprintf(set_alt_dns,"netsh interface ip add dns \"以太网\" %s",myData.alt_dns);
		printf("\n******请耐心等等几秒******\n******如果提示DNS不正确或不存在，请检查ip是否输入错误******\n*******如果没有提示，则配置成功，可以使用了********\n\n");
		printf("\n正在配置 ->ip地址:%s\n\t ->子网掩码:%s\n\t ->默认网关:%s\n",myData.ip,myData.mask,myData.gateway);
		system(set_ip);										//system()为命令行函数,执行需管理员权限，下同
		printf("\n正在配置 ->首选DNS服务器:%s\n",myData.dns);
		system(set_dns);
		printf("\n正在配置 ->备用DNS服务器:%s\n",myData.alt_dns);
		system(set_alt_dns);
		come_on(getsStr("请输入指令：").c,s_ip,ip);
	}
	else if(strcmp(c,"over") == 0){
		printf("程序结束\n");
	}
	else if(strcmp(c,"auto") == 0)
	{
		system("netsh interface ip set address name=\"以太网\" source=dhcp");
		system("netsh interface ip set dns name=\"以太网\" source=dhcp");
		printf("设置自动获取ip.\n");
		come_on(getsStr("请输入指令：").c,s_ip,ip);
	}
	else if(strcmp(c,"me") == 0)
	{
		system("netsh interface ip set address \"以太网\" static \"49.140.167.42\" \"255.255.255.0\" \"49.140.167.254\"");
		system("netsh interface ip set dns name=\"以太网\" \"10.10.10.10\"");
		system("netsh interface ip add dns name=\"以太网\" \"202.98.18.3\"");
		printf("已设置我的ip.\n");
		come_on(getsStr("请输入指令：").c,s_ip,ip);
	}
	else {
		printf("无此命令：%s\n命令如下：\n\t1.  mac\t\t->查询本机mac\n\t2.  ip\t\t->配置本机ip地址\n\t3.  over\t->退出\n\n",c);
		come_on(getsStr("请输入指令:").c,s_ip,ip);
	}
}
//检验ip合理性，通过is_ok的值判断，1 -> 合理，-1 -> 不合理
void checkip(char *s_ip,char *ip,int *is_ok){
	int i = 0,j = 0,b = 0;			//i用来判断ip段长度，4为合理;j为普通变量，循环用的;b记录ip格式的正确性，0为正确，正数为不正确
	char *p_ip[5];					//切割ip时记录用
	char buf[64];					//备份ip
	int k = 0;						//判断每段Ip是不越界，超出0 ~ 255范围，0为不超出，正数为超出
	strcpy(buf,s_ip);
	while(1){						//逐个字符判断合理性，看是否包含除数字及不数点之外的其它字符
		if(buf[j] == '\0') break;
		if((buf[j] != '.') && !(buf[j] <= '9' && buf[j] >= '0')) {			//如果该字符不属于'.'和数字1 - 9
			b++;
			break;
		}
		j++;
		
	}
	if(b != 0) {
		printf("你输入的ip地址不正确，ip地址只能包含数字和小数点\n请重新输入：");
		*is_ok = -1;
	}
	else {
		strcpy(ip,s_ip);
		p_ip[0] = strtok(ip,".");			//分割ip，用于判断ip长度合理性
		while(p_ip[i] != NULL){
			i++;
			p_ip[i] = strtok(NULL,".");
		}
		if(i != 4) {
			printf("你输入的ip地址长度不对，请重新输入：");
			*is_ok = -1;
		}
		else {
			for (j = 0;j<4;j++)
				if(atoi(p_ip[j]) <0 || atoi(p_ip[j])>255) k++;		//atoi()：字符串转整型函数，此处判断每段Ip是否在0 ~ 255之间
			if(k > 0){
				printf("你的ip地址越界,ip地址每一位所在区间为0 %c 255;\n请重新输入：",126);
				*is_ok = -1;
			}
			else 
				*is_ok = 1;						//全都正确,设定is_ok = 1
		}
	}
}
/*获取Mac地址函数*/
void getMac(){
	char c[30];				//记录mac地址
	int i = 1;				//记录文件ip_address.txt的行数，便于文件定位到某行
	FILE * fp;				//文件指针，读取ip_address.txt的内容
	int fgotostr(FILE *fp,char *s);				//从当前位置出发，在本行中找某 ->字符串 *s<- 并定位到那儿，返回1，失败刚退回到原位置，返回-1
	int fgotochar(FILE *fp,char k);				//从当前位置出发，在本行中找某 ->字  符  k<- 并定位到那儿，返回1，失败刚退回到原位置，返回-1
	int fgotoline(FILE *fp,int m);				//从文本内容首行首地址开始，定位到第 m 行首地址，行数计算从1开始,第一行除外
	system("ipconfig/all>d:/ip_address.txt");	//命令行查详细信息并写入d:/ip_address.txt中
	if((fp = fopen("d:/ip_address.txt","rb")) == NULL){		//打开 d:/ip_addreess.txt
		printf("can't open this file");
		exit(0);
	}
	while(fgotoline(fp,i) == 1){				//**定位到以太网或本地连接处：从第一行开始，逐行匹配关键字，是则退出，
		i++;									//**此时文件标识位置在关键字处
		if(fgotostr(fp,"以太网适配器 以太网") == 1) break;	
		if(fgotostr(fp,"以太网适配器 本地连接") == 1) break;
	}
	i -=1;
	do{
		i++;
		if(fgotostr(fp,"物理地址") == 1 ) break;
	}
	while(fgotoline(fp,i) == 1);				//再往下逐行匹配"物理地址"关键字，匹配成功退出，文件标识在"址"之后
	fgotochar(fp,':');							//出发定位到':'处，其后即为mac地址
	fgets(c,30*sizeof(c[0]),fp);				//取出mac地址放到c里
	printf("\n此电脑的mac地址为：%s\n\n",c);
	fclose(fp);									//关闭文件
	system("del D:\\ip_address.txt");			//删除d:/ip_address.txt
}

	
