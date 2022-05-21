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
    // TODO: Initialize a set with hash value
    ds[i].parent=i;
    ds[i].rank=0;
}
/*
inline void static init(int i) {
    if (!set[i]) {
        makeset(i);
        set[i] = 1;
    }
}
*/
int find_set(int i) {
    //init(i);
    // TODO: Implement your find algorithm here
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[i].parent);
    }
    return ds[i].parent;
}

void group(int a, int b) {
    a=find_set(a);
    b=find_set(b);
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

bool same_set(int a,int b) {
    // TODO: Implement your algorithm here
    int aa=find_set(a);
    int bb=find_set(b);
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

    for(int i=0;i<N;i++){
        makeset(i);
    }

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
            if(!same_set(command[i][1],command[i][2])){
                N--;
                group(command[i][1],command[i][2]);
            }
        }
        else{
            //command[i][1]
        }
    }
    
    /*
    for(int i=0;i<num;i++){
        scanf("%s %d %d",str,&person1,&person2);
        if(str[0]=='g'){
            group(person1,person2);
        }
        else{
            if(same_set(person1,person2)){
                printf("Positive\n");
            }
            else{
                printf("Negative\n");
            }
        }
    }
    */
}