#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int rank;
    int parent; 
} DisjointSet;

void makeset(int N,DisjointSet* ds){
    // TODO: Initialize a set
    for(int i=0;i<N;i++){
        ds[i].parent=i;
        ds[i].rank=0;
    }
    
}

int find_set(int i,DisjointSet* ds) {
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[i].parent,ds);
    }
    return ds[i].parent;
}

void group(int a, int b,DisjointSet* ds) {
    a=find_set(a,ds);
    b=find_set(b,ds);
    if(ds[a].rank < ds[b].rank){
        ds[a].parent=b;
    }
    else if(ds[a].rank > ds[b].rank){
        ds[b].parent=a;
    }
    else{
        ds[b].parent=a;
        ds[a].rank++;
    }
}

bool same_set(int a,int b,DisjointSet* ds) {
    int aa=find_set(a,ds);
    int bb=find_set(b,ds);
    if(aa==bb){
        return true;
    }
    return false;
}

int command[1000000][3]={};
int main() {
    int N,M;
    scanf("%d %d",&N,&M);
    int ds_size=N*sizeof(DisjointSet);
    DisjointSet* ds= malloc(ds_size);
    makeset(N,ds);
    
    char str[10000];
    int person1;
    int person2;
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

    //算boom數量
    int* boom=malloc(M*sizeof(int));
    for(int i=0;i<M;i++){
        boom[i]=0;
    }
    for(int i=0;i<M;i++){
        //query0, merge1, boom2
        if(command[i][0]==2){
            boom[command[i][1]]=1;
        }
    }

    //製作儲存boom日子的ds
    DisjointSet** ds_day= malloc(M*sizeof(DisjointSet*));
    for(int i=0;i<M;i++){
        ds_day[i]=malloc(ds_size);
    }

    //執行每天動作
    for(int i=0;i<M;i++){
        //存日後boom
        if(boom[i]){
            memcpy(ds_day[i],ds,ds_size);
            boom[i]=N;
            /*printf("%d:",i);
            for(int j=0;j<N;j++){
                printf("%d %d  ",j,ds[j].parent);
            }
            printf("\n");*/
        }
        //query0, merge1, boom2
        if(command[i][0]==0){
            printf("%d\n",N);
        }
        else if(command[i][0]==1){
            if(!same_set(command[i][1],command[i][2],ds)){
                N--;
                group(command[i][1],command[i][2],ds);
            }
        }
        else{
            memcpy(ds,ds_day[command[i][1]],ds_size);
            N=boom[command[i][1]];
        }
    }
    
    free(ds);
    for(int i=0;i<M;i++){
        free(ds_day[i]);
    }
    free(ds_day);
}