#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>   //类型相关
#include<sys/stat.h>    //状态相关
#include<fcntl.h>       //属性相关
#include<string.h>

int main(int argc,char **argv)
{
	//参数个数不能小于5
    if(argc<5)
	{
     printf("输入数据异常！\n");
	 exit(-1);
	}
   //源文件
   int file1=open(argv[1],O_RDONLY);
   //目标文件，需要自行创建
   int file2=open(argv[2],O_WRONLY|O_CREAT,0664);
   //将传入的总进程数，第n个进程的字符串格式转换为整形
   int process_all=atoi(argv[3]);
   int process_n=atoi(argv[4]);
   
   //获取原文件大小
   int file1_size=lseek(file1,0,SEEK_END);
   //计算每一个子进程需要拷贝文件字节数的大小
   int size=file1_size/process_all+1;
   char a[size];
   bzero(a,size);
   //偏移读写指针位置
   lseek(file1,(process_n-1)*size,SEEK_SET);
   lseek(file2,(process_n-1)*size,SEEK_SET);
   int lenth=read(file1,a,size);
   write(file2,a,size); 
   //文件描述符进程结束要关闭，防止内存泄漏
   close(file1);
   close(file2);

	return 0;
}
