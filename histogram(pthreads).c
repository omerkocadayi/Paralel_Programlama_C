#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct arg_struct {
    float data;
    float* bin_maxes;
    int bin_count;
    float min_meas;
};


void Gen_bins(float min_meas,float max_meas,float bin_maxes[], int   bin_counts[],int   bin_count);

void* Which_bin(void* args);

void Print_histo(float bin_maxes[],int bin_counts[],int bin_count ,float min_meas);

int main(int argc, char* argv[]) {
   int bin_count=5, i, bin;
   float min_meas=0.3, max_meas=4.9;
   float bin_maxes[5];
   int* bin_counts;
   int data_count=20;
   float data[]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};

   bin_counts = malloc(bin_count*sizeof(int));
   Gen_bins(min_meas, max_meas, bin_maxes, bin_counts, bin_count);


   // Pthread Kodları
   // #########################################################
   int thread_count = strtol(argv[1], NULL, 10);
   pthread_t* threads = malloc(thread_count*sizeof(pthread_t));
   void* my_bin;
   int temp;
   struct arg_struct* args = malloc(sizeof(struct arg_struct));

   args->bin_maxes = bin_maxes;
   args->bin_count = bin_count;
   args->min_meas = min_meas;
   // #########################################################

   for (i = 0; i < data_count; i++) {
      
      args->data = data[i];

      pthread_create(&threads[i%thread_count], NULL, Which_bin, (void*) args);
      pthread_join(threads[i%thread_count], &my_bin);

      temp = (int) my_bin; 
      bin_counts[temp]++;
   }


   Print_histo(bin_maxes, bin_counts, bin_count, min_meas);

 
   free(bin_counts);
   return 0;

} 
void Gen_bins(float min_meas,float max_meas,float bin_maxes[],int bin_counts[] ,int bin_count) {
   float bin_width;
   int   i;

   bin_width = (max_meas - min_meas)/bin_count;

   for (i = 0; i < bin_count; i++) {
      bin_maxes[i] = min_meas + (i+1)*bin_width;
      bin_counts[i] = 0;
   }

}


void* Which_bin(void* args) {

   struct arg_struct* arguments = (struct arg_struct*) args;

   // Pthreads variables 
   float my_data = arguments->data;
   float* my_bin_maxes = arguments->bin_maxes;
   int my_bin_count = arguments->bin_count;
   float my_min_meas = arguments->min_meas;


   int my_bottom = 0;
   int my_top = my_bin_count - 1;
   int my_mid;
   
   float bin_max, bin_min;

   while (my_bottom <= my_top) {
      my_mid = (my_bottom + my_top)/2;
      bin_max = my_bin_maxes[my_mid];
      bin_min = (my_mid == 0) ? my_min_meas: my_bin_maxes[my_mid-1];
      if (my_data >= bin_max) 
         my_bottom = my_mid+1;
      else if (my_data < bin_min)
         my_top = my_mid-1;
      else
         return (void*) my_mid;
   }

}

void Print_histo(float bin_maxes[],int bin_counts[],int bin_count,float min_meas) {
   int i, j;
   float bin_max, bin_min;

   for (i = 0; i < bin_count; i++) {
      bin_max = bin_maxes[i];
      bin_min = (i == 0) ? min_meas: bin_maxes[i-1];
      printf("%.3f-%.3f:\t", bin_min, bin_max);
      for (j = 0; j < bin_counts[i]; j++)
         printf("X");
      printf("\n");
   }
}
