#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int rank;
    int parent; 
    char* str;
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

void makeset(const char* s){
    // TODO: Initialize a set with hash value
    int i = hash(s);
    ds[i].parent=i;
    ds[i].rank=0;
    ds[i].str = (char*)malloc(strlen(s)+1);
    strcpy(ds[i].str,s);
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {
        makeset(s);
        set[i] = 1;
    }
}

int find_set(const char* s) {
    init(s);
    int i = hash(s);
    // TODO: Implement your find algorithm here
    if(ds[i].parent!=i){
        ds[i].parent=find_set(ds[ds[i].parent].str);
    }
    return hash(ds[ds[i].parent].str);
}

void group(const char *ra, const char *rb) {
    int a = find_set(ra), b = find_set(rb);
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
    int aa=find_set(a);
    int bb=find_set(b);
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