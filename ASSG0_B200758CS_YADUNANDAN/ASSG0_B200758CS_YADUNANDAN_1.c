#include <stdio.h>
#include <stdlib.h>

struct STACK
{
    int *A;
    int top;
    int size;
};

void PUSH(struct STACK *S, int value);
int POP(struct STACK *S);
int ISEMPTY(struct STACK S);
int ISFULL(struct STACK S);

int ISEMPTY(struct STACK S)
{
    if (S.top == -1)
        return 1;
    else
        return -1;
}

int ISFULL(struct STACK S)
{
    if (S.top == S.size - 1)
        return 1;
    else
        return -1;
}

void PUSH(struct STACK *S, int value)
{
    if (ISFULL(*S) == 1)
    {
        printf("1\n");

        int *B = (int *)malloc(sizeof(int) * S->size * 2);

        for (int i = 0; i <= S->top; i++)
        {
            B[i] = S->A[i];
        }

        free(S->A);
        S->A = B;
        S->size *= 2;
    }
    S->top++;
    S->A[S->top] = value;
}

int POP(struct STACK *S)
{
    if (ISEMPTY(*S) == 1)
    {
        return -1;
    }
    else
    {
        return S->A[S->top--];
    }
}

int main()
{
    struct STACK S;

    int size;
    scanf("%d", &size);
    S.A = (int *)malloc(sizeof(int) * size);
    S.top = -1;
    S.size = size;

    char choice = 'x';
    int data, deleted;

    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            PUSH(&S, data);
            break;

        case 'd':
            deleted = POP(&S);
            printf("%d\n", deleted);
            break;

        default:
            break;
        }
    }
    return 0;
}