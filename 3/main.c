#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc / free 
#include <memory.h> // memset
#include <ctype.h>//isdigit

#define myMalloc(x)  (x *)malloc(sizeof(x)) // Macro definition


/*----------------- type defined ------------*/

typedef struct node{ 
    int data;
    int group;
    struct node *left, *right; 
} Node;

typedef struct stack{ 
    struct node *top; 
    bool open;
} Stack;



/*----------------  function prototype ------------*/
void cow();
Stack *alloc_stack();
Node *find(Stack *, int );
void push(Stack *,int ,int );
void pop(Stack *);
void go(Stack *);
void print(Stack *S);


/*------------- main() --------------*/

int main(){
    cow();
    return 0;
}

Stack *alloc_stack(){
    Stack *tmp = myMalloc(Stack); 
    tmp->top =NULL; 
    tmp->open=true;
    return tmp;
}

int peep(Stack *S){ // not define prototype yet
    return S->top->data;
}

Node *find(Stack *S, int group){
    Node *tmp=S->top;
    if (!tmp) { // to prevent shut down when access tmp->group
		printf("some memory error at S->top\n"); 
		exit(1);
	}
    do {
        if(tmp->group==group&&tmp->right->group!=group)
            return tmp;
        tmp=tmp->right;
    }while(tmp!=S->top);
    
    return tmp->left;
}

void push(Stack *S,int data,int group){
    Node *tmp= myMalloc(Node);
    tmp->data=data;
    tmp->group=group;
    if(S->top==NULL){ 
        tmp->left=tmp;
        tmp->right=tmp;
        S->top=tmp;
    }
    else{
        Node *position=find(S,group);
        tmp->left=position;
        tmp->right=position->right;
        position->right=tmp;
        tmp->right->left=tmp;
    }
}

void pop(Stack *S){
    Node*tmp=S->top;
    if(tmp && tmp==tmp->right) // only one node
	    S->top=NULL;
	else{
        tmp=tmp->left;
		tmp->left->right=tmp->right;
        tmp->right->left=tmp->left;
        tmp->left=tmp->right=NULL;
    }
 //   free(tmp);
    return;
}

void go(Stack *S){
   Node *tmp=S->top;
    if(tmp && tmp==tmp->right) // only one node
	    S->top=NULL;
    else{  	
        S->top= S->top->right;
        tmp->left->right=tmp->right;
        tmp->right->left=tmp->left;
        tmp->left= tmp->right=NULL;
    }
    free(tmp);
    return;    
}


void print(Stack *S){
    Node* tmp=S->top;
    
    if(tmp) {   // not empty
   		do {
    		printf("%d ",tmp->data);
            tmp=tmp->right;
		} while (tmp!=S->top);

	}
    printf("\n");
    return;
}


void cow(){
    int M=0,N=0,K=0, i;
 //   Stack *lineAry[1000000];  /*--------  TOO BIG to run -----------*/
     Stack *lineAry[10000]; 
    scanf("%d %d %d",&M,&N,&K);   
  //  printf("my test: %d %d %d",M,N,K);  //test
 
    for(i=0;i<M;i++){
        lineAry[i]=alloc_stack();
    }

    for(i=0;i<N;i++){  
        int group, id, line;
        char str[10];
        scanf("%s",str);     
     
// if else should change to be switch(str[0]) { case 'e': ¡K }
        if(str[0]=='e'){//enter
            scanf("%d %d %d",&group,&id,&line);   
            push(lineAry[line], id, group);
        }
        else if(str[0]=='l'){//leave
            scanf("%d",&group);  
            pop(lineAry[group]);
        }
        else if(str[0]=='g'){//go
            scanf("%d",&group);  
            go(lineAry[group]);
        }
        else if(str[0]=='c'){//close
            scanf("%d",&group);  
            //go(lineAry[group]);
        }

    }

    for( i=0;i<M;i++)  
	    print(lineAry[i]);
    
    /*
    for(int i=0;i<M;i++){
        destroy_stack(lineAry[i]);
    }
    *///
    
}



