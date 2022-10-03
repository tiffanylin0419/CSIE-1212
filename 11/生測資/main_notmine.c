#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
int gg=5;
// flag = 1 => upload judge
int flag = 0;
int N, Q;

typedef struct node
{
    int priority, size, val, rev, max, second, max_num;
    long long sum, lazy, lazy2;
    struct node *left, *right;
} node;

node *alloc(int val)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->priority = rand();
    tmp->left = tmp->right = NULL;
    tmp->sum = val;
    tmp->val = val;
    tmp->max = val;
    tmp->rev = 0;
    tmp->lazy = 0;
    tmp->lazy2 = -1;
    tmp->second = 0;
    tmp->max_num = 1;
    tmp->size = 1;
    return tmp;
}

int Get_Size(node *t)
{
    return t ? t->size : 0;
}

void Push(node *t)
{
    if (t == NULL || t->rev == 0)
        return;

    node *tmp = t->right;
    t->right = t->left;
    t->left = tmp;
    t->val += t->lazy;
    t->sum += t->lazy;
    t->max += t->lazy;
    if (t->left)
    {
        t->left->lazy += t->lazy;
        t->left->rev ^= 1;
    }
    if (t->right)
    {
        t->right->rev ^= 1;
        t->right->lazy += t->lazy;
    }

    t->lazy = 0;
    t->rev = 0;
}

void Change(node *t, int k)
{
    t->sum -= t->max_num * (t->max - k);
    t->val = t->val < k ? t->val : k;
    t->max = k;

    if (t->left)
    {
        if (t->left->lazy2 == -1)
            t->left->lazy2 = k;
        else
            t->left->lazy2 = t->left->lazy2 < k ? t->left->lazy2 : k;
    }
    if (t->right)
    {
        if (t->right->lazy2 == -1)
            t->right->lazy2 = k;
        else
            t->right->lazy2 = t->right->lazy2 < k ? t->right->lazy2 : k;
    }
    t->lazy2 = -1;
}

void Push2(node *t)
{
    if (!t || t->lazy2 == -1)
        return;

    if (t->max <= t->lazy2)
    {
        t->lazy2 = -1;
        return;
    }
    else
    {
        Change(t, t->lazy2);
        return;
    }
}

void Pull(node *t)
{
    if (!t)
        return;

    Push2(t);
    t->size = 1;
    t->sum = t->val;
    t->max = t->val;
    t->second = 0;
    t->max_num = 1;
    if (t->left != NULL)
    {
        Push2(t->left);
        t->size += t->left->size;
        t->sum += t->left->sum;
        if (t->left->max > t->max)
        {
            t->second = t->left->second > t->max ? t->left->second : t->max;
            t->max = t->left->max;
            t->max_num = t->left->max_num;
        }
        else if (t->left->max < t->max)
            t->second = t->left->max > t->second ? t->left->max : t->second;
        else
        {
            t->max_num += t->left->max_num;
            t->second = t->left->second > t->second ? t->left->second : t->second;
        }
    }

    if (t->right != NULL)
    {
        Push2(t->right);
        t->size += t->right->size;
        t->sum += t->right->sum;
        if (t->right->max > t->max)
        {
            t->second = t->right->second > t->max ? t->right->second : t->max;
            t->max = t->right->max;
            t->max_num = t->right->max_num;
        }
        else if (t->right->max < t->max)
            t->second = t->right->max > t->second ? t->right->max : t->second;
        else
        {
            t->max_num += t->right->max_num;
            t->second = t->right->second > t->second ? t->right->second : t->second;
        }
    }
}

node *Merge(node *a, node *b)
{
    // base case
    if (a == NULL || b == NULL)
        return a ? a : b;
    if (a->priority > b->priority)
    {
        Push(a);
        Push2(a);
        a->right = Merge(a->right, b);
        Pull(a);
        return a;
    }
    else
    {
        Push(b);
        Push2(b);
        b->left = Merge(a, b->left);
        Pull(b);
        return b;
    }
}

void Split(node *t, int location, node **a, node **b)
{
    if (t == NULL)
    {
        *a = *b = NULL;
        return;
    }
    Push(t);
    Push2(t);

    if (Get_Size(t->left) >= location)
    {
        *b = t;
        Push(*b);
        Push2(*b);
        Split(t->left, location, a, &((*b)->left));
        Pull(*b);
    }
    else
    {
        *a = t;
        Push(*a);
        Push2(*a);
        Split(t->right, location - Get_Size(t->left) - 1, &((*a)->right), b);
        Pull(*a);
    }
}

node *Insert(node *t, int location, int v)
{
    node *lt = NULL;
    node *rt = NULL;
    Split(t, location, &lt, &rt);
    t = Merge(Merge(lt, alloc(v)), rt);
    return t;
}

node *Delete(node *t, int location)
{
    node *lt = NULL;
    node *rt = NULL;
    Split(t, location - 1, &lt, &t);
    Split(t, 1, &t, &rt);
    t = Merge(lt, rt);
    return t;
}

node *Reverse(node *t, int l, int r)
{
    node *x, *y, *z;
    Split(t, l - 1, &x, &y);
    Split(y, r - l + 1, &y, &z);
    y->rev ^= 1;
    t = Merge(x, Merge(y, z));
    return t;
}

node *Swap(node *t, int l, int r, int x, int y)
{
    node *A, *B, *C, *D, *E;
    Split(t, l - 1, &A, &B);
    Split(B, r - l + 1, &B, &C);
    Split(C, x - r - 1, &C, &D);
    Split(D, y - x + 1, &D, &E);
    t = Merge(Merge(Merge(Merge(A, D), C), B), E);
    return t;
}

void Update(node *t, int k)
{
    if (!t)
        return;
    
    Push(t);
    Push2(t);
    if (t->max <= k)
        return;
    else if (t->second <= k)
        Change(t, k);
    else
    {
        t->val = t->val < k ? t->val : k;
        Update(t->left, k);
        Update(t->right, k);
        Pull(t);
    }
}

node *Query(node *t, int l, int r, long long* number)
{
    
    node *x, *y, *z;
    Split(t, l - 1, &x, &y);
    Split(y, r - l + 1, &y, &z);
    printf("%lld\n", y->sum);//?
    *number=y->sum;
    t = Merge(x, Merge(y, z));
    
    return t;
}

void Inorder(node *tmp)
{
    if (tmp != NULL)
    {
        Inorder(tmp->left);
        printf("%d(%lld,%d,%d,%d,%d) ", tmp->val, tmp->sum, tmp->size, tmp->max, tmp->second, tmp->max_num);
        printf("\n");
        Inorder(tmp->right);
    }
}

int main()
{
    FILE *fp;
    if (flag)
        scanf("%d %d", &N, &Q);
    else
    {
        
        char filename[20];
        sprintf(filename,"test%d.txt",gg);
        fp = fopen(filename, "r");
        fscanf(fp, "%d %d", &N, &Q);
    }

    srand(1);
    node *root = NULL;
    int time;
    for (int n = 0; n < N; n++)
    {
        if (flag)
            scanf("%d", &time);
        else
            fscanf(fp, "%d", &time);
        root = Merge(root, alloc(time));
    }
    char file[20];
    sprintf(file,"2out%d.txt",gg);
    remove(file);
    FILE *ff =fopen(file, "a"); 
    int op, a, b, c, d;
    for (int q = 1; q <= Q; q++)
    {
        if (flag)
            scanf("%d", &op);
        else
            fscanf(fp, "%d", &op);
        switch (op)
        {
        case 1:
            if (flag)
                scanf("%d %d", &a, &b);
            else
                fscanf(fp, "%d %d", &a, &b);
            root = Insert(root, a, b);
            break;
        case 2:
            if (flag)
                scanf("%d", &a);
            else
                fscanf(fp, "%d", &a);
            root = Delete(root, a);
            break;
        case 3:
            if (flag)
                scanf("%d %d", &a, &b);
            else
                fscanf(fp, "%d %d", &a, &b);
            root = Reverse(root, a, b);
            break;
        case 4:
            if (flag)
                scanf("%d %d %d %d", &a, &b, &c, &d);
            else
                fscanf(fp, "%d %d %d %d", &a, &b, &c, &d);
            if (a < c)
                root = Swap(root, a, b, c, d);
            else
                root = Swap(root, c, d, a, b);
            break;
        case 5:
            if (flag)
                scanf("%d %d %d", &a, &b, &c);
            else
                fscanf(fp, "%d %d %d", &a, &b, &c);
            node *x, *y, *z;
            Split(root, a - 1, &x, &y);
            Split(y, b - a + 1, &y, &z);
            Update(y, c);
            root = Merge(x, Merge(y, z));
            break;
        case 6:
            if (flag)
                scanf("%d %d", &a, &b);
            else
                fscanf(fp, "%d %d", &a, &b);
            long long number;
            root = Query(root, a, b,&number);
            
            
            fprintf(ff,"%lld\n", number);//?
            
            break;
        default:
            break;
        }
        
    }
    fclose(ff);//?
    if (!flag)
        Inorder(root);
    return 0;
}