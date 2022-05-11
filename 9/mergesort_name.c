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
}
void merge_sort(long long* arr,int* tag,int left,int right){
    if (left<right){
        int mid=(left+right)/2;
        merge_sort(arr,tag,left,mid);
        merge_sort(arr,tag,mid+1,right);
        merge(arr,tag,left,mid,right);
    }
}

int main(){
    long long arr[10]={0,1,6,3,5,5,3,7,8,0};
    int tag[10];
    for(int i=0;i<10;i++){
        tag[i]=i;
    }

    merge_sort(arr,tag,0,9);

}