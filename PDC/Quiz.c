#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

sem_t hair;
sem_t makeup;
void* customer (void* arg) {
    int id = *(int*)arg;

    printf("Customer %d is waiting for hairdresser...\n", id);
    sem_wait(&hair);
    printf("Customer %d is getting a haircut.\n", id);
    sleep(1); 
    printf("Customer %d has finished the haircut.\n", id);
    sem_post(&hair);

    printf("Customer %d is waiting for makeup artist...\n", id);
    sem_wait(&makeup);
    printf("Customer %d is getting makeup done.\n", id);
    sleep(1); 
    printf("Customer %d has finished the makeup.\n", id);
    sem_post(&makeup);
    

    return NULL;
}
int main(){
    pthread_t t[6]
    sem_init(&hair,0,2);
      sem_init(&makeup,0,1);
      for (int i=0;i<6;i++)
      pthread_create (&t[i],NULL)
    

}


