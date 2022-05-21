#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int rank;
    int parent; 
} DisjointSet;

DisjointSet ds[1000000];
bool set[1000000] = {};

void makeset(int i){
    // TODO: Initialize a set
    ds[i].parent=i;
    ds[i].rank=0;
    set[i] = 1;
}

inline void static init(int i) {
    if (!set[i]) {
        makeset(i);
    }
}

int find_set(int i) {
    init(i);
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[i].parent);
    }
    return ds[i].parent;
}

void group(int a, int b) {
    a=find_set(a);
    b=find_set(b);
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

bool same_set(int a,int b) {
    int aa=find_set(a);
    int bb=find_set(b);
    if(aa==bb){
        return true;
    }
    return false;
}

int cmp ( const void *a , const void *b ) { 
    return *(int *)a - *(int *)b; 
}
int command[1000000][3]={};
int main() {
    int N,M;
    scanf("%d %d",&N,&M);
    
    int ds_size=N*sizeof(DisjointSet);
    

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
    
    //存boom資訊
    int* boom_num=malloc(M*sizeof(int));
    int boom_count=0;
    for(int i=0;i<M;i++){
        //query0, merge1, boom2
        if(command[i][0]==2){
            boom_num[boom_count]=command[i][1];
            boom_count++;
        }
    }
    qsort(boom_num,boom_count,sizeof(int),cmp);
    int* boom_pos=malloc(M*sizeof(int));
    int j=0;
    for(int i=0;i<M;i++){
        boom_pos[i]=-1;
    }
    for(int i=0;i<M&&j<boom_count;i++){
        if(i==boom_num[j]){
            boom_pos[i]=j;
            j++;
        }
    }
    //boom N
    int* N_boom=malloc(boom_count*sizeof(int));
    for(int i=0;i<boom_count;i++){
        N_boom[i]=0;
    }
    //boom ds
    DisjointSet** ds_day= malloc(boom_count*sizeof(DisjointSet*));
    for(int i=0;i<boom_count;i++){
        ds_day[i]=malloc(ds_size);
    }
    
    //執行每天動作
    for(int i=0;i<M;i++){
        
        //存日後boom
        if(boom_pos[i]!=-1){
            memcpy(ds_day[boom_pos[i]],ds,ds_size);
            N_boom[boom_pos[i]]=N;
        }
        
        //query0, merge1, boom2
        if(command[i][0]==0){
            printf("%d\n",N);
        }
        else if(command[i][0]==1){
            if(!same_set(command[i][1],command[i][2])){
                N--;
                group(command[i][1],command[i][2]);
            }
        }
        else{
            memcpy(ds,ds_day[boom_pos[command[i][1]]],ds_size);
            N=N_boom[boom_pos[command[i][1]]];
        }
    }
    
    for(int i=0;i<boom_count;i++){
        free(ds_day[i]);
    }
    free(ds_day);
}