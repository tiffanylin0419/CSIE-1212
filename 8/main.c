# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

int RKP(char* str, int len){  
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
    return pi[len-1]+1;
}

void Magic_Certificate(){
    char* str = malloc(10000000*sizeof(char));
    scanf("%s",str);
    int length=strlen(str);
    int length_2=2*length+1;
    char* str_2 = malloc((length_2)*sizeof(char));
    str_2[length]=' ';
    //front symmetry
    for(int i=0;i<length;i++){
        str_2[i]=str[i];
        str_2[length_2-i-1]=str[i];
    }
    int front=RKP(str_2,length_2);
    //back symmetry
    for(int i=0;i<length;i++){
        str_2[length-i-1]=str[i];
        str_2[length+i+1]=str[i];
    }
    
    int back=RKP(str_2,length_2);
    if(front==length){
        printf("0\n");
        printf("%s\n",str);
    }
    else if(front>back){
        //加在前面
        printf("%d\n",length-front);
        for(int i=length-1;i>=front;i--){
            printf("%c",str[i]);
        }
        printf("%s\n",str);
    }
    else if(back>front){
        //加在後面
        printf("%d\n",length-back);
        printf("%s",str);
        for(int i=length-back-1;i>=0;i--){
            printf("%c",str[i]);
        }
        printf("\n");
    }
    else{
        printf("%d\n",length-front);
        //加在前面
        for(int i=length-1;i>=front;i--){
            printf("%c",str[i]);
        }
        printf("%s\n",str);
        //加在後面
        printf("%s",str);
        for(int i=length-back-1;i>=0;i--){
            printf("%c",str[i]);
        }
        printf("\n");
    }
    
    free(str);
    free(str_2);
    return;
}

int main(){
    Magic_Certificate();    
}

