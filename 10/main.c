#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    int rank;
    int parent; 
} DisjointSet;

typedef struct node{
    int value;
    struct node* next; 
} Node;

DisjointSet ds[1000000];
Node* boom_pos[1000000];
int query[1000000] = {-1};
int action[1000000] = {-1};
int command[1000000][3]={};

void makenode(int i,int val){
    Node* tmp=(Node *)malloc(sizeof(Node)); 
    tmp->value=val;
    tmp->next=boom_pos[i];
    boom_pos[i]=tmp;
}

void makeset(int i){
    // TODO: Initialize a set
    ds[i].parent=i;
    ds[i].rank=0;
}


int find_set(int i) {
    int result=i;
    while(ds[result].parent!=result){
        result=ds[result].parent;
    }
    return result;
}

int group(int a, int b) {
    a=find_set(a);
    b=find_set(b);
    if(ds[a].rank < ds[b].rank){
        ds[a].parent=b;
        return a;
    }
    else if(ds[a].rank > ds[b].rank){
        ds[b].parent=a;
        return b;
    }
    else{
        ds[b].parent=a;
        ds[a].rank++;
        return b;
    }
}

void degroup(int a) {
    ds[a].parent=a;
}

bool same_set(int a,int b) {
    int aa=find_set(a);
    int bb=find_set(b);
    if(aa==bb){
        return true;
    }
    return false;
}

void PurpleCow(int start,int M,int N){
    for(int i=start;i<M;i++){
        //query0, merge1, boom2
        if(command[i][0]==0){
            query[i]=N;
        }
        else if(command[i][0]==1){
            if(!same_set(command[i][1],command[i][2])){
                N--;
                int move=group(command[i][1],command[i][2]);
                action[i]=move;
            }
            query[i]=N;
        }
        else{
            //退回去
            while(i>=start){
                if(action[i]!=-1){
                    degroup(i);
                    N++;
                }
                i--;
            }
            break;
        }
        //如果i in boom_pos要recursive
        while(boom_pos[i]->next!=NULL){
            PurpleCow(boom_pos[i]->value+1,M,N);
            boom_pos[i]=boom_pos[i]->next;
        }
    }
    return;
}


int main() {
    // save input info in command
    int N,M;
    scanf("%d %d",&N,&M);
    int ds_size=N*sizeof(DisjointSet);
    for(int i=0;i<N;i++){
        makeset(i);
    }
    char str[10];
    for(int i=0;i<M;i++){
        //query0, merge1, boom2
        scanf("%s",str);
        if(str[0]=='q'){
            command[i][0]=0;
        }
        else if(str[0]=='m'){
            command[i][0]=1;
            scanf("%d %d",&command[i][1],&command[i][2]);
        }
        else{
            command[i][0]=2;
            scanf("%d",&command[i][1]);
        }
    }
    /* debugging
    int N=4,M=11;
    int ds_size=N*sizeof(DisjointSet);
    for(int i=0;i<N;i++){
        makeset(i);
    }
    //query0, merge1, boom2
    command[0][0]=1;
    command[0][1]=1;
    command[0][2]=2;
    command[1][0]=1;
    command[1][1]=1;
    command[1][2]=3;
    command[2][0]=0;
    command[3][0]=2;
    command[3][1]=1;
    command[4][0]=0;
    command[5][0]=1;
    command[5][1]=1;
    command[5][2]=3;
    command[6][0]=1;
    command[6][1]=2;
    command[6][2]=4;
    command[7][0]=2;
    command[7][1]=4;
    command[8][0]=0;
    command[9][0]=2;
    command[9][1]=0;
    command[10][0]=0;
    */

    //保證最後一個是query
    for(int i=M-1;i>=0;i--){
        if(command[i][0]==0){
            M=i+1;
            break;
        }
    }
    
    //save info in boom_pos
    for(int i=0;i<M;i++){
        boom_pos[i]=(Node *)malloc(sizeof(Node)); 
        boom_pos[i]->value=-1;
        boom_pos[i]->next=NULL;
    }
    for(int i=0;i<M;i++){
        if(command[i][0]==2){
            makenode(command[i][1],i);
        }
    }


    PurpleCow(0,M,N);
    int i;
    for(i=0;i<M;i++){
        if(command[i][0]==2){
            break;
        }
    }
    for(int j=i;j<M;j++){
        query[j]++;
    }
    

    for(int i=0;i<M;i++){
        if(command[i][0]==0){
            printf("%d\n",query[i]);
        }
    }

  
}