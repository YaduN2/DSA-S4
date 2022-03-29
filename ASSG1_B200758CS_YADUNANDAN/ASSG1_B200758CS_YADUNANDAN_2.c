// Binary Search Tree with all operations

#include <stdio.h>
#include <stdlib.h>

typedef struct node *node;
typedef struct TREE *TREE;

struct node *CREATENODE(int item);
node INSERT(TREE T, node new_node);
node DELETE(TREE T, node del_node);
node SEARCH(TREE T, int data);
int LEVEL(node root, int data, int level);
node MINVALUE(node root);
node MAXVALUE(node root);
node PREDECESSOR(TREE T, node root);
node SUCCESSOR(TREE T, node root);
void INORDER(TREE T);
void PREORDER(TREE T);
void POSTORDER(TREE T);

node search_node(node root, int data);
void print_preorder(node node);
void print_inorder(node node);
void print_postorder(node node);

struct node
{
    int data;
    node left, right, p;
};

struct TREE
{
    node root;
};

struct node *CREATENODE(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    temp->p = NULL;
    return temp;
}

node search_node(node root, int data)
{
    if (root == NULL)
        return NULL;
    else if (root->data == data)
        return root;
    else if (data <= root->data)
        return search_node(root->left, data);
    else if (data > root->data)
        return search_node(root->right, data);
}

int level_node(node root, int data, int level)
{
    if (root == NULL)
        return 0;

    else if (root->data == data)
        return level;

    int getLevel = level_node(root->left, data, level + 1);
    if (getLevel != 0)
        return getLevel;

    getLevel = level_node(root->right, data, level + 1);
    return getLevel;
}

void print_preorder(node node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    print_preorder(node->left);
    print_preorder(node->right);
}

void print_inorder(node node)
{
    if (node == NULL)
        return;
    print_inorder(node->left);
    printf("%d ", node->data);
    print_inorder(node->right);
}

void print_postorder(node node)
{
    if (node == NULL)
        return;
    print_postorder(node->left);
    print_postorder(node->right);
    printf("%d ", node->data);
}

node INSERT(TREE T, node new_node)
{
    node current = T->root, parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if (new_node->data <= current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    new_node->p = parent;
    if (parent == NULL)
        T->root = new_node;
    else if (new_node->data <= parent->data)
        parent->left = new_node;
    else
        parent->right = new_node;
    return T->root;
}

node SEARCH(TREE T, int data)
{
    return search_node(T->root, data);
}

void INORDER(TREE T)
{
    print_inorder(T->root);
    printf("\n");
}

void POSTORDER(TREE T)
{
    print_postorder(T->root);
    printf("\n");
}

void PREORDER(TREE T)
{
    print_preorder(T->root);
    printf("\n");
}

node FindMIN(node root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

node FindMAX(node root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

node SUCCESSOR(TREE T, node root)
{
    if (root->right != NULL)
        return FindMIN(root->right);
    node parent = root->p;
    while (parent != NULL && root == parent->right)
    {
        root = parent;
        parent = parent->p;
    }
    return parent;
}

node PREDECESSOR(TREE T, node root)
{

    if (root->left != NULL)
        return FindMAX(root->left);

    printf("TEST");
    node parent = root->p;
    while (parent != NULL && root == parent->left)
    {
        root = parent;
        parent = parent->p;
    }
    return parent;
}

node DELETE(TREE T, node del_node)
{
    if (del_node == NULL)
    {
        printf("-1\n");
        return T->root;
    }

    int data = del_node->data;
    printf("%d\n", data);
    // case 1: leaf nodes
    if (del_node->left == NULL && del_node->right == NULL)
    {
        if (T->root == del_node)
        {
            T->root = NULL;
            free(del_node);
            return T->root;
        }
        if (del_node->p->left == del_node)
        {
            del_node->p->left = NULL;
        }
        else
        {
            del_node->p->right = NULL;
        }
        free(del_node);
        return T->root;
    }
    // case 2: one child nodes
    else if (del_node->left == NULL)
    {
        if (del_node->p->left == del_node)
            del_node->p->left = del_node->right;
        else
            del_node->p->right = del_node->right;

        del_node->right->p = del_node->p;
        free(del_node);
        return T->root;
    }
    else if (del_node->right == NULL)
    {
        if (del_node->p->right == del_node)
            del_node->p->right = del_node->left;
        else
            del_node->p->left = del_node->left;

        del_node->left->p = del_node->p;
        free(del_node);
        return T->root;
    }
    // case 3: two child nodes
    else
    {
        node min = FindMIN(del_node->right);
        del_node->data = min->data;

        if (min->p->left == min)
            min->p->left = NULL;
        else
            min->p->right = NULL;
        free(min);
        return T->root;
    }
}

int main()
{
    char choice = 'x';
    int data;
    node del_node, temp, search;
    TREE T;
    T = (TREE)malloc(sizeof(TREE));
    T->root = NULL;

    while (choice != 'e')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'a':
            scanf("%d", &data);
            T->root = INSERT(T, CREATENODE(data));
            break;

        case 'd':
            scanf("%d", &data);
            del_node = SEARCH(T, data);
            T->root = DELETE(T, del_node);
            break;

        case 's':
            scanf("%d", &data);
            if (SEARCH(T, data) == NULL)
                printf("-1\n");
            else
                printf("1\n");
            break;

        case 'l':
            scanf("%d", &data);
            int level = level_node(T->root, data, 1);
            if (level == 0)
                printf("-1\n");
            else
                printf("%d\n", level);
            break;

        case 'm':
            printf("%d\n", FindMIN(T->root)->data);
            break;

        case 'x':
            printf("%d\n", FindMAX(T->root)->data);
            break;

        case 'r':
            scanf("%d", &data);
            search = SEARCH(T, data);
            if (search == NULL)
            {
                printf("-1\n");
                break;
            }
            temp = PREDECESSOR(T, search);
            if (temp != NULL)
                printf("%d\n", temp->data);
            else
                printf("-1\n");
            break;

        case 'u':
            scanf("%d", &data);
            search = SEARCH(T, data);
            if (search == NULL)
            {
                printf("-1\n");
                break;
            }
            temp = SUCCESSOR(T, search);
            if (temp != NULL)
                printf("%d\n", temp->data);
            else
                printf("-1\n");
            break;

        case 'i':
            INORDER(T);
            break;

        case 't':
            POSTORDER(T);
            break;

        case 'p':
            PREORDER(T);
            break;

        default:
            break;
        }
    }
    return 0;
}