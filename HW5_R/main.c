#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Arr[10000], uArr[10000];

void HeapSort(int size);
void maxHeapify(int i, int size);
void merge(int arr[], int l, int m, int r);
void MergeSort(int arr[], int l, int r);
void InsertionSort(int size);

int main(void) {
    //FILE *input;
    char ss[20];
    clock_t start, stop;
    double time_HS, time_IS, time_MS;

    /*
    input = fopen("input.txt", "r");
    for(int i=0;i<1000;i++) {
        fscanf(input, "%s", ss);
        Arr[i] = atoi(ss);
    }
    fclose(input);
    */

    for(int i=0;i<10000;i++) {
        scanf("%s", ss);
        Arr[i] = atoi(ss);
    }

    printf("  Tn  |   HS   |   MS   |   IS   |\n");
    printf("==================================\n");

    for(int j=1000;j<=10000;j=j+1000) {

        for(int k=0;k<j;k++) uArr[k] = Arr[k];
        start = clock();
        HeapSort(j);
        stop = clock();
        time_HS = ((double) (stop - start)) / CLOCKS_PER_SEC;

        for(int k=0;k<j;k++) uArr[k] = Arr[k];
        start = clock();
        MergeSort(uArr, 0, j-1);
        stop = clock();
        time_MS = ((double) (stop - start)) / CLOCKS_PER_SEC;

        for(int k=0;k<j;k++) uArr[k] = Arr[k];
        start = clock();
        InsertionSort(j);
        stop = clock();
        time_IS = ((double) (stop - start)) / CLOCKS_PER_SEC;

        if(j%1000==0) printf("%5d: %.6lf %.6lf %.6lf\n", j, time_HS, time_MS, time_IS);
    }

    return 0;
}

void HeapSort(int size) {
    for(int i = size/2-1;i>=0;i--) maxHeapify(i, size);
    for(int j = size-1;j>0;j--) {
        int temp = uArr[0];
        uArr[0] = uArr[j];
        uArr[j] = temp;
        maxHeapify(0, j);
    }
}

void maxHeapify(int i, int size) {
    int l, r, largest;

    if(i*2+1 < size) {
        l = i*2+1;
        r = i*2+2;
        if(uArr[l] > uArr[i]) largest = l;
        else largest = i;
        if( (r < size) && (uArr[r] > uArr[largest]) ) largest = r;
        if(largest != i) {
            int temp = uArr[i];
            uArr[i] = uArr[largest];
            uArr[largest] = temp;
            maxHeapify(largest, size);
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        MergeSort(arr, l, m);
        MergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void InsertionSort(int size) {
    int key, i, j;

    for(i=1;i<size;i++) {
        key = uArr[i];
        j = i - 1;
        while(j >= 0 && uArr[j] > key) {
            uArr[j+1] = uArr[j];
            j = j - 1;
        }
        uArr[j+1] = key;
    }
}
