#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
Ращупкин Евгений КЭ-203
28 вариант
Lab6
Осуществить алгоритм упорядоченного дерева поиска.
Найти ключ поиска и удалить его из дерева.
*/

typedef struct Node {
    int value;
    struct Node *parent;
    struct Node *less;
    struct Node *more;
} Node;



// Минимальный элемент поддерева
Node *TreeMin(Node *root) {
    Node *l = root;
    while (l -> less != NULL)
        l = l -> less;
    return l;
}

// Максимальный элемент поддерева
Node *TreeMax(Node *root) {
    Node *r = root;
    while (r -> more != NULL)
        r = r -> more;
    return r;
}





Node *add(Node *root, int key) {
    Node *root2 = root, *root3 = NULL;
    Node *tmp = malloc(sizeof(Node));
    // Присваивание значения ключу
    tmp->value = key;
    /* Поиск нужной позиции для вставки (руководствуемся правилом
    вставки элементов, см. начало статьи, пункт 3) */
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2->value)
            root2 = root2->less;
        else
            root2 = root2->more;
    }
    /* Присваивание указателю на родителя значения указателя root3
    (указатель root3 был найден выше) */
    tmp->parent = root3;
    // Присваивание указателю на левое и правое поддерево значения NULL
    tmp->less = NULL;
    tmp->more = NULL;
    /* Вставляем узел в дерево (руководствуемся правилом
    вставки элементов, см. начало статьи, пункт 3) */
    if (key < root3->value)
        root3->less = tmp;
    else
        root3->more = tmp;
    printf("%d Added\n", key);
    return root;
}



Node *search(Node *root, int data) {   
    if (root == NULL) {
        printf("\n No element %d\n", data);
        return root;
    }

    printf("-> %d ", root->value);

    if (data < root->value)
        return search(root->less, data);
    else if (data > root->value)
        return search(root->more, data);

    else if (root->value == data) {
        printf("\n Catch!\n");
        return root;
    }
}



Node *succ(Node *root)
{
    Node *p = root, *l = NULL;
// Если есть правое поддерево, то ищем минимальный элемент в этом поддереве
    if (p -> more != NULL)
        //return min(p -> right);
/* Правое дерево пусто, идем по родителям до тех пор,
пока не найдем родителя, для которого наше поддерево левое */
    l = p -> parent;
    while ((l != NULL) && (p == l -> more))
    {
        p = l;
        l = l -> parent;
    }
    return l;
}



Node *delete(Node *root, Node *desired) {
// Поиск удаляемого узла по ключу
    Node *p = root, *l = desired, *m = NULL;
// 1 случай
    if ((l -> less == NULL) && (l -> more == NULL))
    {
        m = l -> parent;
        if (l == m -> more) m -> less = NULL;
        else m -> less = NULL;
        free(l);
    }
// 2 случай, 1 вариант - поддерево справа
    if ((l -> less == NULL) && (l -> more != NULL))
    {
        m = l -> parent;
        if (l == m -> more) m -> more = l -> more;
        else m -> less = l -> more;
        free(l);
    }
// 2 случай, 2 вариант - поддерево слева
    if ((l -> less != NULL) && (l -> more == NULL))
    {
        m = l -> parent;
        if (l == m -> more) m -> more = l -> less;
        else m -> less = l -> more;
        free(l);
    }
// 3 случай
    if ((l -> less != NULL) && (l -> more != NULL))
    {
        /*
        m = succ(l);
        l -> key = m -> key;
        if (m -> right == NULL)
            m -> parent -> left = NULL;
        else m -> parent -> left = m -> right;
        */
        free(m);
        
    }
    return root;
}






void PrintArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void RandArr(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}


void FromArray(int *arr, int size, Node *root) {
    root->value = arr[0];
    root->parent = NULL;
    root->less = root->more = NULL;
    for (int i = 1; i < size; i++) {
        add(root, arr[i]);
    }
    printf("\n");
}

void Menu(){
    printf("/=====================/\n");
    printf("        Menu\n");
    printf("/=====================/\n");
    printf("1. Add\n");
    printf("2. Search\n");
    printf("3. Search and delete\n");
    printf("0. Exit\n");
    printf(">>");
}

int main() {
    Node *root = malloc(sizeof(Node));
    int arr[9] = {8, 3, 10, 1, 6, 4, 7, 14, 13};
    int n = sizeof(arr)/sizeof(int);
    FromArray (arr, n, root);

    int value;
    int choise = 1;
    while (choise){
        getch();
        Menu();
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            printf(">>");
            scanf("%d", &value);
            add(root, value);
            break;
        
        case 2:
            printf(">>");
            scanf("%d", &value);
            search(root, value);
            break;
        
        case 3:
            printf(">>");
            scanf("%d", &value);
            Node *desired = search(root, value);
            if (desired){
                printf("%d deliting\n", desired -> value);
            }

            
            break;
        
        case 0:
            printf("Stopped.");
            break;
        
        default:
            printf("Invalid input\n");
            exit(0);
        }
        
    }

    return 0;
}