#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned long long PARENT(unsigned long long i){
  return (i+1)/2-1;
}    
unsigned long long LEFT(unsigned long long i){
  return 2*(i+1)-1;
}
unsigned long long RIGHT(unsigned long long i){
  return 2*(i+1) ;
}
typedef struct heap {
  unsigned long long* array;
  unsigned long long size;
}HEAP;
// Create node
HEAP* createHeap(unsigned long long size) {
  HEAP* newNode = malloc(sizeof(HEAP));
  newNode->size = size;
  newNode->array=malloc(sizeof(unsigned long long)*size);
  return newNode;
}
void MAX_HEAPIFY(HEAP *A,unsigned long long i){
  unsigned long long l = LEFT(i);
  unsigned long long r = RIGHT(i);
  unsigned long long largest;
  if(l < A->size && A->array[l]>A->array[i]){
    largest = l ;
  }
  else{
    largest = i;
  }   
  if(r < A->size && A->array[r]>A->array[largest]) {
    largest = r;
  }  
  if(largest != i){
    unsigned long long tmp=A->array[i];
    A->array[i]=A->array[largest];
    A->array[largest]=tmp;
    MAX_HEAPIFY(A,largest);
  }    
}
void BUILD_MAX_HEAP(HEAP *A){
  for(unsigned long long i =A->size/2;i>=0;i--){
    MAX_HEAPIFY(A,i);
  }
}
void PRINT_HEAP(HEAP *A){
  for(unsigned long long i=0;i<A->size;i++){
    printf("%llu ",A->array[i]);
  }
  printf("\n%llu\n",A->size);

}    
void HEAPSORT(HEAP *A){
  BUILD_MAX_HEAP(A);
  unsigned long long size=A->size;
  for(unsigned long long i =A->size-1;i>0;i--){
    unsigned long long tmp=A->array[0];
    A->array[0]=A->array[i];
    A->array[i]=tmp;
    A->size--; 
    MAX_HEAPIFY(A,0);
  }
  A->size=size;
}
void REMOVE_LARGEST(HEAP *A){
  A->array[0]=A->array[A->size-1];
  A->size--;
  unsigned long long cursor = 0; 
  unsigned long long larger;
  while(cursor<A->size){
    larger=cursor;
    if(A->array[LEFT(cursor)]>A->array[cursor] && LEFT(cursor)<A->size){
      larger=LEFT(cursor);
      if(A->array[RIGHT(cursor)]>A->array[larger] && RIGHT(cursor)<A->size){
        larger=RIGHT(cursor);
      }
    }
    else if(A->array[RIGHT(cursor)]>A->array[larger] && RIGHT(cursor)<A->size){
      larger=RIGHT(cursor);
    }
    else{
      return;
    }
    
    unsigned long long tmp=A->array[cursor];
    A->array[cursor]=A->array[larger];
    A->array[larger]=tmp;
    cursor = larger;
  }
}
unsigned long long PEEP_LARGEST(HEAP *A){
  return A->array[0];
}

void INSERT(HEAP *A,unsigned long long data){
  A->array[A->size]=data;
  unsigned long long cursor = A->size;
  A->size++;
  while(cursor>0){
    if(A->array[PARENT(cursor)]>=A->array[cursor]){
      return;
    }
    else{
      unsigned long long tmp=A->array[PARENT(cursor)];
      A->array[PARENT(cursor)]=A->array[cursor];
      A->array[cursor]=tmp;
      cursor=PARENT(cursor);
    }
  }
}

int main(){
  HEAP* h=createHeap(7);
  for(unsigned long long i=0;i<h->size;i++){
    h->array[i]=i;
  }
  BUILD_MAX_HEAP(h);
  //HEAPSORT(h);
  PRINT_HEAP(h);
  for(unsigned long long i=0;i<3;i++){
    INSERT(h,i+7);
    PRINT_HEAP(h);
  }
  
  //PRINT_HEAP(h);
  

  return 0;
}
