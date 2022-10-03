#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void CoolServer(int start,int M,int N){
    
}
long long tmp[200001]={0};
long long arr[200001]={0};
long long sum[200001]={0};
int command[100000][5]={0};
int main() {
    // save input info in command
    int gg=5;
    char filename[20];
    sprintf(filename,"test%d.txt",gg);
    FILE *f =fopen(filename, "r");
    int N,Q;
    fscanf(f,"%d %d",&N,&Q);
    for(int i=1;i<=N;i++){
        fscanf(f,"%lld",&arr[i]);
    }
    for(int i=1;i<=N;i++){
        sum[i]=sum[i-1]+arr[i];
    }

    for(int i=0;i<Q;i++){
        fscanf(f,"%d",&command[i][0]);
        if(command[i][0]==1){
            fscanf(f,"%d %d",&command[i][1],&command[i][2]);
        }else if(command[i][0]==2){
            fscanf(f,"%d",&command[i][1]);
        }else if(command[i][0]==3){
            fscanf(f,"%d %d",&command[i][1],&command[i][2]);
        }else if(command[i][0]==4){
            fscanf(f,"%d %d %d %d",&command[i][1],&command[i][2],&command[i][3],&command[i][4]);
        }else if(command[i][0]==5){
            fscanf(f,"%d %d %d",&command[i][1],&command[i][2],&command[i][3]);
        }else{
            fscanf(f,"%d %d",&command[i][1],&command[i][2]);
        }
    }
    fclose(f);
    sprintf(filename,"1out%d.txt",gg);
    remove(filename);
    FILE *ff =fopen(filename, "a");  

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
            for(int j=command[i][1];j<=command[i][2];j++){
                tmp[j]=sum[j]-sum[j-1];
            }
            int minus=0;
            int key=command[i][3];
            for(int j=command[i][1];j<=command[i][2];j++){
                if(tmp[j]>key){
                    minus+=(tmp[j]-key);
                }
                sum[j]-=minus;
            }
            for(int j=command[i][2]+1;j<=N;j++){
                sum[j]-=minus;
            }
        }else if(command[i][0]==6){
            fprintf(ff,"%lld\n",sum[command[i][2]]-sum[command[i][1]-1]);

        }
        /*
        for(int j=1;j<=N;j++){
            printf("%lld ",sum[j]);
        }
        printf("\n");*/
    }
    fclose(ff);
}