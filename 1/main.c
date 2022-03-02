#include<stdio.h>
#include <stdbool.h>
#include <string.h>
bool bigger(int a[], int b[],int lena, int lenb){
    if (lena>lenb)
    {
        return 1;
    }
    else if(lenb>lena)
    {
        return 0;
    }
    for (int i=lena-1;i>=0;i--){
        if(a[i]>b[i]){
            return 1;
        }
        else if(a[i]<b[i]){
            return 0;
        }
    }
    return 0;
}
bool isZero(int a[],int lena){
    if(lena==1 && a[0]==0){
        return 1;
    }
    return 0;
}
void checkNum(int a[],int* lena){
    for(int i=0;i<*lena;i++){
        if(a[i]>=10){
            if(i!=*lena-1){
                a[i+1]+=(a[i]/10);
            }
            else{
                a[i+1]=(a[i]/10);
                *lena+=1;
            }
            a[i]%=10;
        }
    }
    for(int i=*lena-1;i>0;i--){
        if (a[i]!=0){
            *lena=i+1;
            break;
        }
        *lena=1;
    }
    return;
}
void timesTwo(int a[],int* lena){
    for(int i=0;i<*lena;i++){
        a[i]*=2;
    }
    checkNum(a,lena);
    return;
}
void divideTwo(int a[],int* lena){
    for(int i=*lena-1;i>=0;i--){
        if(a[i]%2==0){
            a[i]/=2;
        }
        else{
            a[i]/=2;
            if(i!=0){
                a[i-1]+=10;
            }
            if(i==*lena-1&&i!=0){
                if(a[i]==0){
                    *lena-=1;
                }
            }
        }
    }
    return;
}

void minus(int a[], int b[],int* lena, int* lenb){
    for(int i=0;i<*lena;i++){
        a[i]-=b[i];
        if(a[i]<0){
            a[i]+=10;
            a[i+1]-=1;
        }
    }
    if(a[*lena-1]==0&&*lena!=1){
        *lena-=1;
    }
    for(int i=*lena-1;i>0;i--){
        if (a[i]!=0){
            *lena=i+1;
            break;
        }
        *lena=1;
    }
    return;
}
void times(int a[], int b[],int lena, int lenb){
    int result[300]={0};
    int lenresult=lena + lenb;
    for(int i=0;i<lena;i++){
        for (int j=0;j<lenb;j++){
            result[i+j]+=a[i]*b[j];
        }
    }
    checkNum(result,&lenresult);
    for(int i=lenresult-1;i>=0;i--){
        printf("%d",result[i]);
    }
}

void GCD_By_Binary(int a[], int b[],int lena, int lenb){
    int ans[300]={1};
    int lenans=1;
    //make a>b
    if(bigger(b,a,lenb,lena)){
        int* tempp=b;
        b=a;
        a=tempp;
        int temp=lenb;
        lenb=lena;
        lena=temp;
    }
    while(!isZero(a,lena) && !isZero(b,lenb)){
        
        if (a[0]%2==0 && b[0]%2==0){
            timesTwo(ans,&lenans);
            divideTwo(a,&lena);
            divideTwo(b,&lenb);
        }
        else if (b[0]%2==0){
            divideTwo(b,&lenb);
        }
        else if (a[0]%2==0){
            divideTwo(a,&lena);
        }
        
        if(bigger(b,a,lenb,lena)){
            int* tempp=b;
            b=a;
            a=tempp;
            int temp=lenb;
            lenb=lena;
            lena=temp;
        }
        minus(a,b,&lena,&lenb);
        
    }
    times(ans,b,lenans,lenb);
    return; 
}
int main(){
    char sa[800],sb[300];
    scanf("%s", sa);
    //printf("%s\n", sa);
    scanf("%s", sb);
    //printf("%s\n", sb);

    int a[300],b[300];
    int lena=strlen(sa);
    int lenb=strlen(sb);
    for (int i=0;i<lena;i++){
        a[i]=sa[lena-i-1]-48;
    }
    for (int i=0;i<lenb;i++){
        b[i]=sb[lenb-i-1]-48;
    }
    GCD_By_Binary(a,b,lena,lenb);
    
    return 0;
}