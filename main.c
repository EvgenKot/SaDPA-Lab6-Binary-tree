#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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



Node *create(Node *root, int data)
{
// Выделение памяти под корень дерева
    Node *tmp = malloc(sizeof(Node));
// Присваивание значения ключу
    tmp -> value = data;
// Присваивание указателю на родителя значения NULL
    tmp -> parent = NULL;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> less = tmp -> more = NULL;
    root = tmp;
    return root;
}


Node *add(Node *root, int key)
{
    Node *root2 = root, *root3 = NULL;
// Выделение памяти под узел дерева
    Node *tmp = malloc(sizeof(Node));
// Присваивание значения ключу
    tmp -> key = key;
/* Поиск нужной позиции для вставки (руководствуемся правилом 
вставки элементов, см. начало статьи, пункт 3) */
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2 -> key)
            root2 = root2 -> left;
        else
            root2 = root2 -> right;
    }
/* Присваивание указателю на родителя значения указателя root3 
(указатель root3 был найден выше) */
    tmp -> parent = root3;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> left = NULL;
    tmp -> right = NULL;
/* Вставляем узел в дерево (руководствуемся правилом
вставки элементов, см. начало статьи, пункт 3) */
    if (key < root3 -> key) root3 -> left = tmp;
    else root3 -> right = tmp;
    return root;
}



void PrintArray(int *arr, int n){
    for (int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}




void RandArr(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++){
        arr[i] = rand() %100;
    }
    
}





int main() {
    int n;
    int key;

    srand(time(NULL));

    printf("Len of arr: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    RandArr (arr, n);
    PrintArray (arr, n);

   
    free(arr);
    return 0;
}