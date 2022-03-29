#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node *node;
node createNode(int item);
node insert(node node, int key);
node search(node root, int data);
int maxAB(int a, int b);
int getHeight(node root, node node);
int isAVL(node root);

struct node
{
    int key;
    node left;
    node right;
};

node createNode(int item)
{
    node temp = (node)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

node insert(node node, int key)
{
    if (node == NULL)
        return createNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

node search(node root, int data)
{
    if (root == NULL)
        return NULL;
    else if (root->key == data)
        return root;
    else if (data <= root->key)
        return search(root->left, data);
    else if (data > root->key)
        return search(root->right, data);
}

int maxAB(int a, int b)
{
    return (a >= b) ? a : b;
}

int getHeight(node root, node node)
{
    if (node == NULL)
        return 0;
    else
        return 1 + (maxAB(getHeight(root, node->left), getHeight(root, node->right)));
}

int isAVL(node root)
{
    if (root == NULL)
        return 1;
    int left = getHeight(root, root->left);
    int right = getHeight(root, root->right);
    if (abs(left - right) <= 1 && isAVL(root->left) && isAVL(root->right))
        return 1;
    return 0;
}

int main()
{
    node root = NULL;
    char choice = 'x';
    int data;
    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 'c':
            printf("%d\n", isAVL(root));
            break;
        default:
            break;
        }
    }
    return 0;
}
