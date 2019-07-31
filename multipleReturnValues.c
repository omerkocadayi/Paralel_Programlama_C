#include <pthread.h>
#include <stdio.h>

void *myThread()
{
   int ret = 42;
   return (void*) ret;
}

int main()
{
   pthread_t* tid = malloc(5*sizeof(pthread_t));
   void *status;
   int i;

   for(i=0;i<5;i++){
   pthread_create(&tid[i], NULL, myThread, NULL);
   pthread_join(tid[i], &status);   
   printf("%d\n",(int) status);// Thread'lerin dönüş değerleri birbirleri
 			       // ne karışmadan ekrana sırayla yazdırılır.
   }

   return 0;
}
