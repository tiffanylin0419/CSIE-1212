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



//min
typedef struct node{ 
  unsigned long long data;
  int group; 
} NODE;

NODE *alloc(unsigned long long data, int group){
  NODE *tmp = (NODE *)malloc(sizeof(NODE)); 
  tmp->data = data;
  tmp->group = group;
  return tmp;
}

typedef struct node_heap{
  NODE** array;
  int size;
}NODE_HEAP;

NODE_HEAP* createNodeHeap(int size) {
  NODE_HEAP* newNode = malloc(sizeof(NODE_HEAP));
  newNode->size = size;
  newNode->array=malloc(sizeof(NODE*)*size);
  return newNode;
}

void MIN_HEAPIFY(NODE_HEAP *A,int i){
  int l = LEFT(i);
  int r = RIGHT(i);
  int smallest=i;
  if(l < A->size){
    if(A->array[l]->data<A->array[i]->data){
      smallest = l ;
    }
  }
  if(r < A->size) {
    if(A->array[r]->data<A->array[smallest]->data){
      smallest = r;
    }
  }  
  if(smallest != i){
    NODE *tmp=A->array[i];
    A->array[i]=A->array[smallest];
    A->array[smallest]=tmp;
    MIN_HEAPIFY(A,smallest);
  }    
}
void BUILD_MIN_HEAP(NODE_HEAP *A){
  for(int i =A->size/2;i>=0;i--){
    MIN_HEAPIFY(A,i);
  }
}
void REMOVE_AND_INSERT_NODE(NODE_HEAP *A,unsigned long long* ki,int *stacks,int length,int* A_pos){
  *ki=A->array[0]->data;
  int group=A->array[0]->group;
  if(group>=length){
    //delete min
    A->array[0]->data=A->array[A->size-1]->data;
    A->array[0]->group=A->array[A->size-1]->group;
    A->size--;
  }
  else{
    A->array[0]->data=price(stacks[group],A_pos[group]);
    A_pos[group]++;
  }
  
  int cursor = 0; 
  int smaller;
    while(cursor<A->size){
    smaller=cursor;
    if(LEFT(cursor)>=A->size){
      if(RIGHT(cursor)>=A->size){
        return;
      }
      else{
        if(A->array[cursor]->data<A->array[RIGHT(cursor)]->data){
          return;
        }
        else{
          smaller=RIGHT(cursor);
        }
      }
    }
    else if(RIGHT(cursor)>=A->size){
      if(A->array[cursor]->data<A->array[LEFT(cursor)]->data){
        return;
      }
      else{
        smaller=LEFT(cursor);
      }
    }
    else if(A->array[cursor]->data<A->array[RIGHT(cursor)]->data && A->array[cursor]->data<A->array[LEFT(cursor)]->data){
      return;
    }
    else if(A->array[RIGHT(cursor)]->data<A->array[LEFT(cursor)]->data){
      smaller=RIGHT(cursor);
    }
    else{
      smaller=LEFT(cursor);
    }
    NODE* tmp=A->array[cursor];
    A->array[cursor]=A->array[smaller];
    A->array[smaller]=tmp;
    cursor = smaller;
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

unsigned long long kth_good(unsigned long long* sorted, int stock,int num1, int num2, int day,int k_max){
  int return_size=0;
  HEAP* h=createHeap(4*day+2);
  h->size=0;
  //num1 sorted
  if(num1>day){
    for (int i=num1;i>=num1-day;i--){
      h->array[h->size]=sorted[i];
      h->size++;
    }
    return_size+=day+1;
  }
  else{
    for (int i=0;i<=num1;i++){
      h->array[h->size]=sorted[i];
      h->size++;
    }
    return_size+=num1+1;
  }
  if(k_max-num1-1>day){
    for (int i=num1+1;i<=num1+day;i++){
      h->array[h->size]=sorted[i];
      h->size++;
    }
  }
  else{
    for (int i=num1+1;i<k_max;i++){
      h->array[h->size]=sorted[i];
      h->size++;
    }
  }
  //num2 not sorted
  if(num2>day){
    for (int i=num2;i>=num2-day;i--){
      h->array[h->size]=price(stock,i);
      h->size++;
    }
    return_size+=day+1;
  }
  else{
    for (int i=1;i<=num2;i++){
      h->array[h->size]=price(stock,i);
      h->size++;
    }
    return_size+=num2;
  }
  

  for (int i=num2+1;i<=num2+day;i++){
    h->array[h->size]=price(stock,i);
    h->size++;
  }

  HEAPSORT(h);
  return h->array[return_size-1];
}

void return_kth(int stock, int num, int day,unsigned long long *a,unsigned long long *b){
  if(num>day){
    HEAP* h=createHeap(2*day+1);
    for(int i=0;i<h->size;i++){
      h->array[i]=price(stock,num-day+i);
    } 
    HEAPSORT(h);
    *a=h->array[day];
    *b=h->array[day+1];
    free(h->array);
    free(h);  
  }
  else{
    HEAP* h=createHeap(num+day);
    for(int i=0;i<h->size;i++){
      h->array[i]=price(stock,i+1);
    }
    HEAPSORT(h);
    *a=h->array[num-1];
    *b=h->array[num];
    free(h->array);
    free(h);
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

  /*
  int A=1;
  int Q=2;
  int N=1;
  int *stacks = (int*) malloc(sizeof(int)*A);
  
  for(int i=0;i<A;i++){
    stacks[i]=1;
  }
  
  int *s = (int*) malloc(sizeof(int)*Q);
  int *k = (int*) malloc(sizeof(int)*Q);
  s[0]=0;
  s[1]=0;
  k[0]=1;
  k[1]=1000000;
*/
  int max_k=0;
  for(int i=0;i<Q;i++){
    if(k[i]>max_k){
      max_k=k[i];
    }
  }
  
  //get NA min heap
  NODE_HEAP* h=createNodeHeap(N*A);
  int i=0;
  for (int j=0;j<A;j++){
    for(int l=1;l<=N;l++){
      h->array[i]=alloc(price(stacks[j],l),j);
      i++;
    }
  }
  BUILD_MIN_HEAP(h);
  //create array k & array A
  unsigned long long *array_k=malloc(sizeof(unsigned long long)*max_k);
  int *A_pos=malloc(sizeof(int)*A);
  for(int i=0;i<A;i++){
    A_pos[i]=N+1;
  }
  for(int i=0;i<max_k;i++){
    REMOVE_AND_INSERT_NODE(h,&array_k[i],stacks,A,A_pos);
  }
  
  
  //solve question
  for(int i=0;i<Q;i++){
    if(s[i]!=0){
      //短k條件
      if(k[i]==1){
        unsigned long long first_in_s=kth(s[i],1,N);
        if(first_in_s>array_k[0]){
          printf("%llu\n",array_k[0]);
        }
        else{
          printf("%llu\n",first_in_s);
        }
        continue;
      }
      else if(k[i]==2){
        unsigned long long first_in_s;
        unsigned long long second_in_s;
        return_kth(s[i],1,N,&first_in_s,&second_in_s);
        unsigned long long first_in_sort=array_k[0];
        unsigned long long second_in_sort=array_k[1];
        unsigned long long second_small;
        unsigned long long first_large;
        if(second_in_s>second_in_sort){
          second_small=second_in_sort;
        }
        else{
          second_small=second_in_s;
        }

        if(first_in_s>first_in_sort){
          first_large=first_in_s;
        }
        else{
          first_large=first_in_sort;
        }

        if(first_large<second_small){
          printf("%llu\n",first_large);
        }
        else{
          printf("%llu\n",second_small);
        }
        continue;
      }

      //邊界條件      
      if(array_k[0]>=kth(s[i],k[i]-1,N)){
        if(array_k[0]>=kth(s[i],k[i],N)){
          printf("%llu\n",kth(s[i],k[i],N));
        }
        else{
          printf("%llu\n",array_k[0]);
        }
        continue;
      }
      if(array_k[k[i]-2]<=kth(s[i],1,N)){
        if(array_k[k[i]-1]>=kth(s[i],1,N)){
          printf("%llu\n",kth(s[i],1,N));
        }
        else{
          printf("%llu\n",array_k[k[i]-1]);
        }
        continue; 
      }
      
      //binary search
      int left_num=0;
      int right_num=k[i]-1;
      int mid=(left_num+right_num)/2;
      unsigned long long sorted_m=array_k[mid];
      unsigned long long sorted_m1=array_k[mid+1];
      unsigned long long unsorted_k=price(s[i],k[i]-mid-1);//func
      unsigned long long unsorted_k1=price(s[i],k[i]-mid);//func
      while(true){
        if(unsorted_k<=sorted_m && sorted_m<=unsorted_k1){
          unsigned long long ans=kth_good(array_k, s[i],mid,k[i]-mid-1, N,max_k);
          printf("%llu\n",ans);
          break;
        }
        else if(sorted_m<=unsorted_k && unsorted_k<=sorted_m1){
          unsigned long long ans=kth_good(array_k, s[i],mid,k[i]-mid-1, N,max_k);
          printf("%llu\n",ans);
          break;
        }
        else if(sorted_m<unsorted_k){
          left_num=mid;
        }
        else{
          right_num=mid;
        }
        mid=(left_num+right_num)/2;
        sorted_m=array_k[mid];
        sorted_m1=array_k[mid+1];
        unsorted_k=price(s[i],k[i]-mid-1);//func
        unsorted_k1=price(s[i],k[i]-mid);//func
      }

    }
    else{
      printf("%llu\n",array_k[k[i]-1]);
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

void Brain(){
  
  int A=1;
  int Q=2;
  int N=1;
  int *stacks = (int*) malloc(sizeof(int)*A);
  
  for(int i=0;i<A;i++){
    stacks[i]=1;
  }
  
  int *s = (int*) malloc(sizeof(int)*Q);
  int *k = (int*) malloc(sizeof(int)*Q);
  s[0]=0;
  s[1]=0;
  k[0]=1;
  k[1]=1000000;
  
  int max_k=0;
  for(int i=0;i<Q;i++){//?
    if(k[i]>max_k){
      max_k=k[i];
    }
  }
  //get NA min heap
  NODE_HEAP* h=createNodeHeap(N*A);
  int i=0;
  for (int j=0;j<A;j++){
    for(int l=1;l<=N;l++){
      h->array[i]=alloc(price(stacks[j],l),j);
      i++;
    }
  }
  BUILD_MIN_HEAP(h);
  //create array k & array A
  unsigned long long *array_k=malloc(sizeof(unsigned long long)*max_k);
  int *A_pos=malloc(sizeof(int)*A);
  for(int i=0;i<A;i++){
    A_pos[i]=N+1;
  }
  for(int i=0;i<max_k;i++){
    REMOVE_AND_INSERT_NODE(h,&array_k[i],stacks,A,A_pos);
  }
  
  
  //solve question
  for(int i=0;i<Q;i++){
    if(s[i]!=0){
      //短k條件
      if(k[i]==1){
        unsigned long long first_in_s=kth(s[i],1,N);
        if(first_in_s>array_k[0]){
          printf("%llu\n",array_k[0]);
        }
        else{
          printf("%llu\n",first_in_s);
        }
        continue;
      }
      else if(k[i]==2){
        unsigned long long first_in_s;
        unsigned long long second_in_s;
        return_kth(s[i],1,N,&first_in_s,&second_in_s);
        unsigned long long first_in_sort=array_k[0];
        unsigned long long second_in_sort=array_k[1];
        unsigned long long second_small;
        unsigned long long first_large;
        if(second_in_s>second_in_sort){
          second_small=second_in_sort;
        }
        else{
          second_small=second_in_s;
        }

        if(first_in_s>first_in_sort){
          first_large=first_in_s;
        }
        else{
          first_large=first_in_sort;
        }

        if(first_large<second_small){
          printf("%llu\n",first_large);
        }
        else{
          printf("%llu\n",second_small);
        }
        continue;
      }

      //邊界條件      
      if(array_k[0]>=kth(s[i],k[i]-1,N)){
        if(array_k[0]>=kth(s[i],k[i],N)){
          printf("%llu\n",kth(s[i],k[i],N));
        }
        else{
          printf("%llu\n",array_k[0]);
        }
        continue;
      }
      if(array_k[k[i]-2]<=kth(s[i],1,N)){
        if(array_k[k[i]-1]>=kth(s[i],1,N)){
          printf("%llu\n",kth(s[i],1,N));
        }
        else{
          printf("%llu\n",array_k[k[i]-1]);
        }
        continue; 
      }
      
      //binary search
      int left_num=0;
      int right_num=k[i]-1;
      int mid=(left_num+right_num)/2;
      unsigned long long sorted_m=array_k[mid];
      unsigned long long sorted_m1=array_k[mid+1];
      unsigned long long unsorted_k;//func
      unsigned long long unsorted_k1;//func
      return_kth(s[i],k[i]-mid-1,N,&unsorted_k,&unsorted_k1);
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
          left_num=mid;
        }
        else{
          right_num=mid;
        }
        mid=(left_num+right_num)/2;
        sorted_m=array_k[mid];
        sorted_m1=array_k[mid+1];
        return_kth(s[i],k[i]-mid-1,N,&unsorted_k,&unsorted_k1);
      }
    }
    else{
      printf("%llu\n",array_k[k[i]-1]);
    }
  }
  free(h->array);
  free(h);
  free(stacks);
  free(s);
  free(k);
}*/
