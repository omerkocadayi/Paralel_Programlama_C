#include <pthread.h>
#include <stdio.h>

void *myThread()
{
   int ret = 42;
   return (void*) ret;
}

int main()
{
   pthread_t tid = malloc(sizeof(pthread_t));
   void *status;

   pthread_create(&tid, NULL, myThread, NULL);
   pthread_join(tid, &status);

   printf("%d\n",(int) status);   

   return 0;
}
