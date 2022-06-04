#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int N,Q;
long long arr[100001]={0};

typedef struct treap{
    struct treap *l, *r;
    long long key;
    int priority;
    long long sum;
    int size;
    bool flip;
}Treap;
Treap *alloc(long long key, int priority){
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
void push(Treap *t){
    if(t->flip){
        t->flip=false;
        if(t->r==NULL&&t->l==NULL){
            return;
        }else if(t->r==NULL){
            t->r=t->l;
            t->l=NULL;
            t->r->flip=(t->r->flip==false);
        }else if(t->l==NULL){
            t->l=t->r;
            t->r=NULL;
            t->l->flip=(t->l->flip==false);
        }else{
            Treap *tmp=t->l;
            t->l=t->r;
            t->r=tmp;
            t->l->flip=(t->l->flip==false);
            t->r->flip=(t->r->flip==false);
        }
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
Treap* build(long long *arr,int len){
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
    printf("%lld: %d %lld\n",t->key,t->size,t->sum);
    //printf("%d\n",t->priority);
    if(t->r!=NULL){
        INORDER_TRAVERSAL(t->r);
    }
}

void kth(Treap* t,int k, Treap** kk){
    push(t);
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

void split(Treap* t,int k, Treap** a, Treap** b,  Treap* kk)
{ 
    push(t);
    if(t==kk){
        *a=kk;
        *b=kk->r;
        kk->r=NULL;
        update_nodes(t);
        return;
    }
    if(t->l==NULL){
        *a = t;
        split(t->r, k - 1, &((*a)->r), b,kk);
    }
    else if(k<=t->l->size){
        *b = t;
        split(t->l, k, a, &((*b)->l),kk);
    }else{
        *a = t;
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
    push(l);
    push(r);
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
    //2 split + 1 merge
    Treap *t1=NULL,*t2=NULL,*t3=NULL,*tmp=NULL;
    splits(*t,pos-1,&t1,&tmp);
    splits(tmp,1,&t2,&t3);
    merge (t, t1, t3);
    N--;
}
void shift(Treap** t,long long l,long long r,long long x,long long y){
    //1 split + 2 merge
    Treap *t1=NULL,*t2=NULL,*t3=NULL,*t4=NULL,*t5=NULL,*tmp=NULL;
    splits(*t,l-1,&t1,&tmp);
    splits(tmp,r-l+1,&t2,&tmp);
    splits(tmp,x-r-1,&t3,&tmp);
    splits(tmp,y-x+1,&t4,&t5);
    merge(&tmp, t1, t4);
    merge(&tmp, tmp, t3);
    merge(&tmp, tmp, t2);
    merge(t, tmp, t5);
}
void reverse(Treap** t,long long l,long long r){
    Treap *t1=NULL,*t2=NULL,*t3=NULL,*t4=NULL,*t5=NULL,*tmp=NULL;
    splits(*t,l-1,&t1,&tmp);
    splits(tmp,r-l+1,&t2,&t3);
    t2->flip=(t2->flip==false);
    merge(&tmp, t1, t2);
    merge(t, tmp, t3);
}

long long command[100000][5]={0};
int main() {
    // input
    scanf("%d %d",&N,&Q);
    for(int i=0;i<N;i++){
        scanf("%lld",&arr[i]);
    }
    Treap* root=build(arr,N);
    for(int i=0;i<Q;i++){
        scanf("%lld",&command[i][0]);
        if(command[i][0]==1){
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }else if(command[i][0]==2){
            scanf("%lld",&command[i][1]);
        }else if(command[i][0]==3){
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }else if(command[i][0]==4){
            scanf("%lld %lld %lld %lld",&command[i][1],&command[i][2],&command[i][3],&command[i][4]);
        }else if(command[i][0]==5){
            scanf("%lld %lld %lld",&command[i][1],&command[i][2],&command[i][3]);
        }else{
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }
    }

    //command
    for(int i=0;i<Q;i++){
        if(command[i][0]==1){
            insert(&root,command[i][1],command[i][2]);
        }else if(command[i][0]==2){
            delete(&root,command[i][1]);
        }else if(command[i][0]==3){
            long long l=command[i][1],r=command[i][2];
            reverse(&root,l,r);
        }else if(command[i][0]==4){
            long long l,r,x,y;
            if(command[i][1]<command[i][3]){
                l=command[i][1];
                r=command[i][2];
                x=command[i][3];
                y=command[i][4];
            }else{
                l=command[i][3];
                r=command[i][4];
                x=command[i][1];
                y=command[i][2];
            }
            shift(&root,l,r,x,y);
        }else if(command[i][0]==5){
            continue;
        }else if(command[i][0]==6){
            printf("%lld\n",sums(root,command[i][1],command[i][2]));
        }
    }
}