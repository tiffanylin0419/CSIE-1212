# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

void Magic_Certificate(){
    char* str = malloc(10000000*sizeof(char));
    //char str[10000];
    scanf("%s",str);
    int length=strlen(str);
    int temp_length=length;
    for(int temp_length=length,temp_start=0;temp_length>=0;temp_length--,temp_start++){
        //front
        bool run_front=true;
        for(int i=0,j=temp_length-1;i<=j;i++,j--){
            if(str[i]!=str[j]){
                run_front=false;
                break;
            }
        }
        //end
        bool run_end=true;
        for(int i=temp_start,j=length-1;i<=j;i++,j--){
            if(str[i]!=str[j]){
                run_end=false;
                break;
            }
        }
        //print
        if(run_front || run_end){
            printf("%d\n",length-temp_length);
            if(run_front){
                for(int i=length-1;i>=temp_length;i--){
                    printf("%c",str[i]);
                }
                printf("%s\n",str);
            }
            if(run_end && length!=temp_length){
                printf("%s",str);
                for(int i=temp_start-1;i>=0;i--){
                    printf("%c",str[i]);
                }
                printf("\n");
            }
            break;
        }
    } 
    free(str);
    return;
}

int main(){
    Magic_Certificate();    
}

