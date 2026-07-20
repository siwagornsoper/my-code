#include <stdlib.h>
#include <stdio.h>

struct Heap{
    int *array;
    int size;
};

/*for practice i'm just going to program the heap algorithms to operate on arrays*/

int heapParent(int index){
    return index/2;
}

int heapLeft(int index){
    return index*2+1;
}

int heapRight(int index){
    return index*2+2;
}

void maxHeapify(struct Heap *heap, int index){
    int left;
    int right;
    int greatest;
    int holder;

    left = heapLeft(index);
    right = heapRight(index);

    if(left < heap->size && heap->array[left] > heap->array[index]){
        greatest = left;
    }
    else{
        greatest = index;
    }

    if(right < heap->size && heap->array[right] > heap->array[greatest]){
        greatest = right;
    }

    if(greatest != index){
        holder = heap->array[index];
        heap->array[index] = heap->array[greatest];
        heap->array[greatest] = holder;

        maxHeapify(heap, greatest);
    }
}

void formMaxHeap(struct Heap *heap){
    int i;
    for(i = heap->size/2; i >= 0; i--){
        maxHeapify(heap, i);
    }
}

int main(){
    struct Heap heap;
    int holder;
    int array[] = {5, 8, 4, 3, 6, 9, 2, 1, 10, 7};
    int i;

    heap.array = array;
    heap.size = 10;

    formMaxHeap(&heap);

    while(heap.size >= 0){
        holder = heap.array[heap.size-1];
        
        heap.array[heap.size-1] = heap.array[0];
        heap.array[0] = holder;
        heap.size--;

        maxHeapify(&heap,0);
    }

    for(i=0; i<10; i++){
        printf("%i ",array[i]);
    }
    printf("\n");
}

