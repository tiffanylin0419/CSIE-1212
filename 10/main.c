#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int rank;
    int parent; 
} DisjointSet;

//DisjointSet ds[1000000];

void makeset(int N,DisjointSet* ds){
    // TODO: Initialize a set with hash value
    for(int i=0;i<N;i++){
        ds[i].parent=i;
        ds[i].rank=0;
    }
    
}

int find_set(int i,DisjointSet* ds) {
    // TODO: Implement your find algorithm here
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[i].parent,ds);
    }
    return ds[i].parent;
}

void group(int a, int b,DisjointSet* ds) {
    a=find_set(a,ds);
    b=find_set(b,ds);
    // TODO: Implement your union algorithm here
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
    // TODO: Implement your algorithm here
    int aa=find_set(a,ds);
    int bb=find_set(b,ds);
    if(aa==bb){
        return true;
    }
    return false;
}

int command[1000000][3]={};
int main() {
    // TODO: Implement your algorithm here
    int N,M;
    scanf("%d %d",&N,&M);

    DisjointSet* ds= malloc(N*sizeof(DisjointSet));
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
    for(int i=0;i<M;i++){
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
            //command[i][1]
        }
    }
    
}