#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc / free 
#include <memory.h> // memset
#include <ctype.h>//isdigit

typedef struct node{ 
    int top;
    long long int arr[1000000]; 
} stack;

void push(stack *S,long long int data){
    S->arr[S->top]=data;
    S->top+=1;
}

long long int peep(stack *S){
    return S->arr[S->top-1];
}

long long int pop(stack *S){
    S->top-=1;
    return S->arr[S->top];
}

stack *alloc(){
    stack *tmp = (stack *)malloc(sizeof(stack)); 
    tmp->top = 0;
    return tmp;
}

void destroy(stack *S){ 
    // clean sensitive data.
    memset(S, 0, sizeof(*S));
    free(S); 
    return;
}

stack *input(){
    char sa[1000000];
   
    scanf("%s", sa);
    
    stack *S=alloc();
    //put into stack
    for(int i=0;i<strlen(sa);i++){
        long long int num=0;
        
        if(sa[i]=='('){
            num=-1;
        }
        else if(sa[i]==')'){
            num=-2;
        }
        else if(sa[i]=='*'){
            num=-3;
        }
        else if(sa[i]=='/'){
            num=-4;
        }
        else if(sa[i]=='%'){
            num=-5;
        }
        else if(sa[i]=='+'){
            num=-6;
        }
        else if(sa[i]=='-'){
            num=-7;
        }
        
        else if(sa[i]=='='){
            num=-8;
        }
        
        else{
            while(isdigit(sa[i]) && i<strlen(sa)){
                num=10*num+sa[i]-48;
                i++;
            }
            i--;
        }
        push(S,num); 
    }
    return S;
}

stack *InToPost(stack *infix){
    stack *S=alloc();
    stack *notation=alloc();

    for (int i=0;i<infix->top;i++){
        if(infix->arr[i]>=0){
            push(S,infix->arr[i]); 
        }
        else{
            if(infix->arr[i]==-1){
                push(notation,infix->arr[i]); 
            }
            else if(infix->arr[i]==-8){
                while(notation->top!=0){
                    push(S,pop(notation));
                }
                push(S,infix->arr[i]);
            }
            else if(infix->arr[i]==-2){
                while(peep(notation)!=-1){
                    push(S,pop(notation)); 
                }
                pop(notation);//get rid of (
            }
            else if(-5<=infix->arr[i] && infix->arr[i]<=-3){
                while((notation->top!=0 && -5<=peep(notation)) && peep(notation)<=-3){
                    push(S,pop(notation)); 
                }
                push(notation,infix->arr[i]);
            }
            else{
                while(notation->top!=0 && -2>peep(notation)){
                    push(S,pop(notation));
                }
                push(notation,infix->arr[i]);
            }
        }
    }
    
    while(notation->top!=0 && -2>peep(notation)){
        push(S,pop(notation));
    }

    destroy(notation);
    return S;
}
long long int divide(long long int a,long long int b){
    int notation=1;
    if(a<0){
        notation=-notation;
        a=-a;
    }
    if(b<0){
        notation=-notation;
        b=-b;
    }
    long long int c=a/b;
    c=notation*c;
    if(notation<0){
        c-=1;
    }
    return c;
}

void CSIE(){
    long long int c=0;
    long long int a,b;
    stack *infix=input();
    stack *postfix=InToPost(infix);


    stack *ans=alloc();
    for (int i=0;i<postfix->top;i++){
        if(postfix->arr[i]>=0){
            push(ans,postfix->arr[i]);
        }
        else if(postfix->arr[i]==-8){
            printf("Print: %lld\n",peep(ans));
        }
        else{
            b=pop(ans);
            a=pop(ans);
            if(postfix->arr[i]==-3){
                push(ans,a*b);
            }
            else if(postfix->arr[i]==-4){
                push(ans,divide(a,b));
            }
            else if(postfix->arr[i]==-5){
                push(ans,a%b);
            }
            else if(postfix->arr[i]==-6){
                push(ans,a+b);
            }
            else if(postfix->arr[i]==-7){
                push(ans,a-b);
            }
        }
    }
    
    /*
    // print the nodes
    for (int i=0;i<infix->top;i++){
        printf("%d, ", infix->arr[i]); // print the data in the node 
    }
    printf("\n");
    
    // print the nodes
    for (int i=0;i<postfix->top;i++){
        printf("%d, ", postfix->arr[i]); // print the data in the node 
    }
    printf("\n");
    
    
    // print the nodes
    for (int i=0;i<ans->top;i++){
        printf("%d, ", ans->arr[i]); // print the data in the node 
    }
    printf("\n");
    */
    c=ans->arr[0];
    destroy(infix);
    destroy(postfix);
    destroy(ans);
    
    return; 
}


int main(){
    CSIE();
    return 0;
}