#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct Tnode *Tnode;
typedef struct Stack *Stack;

int stackEmpty(Stack S);
int stackFull(Stack S);
void PUSH(Stack S, long int k);
void POP(Stack S);
Tnode createNode(int val);
void printPreorder(Tnode root);
void getStr(char str[], char newStr[]);
int getEnd(char str[], int start, int end);
Tnode buildTree(char newStr[], int start, int end);

struct Tnode
{
    int data;
    Tnode left;
    Tnode right;
};

struct Stack
{
    long int A[10000];
    int top;
    int size;
};

int stackEmpty(Stack S)
{
    if (S->top == -1)
        return -1;
    else
        return 1;
}

int stackFull(Stack S)
{
    if (S->top == S->size - 1)
        return 1;
    else
        return 0;
}

void PUSH(Stack S, long int k)
{
    if (stackFull(S) == 1)
        return;
    else
    {
        // printf("%d\n",S->top);
        S->top = S->top + 1;
        // printf("%d\n",S->top);
        S->A[S->top] = k;
    }
}

void POP(Stack S)
{
    if (stackEmpty(S) == -1)
        // printf("-1\n");
        return;
    else
    {
        // printf("%d\n",S->top);
        // printf("%ld\n",S->A[S->top]);
        S->top = S->top - 1;
        // printf("%d\n",S->top);
    }
}

Tnode createNode(int val)
{
    Tnode root = (Tnode)malloc(sizeof(Tnode));
    root->left = NULL;
    root->right = NULL;
    root->data = val;
    return root;
}

void printPreorder(Tnode root)
{

    if (root != NULL)
    {

        printf("%d ", root->data);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void getStr(char str[], char newStr[])
{
    int i;
    int j = 0;
    for (i = 1; i < strlen(str) - 1; i++)
    {
        if (str[i] != ' ')
        {
            if (str[i] == '(' && str[i + 1] == ' ' && str[i + 2] == ')')

            {
                newStr[j] = str[i];
                newStr[j + 1] = 'X';
                newStr[j + 2] = str[i + 2];
                i = i + 2;
                j = j + 3;
            }
            else
            {
                newStr[j] = str[i];
                j++;
            }
        }
    }
    printf("%s\n", newStr);
}

int getEnd(char str[], int start, int end)
{
    Stack S;
    int i;
    S = (Stack)malloc(sizeof(struct Stack));
    S->size = 10000;
    S->top = -1;
    if (start > end)
        return -1;
    for (i = start; i <= end; i++)
    {
        if (str[i] == '(')
            PUSH(S, str[i]);
        else if (str[i] == ')')
            if (S->A[S->top] = '(')
            {
                POP(S);
                if (stackEmpty(S) == -1)
                    return i;
            }
    }
    return -1;
}

Tnode buildTree(char newStr[], int start, int end)
{

    if (start > end)
        return NULL;

    Tnode root;
    int num = 0;
    int negative = 0;

    int k;
    if (newStr[start] == '-')
    {
        negative = 1;
        start++;
        // printf("in negative\n");
    }
    while (newStr[start] >= '0' && newStr[start] <= '9')
    {
        num *= 10;
        num = num + (newStr[start] - '0');
        start++;
    }
    start--;

    if (negative == 1)
        num = num * -1;
    // printf("%d ",num);

    if (newStr[start + 1] == 'X')
        root = NULL;
    else
        root = createNode(num);

    int i = -1;

    if (start + 1 <= end && newStr[start + 1] == '(')
        i = getEnd(newStr, start + 1, end);
    if (i != -1)
    {
        root->left = buildTree(newStr, start + 2, i - 1);
        root->right = buildTree(newStr, i + 2, end - 1);
    }
    return root;
}

Tnode getLCA(Tnode root, int nodeData1, int nodeData2)
{
    if (root == NULL || root->data == nodeData1 || root->data == nodeData2)
        return root;

    Tnode left = getLCA(root->left, nodeData1, nodeData2);
    Tnode right = getLCA(root->right, nodeData1, nodeData2);

    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;
    else
        return root;
}

int main()
{
    char op;
    long int k;
    char str[10000];
    char newStr[10000];
    scanf("%[^\n]", str);

    Tnode root = NULL;

    getStr(str, newStr);

    root = buildTree(newStr, 0, strlen(str) - 1);

    // printPreorder(root);
    // printf("\n");

    int node1, node2;
    scanf("%d", &node1);
    scanf("%d", &node2);

    Tnode nodeLCA = getLCA(root, node1, node2);

    printf("%d", nodeLCA->data);
}