#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void CoolServer(int start,int M,int N){
    
}

int arr[100001]={0};
long long sum[100001]={0};
int command[100000][5]={0};
int add[100000]={0};
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
    int add_len=0;
    for(int i=0;i<Q;i++){
        if(command[i][0]==1){
            break;
        }else if(command[i][0]==2){
            break;
        }else if(command[i][0]==3){
            break;
        }else if(command[i][0]==4){
            break;
        }else if(command[i][0]==5){
            break;
        }else if(command[i][0]==6){
            /*
            int add_num=0;
            for(int j=0;j<add_len;j++){
                if(command[i][1]<=command[add[j]][1]+1 && command[add[j]][1]+1<=command[i][2]){
                    command[i][2]--;
                    add_num+=command[add[j]][2];
                }else if(command[add[j]][1]+1<command[i][1]){
                    command[i][1]--;
                    command[i][2]--;
                }
            }
            printf("%lld\n",sum[command[i][2]]-sum[command[i][1]-1]+add_num);
            */
            long long sums=0;
            for(int j=command[i][1];j<=command[i][2];j++){
                sums+=arr[j];
            }
            printf("%lld\n",sums);
        }
    }
}