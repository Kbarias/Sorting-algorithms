
/*
SortingTests.cpp
Kiara Barias
November, 2018
CSCI 235, Fall 2018, Project 5
Implementation of sorting tests selection sort, insertion sort, and merge sort.
*/


#include "SortingTests.hpp"

void selectionSort(int a[], size_t size)
{
int n = size; // initialise to a's length 
 /* advance the position through the entire array */
 /*   (could do j < n-1 because single element is also min element) */
 for (int j = 0; j < n-1; j++)
 {
     /* find the min element in the unsorted a[j .. n-1] */
 
     /* assume the min is the first element */
     int iMin = j;
     /* test against elements after j to find the smallest */
     for (int i = j+1; i < n; i++)
     {
         /* if this element is less, then it is the new minimum */
         if (a[i] < a[iMin])
         {
             /* found new minimum; remember its index */
             iMin = i;
         }
     }
 
     if (iMin != j) 
     {
         std::swap(a[j], a[iMin]);
     }
 }

}


void insertionSort(int a[], size_t size){ 

	int temp; 
	int pos = 1; 
	while (pos < size) {
		int j = pos; 
		//while there's a position && the second index is > first ----swap 
		while ((j > 0) && (a[j - 1] > a[j])){
			temp = a[j]; 
			a[j] = a[j-1]; 
			a[j-1] = temp; 
			j--; 
		}
		pos++;
	}
}


 void merge(int arr[], int l, int m, int r, int leftArr[], int rightArr[]) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; //size left
    int n2 =  r - m; //size right
	int* L = leftArr;
	int* R = rightArr;
    /* create temp arrays */
    //int L[n1], R[n2];             //allocate  DYNAMIC ARRAY ????
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int a[], int from, int to, int leftArr[], int rightArr[]) 
{
	if (from < to) 
    {         
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        //int m = from + (to - from)/2; 
  		int m = (from + to) / 2;
        // Sort first and second halves 
        mergeSort(a, from, m, leftArr, rightArr); 
        mergeSort(a, m+1, to, leftArr, rightArr); 
  
        merge(a, from, m, to, leftArr, rightArr); 
    } 
}


void mergeSort(int a[], int from, int to)
{

	int * leftArr = new int[to - from];
	int * rightArr = new int[to - from];
	mergeSort(a, from, to, leftArr, rightArr);

	delete[] leftArr;
	delete[] rightArr; 
}



void generateRandomArray(int values[], size_t size)
{

	srand(static_cast<unsigned>(time(0)));
 	int aRandVar;
	for(int i = 0; i < size; i++ )
	{
     aRandVar = rand() % size;

     values[i] = aRandVar;

	}
}

/**
 @post Populates values with integers in ascending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateAscendingArray(int values[], size_t size)
{

    srand(static_cast<unsigned>(time(0)));
 	int aRandVar;
     
 	for(int i = 0; i < size; i++)
 	{
  		aRandVar = rand() % size; 
  		values[i]= aRandVar;
     
 	}
    selectionSort(values, size);
}

/**
 @post Populates values with integers in descending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateDescendingArray(int values[], size_t size)
{
	generateRandomArray(values, size);
	for(int i = 0; i < size-1; i++)
	{
		int max_index = i; //index with largest value
		for(int j = i+1; j < size; j++) //look to see if there is another largest value in unsorted set
		{
			if(values[j] > values[max_index])
			{
				max_index = j;
			}
		}
		std::swap(values[i], values[max_index]);
	}

}


void generateLastTenRandomArray(int values[], size_t size)
{
  srand(static_cast<unsigned>(time(0)));
  int aRandVar;
     
  for(int i = 0; i < size-10; i++)
  {
      aRandVar = rand() % size; 
      values[i]= aRandVar;
     
  }
    selectionSort(values, size-10);

  for(int i = 10; i < size; i++)
  {
    aRandVar = rand() % size; 
    values[i]= aRandVar; 


  }

}

/**
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */
void generateFewRandomArray(int values[], size_t size)
{

    srand(static_cast<unsigned>(time(0)));
 	int aRandVar;
     
 	for(int i = 0; i < size; i++)
 	{
  		aRandVar = rand() % size *0.10; 
  		values[i]= aRandVar;
     
 	}
}

double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size)
{
double runtime_sum = 0;
int *copy = new int [size];
for(int t = 0; t < 10; t++)
{
  for(int i = 0; i < size; i++)
  {
    
    copy[i] = values[i];

  }

  auto start_time = high_resolution_clock().now();
 	sortingFunction(values, size);
  auto end_time = high_resolution_clock().now();
  duration<float, std::micro> runt_time = duration_cast<microseconds>(end_time - start_time);
  runtime_sum += runt_time.count();

}
return runtime_sum/10;

}


double mergeSortTest(int values[], size_t size)
{

double runtime_sum = 0;
int *copy = new int [size];
for(int t = 0; t < 10; t++)
{
  for(int i = 0; i < size; i++)
  {
    
    copy[i] = values[i];

  }

  auto start_time = high_resolution_clock().now();
  mergeSort(values, 0 , size - 1);
  auto end_time = high_resolution_clock().now();
  duration<float, std::micro> runt_time = duration_cast<microseconds>(end_time - start_time);
  runtime_sum += runt_time.count();

}
return runtime_sum/10;

}
