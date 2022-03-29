#include <stdio.h>
#include <stdlib.h>

typedef struct node *node;
typedef struct treeAVL *treeAVL;
int maxAB(int a, int b);
int getHeight(node N);
node newnode(int data);
node RIGHTROTATE(node y);
node LEFTROTATE(node x);
int GETBALANCE(node N);
node insert(node node, int data);
void preOrder(node root);

struct node
{
    int data;
    node left;
    node right;
    int height;
};

struct treeAVL
{
    node root;
};

int getHeight(node N)
{
    if (N == NULL)
        return 0;
    return 1 + maxAB(getHeight(N->left), getHeight(N->right));
}

int maxAB(int a, int b)
{
    return (a > b) ? a : b;
}

node newnode(int data)
{
    node node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return (node);
}

node RIGHTROTATE(node y)
{
    node x = y->left;
    node T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = getHeight(y);
    x->height = getHeight(x);

    return x;
}

node LEFTROTATE(node x)
{
    node y = x->right;
    node T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = getHeight(x);
    y->height = getHeight(y);

    return y;
}

int GETBALANCE(node N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

node insert(node node, int data)
{
    if (node == NULL)
        return (newnode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = getHeight(node);

    int balance = GETBALANCE(node);

    if (balance > 1 && data < node->left->data)
        return RIGHTROTATE(node);

    if (balance < -1 && data > node->right->data)
        return LEFTROTATE(node);

    if (balance > 1 && data > node->left->data)
    {
        node->left = LEFTROTATE(node->left);
        return RIGHTROTATE(node);
    }

    if (balance < -1 && data < node->right->data)
    {
        node->right = RIGHTROTATE(node->right);
        return LEFTROTATE(node);
    }

    return node;
}

node minValueNode(node root)
{
    node current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node deleteNode(node root, int data)
{

    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);

    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    else
    {
        printf("%d\n", data);
        if ((root->left == NULL) || (root->right == NULL))
        {
            node temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            node temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + maxAB(getHeight(root->left),
                             getHeight(root->right));

    int balance = GETBALANCE(root);

    if (balance > 1 && GETBALANCE(root->left) >= 0)
        return RIGHTROTATE(root);

    if (balance > 1 && GETBALANCE(root->left) < 0)
    {
        root->left = LEFTROTATE(root->left);
        return RIGHTROTATE(root);
    }

    if (balance < -1 && GETBALANCE(root->right) <= 0)
        return LEFTROTATE(root);

    if (balance < -1 && GETBALANCE(root->right) > 0)
    {
        root->right = RIGHTROTATE(root->right);
        return LEFTROTATE(root);
    }
    return root;
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
        printf("%d ", node->data);
    }
    PRINTTREE(node->left);
    PRINTTREE(node->right);
    printf(") ");
}

int main()
{
    treeAVL T = (struct treeAVL *)malloc(sizeof(treeAVL));
    T->root = NULL;
    node node;
    char choice = 'x';
    int data;
    while (choice != 'e')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            T->root = insert(T->root, data);
            break;
        case 'd':
            scanf("%d", &data);
            T->root = deleteNode(T->root, data);
            break;
        case 's':
            scanf("%d", &data);
            node = SEARCH(T->root, data);
            if (node != NULL)
                printf("TRUE\n");
            else
                printf("FALSE\n");
            break;
        case 'b':
            scanf("%d", &data);
            node = SEARCH(T->root, data);
            if (node != NULL)
            {
                int balance = GETBALANCE(node);
                printf("%d\n", balance);
            }
            else
            {
                printf("FALSE\n");
            }
            break;
        case 'p':
            PRINTTREE(T->root);
            printf("\n");
            break;
        default:
            break;
        }
    }
    return 0;
}
