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


int find_set(int i) {
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


int command[1000000][3]={};
int main() {
    for(int gg=0;gg<100;gg++){
        char filename[20];
        sprintf(filename,"test%d.txt",gg);
        FILE *f =fopen(filename, "r");
        // TODO: Implement your algorithm here
        int N,M;
        fscanf(f,"%d %d",&N,&M);
        int ds_size=(N+1)*sizeof(DisjointSet);
        for(int i=1;i<=N;i++){
            makeset(i);
        }

        char str[10];
        int person1;
        int person2;
        for(int i=0;i<M;i++){
            //query0, merge1, boom2
            fscanf(f,"%s",str);
            if(str[0]=='q'){
                command[i][0]=0;
            }
            else if(str[0]=='m'){
                command[i][0]=1;
                fscanf(f,"%d %d",&command[i][1],&command[i][2]);
            }
            else{
                command[i][0]=2;
                fscanf(f,"%d",&command[i][1]);
            }
        }
        fclose(f);
        //算boom數量
        int* boom=malloc(M*sizeof(int));
        bool boom_exist=false;
        for(int i=0;i<M;i++){
            boom[i]=0;
        }
        for(int i=0;i<M;i++){
            //query0, merge1, boom2
            if(command[i][0]==2){
                boom[command[i][1]]=1;
                boom_exist=true;
            }
        }

    
        //製作儲存boom日子的ds
        DisjointSet** ds_day= malloc(M*sizeof(DisjointSet*));
        for(int i=0;i<M;i++){
            ds_day[i]=malloc(ds_size);
        }
        //執行每天動作
        sprintf(filename,"1out%d.txt",gg);
        remove(filename);
        FILE *ff =fopen(filename, "a");   
        for(int i=0;i<M;i++){
            //存日後boom
            if(boom[i]){
                memcpy(ds_day[i],ds,ds_size);
                boom[i]=N;
            }
            //query0, merge1, boom2
            if(command[i][0]==0){
                fprintf(ff,"%d\n",N);
            }
            else if(command[i][0]==1){
                if(!same_set(command[i][1],command[i][2])){
                    N--;
                    group(command[i][1],command[i][2]);
                }
            }
            else{
                memcpy(ds,ds_day[command[i][1]],ds_size);
                N=boom[command[i][1]];
            }
        }
        fclose(ff);

        for(int i=0;i<M;i++){
            free(ds_day[i]);
        }
        free(ds_day);
        
    }
    
    
}