# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

int RKP(char* str, int len){
    
    //m=P.length
    int* pi = malloc(len*sizeof(int));
    pi[0]=-1; 

    int k=-1;
    for(int i=1;i<len;i++){
        while(k>=0 && str[k+1]!=str[i]){
            k=pi[k];
        }
        if(str[k+1]==str[i]){
            k++;
        }
        pi[i]=k;
    }
    //print
    //for(int i=0;i<len;i++){
    //    printf("%d ",pi[i]+1);
    //}

    free(str);
    return pi[len-1]+1;
}

int main(){
    char* str = malloc(10000000*sizeof(char));
    scanf("%s",str);
    int length=strlen(str);
    //char* str = malloc((2*length+1)*sizeof(char));

    RKP(str,length);    
}

