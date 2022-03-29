#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node *node;
typedef struct treeRB *treeRB;
int maxAB(int a, int b);
int getHeight(node N);
node newnode(int data);
node RIGHTROTATE(node y);
node LEFTROTATE(node x);
int GETBALANCE(node N);
node insertBST(node root, node newNode);
void preOrder(node root);

struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
    char color;
};

struct treeRB
{
    struct node *root;
};

int maxAB(int a, int b)
{
    return (a > b) ? a : b;
}

char changeColor(node node)
{
    return (node->color == 'R') ? 'B' : 'R';
}

node newnode(int data)
{
    node node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = 'R';
    return (node);
}

void rightRotate(treeRB T, node x)
{
    struct node *left = x->left;
    x->left = left->right;

    if (x->left)
        x->left->parent = x;

    left->parent = x->parent;

    if (!x->parent)
        T->root = left;
    else if (x == x->parent->left)
        x->parent->left = left;
    else
        x->parent->right = left;

    left->right = x;
    x->parent = left;
}

void leftRotate(treeRB T, node x)
{
    struct node *right = x->right;
    x->right = right->left;

    if (x->right)
        x->right->parent = x;

    right->parent = x->parent;

    if (!x->parent)
        T->root = right;
    else if (x == x->parent->left)
        x->parent->left = right;
    else
        x->parent->right = right;

    right->left = x;
    x->parent = right;
}

node insertBST(node root, node newNode)
{
    if (root == NULL)
        return newNode;
    if (newNode->data < root->data)
    {
        root->left = insertBST(root->left, newNode);
        root->left->parent = root;
    }
    else if (newNode->data >= root->data)
    {
        root->right = insertBST(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void insertFix(treeRB T, node selNode)
{
    node parent = NULL;
    node grandparent = NULL;
    while ((selNode != T->root) && (selNode->color != 'B') && (selNode->parent->color == 'R'))
    {
        parent = selNode->parent;
        grandparent = selNode->parent->parent;

        if (parent == grandparent->left)
        {
            node uncle = grandparent->right;
            if (uncle != NULL && uncle->color == 'R')
            {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                selNode = grandparent;
            }
            else
            {
                if (selNode == parent->right)
                {
                    leftRotate(T, parent);
                    selNode = parent;
                    parent = selNode->parent;
                }
                rightRotate(T, grandparent);
                char t = parent->color;
                parent->color = grandparent->color;
                grandparent->color = t;
                selNode = parent;
            }
        }
        else
        {
            node uncle = grandparent->left;
            if ((uncle != NULL) && (uncle->color == 'R'))
            {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                selNode = grandparent;
            }
            else
            {
                if (selNode == parent->left)
                {
                    rightRotate(T, parent);
                    selNode = parent;
                    parent = selNode->parent;
                }
                leftRotate(T, grandparent);
                char t = parent->color;
                parent->color = grandparent->color;
                grandparent->color = t;
                selNode = parent;
            }
        }
    }
    T->root->color = 'B';
}

void preOrder(node root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

node SEARCH(node root, int data)
{
    if (root == NULL)
        return NULL;
    else if (root->data == data)
        return root;
    else if (root->data > data)
        SEARCH(root->left, data);
    else
        SEARCH(root->right, data);
}

void PRINTTREE(node node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }
    else
    {
        printf("( ");
        printf("%d %c ", node->data, node->color);
    }
    PRINTTREE(node->left);
    PRINTTREE(node->right);
    printf(") ");
}

void InsertRedBlack(treeRB T, int data)
{
    node node = newnode(data);
    if (T->root == NULL)
    {
        T->root = node;
        T->root->color = 'B';
    }
    else
    {
        T->root = insertBST(T->root, node);
        insertFix(T, node);
    }
    PRINTTREE(T->root);
    printf("\n");
}

int main()
{
    treeRB T = (struct treeRB *)malloc(sizeof(treeRB));
    T->root = NULL;
    node node;
    int data;
    char input[100];
    while (input[0] != 't')
    {
        scanf("%s", input);
        if (isdigit(input[0]))
        {
            data = atoi(input);
            InsertRedBlack(T, data);
        }
    }
    // PRINTTREE(T->root);
    return 0;
}
