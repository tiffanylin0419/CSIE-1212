#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc / free 
#include <memory.h> // memset
#include <ctype.h>//isdigit

typedef struct node{ 
    int data;
    struct node *next; 
} node;

typedef struct group{ 
    int group_id;
    struct node *head; 
    struct group *left, *right; 
} group;

typedef struct line{ 
    struct group *head; 
    struct group *tail; 
    bool open;
} line;

node *alloc(){
    node *tmp = (node *)malloc(sizeof(node)); 
    tmp->next=NULL;
    return tmp;
}

void destroy(node *N){ 
    // clean sensitive data.
    memset(N, 0, sizeof(*N));
    free(N); 
    N=NULL;
    return;
}
void destroy_group(group *G){ 
    // clean sensitive data.
    memset(G, 0, sizeof(*G));
    free(G); 
    G=NULL;
    return;
}

group *alloc_group(){
    group *tmp = (group *)malloc(sizeof(group)); 
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->head=NULL;
    return tmp;
}

line *alloc_line(){
    line *tmp = (line *)malloc(sizeof(line)); 
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->open=true;
    return tmp;
}
node *secondLastInLine(group *G){
    node *tmp=G->head;
    node *tmpp;
    while(tmp->next!=NULL){
        tmpp=tmp;
        tmp=tmp->next;
    }
    return tmpp;
}

node *lastInLine(group *G){
    node *tmp=G->head;
    while(tmp->next!=NULL){
        tmp=tmp->next;
    }
    return tmp;
}

group *find(line *S,int group_id){
    group *tmp=S->head;
    while(tmp!=S->tail){
        if(tmp->group_id==group_id){
            return tmp;
        }
        tmp=tmp->right;
    }
    return S->tail;
}

void push(line *S,int data,int group_id){
    node *tmp=alloc();
    tmp->data=data;
    //tmp->group=group;
    if(S->head==NULL){
        group *tmpp=alloc_group();
        tmpp->head=tmp;
        tmpp->group_id=group_id;
        S->head=tmpp;
        S->tail=tmpp;
    }
    else{
        group *position=find(S,group_id);
        if(position->group_id==group_id){
            node *front=lastInLine(position);
            front->next=tmp;
        }
        else{
            group *tmpp=alloc_group();
            S->tail->right=tmpp;
            tmpp->left=S->tail;
            tmpp->head=tmp;
            tmpp->group_id=group_id;
            S->tail=tmpp;
        }
    }
}
void pop(line *S){
    group *tmp=S->tail;

    if(tmp->head->next==NULL){
        //只有一顆
        destroy(tmp->head);
        //delete group
        if(S->head==S->tail){
            destroy_group(S->tail);
            S->tail=NULL;
            S->head=NULL;
        }
        else{
            S->tail=S->tail->left;
            destroy_group(S->tail->right);
            S->tail->right=NULL;
        } 
    }
    else{
        node *tmpp=secondLastInLine(tmp);
        destroy(tmpp->next);
        tmpp->next=NULL;
    }
    return;
}
void go(line *S){
    group *tmp=S->head;
    if(tmp->head->next==NULL){
        //只有一顆
        destroy(tmp->head);
        //delete group
        if(S->head==S->tail){
            destroy_group(S->head);
            S->tail=NULL;
            S->head=NULL;
        }
        else{
            S->head=S->head->right;
            destroy_group(S->head->left);
            S->head->left=NULL;
        } 
    }
    else{
        node *tmpp=tmp->head;
        tmp->head=tmp->head->next;
        destroy(tmpp);
        tmpp->next=NULL;
    }
    return;
}
/*
void destroy_line(line *S){
    while(S->top->right!=NULL){
        pop(S);
    }
    // clean sensitive data.
    memset(S, 0, sizeof(*S));
    free(S); 
    return;
}
*/
void print(line *S){
    group* tmp=S->head;

    if(tmp!=NULL){
        while (tmp->right!=NULL) {
            node *tmpp =tmp->head;
            while(tmpp->next!=NULL){
                printf("%d ",tmpp->data);
                tmpp=tmpp->next;
            }
            tmp=tmp->right;
            printf("%d ",tmpp->data);
        }
        node *tmpp =tmp->head;
            while(tmpp->next!=NULL){
                printf("%d ",tmpp->data);
                tmpp=tmpp->next;
            }
            tmp=tmp->right;
            printf("%d ",tmpp->data);
    }
    printf("\n");
    return;
}


void cow(){
    int M=0,N=0,K=0;
    scanf("%d %d %d",&M,&N,&K);

    line *S[100000];
    for(int i=0;i<M;i++){
        S[i]=alloc_line();
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
        /*
        for(int i=0;i<M;i++){
            print(S[i]);
        }
        */

    }
    for(int i=0;i<M;i++){
        print(S[i]);
    }
    /*
    for(int i=0;i<M;i++){
        destroy_line(S[i]);
    }
    */
    return; 
}


int main(){
    cow();
    return 0;
}