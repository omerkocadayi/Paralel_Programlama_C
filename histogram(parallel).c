#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int find_bin(float data,float bin_maxes[],int bin_count ,float min_meas );
void printHistogram(float bin_maxes[],int bin_counts[],int bin_count ,float min_meas);


int main(int argc, char* argv[]) {
	clock_t begin, end;
	double runtime;

	int data_count=20;
   	float data[]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};
   	float min_meas=0.3;
   	float max_meas=4.9;
   	int bin_count=5, i;
   	float bin_maxes[5];
   	int* bin_counts;
   	float bin_width = (max_meas - min_meas)/bin_count;

   	// Clock starts
   	begin = clock();

   	bin_counts = malloc(bin_count*sizeof(int));

    #pragma omp parallel num_threads(10)
    {
        #pragma omp for
        for (i = 0; i < bin_count; i++) {
            bin_maxes[i] = min_meas + (i+1)*bin_width;
            bin_counts[i] = 0;
        }

        #pragma omp barrier

        int bin;

        #pragma omp for
   	    for (i = 0; i < data_count; i++) {
      	    bin = find_bin(data[i], bin_maxes, bin_count, min_meas);
            
            #pragma omp critical
            bin_counts[bin]++;
   	    }
    }

   	printHistogram(bin_maxes, bin_counts, bin_count, min_meas);
   	free(bin_counts);

    // Clock ends
   	end = clock();
   	runtime = (double)(end - begin) / CLOCKS_PER_SEC;
   	printf("\n\nRuntime : %f\n\n", runtime);

   	return 0;

}

int find_bin(float data,float bin_maxes[],int bin_count,float min_meas) {
   	int bottom = 0, top =  bin_count-1;
   	int mid;
   	float bin_max, bin_min;

   	while (bottom <= top) {
      	mid = (bottom + top)/2;
      	bin_max = bin_maxes[mid];
      	bin_min = (mid == 0) ? min_meas: bin_maxes[mid-1];

      	if (data >= bin_max)
         	bottom = mid+1;
      	else if (data < bin_min)
         	top = mid-1;
      	else
         	return mid;
   	}
}

void printHistogram(float bin_maxes[],int bin_counts[],int bin_count,float min_meas) {
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

