#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t sem[6]; //Criação de um vetor do tipo semáforo (um para cada letra).
int repeticao[7] = {22,5,16,5,1,17,4}; //Criação de um vetor de valores a repetir as letras, conforme especificado.
int length = 6; //Variável auxiliar
 
//Thread para impressão da letra A
void* fun1(void* arg)
{
    int monitor = 0;
    //Loop infinito
    while(1)
    {
        sem_wait(&sem[0]); //Coloca a Thread na espera no semaforo 0
        //Loop para repetição das letras
        for (int i=0; i<repeticao[length]; i++)
            printf("a\n");
        sleep(1);
        length -= 1; //Diminui o valor da variável auxiliar, de maneira a seguir a ordem das repetições
        monitor += 1;
        sem_post(&sem[1]); //Libera a próxima thread, fazendo o post do semáforo
        //Verifica se já cumpriu todas as impressões necessárias
        if (monitor == 2)
            pthread_exit(NULL);
        
    }
}

//Thread para impressão da letra B
void* fun2(void* arg)
{
    int monitor = 0;
    while(1)
    {
        sem_wait(&sem[1]);//Coloca a Thread na espera no semaforo 1
        //Loop para repetição das letras
        for (int i=0; i<repeticao[length]; i++)
            printf("b\n");
        sleep(1);
        length -= 1; //Diminui o valor da variável auxiliar, de maneira a seguir a ordem das repetições
        //Verifica se já cumpriu todas as impressões necessárias
        if (monitor == 0){
            monitor += 1;
            sem_post(&sem[5]); //Libera a próxima thread, fazendo o post do semáforo
        }
        else if (monitor == 1)
        {
            monitor += 1;
            sem_post(&sem[0]); //Libera a próxima thread, fazendo o post do semáforo
        }
        else pthread_exit(NULL);

        
    }
}

//Thread para impressão da letra C
//Como essa letra não necessita ser impressa, ela apenas sai
void* fun3(void* arg)
{
      while(1)
      {
        pthread_exit(NULL);
        printf("c\n");
         
      }
}

//Thread para impressão da letra D
void* fun4(void* arg)
{
    while(1)
    {
        sem_wait(&sem[3]); //Coloca a Thread na espera no semaforo 3
        //Loop para repetição das letras
        for (int i=0; i<repeticao[length]; i++)
            printf("d\n");
        sleep(1);
        length -= 1; //Diminui o valor da variável auxiliar, de maneira a seguir a ordem das repetições
        sem_post(&sem[0]); //Libera a próxima thread, fazendo o post do semáforo
        pthread_exit(NULL);
    }
}

//Thread para impressão da letra E
//Como essa letra não necessita ser impressa, ela apenas sai
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
        sem_wait(&sem[5]); //Coloca a Thread na espera no semaforo 5
        //Loop para repetição das letras
        for (int i=0; i<repeticao[length]; i++)
            printf("f\n");
        sleep(1);
        length -= 1; //Diminui o valor da variável auxiliar, de maneira a seguir a ordem das repetições
        sem_post(&sem[1]); //Libera a próxima thread, fazendo o post do semáforo
        pthread_exit(NULL);
      }
}
int main()
{
      //Cria vetor de Threads (tamanho conforme a quantidade de letras)
      pthread_t id[6];
      
      //Inicia todos os semáforos. Observar que apenas o primeiro inicia "aberto". Ou seja, quando a thread iniciar, já será executada.
      sem_init(&sem[0],0,0);
      sem_init(&sem[1],0,0);
      sem_init(&sem[2],0,0);
      sem_init(&sem[3],0,1); //Semáforo inicia "aberto"
      sem_init(&sem[4],0,0);
      sem_init(&sem[5],0,0);
 
      //Cria todas as Threads ao mesmo tempo
      pthread_create(&id[0],NULL,fun1,NULL);
      pthread_create(&id[1],NULL,fun2,NULL);
      pthread_create(&id[2],NULL,fun3,NULL);
      pthread_create(&id[3],NULL,fun4,NULL);
      pthread_create(&id[4],NULL,fun5,NULL);
      pthread_create(&id[5],NULL,fun6,NULL);
      
      //Espera a finalização de todas as Threads para finalizar o programa
      pthread_join(id[0],NULL);
      pthread_join(id[1],NULL);
      pthread_join(id[2],NULL);
      pthread_join(id[3],NULL);
      pthread_join(id[4],NULL);
      pthread_join(id[5],NULL);
 
      //Finaliza todos os semáforos
      sem_destroy(&sem[0]);
      sem_destroy(&sem[1]);
      sem_destroy(&sem[2]);
      sem_destroy(&sem[3]);
      sem_destroy(&sem[4]);
      sem_destroy(&sem[5]);
 
      exit(0);
}
