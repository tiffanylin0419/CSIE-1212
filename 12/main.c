#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int rank;
    int parent; 
} DisjointSet;

DisjointSet ds[1 << 24];
bool set[1 << 24] = {};

int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(int i){
    // TODO: Initialize a set with hash value
    ds[i].parent=i;
    ds[i].rank=0;
}

inline void static init(int i) {
    if (!set[i]) {
        makeset(i);
        set[i] = 1;
    }
}

int find_set(int i) {
    init(i);
    // TODO: Implement your find algorithm here
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[i].parent);
    }
    return ds[i].parent;//?
}

void group(const char *ra, const char *rb) {
    int a = find_set(hash(ra)), b = find_set(hash(rb));
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

bool same_set(const char*a, const char* b) {
    // TODO: Implement your algorithm here
    int aa=find_set(hash(a));
    int bb=find_set(hash(b));
    if(aa==bb){
        return true;
    }
    return false;
}

int main() {
    // TODO: Implement your algorithm here
    int num;
    scanf("%d",&num);
    char str[10000];
    char person1[10000];
    char person2[10000];
    for(int i=0;i<num;i++){
        scanf("%s %s %s",str,person1,person2);
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
}