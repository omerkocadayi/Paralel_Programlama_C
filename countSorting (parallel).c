#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#define SIZE 100000

void count_sort(int a[], int n)
{
    int i, j, count;
    int *temp = malloc(n*sizeof(int));

    #pragma omp parallel for num_threads(100) private(i, j, count)
    for(i=0; i<n; i++){
        count = 0;

        for(j=0; j<n; j++){
            if(a[j] < a[i]){
                #pragma omp atomic
                count++;
            }
            else if(a[j] == a[i] && j < i){
                #pragma omp atomic
                count++;
            }
        }

        temp[count] = a[i];
    }

    memcpy(a, temp, n*sizeof(int));
}

int *create_array(int n){
    int i;
    int *a = malloc(n*sizeof(int));

    srand(time(NULL));

    for(i=0; i<n; i++){
        a[i] = rand()%10;
    }

    return a;
}

void print_array(int *a, int n){
    int i;

    for(i=0; i<n; i++){
        printf("%d ", a[i]);
    }

    printf("\n\n");
}

int main()
{
    clock_t begin, end;
	double runtime;

	// Clock starts
   	begin = clock();

   	// Program runs
    int *a = create_array(SIZE);
    count_sort(a, SIZE);
    print_array(a, SIZE);

    // Clock ends
    end = clock();
   	runtime = (double)(end - begin) / CLOCKS_PER_SEC;
   	printf("\n\nRuntime : %f\n\n", runtime);

    return 0;
}
