#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc / free 
#include <memory.h> // memset
#include <ctype.h>//isdigit

typedef struct node{ 
    int data;
    int group;
    struct node *left, *right; 

} node;

typedef struct stack{ 
    struct node *top; 
    bool open;
} stack;

node *alloc(){
    node *tmp = (node *)malloc(sizeof(node)); 
    return tmp;
}

void destroy(node *N){ 
    // clean sensitive data.
    memset(N, 0, sizeof(*N));
    free(N); 
    return;
}

stack *alloc_stack(){
    stack *tmp = (stack *)malloc(sizeof(stack)); 
    node *tmpp=alloc();
    tmp->top = tmpp;
    tmp->open=true;
    return tmp;
}
int peep(stack *S){
    return S->top->data;
}
node *find(stack *S,int group){
    node *tmp=S->top->right;
    while(tmp!=S->top){
        if(tmp->group==group&&tmp->right->group!=group){
            return tmp;
        }
        tmp=tmp->right;
    }
    return S->top;
}
void push(stack *S,int data,int group){
    node *tmp=alloc();
    tmp->data=data;
    tmp->group=group;
    if(S->top->right==NULL){
        tmp->left=tmp;
        tmp->right=tmp;
        S->top=tmp;
    }
    else{
        node *position=find(S,group);
        tmp->left=position;
        tmp->right=position->right;
        position->right=tmp;
        tmp->right->left=tmp;
        if(position==S->top){
            S->top=tmp;
        }

    }
}
int pop(stack *S){
    int i=peep(S);
    node*tmp=S->top;
    S->top->left->right=S->top->right;
    S->top->right->left=S->top->left;
    S->top=S->top->left;
    destroy(tmp);
    return i;
}

void go(stack *S){
    node *tmp=S->top->right;
    S->top->right=S->top->right->right;
    S->top->right->left=S->top;
    destroy(tmp);
    
    return;
}

void destroy_stack(stack *S){
    while(S->top->right!=NULL){
        pop(S);
    }
    // clean sensitive data.
    memset(S, 0, sizeof(*S));
    free(S); 
    return;
}

void print(stack *S){
    node* tmp=S->top;
    if(tmp->right!=NULL){
        tmp=tmp->right;
        while(tmp!=S->top){
            //printf("%p %d %d %p\n",tmp->left,tmp->data,tmp->group,tmp->right);
            printf("%d ",tmp->data);
            tmp=tmp->right;
        }
        //printf("%p %d %d %p\n",tmp->left,tmp->data,tmp->group,tmp->right);
        printf("%d",tmp->data);
    }
    printf("\n");
    return;
}


void cow(){
    int M,N,K;
    scanf("%d %d %d",&M,&N,&K);
    stack *S[1000000];
    for(int i=0;i<M;i++){
        S[i]=alloc_stack();
    }
    for(int i=0;i<N;i++){  
        int ii,jj,kk;
        char str[10];
        scanf("%s",str);
        if(str[0]=='e'){//enter
            scanf("%d %d %d",&ii,&jj,&kk);
            push(S[kk],jj,ii);
        }
        else if(str[0]=='l'){//leave
            scanf("%d",&ii);
            pop(S[ii]);
        }
        else if(str[0]=='g'){//go
            scanf("%d",&ii);
            go(S[ii]);
        }
        else if(str[0]=='c'){//close
            scanf("%d",&ii);
            //go(S[ii]);
        }
    }
    for(int i=0;i<M;i++){
        print(S[i]);
    }
    /*
    for(int i=0;i<M;i++){
        destroy_stack(S[i]);
    }
    */
    return; 
}


int main(){
    cow();
    return 0;
}