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
  int largest=i;
  if(l < A->size){
    if(A->array[l]>A->array[i]){
      largest = l ;
    }
  }
  if(r < A->size) {
    if(A->array[r]>A->array[largest]){
      largest = r;
    }
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
  printf("\nsize: %d\n",A->size);
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

unsigned long long kth(int stock, int num, int day){
  if(num>day){
    HEAP* h=createHeap(2*day+1);
    for(int i=0;i<h->size;i++){
      h->array[i]=price(stock,num-day+i);
    } 
    HEAPSORT(h);
    return h->array[day];
  }
  else{
    HEAP* h=createHeap(num+day);
    for(int i=0;i<h->size;i++){
      h->array[i]=price(stock,i+1);
    }
    HEAPSORT(h);
    return h->array[num-1];
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
    if(s[i]!=0){
      //邊界條件
      if(h->array[0]>=kth(s[i],k[i]-1,N)){
        if(h->array[0]>=kth(s[i],k[i],N)){
          printf("%llu",kth(s[i],k[i],N));
          continue;
        }
        else{
          printf("%llu",h->array[0]);
          continue;
        }
      }
      if(h->array[k[i]-2]<=kth(s[i],1,N)){
        if(h->array[k[i]-1]>=kth(s[i],1,N)){
          printf("%llu",kth(s[i],1,N));
          continue; 
        }
        else{
          printf("%llu",h->array[k[i]-1]);
          continue;
        }
      }
      //binary search
      int left_num=0;
      int right_num=k[i]-1;
      int mid=(left_num+right_num)/2;
      unsigned long long sorted_m=h->array[mid];
      unsigned long long sorted_m1=h->array[mid+1];
      unsigned long long unsorted_k=kth(s[i],k[i]-mid-1,N);//func
      unsigned long long unsorted_k1=kth(s[i],k[i]-mid,N);//func
      while(true){
        if(unsorted_k<=sorted_m && sorted_m<=unsorted_k1){
          printf("%llu\n",sorted_m);
          break;
        }
        else if(sorted_m<=unsorted_k && unsorted_k<=sorted_m1){
          printf("%llu\n",unsorted_k);
          break;
        }
        else if(sorted_m<unsorted_k){
          /*
          if(left_num-mid==0){
            left_num++;
          }
          */
          //else{
            left_num=mid;
          //}
        }
        else{
          right_num=mid;
        }
        mid=(left_num+right_num)/2;
        sorted_m=h->array[mid];
        sorted_m1=h->array[mid+1];
        unsorted_k=kth(s[i],k[i]-mid-1,N);//func
        unsorted_k1=kth(s[i],k[i]-mid,N);//func
        //keep second smallest
        /*
        if(right_num-left_num<=1){
          if(sorted_m==unsorted_k){
            printf("%llu\n",unsorted_k);
          }
          if(sorted_m<unsorted_k){
            if(unsorted_k<sorted_m1){
              printf("%llu\n",unsorted_k);
            }
            else{
              printf("%llu\n",sorted_m1);
            }
          }
          else{
            if(unsorted_k+1<sorted_m){
              printf("%llu\n",unsorted_k+1);
            }
            else{
              printf("%llu\n",sorted_m);
            }
          }
          break;
        }
        */
      }
    }
    else{
      printf("%llu \n",h->array[k[i]-1]);
    }
  }
  free(h->array);
  free(h);
  free(stacks);
  free(s);
  free(k);
}

int main(){
  Brain();
  return 0;
}
/*
unsigned long long price(unsigned long long s,unsigned long long k){
  return s+k;
}


*/

/*
void Brain(){
  
  int A=3;
  int Q=3;
  int N=1000;
  int *stacks = (int*) malloc(sizeof(int)*A);
  
  for(int i=0;i<A;i++){
    stacks[i]=i+999999991;
  }
  
  int *s = (int*) malloc(sizeof(int)*Q);
  int *k = (int*) malloc(sizeof(int)*Q);
  s[0]=0;
  s[1]=999999994;
  s[2]=900000005;
  k[0]=1000000;
  k[1]=1000000;
  k[2]=123456;
  
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
    if(s[i]!=0){
      HEAP* s_heap=createHeap(k[i]);
      s_heap->size=0;
      int j=0;
      while(j<k[i]){
        int num=price(s[i],j+1);
        if(num<h->array[h->size-1]){
          s_heap->array[j]=num;
          s_heap->size++;
        }
        else{
          break;
        }
        j++;
      }
      for(int l=0;l<N+1 && j+l<k[i];l++){
        int num=price(s[i],j+1+l);
        if(num<h->array[h->size-1]){
          s_heap->array[j+l]=num;
          s_heap->size++;
        }
      }
      
      //???
      BUILD_MAX_HEAP(s_heap);
      HEAPSORT(s_heap);
      //PRINT_HEAP(s_heap);
      j=k[i]-1;
      int l=0;
      while(j>=0 && l<s_heap->size){
        if(h->array[j]>s_heap->array[l]){
          j--;
          l++;
        }
        else{
          break;
        }
      }
      printf("%llu \n",h->array[j]);
      
    }
    else{
      printf("%llu \n",h->array[k[i]-1]);
    }
  }
  free(h->array);
  free(h);
  free(stacks);
  free(s);
  free(k);
}
*/
