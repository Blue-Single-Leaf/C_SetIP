#include<stdlib.h>							//���������е����
#include<string.h>							//�ַ������
#include<stdio.h>
#include "../myinput.c"						//����ϲ���������ʽ�������ĵ�getsInt()�ȵȾ��ڴ˶���
#include "../myfile.c"

/*�������ṹ������ΪipSet�������洢ip����Ϣ*/
typedef struct {
	char mask[32];			//��������
	char dns[32];			//dns
	char alt_dns[32];		//����dns
	char ip[32];			//����Ip
	char gateway[32];		//Ĭ������
}ipSet;

//main()��������
int main(int argc,char *argv[]){
	char *ip,*s_ip;			//s_ipΪԴip������֮����ڣ���������ĸ����ֹ�����б�����;ipΪs_ip��ֵ�����������c[100]�У���������
	char c[100]={'\0'};
	void come_on(char *c,char *s_ip,char *ip);
	void show_info();
	show_info();
	s_ip = "127.0.0.1";			//�˴�Ϊs_ip��ʼ���������壬�������¸���
	ip = c;
	come_on(getsStr("������ָ�").c,s_ip,ip);
	return 0;
}
/*��Ϣչʾ*/
void show_info(){
	printf("\n**********************�Զ�����С����*************************\n");
	printf("\n�˳���Ϊ������С�׺�С��ר�ã��ṩ��dns:10.10.10.10;�ͱ���dns:202.98.18.3\n");
	printf("\n����һ��������������\n\t1.�鱾��mac��ַ\t����֮����ѧУ��վ ip.jlu.edu.cn/pay ���ip\n");
	printf("\n\t2.���ñ���ip,����,���أ�DNS");
	printf("\n\n��ܰ��ʾ����������У԰����׼����һ��Ԫ����\n\n\t  �Թ���Ա��ݴ�  ->����һ��˳������б���ɿ�������\n");
	printf("***************************************************************\n\n");
	printf("������ʹ�����£�\n\n");
	printf("\t1.���� mac ->�鱾��mac��ַ\n");
	printf("\n\t2.���� ip ->����ip���ò���\t!��ȷ��������ip\n\n��ֻ�轫֮ǰ��õ�ip���뼴��(ȷ���Թ���ԱȨ�����д˳���\n");
	printf("\n\t3.���� auto ->�����Զ���ȡIP\n");
	printf("\n\t4.���� over ->�˳�\n");
	printf("\n\t5.���� me ->�����ұ��˵�IP\n");
	printf("\n***************************************************************\n\n");
}
/*��������*/
//char *cΪָ���¼���ж�ִ�в�ѯmac������ip���ǽ�������over
void come_on(char *c,char *s_ip,char *ip){
	void getMac();
	int i = 0;		//��checkip()�м�¼����ip����ȷ�ԣ�1Ϊ����ip��-1Ϊ������ip;���������ͨ�������и�ip�������
	int *is_ok;	//is_okָ��i,��ֵ��checkip(),��¼ip��ȷ��
	is_ok = &i;
	strlwr(c);
	if(strcmp(c,"mac") == 0){
		getMac();										//���ú�����ȡMac��ַ
		printf("��mac���µ�  ip.jlu.edu.cn/pay ��ȥ��ȡip,Ȼ�����Թ���Ա��ݴ������������ָ��: ip ,������������õ�ip����\n\n");

		come_on(getsStr("������ָ�").c,s_ip,ip);		//�ص�����
	}
	else if(strcmp(c,"ip") == 0){
		void  checkip(char *v,char *p,int *is_ok);
		char *p_ip[5];										//�и�ipʱ��¼��
		char set_ip[200],set_dns[200],set_alt_dns[200];		//����������ָ����
		ipSet myData = {"255.255.255.0","10.10.10.10","202.98.18.3","\0","\0"};		//���ýṹ�� ipSet����
		s_ip = getsStr("������ip��ַ:").c;
		strcpy(ip,s_ip);									//����ip
		checkip(s_ip,ip,is_ok);								//����ip�����Ժ���
		while(*is_ok == -1)									//ip���������ٴ����롢����
		{
			s_ip = getStr().c;
			checkip(s_ip,ip,is_ok);
		}
		strcpy(ip,s_ip);									//�ظ�ip
		p_ip[0] = strtok(ip,".");							//�и�ip
		i = 0;												//****
		while(p_ip[i] != NULL){								
			i++;											//�и�ip,ע��strtok()���÷�
			p_ip[i] = strtok(NULL,".");
		}													//*
		sprintf(myData.ip,s_ip);							//sprintf()�ַ�����������������õ�ip,���·������أ��Լ�����cmd������
		sprintf(myData.gateway,"%s.%s.%s.254",p_ip[0],p_ip[1],p_ip[2]);
		sprintf(set_ip,"netsh interface ip set address \"��̫��\" static %s %s %s",myData.ip,myData.mask,myData.gateway);
		sprintf(set_dns,"netsh interface ip set dns \"��̫��\" static %s",myData.dns);
		sprintf(set_alt_dns,"netsh interface ip add dns \"��̫��\" %s",myData.alt_dns);
		printf("\n******�����ĵȵȼ���******\n******�����ʾDNS����ȷ�򲻴��ڣ�����ip�Ƿ��������******\n*******���û����ʾ�������óɹ�������ʹ����********\n\n");
		printf("\n�������� ->ip��ַ:%s\n\t ->��������:%s\n\t ->Ĭ������:%s\n",myData.ip,myData.mask,myData.gateway);
		system(set_ip);										//system()Ϊ�����к���,ִ�������ԱȨ�ޣ���ͬ
		printf("\n�������� ->��ѡDNS������:%s\n",myData.dns);
		system(set_dns);
		printf("\n�������� ->����DNS������:%s\n",myData.alt_dns);
		system(set_alt_dns);
		come_on(getsStr("������ָ�").c,s_ip,ip);
	}
	else if(strcmp(c,"over") == 0){
		printf("�������\n");
	}
	else if(strcmp(c,"auto") == 0)
	{
		system("netsh interface ip set address name=\"��̫��\" source=dhcp");
		system("netsh interface ip set dns name=\"��̫��\" source=dhcp");
		printf("�����Զ���ȡip.\n");
		come_on(getsStr("������ָ�").c,s_ip,ip);
	}
	else if(strcmp(c,"me") == 0)
	{
		system("netsh interface ip set address \"��̫��\" static \"49.140.167.42\" \"255.255.255.0\" \"49.140.167.254\"");
		system("netsh interface ip set dns name=\"��̫��\" \"10.10.10.10\"");
		system("netsh interface ip add dns name=\"��̫��\" \"202.98.18.3\"");
		printf("�������ҵ�ip.\n");
		come_on(getsStr("������ָ�").c,s_ip,ip);
	}
	else {
		printf("�޴����%s\n�������£�\n\t1.  mac\t\t->��ѯ����mac\n\t2.  ip\t\t->���ñ���ip��ַ\n\t3.  over\t->�˳�\n\n",c);
		come_on(getsStr("������ָ��:").c,s_ip,ip);
	}
}
//����ip�����ԣ�ͨ��is_ok��ֵ�жϣ�1 -> ����-1 -> ������
void checkip(char *s_ip,char *ip,int *is_ok){
	int i = 0,j = 0,b = 0;			//i�����ж�ip�γ��ȣ�4Ϊ����;jΪ��ͨ������ѭ���õ�;b��¼ip��ʽ����ȷ�ԣ�0Ϊ��ȷ������Ϊ����ȷ
	char *p_ip[5];					//�и�ipʱ��¼��
	char buf[64];					//����ip
	int k = 0;						//�ж�ÿ��Ip�ǲ�Խ�磬����0 ~ 255��Χ��0Ϊ������������Ϊ����
	strcpy(buf,s_ip);
	while(1){						//����ַ��жϺ����ԣ����Ƿ���������ּ�������֮��������ַ�
		if(buf[j] == '\0') break;
		if((buf[j] != '.') && !(buf[j] <= '9' && buf[j] >= '0')) {			//������ַ�������'.'������1 - 9
			b++;
			break;
		}
		j++;
		
	}
	if(b != 0) {
		printf("�������ip��ַ����ȷ��ip��ַֻ�ܰ������ֺ�С����\n���������룺");
		*is_ok = -1;
	}
	else {
		strcpy(ip,s_ip);
		p_ip[0] = strtok(ip,".");			//�ָ�ip�������ж�ip���Ⱥ�����
		while(p_ip[i] != NULL){
			i++;
			p_ip[i] = strtok(NULL,".");
		}
		if(i != 4) {
			printf("�������ip��ַ���Ȳ��ԣ����������룺");
			*is_ok = -1;
		}
		else {
			for (j = 0;j<4;j++)
				if(atoi(p_ip[j]) <0 || atoi(p_ip[j])>255) k++;		//atoi()���ַ���ת���ͺ������˴��ж�ÿ��Ip�Ƿ���0 ~ 255֮��
			if(k > 0){
				printf("���ip��ַԽ��,ip��ַÿһλ��������Ϊ0 %c 255;\n���������룺",126);
				*is_ok = -1;
			}
			else 
				*is_ok = 1;						//ȫ����ȷ,�趨is_ok = 1
		}
	}
}
/*��ȡMac��ַ����*/
void getMac(){
	char c[30];				//��¼mac��ַ
	int i = 1;				//��¼�ļ�ip_address.txt�������������ļ���λ��ĳ��
	FILE * fp;				//�ļ�ָ�룬��ȡip_address.txt������
	int fgotostr(FILE *fp,char *s);				//�ӵ�ǰλ�ó������ڱ�������ĳ ->�ַ��� *s<- ����λ���Ƕ�������1��ʧ�ܸ��˻ص�ԭλ�ã�����-1
	int fgotochar(FILE *fp,char k);				//�ӵ�ǰλ�ó������ڱ�������ĳ ->��  ��  k<- ����λ���Ƕ�������1��ʧ�ܸ��˻ص�ԭλ�ã�����-1
	int fgotoline(FILE *fp,int m);				//���ı����������׵�ַ��ʼ����λ���� m ���׵�ַ�����������1��ʼ,��һ�г���
	system("ipconfig/all>d:/ip_address.txt");	//�����в���ϸ��Ϣ��д��d:/ip_address.txt��
	if((fp = fopen("d:/ip_address.txt","rb")) == NULL){		//�� d:/ip_addreess.txt
		printf("can't open this file");
		exit(0);
	}
	while(fgotoline(fp,i) == 1){				//**��λ����̫���򱾵����Ӵ����ӵ�һ�п�ʼ������ƥ��ؼ��֣������˳���
		i++;									//**��ʱ�ļ���ʶλ���ڹؼ��ִ�
		if(fgotostr(fp,"��̫�������� ��̫��") == 1) break;	
		if(fgotostr(fp,"��̫�������� ��������") == 1) break;
	}
	i -=1;
	do{
		i++;
		if(fgotostr(fp,"�����ַ") == 1 ) break;
	}
	while(fgotoline(fp,i) == 1);				//����������ƥ��"�����ַ"�ؼ��֣�ƥ��ɹ��˳����ļ���ʶ��"ַ"֮��
	fgotochar(fp,':');							//������λ��':'�������Ϊmac��ַ
	fgets(c,30*sizeof(c[0]),fp);				//ȡ��mac��ַ�ŵ�c��
	printf("\n�˵��Ե�mac��ַΪ��%s\n\n",c);
	fclose(fp);									//�ر��ļ�
	system("del D:\\ip_address.txt");			//ɾ��d:/ip_address.txt
}

	
