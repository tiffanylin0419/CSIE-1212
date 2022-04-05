#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc / free 
#include <memory.h> // memset
#include <ctype.h>//isdigit

typedef struct node{ 
    int data;
    struct node *left,*right; 
} node;

typedef struct group{ 
    int group_id;
    struct node *head,*tail; 
    struct group *left, *right; 
    bool direction;//initaially true
} group;

typedef struct line{ 
    struct group *head,*tail; 
    bool open;
} line;

node *alloc(){
    node *tmp = (node *)malloc(sizeof(node)); 
    tmp->left=NULL;
    tmp->right=NULL;
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
    tmp->tail=NULL;
    tmp->direction=true;
    return tmp;
}

line *alloc_line(){
    line *tmp = (line *)malloc(sizeof(line)); 
    tmp->head = NULL;
    tmp->tail = NULL;
    //tmp->left=NULL;
    //tmp->right=NULL;
    tmp->open=true;
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
//start?
void push(line *S,int data,int group_id){
    node *tmp=alloc();
    tmp->data=data;
    //tmp->group=group;
    if(S->head==NULL){
        group *tmpp=alloc_group();
        tmpp->head=tmp;
        tmpp->tail=tmp;
        tmpp->group_id=group_id;
        S->head=tmpp;
        S->tail=tmpp;
    }
    else{
        group *position=find(S,group_id);
        if(position->group_id==group_id){
            node *front=position->tail;
            front->right=tmp;
            tmp->left=front;
            position->tail=tmp;
        }
        else{
            group *tmpp=alloc_group();
            S->tail->right=tmpp;
            tmpp->left=S->tail;
            tmpp->head=tmp;
            tmpp->tail=tmp;
            tmpp->group_id=group_id;
            S->tail=tmpp;
        }
    }
}

void pop(line *S){
    group *tmp=S->tail;

    if(tmp->head->right==NULL){
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
        node *tmpp=tmp->tail->left;
        tmp->tail=tmpp;
        destroy(tmpp->right);
        tmpp->right=NULL;
    }
    return;
}
void go(line *S){
    group *tmp=S->head;
    if(tmp->head->right==NULL){
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
        tmp->head=tmp->head->right;
        tmp->head->left=NULL;
        destroy(tmpp);
        //tmpp->right=NULL;
    }
    return;
}

void reverse(group *G){
    node *tmp=G->head;
    G->head=G->tail;
    G->tail=tmp;
    tmp=G->head;
    while(tmp->left!=NULL){
        node *tmpp=tmp->right;
        tmp->right=tmp->left;
        tmp->left=tmpp;
        tmp=tmp->right;
    }
    node *tmpp=tmp->right;
    tmp->right=tmp->left;
    tmp->left=tmpp;
    return;
}

void move(line *S1,line *S2){
    //close S1 put into S2
    S1->open=false;
    group *tmp=S1->tail;
    //bathroom is empty
    if(S2->head==NULL){
        //group 0011 close 0有問題
        reverse(tmp);
        S2->head=tmp;
        S2->tail=tmp;

        if(tmp->left!=NULL){
            tmp=tmp->left;
            while(tmp->left!=NULL){
                reverse(tmp);
                group *position=S2->tail;
                position->right=tmp;
                tmp=tmp->left;
                position->right->left=position;
                position->right->right=NULL;
                S2->tail=position->right;
            }
            reverse(tmp);
            group *position=S2->tail;
            position->right=tmp;
            position->right->left=position;
            position->right->right=NULL;
            S2->tail=position->right;
        }

        S2->head->left=NULL;
        S2->tail->right=NULL;
        S1->head=NULL;
        S1->tail=NULL;
        return;
    }
    while(tmp!=S1->head){
        reverse(tmp);
        group *position=find(S2,tmp->group_id);
        if(position !=S2->tail){
            node *tmpp=position->tail;
            position->tail=tmp->tail;
            tmpp->right=tmp->head;
            tmp->head->left=tmpp;
            tmp=tmp->left;
            destroy_group(tmp->right);
            tmp->right=NULL;
        }
        else{
            if(tmp->group_id==position->group_id){
                node *tmpp=position->tail;
                position->tail=tmp->tail;
                tmpp->right=tmp->head;
                tmp->head->left=tmpp;
                tmp=tmp->left;
                destroy_group(tmp->right);
                tmp->right=NULL;
            }
            
            else{
                //接在Ｓ2後面
                position->right=tmp;
                tmp=tmp->left;
                position->right->left=position;
                position->right->right=NULL;
                S2->tail=position->right;
            }
        }
    }

    reverse(tmp);
    group *position=find(S2,tmp->group_id);
    if(position !=S2->tail){
        node *tmpp=position->tail;
        position->tail=tmp->tail;
        tmpp->right=tmp->head;
        tmp->head->left=tmpp;
        destroy_group(tmp);
    }
    else{
        if(tmp->group_id==position->group_id){
            node *tmpp=position->tail;
            position->tail=tmp->tail;
            tmpp->right=tmp->head;
            tmp->head->left=tmpp;
            destroy_group(tmp);
            
        }   
        else{
            //接在Ｓ2後面  
            position->right=tmp;
            position->right->left=position;
            position->right->right=NULL;
            S2->tail=position->right;
        }
    }
    S1->head=NULL;
    S1->tail=NULL;

    S2->head->left=NULL;
    S2->tail->right=NULL;
    //destroy_line(S1) 
    //afterwards when S is malloced
    
    return;
}

void print(line *S){
    
    group* tmp=S->head;
     
    if(tmp!=NULL){
        while (tmp->right!=NULL) {
            node *tmpp =tmp->head;
            while(tmpp->right!=NULL){
                printf("%d ",tmpp->data);
                tmpp=tmpp->right;
            }
            tmp=tmp->right;
            printf("%d ",tmpp->data);
            //printf("%p %d %p\n",tmpp->left,tmpp->data,tmpp->right);
        }
        //printf("head:%d tail: %d\n",tmp->head->data,tmp->tail->data);
        //printf("%d\n",tmp->group_id);
        node *tmpp =tmp->head;
        while(tmpp->right!=NULL){
            //printf("%p %d %p\n",tmpp->left,tmpp->data,tmpp->right);
            printf("%d ",tmpp->data);
            tmpp=tmpp->right;
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
    line **S = (line **)malloc(sizeof(line *)*M); 
    for(int i=0;i<M;i++){
        S[i]=alloc_line();
    }
    for(int i=0;i<N;i++){  
        int ii,jj,kk;
        char str[10];
        scanf("%s",str);
        if(str[0]=='e'){//enter
            scanf("%d %d %d",&ii,&jj,&kk);
            bool notdone=true;
            for(int j=kk;j>=0 && notdone;j--){
                if(S[j]->open ){
                    push(S[j],jj,ii);
                    notdone=false;
                }
            }
            for(int j=M-1;j>kk && notdone;j--){
                if(S[j]->open ){
                    push(S[j],jj,ii);
                    notdone=false;
                }
            }
            
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
            if(S[ii]->head==NULL){
                S[ii]->open=false;
            }
            else{
                bool notdone=true;
                for(int j=ii-1;j>=0 && notdone;j--){
                    if(S[j]->open ){
                        //printf("move to%d\n",j);
                        move(S[ii],S[j]);
                        notdone=false;
                    }
                }
    
                for(int j=M-1;j>ii && notdone;j--){
                    if(S[j]->open && notdone){
                        //printf("moves to%d\n",j);
                        move(S[ii],S[j]);
                        notdone=false;
                    }
                }
            }
            
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

    return; 
}


int main(){
    cow();
    return 0;
}