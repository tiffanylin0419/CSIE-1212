#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void PurpleCow(int start,int M,int N){
    
}
int arr[100000]={0};
long long sum[100000]={0};

int main() {
    // save input info in command
    
    int N,Q;
    scanf("%d %d",&N,&Q);
    for(int i=1;i<=N;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=1;i<=N;i++){
        sum[i]=sum[i-1]+arr[i];
    }

    int action;
    int l;
    int r;
    for(int i=0;i<Q;i++){
        scanf("%d",&action);
        if(action==6){
            scanf("%d %d",&l,&r);
            printf("%lld\n",sum[r]-sum[l-1]);
        }
    }
}