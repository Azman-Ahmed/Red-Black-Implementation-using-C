#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int value, color;
    struct Node *child[2];
};

struct Node *root = NULL;

struct Node *Create(int value)
{
    struct Node *newnode;
    newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->value = value;
    newnode->color = 2;
    newnode->child[0] = newnode->child[1] = NULL;
    return newnode;
}

void Insert(int value)
{
    struct Node *stack[98], *temp, *newnode, *x, *y;
    int arr[98], height = 0, index;
    temp = root;
    if (!root)
    {
        root = Create(value);
        return;
    }

    stack[height] = root;
    arr[height++] = 0;
    while (temp != NULL)
    {
        if(value>=temp->value) index = 1;
        else index = 0;
        stack[height] = temp;
        temp = temp->child[index];
        arr[height++] = index;
    }
    stack[height - 1]->child[index] = newnode = Create(value);
    while ((height >= 3) && (stack[height - 1]->color == 2))
    {
        if (arr[height - 2] == 0)
        {
            y = stack[height - 2]->child[1];
            if (y != NULL && y->color == 2)
            {
                stack[height - 2]->color = 2;
                stack[height - 1]->color = y->color = 1;
                height = height - 2;
            }
            else
            {
                if (arr[height - 1] == 0)
                {
                    y = stack[height - 1];
                }
                else
                {
                    x = stack[height - 1];
                    y = x->child[1];
                    x->child[1] = y->child[0];
                    y->child[0] = x;
                    stack[height - 2]->child[0] = y;
                }
                x = stack[height - 2];
                x->color = 2;
                y->color = 1;
                x->child[0] = y->child[1];
                y->child[1] = x;
                if (x == root)
                {
                    root = y;
                }
                else
                {
                    stack[height - 3]->child[arr[height - 3]] = y;
                }
                break;
            }
        }
        else
        {
            y = stack[height - 2]->child[0];
            if ((y != NULL) && (y->color == 2))
            {
                stack[height - 2]->color = 2;
                stack[height - 1]->color = y->color = 1;
                height = height - 2;
            }
            else
            {
                if (arr[height - 1] == 1)
                {
                    y = stack[height - 1];
                }
                else
                {
                    x = stack[height - 1];
                    y = x->child[0];
                    x->child[0] = y->child[1];
                    y->child[1] = x;
                    stack[height - 2]->child[1] = y;
                }
                x = stack[height - 2];
                y->color = 1;
                x->color = 2;
                x->child[1] = y->child[0];
                y->child[0] = x;
                if (x == root)
                {
                    root = y;
                }
                else
                {
                    stack[height - 3]->child[arr[height - 3]] = y;
                }
                break;
            }
        }
    }
    root->color = 1;
}


void Delete(int value)
{
    struct Node *stack[98], *temp, *x, *y;
    struct Node *ptemp, *qtemp, *right_temp;
    int arr[98], height = 0, diff, i;
    int color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    temp = root;
    while (temp != NULL)
    {
        if ((value - temp->value) == 0) break;
        if(value>temp->value) diff = diff = 1;
        else diff=0;
        stack[height] = temp;
        arr[height++] = diff;
        temp = temp->child[diff];
    }

    if (temp->child[1] == NULL)
    {
        if ((temp == root) && (temp->child[0] == NULL))
        {
            free(temp);
            root = NULL;
        }
        else if (temp == root)
        {
            root = temp->child[0];
            free(temp);
        }
        else
        {
            stack[height - 1]->child[arr[height - 1]] = temp->child[0];
        }
    }
    else
    {
        x = temp->child[1];
        if (x->child[0] == NULL)
        {
            x->child[0] = temp->child[0];
            color = x->color;
            x->color = temp->color;
            temp->color = color;

        if (temp == root)
        {
            root = x;
        }
        else
        {
            stack[height - 1]->child[arr[height - 1]] = x;
        }

        arr[height] = 1;
        stack[height++] = x;
        }
        else
        {
            i = height++;
            while (1)
            {
                arr[height] = 0;
                stack[height++] = x;
                y = x->child[0];
                if (!y->child[0]) break;
                x = y;
            }

            arr[i] = 1;
            stack[i] = y;
            if (i > 0) stack[i - 1]->child[arr[i - 1]] = y;

            y->child[0] = temp->child[0];

            x->child[0] = y->child[1];
            y->child[1] = temp->child[1];

            if (temp == root) root = y;

            color = y->color;
            y->color = temp->color;
            temp->color = color;
        }
    }

    if (height < 1) return;

    if (temp->color == 1)
    {
        while (1)
        {
            ptemp = stack[height - 1]->child[arr[height - 1]];
            if (ptemp && ptemp->color == 2)
            {
                ptemp->color = 1;
                break;
            }

            if (height < 2) break;

            if (arr[height - 2] == 0)
            {
                right_temp = stack[height - 1]->child[1];

                if (!right_temp) break;

                if (right_temp->color == 2)
                {
                    stack[height - 1]->color = 2;
                    right_temp->color = 1;
                    stack[height - 1]->child[1] = right_temp->child[0];
                    right_temp->child[0] = stack[height - 1];

                    if (stack[height - 1] == root)
                    {
                        root = right_temp;
                    }
                    else
                    {
                        stack[height - 2]->child[arr[height - 2]] = right_temp;
                    }
                    arr[height] = 0;
                    stack[height] = stack[height - 1];
                    stack[height - 1] = right_temp;
                    height++;

                    right_temp = stack[height - 1]->child[1];
                }

                if ((!right_temp->child[0] || right_temp->child[0]->color == 1) && (!right_temp->child[1] || right_temp->child[1]->color == 1))
                {
                    right_temp->color = 2;
                }
                else
                {
                    if (!right_temp->child[1] || right_temp->child[1]->color == 1)
                    {
                        qtemp = right_temp->child[0];
                        right_temp->color = 2;
                        qtemp->color = 1;
                        right_temp->child[0] = qtemp->child[1];
                        qtemp->child[1] = right_temp;
                        right_temp = stack[height - 1]->child[1] = qtemp;
                    }
                    right_temp->color = stack[height - 1]->color;
                    stack[height - 1]->color = 1;
                    right_temp->child[1]->color = 1;
                    stack[height - 1]->child[1] = right_temp->child[0];
                    right_temp->child[0] = stack[height - 1];
                    if (stack[height - 1] == root) root = right_temp;
                    else stack[height - 2]->child[arr[height - 2]] = right_temp;
                    break;
                }
            }
            else
            {
                right_temp = stack[height - 1]->child[0];
                if (!right_temp) break;

                if (right_temp->color == 2)
                {
                    stack[height - 1]->color = 2;
                    right_temp->color = 1;
                    stack[height - 1]->child[0] = right_temp->child[1];
                    right_temp->child[1] = stack[height - 1];

                    if (stack[height - 1] == root) root = right_temp;
                    else stack[height - 2]->child[arr[height - 2]] = right_temp;
                    arr[height] = 1;
                    stack[height] = stack[height - 1];
                    stack[height - 1] = right_temp;
                    height++;

                    right_temp = stack[height - 1]->child[0];
                }
                if ((!right_temp->child[0] || right_temp->child[0]->color == 1) && (!right_temp->child[1] || right_temp->child[1]->color == 1))
                {
                    right_temp->color = 2;
                }
                else
                {
                    if (!right_temp->child[0] || right_temp->child[0]->color == 1)
                    {
                        qtemp = right_temp->child[1];
                        right_temp->color = 2;
                        qtemp->color = 1;
                        right_temp->child[1] = qtemp->child[0];
                        qtemp->child[0] = right_temp;
                        right_temp = stack[height - 1]->child[0] = qtemp;
                    }
                    right_temp->color = stack[height - 1]->color;
                    stack[height - 1]->color = 1;
                    right_temp->child[0]->color = 1;
                    stack[height - 1]->child[0] = right_temp->child[1];
                    right_temp->child[1] = stack[height - 1];
                    if (stack[height - 1] == root) root = right_temp;
                    else
                    {
                        stack[height - 2]->child[arr[height - 2]] = right_temp;
                    }
                    break;
                }
            }
            height--;
        }
    }
}


void PreOrder(struct Node *root)
{
    if(root==NULL) return;
    printf("%d  ",root->value);
    PreOrder(root->child[0]);
    PreOrder(root->child[1]);
}

void InOrder(struct Node *root)
{
    if(root==NULL) return;
    InOrder(root->child[0]);
    printf("%d  ",root->value);
    InOrder(root->child[1]);
}

void PostOrder(struct Node *root)
{
    if(root==NULL) return;
    PostOrder(root->child[0]);
    PostOrder(root->child[1]);
    printf("%d  ",root->value);
}
struct Node* search(struct Node *root, int value)
{
        if(root==NULL) return NULL;
        if(value > root->value) return search(root->child[1],value);
        else if(value < root->value) return search(root->child[0],value);
        else return root;
}

void menu()
{
    printf("\n                Red Black Tree Menu");
    printf("\n 1.Insert");
    printf("\n 2.Delete");
    printf("\n 3.Print PreOrder");
    printf("\n 4.print InOrder");
    printf("\n 5.Print PostOrder");
    printf("\n 6.Search");
    printf("\n 7.Exit");
    printf("\n--------------------------------------\n");
}

// Driver code
int main()
{
    int choice, value;
    while (1)
    {
        menu();
        printf("\nEnter your choice:");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter the element to insert:");
                scanf("%d", &value);
                Insert(value);
                break;
            case 2:
                printf("Enter the element to delete:");
                scanf("%d", &value);
                Delete(value);
                break;
            case 3:
                PreOrder(root);
                printf("\n");
                break;
            case 4:
                InOrder(root);
                printf("\n");
                break;
            case 5:
                PostOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Input item:");
                scanf("%d",&value);
                struct Node *temp=search(root,value);
                if(temp==NULL) printf("Element not found\n");
                else
                {
                    printf("Element Found\n");
                    if(temp->color==1) printf("Color of the Element is Black");
                    else printf("Color of the Element is Red");
                }
                break;
            case 7:
                exit(0);
            default:
                printf("Try Again!\n");
                break;
        }
        printf("\n");
      }
      return 0;
}
