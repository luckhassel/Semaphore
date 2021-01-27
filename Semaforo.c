#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t sem[6];
int repeticao[7] = {22,5,16,5,1,17,4};
int length = 6;
 
void* fun1(void* arg)
{
    int monitor = 0;
    while(1)
    {
        sem_wait(&sem[0]);
        for (int i=0; i<repeticao[length]; i++)
            printf("a\n");
        sleep(1);
        length -= 1;
        monitor += 1;
        sem_post(&sem[1]);
        if (monitor == 2)
            pthread_exit(NULL);
        
    }
}
void* fun2(void* arg)
{
    int monitor = 0;
    while(1)
    {
        sem_wait(&sem[1]);
        for (int i=0; i<repeticao[length]; i++)
            printf("b\n");
        sleep(1);
        length -= 1;
        if (monitor == 0){
            monitor += 1;
            sem_post(&sem[5]);
        }
        else if (monitor == 1)
        {
            monitor += 1;
            sem_post(&sem[0]);
        }
        else pthread_exit(NULL);

        
    }
}
void* fun3(void* arg)
{
      while(1)
      {
        pthread_exit(NULL);
        printf("c\n");
         
      }
}

void* fun4(void* arg)
{
    while(1)
    {
        sem_wait(&sem[3]);
        for (int i=0; i<repeticao[length]; i++)
            printf("d\n");
        sleep(1);
        length -= 1;
        sem_post(&sem[0]);
        pthread_exit(NULL);
    }
}

void* fun5(void* arg)
{
      while(1)
      {
        pthread_exit(NULL);
        printf("e\n");
      }
}

void* fun6(void* arg)
{
      while(1)
      {
        sem_wait(&sem[5]);
        for (int i=0; i<repeticao[length]; i++)
            printf("f\n");
        sleep(1);
        length -= 1;
        sem_post(&sem[1]);
        pthread_exit(NULL);
      }
}
int main()
{
      pthread_t id[6];

      sem_init(&sem[0],0,0);
      sem_init(&sem[1],0,0);
      sem_init(&sem[2],0,0);
      sem_init(&sem[3],0,1);
      sem_init(&sem[4],0,0);
      sem_init(&sem[5],0,0);
 
      pthread_create(&id[0],NULL,fun1,NULL);
      pthread_create(&id[1],NULL,fun2,NULL);
      pthread_create(&id[2],NULL,fun3,NULL);
      pthread_create(&id[3],NULL,fun4,NULL);
      pthread_create(&id[4],NULL,fun5,NULL);
      pthread_create(&id[5],NULL,fun6,NULL);
 
      pthread_join(id[0],NULL);
      pthread_join(id[1],NULL);
      pthread_join(id[2],NULL);
      pthread_join(id[3],NULL);
      pthread_join(id[4],NULL);
      pthread_join(id[5],NULL);
 
      sem_destroy(&sem[0]);
      sem_destroy(&sem[1]);
      sem_destroy(&sem[2]);
      sem_destroy(&sem[3]);
      sem_destroy(&sem[4]);
      sem_destroy(&sem[5]);
 
      exit(0);
}