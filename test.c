#include<pthread.h>

#include"event.h"

void *test_body()
{

	int want=6;
	int timeout=2*1000*1000;
	int events;
	pthread_detach(pthread_self());
	event_wait(0, want,timeout, &events);
	if(events)
	{
		printf("have events:%d\n",events);
	}
	else
	{
		printf("no events:%d\n",events);
	}
}
int main()
{
	pthread_t tid;
	event_open();
	pthread_create(&tid,NULL,test_body,NULL);
	sleep(1);
	event_post(0,3);
	sleep(3);
}
