# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

void merge(long long* arr,int* tag,int left,int mid,int right){
    //char** strs = malloc(k*sizeof(char*));
    long long lenL=mid-left+1;
    long long lenR=right-mid;
    long long* L= malloc((lenL+1)*sizeof(long long));
    long long* R= malloc((lenR+1)*sizeof(long long));
    int* Ltag= malloc((lenL)*sizeof(int));
    int* Rtag= malloc((lenR)*sizeof(int));

    for(int i=0;i<lenL;i++){
        L[i]=arr[left+i];
        Ltag[i]=tag[left+i];
    }
    for(int i=0;i<lenR;i++){
        R[i]=arr[mid+i+1];
        Rtag[i]=tag[mid+i+1];
    }
    
    L[lenL]=LONG_LONG_MAX;
    R[lenR]=LONG_LONG_MAX;
    int j=0,k=0;
    for(int i=left;i<=right;i++){
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
void merge_sort(long long* arr,int* tag,int left,int right){
    if (left<right){
        int mid=(left+right)/2;
        merge_sort(arr,tag,left,mid);
        merge_sort(arr,tag,mid+1,right);
        merge(arr,tag,left,mid,right);
    }
}

void Magic2(){
    int k,l,flag;
    scanf("%d %d %d",&k,&l,&flag);
    char** strs = malloc(k*sizeof(char*));
    for(int i=0;i<k;i++){
        strs[i]=malloc(l*sizeof(char));
        scanf("%s",strs[i]);
    }
    long long* RKP= malloc(k*sizeof(long long));
    long long things=26;
    long long q=LONG_LONG_MAX/(things+1);
    //O(kl)
    for(int i=0;i<k;i++){
        RKP[i]=0;
        for(int j=0;j<l;j++){
            RKP[i]=(things*RKP[i]+(long long)strs[i][j]-97)%q;
        }
    }

    //存成一行k個值，sort，任2相等就檢查是不是是答案
    int* sorted_position= malloc(k*sizeof(int));
    //長度=1
    if(k==1){
        printf("No\n");
        return;
    }
    if(l==1){
        for(int j=0;j<k;j++){
            sorted_position[j]=j;
        }
        merge_sort(RKP,sorted_position,0,k-1);
        int kk;
        for(int j=0;j<k;j++){
            kk=j+1;
            //printf("%d %d,%lld %lld\n",j,kk,RKP_short[j],RKP_short[kk]);
            while(RKP[j]==RKP[kk] && kk<k){
                printf("Yes\n");
                printf("%d %d\n",sorted_position[j],sorted_position[kk]);
                return;
                kk++;
            }
        }
        printf("No\n");
        return;
    }   

    //O(l)
    int* num= malloc(l*sizeof(int));
    num[l-1]=1;
    for(int i=1;i<l;i++){
        num[l-1-i]=num[l-i]*things%q;
    }
    //O(lklgk)
    long long* RKP_short= malloc(k*sizeof(long long));
    
    for(int i=0;i<l;i++){
        for(int j=0;j<k;j++){
            RKP_short[j]=(RKP[j]+q-num[i]*((long long)strs[j][i]-97))%q;
            sorted_position[j]=j;
        }
        //sort
        
        merge_sort(RKP_short,sorted_position,0,k-1);
        int kk;
        for(int j=0;j<k;j++){
            kk=j+1;
            //printf("%d %d,%lld %lld\n",j,kk,RKP_short[j],RKP_short[kk]);
            while(RKP_short[j]==RKP_short[kk] && kk<k){
                printf("Yes\n");
                printf("%d %d\n",sorted_position[j],sorted_position[kk]);

                return;
                kk++;
            }
        }
        printf("No\n");
        return;
    }

    for(int i=0;i<k;i++){
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