#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool boardSolved(int* board,int wid,int len){
    for(int i=0;i<len;i++){
        for (int j=0;j<wid;j++){
            if (board[i*5+j]==0){
                return 0;
            }
        }
    }
    return 1;
}
void printBoard(int* board,int wid,int len){
    for(int i=0;i<len;i++){
        for (int j=0;j<wid;j++){
            if(board[i*5+j]==1){
                printf("o");
            }
            else{
                printf("_");
            }
        }
        printf("\n");
    }
}

bool boardIsValid(int* board,int wid,int* arr_wid,int len,int* arr_len){
    
    
    //check row
    //printf("row\n");
    for(int i=0;i<len;i++){
        int arr_wid_check[5]={0};
        for (int j=0;j<arr_wid[i*6+0];j++){
            arr_wid_check[j]=0;
        }
        int k=0;
        for (int j=0;j<wid;j++){
            if(board[i*5+j]>0){
                arr_wid_check[k]++;
            }
            else{
                if(arr_wid_check[k]==0){
                    continue;
                }
                else{
                    k++;
                }
            }
        } 
        /*
        for (int j=0;j<arr_wid[i*6+0];j++){
            printf("%d ",arr_wid_check[j]);
        }
        for (int j=0;j<arr_wid[i*6+0];j++){
            printf("%d ",arr_wid[i*6+j+1]);
        }
        printf("\n");
         */
        int j;
        for (j=0;j<arr_wid[i*6+0];j++){
            if(arr_wid_check[j]!=arr_wid[i*6+j+1]){
                return 0;
            }
        } 
        if(arr_wid_check[j]!=0){
            
            return 0;
        }
    }

    //check column
    //printf("column\n");
    for(int i=0;i<wid;i++){
        int arr_len_check[5]={0};
        for (int j=0;j<arr_len[i*6+0];j++){
            arr_len_check[j]=0;
        }
        int k=0;
        for (int j=0;j<len;j++){
            if(board[j*5+i]>0){
                arr_len_check[k]+=1;
            }
            else{
                if(arr_len_check[k]==0){
                    continue;
                }
                else{
                    k++;
                }
            }
        }
        /*
        for (int j=0;j<arr_len[i*6+0];j++){
            printf("%d ",arr_len_check[j]);
        }
        for (int j=0;j<arr_len[i*6+0];j++){
            printf("%d ",arr_len[i*6+j+1]);
        }
        printf("\n");
        */
       int j;
        for (j=0;j<arr_len[i*6+0];j++){
            if(arr_len_check[j]!=arr_len[i*6+j+1]){
                return 0;
            }
        }
        if(arr_len_check[j]!=0){
            
            return 0;
        }
    }


    return 1;
}



bool solve(int* board,int wid,int* arr_wid,int len,int* arr_len,int w,int l){
    if(boardSolved(board,wid,len)){
        if(boardIsValid(board,wid,arr_wid,len,arr_len)){
            printBoard(board,wid,len);
            return 1;
        }
        else{
            //printf("bad\n");
            //printBoard(board,wid,len);
            return 0;
        }
    }
    else{
        board[l*5+w]=1;
        int ww=w;
        int ll=l;
        if(ww!=wid-1){
            ww++;
        }
        else{
            ww=0;
            ll++;
        }
        bool succeed=solve(board,wid,arr_wid,len,arr_len,ww,ll);
        if(succeed){
            return 1;
        }
        board[l*5+w]=-1;
        succeed=solve(board,wid,arr_wid,len,arr_len,ww,ll);
        if(succeed){
            return 1;
        }
        board[l*5+w]=0;
        return 0;
    }
}

int main(){
    //input
    int width,length;
    scanf("%d %d", &length,&width);
    int arr_len[30];
    int arr_wid[30];
    int l;
    
    for(int i=0;i<length;i++){
        scanf("%d", &l);
        arr_wid[i*6+0]=l;
        for (int j=1;j<arr_wid[i*6+0]+1;j++){
            scanf("%d", &arr_wid[i*6+j]);
        }
    }
    for(int i=0;i<width;i++){
        scanf("%d", &l);
        arr_len[i*6+0]=l;
        for (int j=1;j<arr_len[i*6+0]+1;j++){
            scanf("%d", &arr_len[i*6+j]);
        }
    }
    
    
    
    //create board
    int board[5][5];
    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            board[i][j]=0;
        }
    }

    //solve
    solve(&board[0][0],width,arr_wid,length,arr_len,0,0);


    return 0;
}