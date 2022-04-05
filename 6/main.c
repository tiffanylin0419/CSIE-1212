#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node* next;
}NODE;

// Create node
NODE* createNode(int data) {
  NODE* newNode = malloc(sizeof(NODE));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

typedef struct Graph {
  int group;
  NODE** connectLists;
}GRAPH;

// Create a graph
GRAPH* createGraph(int num) {
  GRAPH* graph = malloc(sizeof(GRAPH));
  graph->group = num;
  graph->connectLists = malloc((num)* sizeof(NODE*));
  for (int i = 0; i < num; i++)
    graph->connectLists[i] = NULL;
  return graph;
}

// Add edge
void addConnect(GRAPH* graph, int a, int b) {
  // a to b 
  NODE* newNode = createNode(a);
  if(graph->connectLists[b-1]){
    newNode->next = graph->connectLists[b-1];
  }
  graph->connectLists[b-1] = newNode;

  // b to a
  newNode = createNode(b);
  if(graph->connectLists[a-1]){
    newNode->next = graph->connectLists[a-1];
  }
  graph->connectLists[a-1] = newNode;
}

// Print graph
void printGraph(GRAPH* graph) {
  for (int v = 0; v < graph->group; v++) {
    NODE* temp = graph->connectLists[v];
    printf("%d: ", v);
    while (temp) {
      printf("%d, ", temp->data);
      temp = temp->next;
    }
    printf("\n");
  }
}

typedef struct leaf {
  int up;
}LEAF;

// Create a tree
LEAF** createTree(int num) {
  LEAF **tree= (LEAF **)malloc(sizeof(LEAF *)*num);
  for (int i = 0; i < num; i++){
    tree[i]= (LEAF*)malloc(sizeof(LEAF));
    tree[i]->up=-1;
  }  
  return tree;
}

typedef struct Queue {
  int head;
  int tail;
  int* connectLists;
}QUEUE;

// Create a graph
QUEUE* createQueue(int num) {
  QUEUE* queue = malloc(sizeof(QUEUE));
  queue->head=0;
  queue->tail=0;
  queue->connectLists = malloc(num*sizeof(int));
  for (int i = 0; i < num; i++)
    queue->connectLists[i] = 0;
  return queue;
}

void enqueue(QUEUE* queue,int data){
  queue->connectLists[queue->tail]=data;
  queue->tail++;
}

int dequeue(QUEUE* queue){
  int data=queue->connectLists[queue->head];
  queue->head++;
  return data;
}

//save tree in array
void saveTree(GRAPH* graph, LEAF* tree[], int data, int up) {//initial up=0
  QUEUE* queue= createQueue(1000000);//?
  enqueue(queue,data);
  tree[data-1]->up=up;
  while(queue->head!=queue->tail){
    data=dequeue(queue);
    NODE* temp = graph->connectLists[data-1];
    //printf("%d, ",data);
    while (temp) {
      //printf("hi%d ",temp->data);
      if(tree[temp->data-1]->up==-1){
        tree[temp->data-1]->up=data;
        enqueue(queue,temp->data);
      }
      temp = temp->next;
    }
  }
  return;
}

//find answer
int findAns(LEAF* tree1[], LEAF* tree2[], LEAF* tree_ans[], int num) {
  if(tree_ans[num-1]->up!=-1){
    return tree_ans[num-1]->up;
  }
  if(tree1[num-1]->up!=tree2[num-1]->up){
    tree_ans[num-1]->up=num;
    return num;
  }
  else if(tree1[num-1]->up==0){
    tree_ans[num-1]->up=num;
    return num;
  }
  else{
    int temp_num=findAns(tree1,tree2,tree_ans,tree1[num-1]->up);
    tree_ans[num-1]->up=temp_num;
    return temp_num;
  }
  return 0;
}

void Bear(){
    int N,Q,S,R;//number of cities, number of queries, capital city, resort city
    //O(N+Q)
    scanf("%d %d %d %d",&N,&Q,&S,&R);
    GRAPH* graph = createGraph(N);
    int a,b;
    for(int i=0;i<N-1;i++){
      scanf("%d %d",&a,&b);
      addConnect(graph, a,b);
    }
    //printGraph(graph);
    //O(N)
    LEAF **tree_capital= createTree(N);
    LEAF **tree_resort= createTree(N);
    
    saveTree(graph,tree_capital, S, 0);
    /*
    for(int i=0;i<N;i++){
      printf("%d\n",tree_capital[i]->up);
    }
    printf("\n");
    */
    saveTree(graph,tree_resort, R, 0) ;
    /*
    for(int i=0;i<N;i++){
      printf("%d\n",tree_resort[i]->up);
    }
    printf("\n");
    */
    
    //O(N)
    LEAF **tree_answer= createTree(N);
    
    for(int i=0;i<N;i++){
      findAns(tree_capital,tree_resort,tree_answer,i+1);
    }
    
   
    //for(int i=0;i<N;i++){
    //  printf("%d, ",tree_answer[i]->up);
    //}
    
    
    int n=0;
    for(int i=0;i<Q;i++){
      scanf("%d",&n);
      printf("%d\n",tree_answer[n-1]->up);
    }
    
    return; 
}


int main(){
    Bear();
    return 0;
}
