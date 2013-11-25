#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

#include "event.h"

typedef struct
{
int fd;
pid_t pid;
pthread_t tid;
int post_events;
int wait_events;
}EVENT_S;

static EVENT_S event_s;
void event_body(void *arg)
{
	printf("event_body\n");
	pthread_detach(pthread_self());
	event_s.tid=pthread_self();
	event_s.pid=getpid();
	while(1)
	{
		usleep(1*1000*1000);
		printf("usleep(1s)\n");
	}
}
/******************************************************************************
 * 函数介绍: 创建EVENT
 * 输入参数: 无
 * 输出参数: 无
 * 返回值  : <0-失败,>0-EVENT句柄
 *****************************************************************************/
sint32 event_open(void)
{
	event_s.fd=0x12345678;
//	pthread_create(&event_s.tid,NULL,event_body,NULL);
	event_s.post_events=0;
	event_s.wait_events=0;
	return 0;
}

/******************************************************************************
 * 函数介绍: 等待事件
 * 输入参数: handle: 事件句柄
 *           want: 欲接收的event
 * 输出参数: events: 接收到的事件消息
 * 返回值  : <0-失败,0-成功
 *****************************************************************************/
sint32 event_wait(sint32 handle, sint32 want,int timeout, sint32 * events)
{
	int i;
	int time_flag=0;
	if(0 != timeout)
	{
		time_flag=1;
	}
	event_s.wait_events=want;
	*events=0;

	while(1)
	{
		if(event_s.post_events & event_s.wait_events)
		{
			*events =event_s.post_events & event_s.wait_events;
			break;
		}
		if(1 == time_flag)
		{
			if(!timeout)
			{
				break;
			}
			timeout -= 10;			
		}
		usleep(10);
	}	

	event_s.wait_events=0;
	event_s.post_events=0;
	return 0;
}

/******************************************************************************
 * 函数介绍: 发送事件
 * 输入参数: event: 事件句柄
 * 输出参数: events: 待发送事件
 * 返回值  : <0-失败,0-成功
 *****************************************************************************/
sint32 event_post(sint32 handle, sint32 events)
{
	event_s.post_events |= events;
}

/******************************************************************************
 * 函数介绍: 销毁事件,释放资源
 * 输入参数: event: 事件句柄
 * 输出参数: 无
 * 返回值  : <0-失败,0-成功
 *****************************************************************************/
sint32 event_close(sint32 handle);

