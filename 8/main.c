# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

void Magic_Certificate(){
    char* str = malloc(10000000*sizeof(char));
    scanf("%s",str);
    int length=strlen(str);
    int temp_length=length;
    for(int temp_length=length;temp_length>=0;temp_length--){
        bool run=true;
        for(int i=0,j=temp_length-1;i<=j;i++,j--){
            if(str[i]!=str[j]){
                run=false;
                break;
            }
        }
        if(run){
            printf("%d\n",2*length-temp_length);
            for(int i=length;i>=temp_length;i--){
                printf("%c",str[i]);
            }
            printf("%s",str);
            break;
        }
    }
    



    
    free(str);
    return;
}

int main(){
    Magic_Certificate();
}

