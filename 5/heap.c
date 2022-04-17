#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int PARENT(int i){
  return (i+1)/2-1;
}    
int LEFT(int i){
  return 2*(i+1)-1;
}
int RIGHT(int i){
  return 2*(i+1) ;
}
typedef struct heap {
  int* array;
  int size;
}HEAP;
// Create node
HEAP* createHeap(int size) {
  HEAP* newNode = malloc(sizeof(HEAP));
  newNode->size = size;
  newNode->array=malloc(sizeof(int)*size);
  return newNode;
}
void MAX_HEAPIFY(HEAP *A,int i){
  int l = LEFT(i);
  int r = RIGHT(i);
  int largest;
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
    int tmp=A->array[i];
    A->array[i]=A->array[largest];
    A->array[largest]=tmp;
    MAX_HEAPIFY(A,largest);
  }    
}
void BUILD_MAX_HEAP(HEAP *A){
  for(int i =A->size/2;i>=0;i--){
    MAX_HEAPIFY(A,i);
  }
}
void PRINT_HEAP(HEAP *A){
  for(int i=0;i<A->size;i++){
    printf("%d ",A->array[i]);
  }
  printf("\n%d\n",A->size);

}    
void HEAPSORT(HEAP *A){
  BUILD_MAX_HEAP(A);
  int size=A->size;
  for(int i =A->size-1;i>0;i--){
    int tmp=A->array[0];
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
  int cursor = 0; 
  int larger;
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
    
    int tmp=A->array[cursor];
    A->array[cursor]=A->array[larger];
    A->array[larger]=tmp;
    cursor = larger;
  }
}
int PEEP_LARGEST(HEAP *A){
  return A->array[0];
}

void INSERT(HEAP *A,int data){
  A->array[A->size]=data;
  int cursor = A->size;
  A->size++;
  while(cursor>0){
    if(A->array[PARENT(cursor)]>=A->array[cursor]){
      return;
    }
    else{
      int tmp=A->array[PARENT(cursor)];
      A->array[PARENT(cursor)]=A->array[cursor];
      A->array[cursor]=tmp;
      cursor=PARENT(cursor);
    }
  }
}

int main(){
  HEAP* h=createHeap(7);
  for(int i=0;i<h->size;i++){
    h->array[i]=i;
  }
  BUILD_MAX_HEAP(h);
  //HEAPSORT(h);
  PRINT_HEAP(h);
  for(int i=0;i<3;i++){
    INSERT(h,i+7);
    PRINT_HEAP(h);
  }
  
  //PRINT_HEAP(h);
  

  return 0;
}

/*
void REMOVE_LARGEST(HEAP *A){
  A->array[0]=A->array[A->size-1];
  A->size--;
  int cursor = 0; 
  int larger;
  while(cursor<A->size){
    larger=cursor;
    if(LEFT(cursor)>=A->size){
      if(RIGHT(cursor)>=A->size){
        return;
      }
      else{
        larger=RIGHT(cursor);
      }
    }
    else if(RIGHT(cursor)>=A->size){
      larger=LEFT(cursor);
    }
    else if(A->array[RIGHT(cursor)]>A->array[LEFT(cursor)]){
      larger=RIGHT(cursor);
    }
    else{
      larger=LEFT(cursor);
    }
    
    unsigned long long tmp=A->array[cursor];
    A->array[cursor]=A->array[larger];
    A->array[larger]=tmp;
    cursor = larger;
  }
}

void INSERT(HEAP *A,unsigned long long data){
  A->array[A->size]=data;
  int cursor = A->size;
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
*/

void REMOVE_AND_INSERT(HEAP *A,unsigned long long data){
  A->array[0]=data;
  int cursor = 0; 
  int larger;
  while(cursor<A->size){
    larger=cursor;
    if(LEFT(cursor)>=A->size){
      if(RIGHT(cursor)>=A->size){
        return;
      }
      else{
        larger=RIGHT(cursor);
      }
    }
    else if(RIGHT(cursor)>=A->size){
      larger=LEFT(cursor);
    }
    else if(A->array[cursor]>A->array[RIGHT(cursor)] && A->array[cursor]>A->array[LEFT(cursor)]){
      return;
    }
    else if(A->array[RIGHT(cursor)]>A->array[LEFT(cursor)]){
      larger=RIGHT(cursor);
    }
    else{
      larger=LEFT(cursor);
    }
    
    unsigned long long tmp=A->array[cursor];
    A->array[cursor]=A->array[larger];
    A->array[larger]=tmp;
    cursor = larger;
  }
}