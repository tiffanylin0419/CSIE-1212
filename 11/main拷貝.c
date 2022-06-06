#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

struct node{
	int l,r;
	ll mx,se,cnt,sum;
	ll lazy;
}a[maxn*4];

void update(int x)
{
	int l = 2*x,r = 2*x+1;
	a[x].sum = a[l].sum + a[r].sum;
	if( a[l].mx == a[r].mx )
	{
		a[x].mx = a[l].mx;a[x].cnt = a[l].cnt+a[r].cnt;
		a[x].se = max(a[l].se,a[r].se);
	}else
	{
		if( a[l].mx < a[r].mx ) swap(l,r);
		a[x].mx = a[l].mx;a[x].cnt = a[l].cnt;
		a[x].se = max(a[r].mx,a[l].se);
	}
}
void change(int x,ll v)   //这里v已经保证小于a[x]的最大值,大于a[x]的最小值了,只更新,不下传 
{
	a[x].sum -= (a[x].mx-v)*a[x].cnt;
	a[x].mx = v;
	a[x].lazy = v;
}
void pushdown(int x)
{
	ll t = a[x].lazy;
	if( a[2*x].mx > t ) change(2*x,t);
	if( a[2*x+1].mx > t ) change(2*x+1,t);
	a[x].lazy = -1;
}
void modify(int x,int l,int r,ll v)  //将区间[l,r]的值对v取min
{
	if( a[x].mx <= v ) return;      //最大值都小于v,那什么都不用做 
	if( a[x].lazy >= 0 ) pushdown(x);  //懒标记下传 
	int m = (a[x].l+a[x].r)>>1;
	if( a[x].l == l && a[x].r == r )   //找到区间了 
	{
		if( v > a[x].se ) change(x,v);  //v值大于次大值,直接更新 
		else       //否则递归更新,每次递归至少会减少一种元素种类(最大值和次大值都取min变为同一个值了),总的复杂度为nlogn 
		{
			modify(2*x,l,m,v);
			modify(2*x+1,m+1,r,v);
			update(x); 
		}
		return;
	}
	if( r <= m ) modify(2*x,l,r,v);
	else if( l > m ) modify(2*x+1,l,r,v);
	else modify(2*x,l,m,v),modify(2*x+1,m+1,r,v);
	update(x);
} 



long long command[100000][5]={0};
int main() {
    // input
    scanf("%d %d",&N,&Q);
    for(int i=0;i<N;i++){
        scanf("%lld",&arr[i]);
    }
    Treap* root=build(arr,N);
    for(int i=0;i<Q;i++){
        scanf("%lld",&command[i][0]);
        if(command[i][0]==1){
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }else if(command[i][0]==2){
            scanf("%lld",&command[i][1]);
        }else if(command[i][0]==3){
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }else if(command[i][0]==4){
            scanf("%lld %lld %lld %lld",&command[i][1],&command[i][2],&command[i][3],&command[i][4]);
        }else if(command[i][0]==5){
            scanf("%lld %lld %lld",&command[i][1],&command[i][2],&command[i][3]);
        }else{
            scanf("%lld %lld",&command[i][1],&command[i][2]);
        }
    }

    //command
    for(int i=0;i<Q;i++){
        //INORDER_TRAVERSAL(root);
        if(command[i][0]==1){
            insert(&root,command[i][1],command[i][2]);
        }else if(command[i][0]==2){
            delete(&root,command[i][1]);
        }else if(command[i][0]==3){
            long long l=command[i][1],r=command[i][2];
            reverse(&root,l,r);
        }else if(command[i][0]==4){
            long long l,r,x,y;
            if(command[i][1]<command[i][3]){
                l=command[i][1];
                r=command[i][2];
                x=command[i][3];
                y=command[i][4];
            }else{
                l=command[i][3];
                r=command[i][4];
                x=command[i][1];
                y=command[i][2];
            }
            shift(&root,l,r,x,y);
        }else if(command[i][0]==5){
            long long l=command[i][1],r=command[i][2], key=command[i][3];
            updates(&root,l,r,key);
        }else if(command[i][0]==6){
            printf("%lld\n",sums(root,command[i][1],command[i][2]));
            //INORDER_TRAVERSAL(root);
        }
    }
}