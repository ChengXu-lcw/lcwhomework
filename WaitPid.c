#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc,char **argv)
{  
	int i;
	pid_t pid;
	int process_count=3;
	if(argv[3])
	{
		char *processcount=argv[3];
		process_count=atoi(processcount);
		//约束传入执行子进程个数
		if(process_count<1||process_count>100)
		{
			printf("不好意思，请输入进程数为1～100！\n");
			exit(-1);
		}
	}
	//根据传入进程个数(默认为3个)创建子进程
	for(i=1;i<=process_count;i++)
	{
		pid=fork();
		if(pid==0)
			break;
	}
	if(pid>0)
	{
		printf("父进程%d：吼吼\n",getpid());
	}
	else if(pid==0)
	{
		//将子进程i转化成字符串形式存入buff数组中并当作参数传入execl
		char process_n[8];//第n个进程
		sprintf(process_n,"%d",i);
		char process_all[8];//总进程数
		sprintf(process_all,"%d",process_count);
		printf("子进程：%d父id：%d\n",getpid(),getppid());
		execl("/home/colin/cx/Homework/mycopy","mycopy",argv[1],argv[2],process_all,process_n,NULL);
	}else
	{
		perror("error");
		exit(0);
	}
	//父进程回收子进程
	pid_t wpid;
	while((wpid=waitpid(-1,NULL,WNOHANG))>=0)
	{
		if(wpid>0)
		{
			printf("父进程%d的子进程%d已经被回收\n",getpid(),wpid);
		}
	}
	return 0;
}
