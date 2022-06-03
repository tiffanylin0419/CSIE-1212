#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void CoolServer(int start,int M,int N){
    
}

long long arr[200001]={0};
long long sum[200001]={0};
int command[100000][5]={0};
int main() {
    // save input info in command
    
    int N,Q;
    scanf("%d %d",&N,&Q);
    for(int i=1;i<=N;i++){
        scanf("%lld",&arr[i]);
    }
    for(int i=1;i<=N;i++){
        sum[i]=sum[i-1]+arr[i];
    }

    for(int i=0;i<Q;i++){
        scanf("%d",&command[i][0]);
        if(command[i][0]==1){
            scanf("%d %d",&command[i][1],&command[i][2]);
        }else if(command[i][0]==2){
            scanf("%d",&command[i][1]);
        }else if(command[i][0]==3){
            scanf("%d %d",&command[i][1],&command[i][2]);
        }else if(command[i][0]==4){
            scanf("%d %d %d %d",&command[i][1],&command[i][2],&command[i][3],&command[i][4]);
        }else if(command[i][0]==5){
            scanf("%d %d %d",&command[i][1],&command[i][2],&command[i][3]);
        }else{
            scanf("%d %d",&command[i][1],&command[i][2]);
        }
    }
    for(int i=0;i<Q;i++){
        if(command[i][0]==1){
            N++;
            for(int j=N;j>command[i][1];j--){
                sum[j]=sum[j-1]+command[i][2];
            }
        }else if(command[i][0]==2){
            long long num=sum[command[i][1]]-sum[command[i][1]-1];
            for(int j=command[i][1];j<N;j++){
                sum[j]=sum[j+1]-num;
            }
            N--;
        }else if(command[i][0]==3){
            break;
        }else if(command[i][0]==4){
            break;
        }else if(command[i][0]==5){
            break;
        }else if(command[i][0]==6){
            printf("%lld\n",sum[command[i][2]]-sum[command[i][1]-1]);
        }
    }
}