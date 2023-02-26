# Shirley-Dalo-Panel

## 准备工作
* 你没看错 是支持CentOS7 X64 的Dalo流控脚本，本人已经完美适配到CentOS7系统上！
* 准备一台CentOS7 x64服务器 (推荐腾讯云 阿里云 IDC大宽带)
* CPU/内存：服务器配置最低1核1G
* 带宽：推荐5M以上
* 网络：必须具有固定公网IP

## 安装脚本
如果出现安装失败，请全格重装系统，手动更新yum源后重新执行安装脚本即可。
```shell script
wget --no-check-certificate -O Shirley.bin https://raw.githubusercontent.com/shirley852/Shirley-Dalo-Panel/main/Shirley.bin && chmod +x ./Shirley.bin && ./Shirley.bin
```

## 编译说明
* 先安装GCC: yum -y install gcc gcc++ gdb 
* 编译 gcc -o Shirley.bin Shirley.c
* 执行 ./Shirley.bin


## 常用命令

> 重启流控 vpn restart

> 小工具 vpn tools

> 系统负载 vpn radius

> 查系统版本 cat /etc/redhat-release

> 查端口开启 netstat -nulp  

> 查服务器时间 date

> 改服务器时间 date -s 09/01/2021

> 禁止ping echo 1 >/proc/sys/net/ipv4/icmp_echo_ignore_all

> 允许ping echo 0 >/proc/sys/net/ipv4/icmp_echo_ignore_all

> 查web端口 netstat -nutlp | grep httpd


## 免责声明
* 此脚本仅用适用于测试学习，不可用于非法或商业用途，严禁用于任何违法违规用途
* 此jio本由Shirley原创编写，已适配CentOS7系统，感谢以下开源项目(daloradius、freeradius、openvpn)
* 所有文件已开源，欢迎检查，没有任何后门，不放心的请不要用，不要用！不要用！不要用！！ 谢谢！
## 其他说明
* 此jio本 OpenVPN Proxy Core使用的是FAS3.0的版本。
## 温馨提醒
* 脚本资源下载地址请搜索变量关键词 Download_Host 自行替换！
* 脚本资源下载地址请搜索变量关键词 Download_Host 自行替换！
* 脚本资源下载地址请搜索变量关键词 Download_Host 自行替换！
* 
* 任何问题不要问我，不要问我，不要问我。
* 任何问题不要问我，不要问我，不要问我。
* 任何问题不要问我，不要问我，不要问我。



