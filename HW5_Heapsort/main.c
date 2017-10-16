#include <stdio.h>
#include <stdlib.h>

int *arr;

void HeapSort(int size);
void maxHeapify(int i, int size);

int main(void) {
    FILE *input, *output;
    char s[20];
    int size, target;

    input = fopen("input.txt", "r");
    fgets(s, 20, input);
    size = atoi(s);
    arr = calloc(size, sizeof(int));
    for(int i=0;i<size;i++) {
        if(i == size-1) {
            fgets(s, 20, input);
            arr[i] = atoi(s);
        }else {
            fscanf(input, "%s", s);
            arr[i] = atoi(s);
        }
    }
    fgets(s, 20, input);
    target = atoi(s);

    HeapSort(size);

    output = fopen("output.txt", "w");
    fprintf(output, "%d\n", arr[target-1]);
    fclose(output);

    free(arr);

    return 0;
}

void HeapSort(int size) {
    for(int i = size/2-1;i>=0;i--) maxHeapify(i, size);
    for(int j = size-1;j>0;j--) {
        int temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        maxHeapify(0, j);
    }
}

void maxHeapify(int i, int size) {
    int l, r, largest;

    if(i*2+1 < size) {
        l = i*2+1;
        if(i*2+2 < size) r = i*2+2;
        else r = -1;
        if(arr[l] > arr[i]) largest = l;
        else largest = i;
        if(r != -1 && (arr[r] > arr[largest]) ) largest = r;
        if(largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            maxHeapify(largest, size);
        }
    }
}
