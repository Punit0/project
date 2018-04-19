#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

sem_t mutex,empty,full;//semaphore objects/variables
static int buff=0;
void *producer();
void *consumer();
int main()
{
    int a,h;
    pthread_t pro,con;//Threads
	sem_init(&mutex,2,1);//(initialize semaphore object pointed to by mutex,local(0) or shared(non 0),initalise object value
	sem_init(&empty,2,10);
	sem_init(&full,2,0);
	/*semaphore mutex = 1;
	semaphore empty = n;
	semaphore full = 0
	*/
    

do
{
	
printf("\n\t\tEnter one of the following");
printf("\n\t\tEnter 1 for producer");
printf("\n\t\tEnter 2 for consumer\n");
scanf("%d",&a);
if(a==1)
{
pthread_create(&pro,NULL,producer,NULL);

pthread_join(pro,NULL);

}
else if(a==2)
{
pthread_create(&con,NULL,consumer,NULL);
pthread_join(con,NULL);

}
else
{
printf("\n\t\twrong choice try again");
}
printf("\n\t\tPress 1 to produce or consume again ");
scanf("%d",&h);
}
while(h==1);
    return 0;
}

void *producer()
{

		sem_wait(&empty);//decrement empty
		sem_wait(&mutex);//get lock
		if(buff<10)
			{
			buff++;
			printf("\nItem produced and Buffer= %d",buff);
			}
		else
		printf("\nBuffer is full ,Consume some items");
		sem_post(&mutex);//leave lock
		sem_post(&full);//increment full
}

void *consumer()
{

		sem_wait(&full);//decrement full
		sem_wait(&mutex);//get lock
		if(buff!=0)
			{
			buff--;
			printf("\nItem consumed and Buffer= %d",buff);
			}
		else if(buff==0)
			printf("\nBuffer is empty ,Produce some items");
		sem_post(&mutex);//leave lock
		sem_post(&empty);//increment empty

	
}
