#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "price.h"

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
  unsigned long long* array;
  int size;
}HEAP;
// Create node
HEAP* createHeap(int size) {
  HEAP* newNode = malloc(sizeof(HEAP));
  newNode->size = size;
  newNode->array=malloc(sizeof(unsigned long long)*size);
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
    unsigned long long tmp=A->array[i];
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
    printf("%d:%llu ",i+1,A->array[i]);
  }
  printf("\n%d\n",A->size);

}    
void HEAPSORT(HEAP *A){
  BUILD_MAX_HEAP(A);
  int size=A->size;
  for(int i =A->size-1;i>0;i--){
    unsigned long long tmp=A->array[0];
    A->array[0]=A->array[i];
    A->array[i]=tmp;
    A->size--; 
    MAX_HEAPIFY(A,0);
  }
  A->size=size;
}

unsigned long long PEEP_LARGEST(HEAP *A){
  return A->array[0];
}

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
        if(A->array[cursor]>A->array[RIGHT(cursor)]){
          return;
        }
        else{
          larger=RIGHT(cursor);
        }
      }
    }
    else if(RIGHT(cursor)>=A->size){
      if(A->array[cursor]>A->array[LEFT(cursor)]){
        return;
      }
      else{
        larger=LEFT(cursor);
      }
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


void Brain(){
  int A,Q,N;
  scanf("%d %d %d",&A,&Q,&N);
  int *stacks = (int*) malloc(sizeof(int)*A);
  
  for(int i=0;i<A;i++){
    scanf("%d",&stacks[i]);
  }
  
  int *s = (int*) malloc(sizeof(int)*Q);
  int *k = (int*) malloc(sizeof(int)*Q);
  for(int i=0;i<Q;i++){
    scanf("%d %d",&s[i],&k[i]);
  }
  
  int max_k=0;
  for(int i=0;i<Q;i++){
    if(k[i]>max_k){
      max_k=k[i];
    }
  }
  
  //get k values
  HEAP* h=createHeap(max_k);
  int mid=max_k%A;
  int initial_num=max_k/A+1;
  int i=0;
  for (int j=0;j<mid;j++){
    for(int l=1;l<=initial_num;l++){
      h->array[i]=price(stacks[j],l);
      i++;
    }
  }
  for (int j=mid;j<A;j++){
    for(int l=1;l<initial_num;l++){
      h->array[i]=price(stacks[j],l);
      i++;
    }
  }
  //max heapify
  BUILD_MAX_HEAP(h);
  
  //check
  //printf("%llu \n",h->array[0]);
  //PRINT_HEAP(h);

  //add A*N values
  unsigned long long num;
  for (int j=0;j<mid;j++){
    bool able_to_add=true;
    int l=0;
    for(;able_to_add;l++){
      num=price(stacks[j],initial_num+1+l);
      if(num<PEEP_LARGEST(h)){
        REMOVE_AND_INSERT(h,num);
        //printf("%llu\n",num);
        //PRINT_HEAP(h);
      }
      else{
        able_to_add=false;
      }
    }
    for(int m=0;m<=N;m++){
      num=price(stacks[j],initial_num+1+l+m);
      //printf("hi:%llu \n",num);
      if(num<PEEP_LARGEST(h)){
        REMOVE_AND_INSERT(h,num);
        //PRINT_HEAP(h);
      }
    }
  }
  //check
  //PRINT_HEAP(h);
  //printf("%llu \n",h->array[0]);
  
  for (int j=mid;j<A;j++){
    bool able_to_add=true;
    int l=0;
    for(;able_to_add;l++){
      num=price(stacks[j],initial_num+l);
      if(num<PEEP_LARGEST(h)){
        REMOVE_AND_INSERT(h,num);
        //PRINT_HEAP(h);
      }
      else{
        able_to_add=false;
      }
    }
    
    for(int m=0;m<=N;m++){
      num=price(stacks[j],initial_num+l+m);
      //printf("hi:%llu \n",num);
      if(num<PEEP_LARGEST(h)){
        REMOVE_AND_INSERT(h,num);
        //PRINT_HEAP(h);
      }
    }
  }
  
  //check
  //PRINT_HEAP(h);
  //printf("%llu \n",h->array[0]);

  //heapsort
  HEAPSORT(h);

  //check
  //PRINT_HEAP(h);
  
  //solve question
  for(int i=0;i<Q;i++){
    printf("%llu \n",h->array[k[i]-1]);
  }

  free(h->array);
  free(h);
  free(stacks);
  free(s);
  free(k);
  /*
  for(int i=0;i<9;i++){
    for(int j=1;j<10;j++){
      printf("%llu ",price(stacks[i],j));
    }
    printf("\n");
  }*/
  
}

int main(){
  Brain();
  return 0;
}
/*
unsigned long long price(unsigned long long s,unsigned long long k){
  return s+k;
}

void Brain(){
  int A=9;
  int Q=3;
  int N=1;
  int *stacks = (int*) malloc(sizeof(int)*A);
  
  for(int i=0;i<A;i++){
    stacks[i]=i+1;
  }
  
  int *s = (int*) malloc(sizeof(int)*Q);
  int *k = (int*) malloc(sizeof(int)*Q);
  for(int i=0;i<Q;i++){
    s[i]=0;
  }
  k[0]=1000000;
  k[1]=16384;
  k[2]=121;

  int max_k=0;
  for(int i=0;i<Q;i++){
    if(k[i]>max_k){
      max_k=k[i];
    }
  }
  //get k values
  HEAP* h=createHeap(max_k);
  int mid=max_k%A;
  int i=0;
  for (int j=0;j<mid;j++){
    for(int l=0;l<=max_k/A;l++){
      h->array[i]=price(stacks[j],l+1);
      i++;
    }
  }
  for (int j=mid;j<A;j++){
    for(int l=0;l<max_k/A;l++){
      h->array[i]=price(stacks[j],l+1);
      i++;
    }
  }
  
  
  //max heapify
  BUILD_MAX_HEAP(h);
  //check
  printf("%llu ",h->array[0]);
  
  //add A*N values
  unsigned long long num;
  for (int j=0;j<mid;j++){
    bool able_to_add=true;
    int l=0;
    for(;able_to_add;l++){
      num=price(stacks[j],max_k/A+1+l);
      if(num<PEEP_LARGEST(h)){
        REMOVE_LARGEST(h);
        INSERT(h,num);
      }
      else{
        able_to_add=false;
      }
    }
    
    
    for(;l<N && max_k/A+1+l<1000000000;l++){
      num=price(stacks[j],max_k/A+1+l);
      if(num<PEEP_LARGEST(h)){
        REMOVE_LARGEST(h);
        INSERT(h,num);
      }
    }
    
  }
  //check
  printf("%llu \n",h->array[0]);
  
  for (int j=mid;j<A;j++){
    bool able_to_add=true;
    int l=0;
    for(;able_to_add;l++){
      num=price(stacks[j],max_k/A+1+l);
      if(num<PEEP_LARGEST(h)){
        REMOVE_LARGEST(h);
        INSERT(h,num);
      }
      else{
        able_to_add=false;
      }
    }
    for(;l<N && max_k/A+l<1000000000;l++){
      num=price(stacks[j],max_k/A+l);
      printf(":%llu \n",num);
      if(num<PEEP_LARGEST(h)){
        REMOVE_LARGEST(h);
        //INSERT(h,num);
      }
    }
  }
  
  //check
  printf("%llu ",h->array[0]);
  printf("%d",h->size);
  

  free(stacks);
  free(s);
  free(k);
  //int a=price(2,3);
  //printf("%d",a);
  
}
*/