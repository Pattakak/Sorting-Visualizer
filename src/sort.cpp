#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "render.h"


//int* shaderID;
using std::cout; 
using std::endl;

void generateArray(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }
}

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
   //Not my code...
void shuffle(int *array, size_t n)
{
    std::srand(std::time(0));
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + std::rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int main() {
    int length = 100; //Number of elements to sort

    init();
    int arr[length];
    generateArray(arr, length);
    shuffle(arr, length);

    cout << endl;

    return 0;
}