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

DisjointSet ds[1000001];
Node* boom_pos[1000001];
int query[1000001] = {0};
int action[1000001] = {0};
int command[1000001][3]={0};

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
    for(int i=start;i<=M;i++){
        
        if(start==i){//?
            query[i]=N;
            while(boom_pos[i]->next!=NULL){
                PurpleCow(boom_pos[i]->value,M,N);
                boom_pos[i]=boom_pos[i]->next;
            }
            continue;
        }
        
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
            i--;//?
            //退回去
            while(i>start){//?
                if(action[i]!=-1){
                    degroup(action[i]);
                }
                i--;
            }
            break;
        }
        if(i==M){//?
            //退回去
            while(i>start){//? >= to >
                if(action[i]!=-1){
                    degroup(action[i]);
                }
                i--;
            }
            break;
        }
        
        //如果i in boom_pos要recursive
        while(boom_pos[i]->next!=NULL){
            PurpleCow(boom_pos[i]->value,M,N);
            boom_pos[i]=boom_pos[i]->next;
        }
    }
    return;
}


int main() {
    for(int gg=0;gg<100;gg++){
        // save input info in command
        char filename[20];
        sprintf(filename,"test%d.txt",gg);
        FILE *f =fopen(filename, "r");
        int N,M;
        fscanf(f,"%d %d",&N,&M);
        
        int ds_size=N*sizeof(DisjointSet);
        for(int i=1;i<=N;i++){
            makeset(i);
        }
        char str[10];
        for(int i=1;i<=M;i++){
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
        

        //保證最後一個是query
        for(int i=M;i>=1;i--){
            if(command[i][0]==0){
                M=i;
                break;
            }
        }
        
        //save info in boom_pos
        for(int i=1;i<=M;i++){
            action[i]=-1;
        }
        for(int i=0;i<=M;i++){
            boom_pos[i]=(Node *)malloc(sizeof(Node)); 
            boom_pos[i]->value=-1;
            boom_pos[i]->next=NULL;
        }
        for(int i=1;i<=M;i++){
            if(command[i][0]==2){
                makenode(command[i][1],i);
            }
        }


        PurpleCow(0,M,N);
        sprintf(filename,"2out%d.txt",gg);
        remove(filename);
        FILE *ff =fopen(filename, "a");    
        for(int i=1;i<=M;i++){
            if(command[i][0]==0){
                fprintf(ff,"%d\n",query[i]);
            }
        }
        fclose(ff);
    }
    
}