#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct treap{
    struct treap *l, *r;
    int key, priority;
    long long sum;
    int size;
    bool flip;
}Treap;
Treap *alloc(int key, int priority){
    Treap *tmp = (Treap *)malloc(sizeof(Treap)); 
    tmp->key = key;
    tmp->priority = priority;
    tmp->flip=false;
    tmp->size=1;
    tmp->sum=key;
    tmp->l=NULL;
    tmp->r=NULL;
    return tmp;
}

long long rand_num=0;
int random_num(){
    //struct timespec tt;
    //clock_gettime(CLOCK_REALTIME, &tt);
    srand(rand_num);
    rand_num++;
    return rand();
}

void update_nodes(Treap* t){
    t->size = 1;
    t->sum = t->key;
    if (t->l!=NULL){
        t->size+=t->l->size;
        t->sum+=t->l->sum;
    }
    if (t->r!=NULL){
        t->size+=t->r->size;
        t->sum+=t->r->sum;
    }
}

void heapify(Treap *t){
    Treap* max=t;
    if(t->l!=NULL && t->l->priority>max->priority){
        max=t->l;
    }
    if(t->r!=NULL && t->r->priority>max->priority){
        max=t->r;
    }
    if(t!=max){
        int tmp=t->priority;
        t->priority=max->priority;
        max->priority=tmp;
        heapify(max);
    }
}
Treap* build(long long* arr, int len){
    int mid=len/2;
    Treap* t=alloc(arr[mid],random_num());
    //t->nodes=len;
    if(mid!=0){
        t->l = build(&arr[0], mid);
    }
    if(len-mid-1!=0){
        t->r = build(&arr[mid+1], len-mid-1);
    }
    update_nodes(t);
    heapify(t);
    return t;
}

void INORDER_TRAVERSAL(Treap* t){
    if(t->l!=NULL){
        INORDER_TRAVERSAL(t->l);
    }
    printf("%d: %d %lld\n",t->key,t->size,t->sum);
    //printf("%d\n",t->priority);
    if(t->r!=NULL){
        INORDER_TRAVERSAL(t->r);
    }
}

void kth(Treap* t,int k, Treap** kk){
    if(t->l==NULL){
        if(k==1){
            *kk=t;
            return;
        }else{
            kth(t->r,k-1,kk);
            return;
        }
    }
    int nodes=t->l->size+1;
    if(nodes==k){
        *kk=t;
        return;
    }else if(k<nodes){
        kth(t->l,k,kk);
        return;
    }else{
        kth(t->r,k-nodes,kk);
        return;
    }
    return;
}

int N=10;
void split(Treap* t,int k, Treap** a, Treap** b,  Treap* kk)
{ 
    //push(t);
    if(t==kk){
        *a=kk;
        *b=kk->r;
        kk->r=NULL;
        update_nodes(t);
        return;
    }
    
    if(t->l==NULL){
        *a = t;
        //push(a);
        split(t->r, k - 1, &((*a)->r), b,kk);
    }
    else if(k<=t->l->size){
        *b = t;
        //push(b);
        split(t->l, k, a, &((*b)->l),kk);
    }else{
        *a = t;
        //push(a);
        split(t->r, k - t->l->size - 1, &((*a)->r), b,kk);
    }
    update_nodes(t);
}
void splits(Treap* t,int k, Treap** a, Treap** b){
    if(k<=0){
        *b=t;
        return;
    }
    else if(k>=t->size){
        *a=t;
        return;
    }
    Treap* kk=NULL;
    kth(t,k,&kk);
    split(t,k,a,b,kk);
}

void merge (Treap **t, Treap *l, Treap *r) {
    if(l==NULL){
        *t=r;
        return;
    }
    if(r==NULL){
        *t=l;
        return;
    }
    //push (l);
    //push (r);
    if (l->priority >= r->priority){
        if(l->r==NULL){
            *t=l;
            l->r=r;
            update_nodes(*t);
            return;
        }
        merge(&(l->r),l->r,r);
        *t=l;
    }else{
        if(r->l==NULL){
            *t=r;
            r->l=l;
            update_nodes(*t);
            return;
        }
        merge(&(r->l),l,r->l);
        *t=r;
    }
    update_nodes(*t);
}

long long sums(Treap *t,int left,int right){
    Treap *t1=NULL,*t2=NULL,*t3=NULL,*tmp=NULL;
    splits(t,left-1,&t1,&tmp);
    splits(tmp,right-left+1,&t2,&t3);
    long long sum=t2->sum;
    merge (&tmp, t1, t2);
    merge (&t, tmp, t3);
    return sum;
}

void insert(Treap** t,long long pos, long long key){
    //1 split + 2 merge
    Treap *t1=NULL,*t3=NULL,*tmp=NULL;
    splits(*t,pos,&t1,&t3);
    Treap* t2=alloc(key,random_num());
    merge (&tmp, t1, t2);
    merge (t, tmp, t3);
    N++;
}

void delete(Treap** t,long long pos){
    //1 split + 2 merge
    Treap *t1=NULL,*t2=NULL,*t3=NULL,*tmp=NULL;
    splits(*t,pos-1,&t1,&tmp);
    splits(tmp,1,&t2,&t3);
    merge (t, t1, t3);
    N--;
}

int main(){
    long long arr[10]={0,1,2,3,4,5,6,7,8,9};
    Treap* root=build(arr,10);
    insert(&root,10,4);
    insert(&root,12,7);
    insert(&root,8,3);
    delete(&root,8);
    //INORDER_TRAVERSAL(root);
    int l=10,r=12;
    printf("sum:%lld\n",sums(root,l,r));
    INORDER_TRAVERSAL(root); 
}