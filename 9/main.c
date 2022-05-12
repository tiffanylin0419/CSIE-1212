# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

void merge(long long* arr,long long* tag,long long left,long long mid,long long right){
    //char** strs = malloc(k*sizeof(char*));
    long long lenL=mid-left+1;
    long long lenR=right-mid;
    long long* L= malloc((lenL+1)*sizeof(long long));
    long long* R= malloc((lenR+1)*sizeof(long long));
    long long* Ltag= malloc((lenL)*sizeof(long long));
    long long* Rtag= malloc((lenR)*sizeof(long long));

    for(long long i=0;i<lenL;i++){
        L[i]=arr[left+i];
        Ltag[i]=tag[left+i];
    }
    for(long long i=0;i<lenR;i++){
        R[i]=arr[mid+i+1];
        Rtag[i]=tag[mid+i+1];
    }
    
    L[lenL]=LLONG_MAX;
    R[lenR]=LLONG_MAX;
    long long j=0,k=0;
    for(long long i=left;i<=right;i++){
        if(L[j]<R[k]){
            arr[i]=L[j];
            tag[i]=Ltag[j];
            j++;
        }
        else{
            arr[i]=R[k];
            tag[i]=Rtag[k];
            k++;
        }
    }
    free(L);
    free(R);
    free(Ltag);
    free(Rtag);
}
void merge_sort(long long* arr,long long* tag,long long left,long long right){
    if (left<right){
        long long mid=(left+right)/2;
        merge_sort(arr,tag,left,mid);
        merge_sort(arr,tag,mid+1,right);
        merge(arr,tag,left,mid,right);
    }
}
void hash(long long* RKP,char** strs,long long k,long long l,long long things,long long q){
    for(long long i=0;i<k;i++){
        RKP[i]=0;
        for(long long j=0;j<l;j++){
            RKP[i]=(things*RKP[i]+(long long)strs[i][j]-33)%q;
        }
    }
}

bool similar(char** strs,long long a,long long b,long long l){
    int different=0;
    for(int m=1;m<l;m++){
        if(strs[a][m]!=strs[b][m]){
            different++;
        }
    }
    if(different<=1){
        return true;
    }
    return false;
}
void Magic2(){
    long long k,l,flag;
    scanf("%lld %lld %lld",&k,&l,&flag);
    char** strs = malloc(k*sizeof(char*));
    for(long long i=0;i<k;i++){
        strs[i]=malloc((l+1)*sizeof(char));
        scanf("%s",strs[i]);
    }
    long long* RKP= malloc(k*sizeof(long long));
    long long things=126-33+1;
    long long q=LLONG_MAX/(things+2)-1;
    //calculate RKP
    //O(kl)
    hash(RKP, strs,k,l,things, q);
    
    //存成一行k個值，sort，任2相等就檢查是不是是答案
    long long* sorted_position= malloc(k*sizeof(long long));
    //長度=1
    if(k==1){
        printf("No\n");
        return;
    }
    if(l==1){
        /*
        for(long long j=0;j<k;j++){
            sorted_position[j]=j;
        }
        merge_sort(RKP,sorted_position,0,k-1);
        long long kk;
        for(long long j=0;j<k;j++){
            kk=j+1;
            //printf("%lld %lld,%lld %lld\n",j,kk,RKP_short[j],RKP_short[kk]);
            while(RKP[j]==RKP[kk] && kk<k){
                printf("Yes\n");
                printf("%lld %lld\n",sorted_position[j],sorted_position[kk]);
                return;
                kk++;
            }
        }
        */
        printf("Yes\n");
        printf("0 1\n");
        return;
    }   
    
    //O(l)
    long long* num= malloc(l*sizeof(long long));
    num[l-1]=1;
    for(long long i=1;i<l;i++){
        num[l-1-i]=num[l-i]*things%q;
    }
    
    //O(lklgk)//?
    long long* RKP_short= malloc(k*sizeof(long long));
    for(long long i=0;i<l;i++){
        for(long long j=0;j<k;j++){
            RKP_short[j]=(RKP[j]+q-num[i]*((long long)strs[j][i]-33))%q;
            sorted_position[j]=j;
        }
        //sort
        merge_sort(RKP_short,sorted_position,0,k-1);
        long long kk;
        for(long long j=0;j<k-1;j++){
            kk=j+1;
            while(RKP_short[j]==RKP_short[kk] && kk<k){
                //?
                printf("Yes\n");
                printf("%lld %lld\n",sorted_position[j],sorted_position[kk]);
                return;
                /*
                if(similar(strs,sorted_position[j],sorted_position[kk],l)){
                    printf("Yes\n");
                    printf("%lld %lld\n",sorted_position[j],sorted_position[kk]);
                    return;
                }
                */
                if(kk>=k-1){
                    break;
                }
                kk++;
            }
        }
        
    }
    printf("No\n");
    
    for(long long i=0;i<k;i++){
        free(strs[i]);
    }
    free(strs);
    free(RKP);
    free(num);
    free(RKP_short);
    free(sorted_position);
    
}

int main(){
    Magic2();
}