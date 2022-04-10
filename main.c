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

/*

Node *create(Node *root, int key)
{
// Выделение памяти под корень дерева
    Node *tmp = malloc(sizeof(Node));
// Присваивание значения ключу
    tmp -> value = key;
// Присваивание указателю на родителя значения NULL
    tmp -> parent = NULL;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> less = tmp -> more = NULL;
    root = tmp;
    return root;
}
*/

Node *add(Node *root, int key) {
    Node *root2 = root, *root3 = NULL;
// Выделение памяти под узел дерева
    Node *tmp = malloc(sizeof(Node));
// Присваивание значения ключу
    tmp -> value = key;
/* Поиск нужной позиции для вставки (руководствуемся правилом 
вставки элементов, см. начало статьи, пункт 3) */
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2 -> value)
            root2 = root2 -> less;
        else
            root2 = root2 -> more;
    }
/* Присваивание указателю на родителя значения указателя root3 
(указатель root3 был найден выше) */
    tmp -> parent = root3;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> less = NULL;
    tmp -> more = NULL;
/* Вставляем узел в дерево (руководствуемся правилом
вставки элементов, см. начало статьи, пункт 3) */
    if (key < root3 -> value) root3 -> less = tmp; //Не работает
    else root3 -> more = tmp;
    printf("%d Added\n", root3 -> value);
    return root;
}




Node *search(Node * root, int data)
{
// Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
    printf("Searching\n");
    if ((root == NULL) || (root -> value == data))
        printf("No element\n");
        return root;
// Поиск нужного узла
    printf ("%d ->", root -> value);
    if (data < root -> value)
        return search(root -> less, data);
    else return search(root -> less, data);
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


void FromArray(int *arr, int n, Node *root) {

    //create(root, arr[0]);

    for (int i = 1; i<n; i++){

        add(root, arr[i]);
        puts("abobus");
        printf("%d added\n", arr[i]);
    }
    printf("\n");
}








int main() {
    int n;


/*
    srand(time(NULL));

    printf("Len of arr: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    RandArr (arr, n);
    PrintArray (arr, n);

    FromArray (arr, n, root);

   
    free(arr);
*/

 //   create(root, 8);


    Node* root = malloc(sizeof(Node));
    root -> value = 8;

    root -> parent = NULL;
    root -> less = root -> more = NULL;



    search(root, 8);
    puts ("asda");
    add(root, 3);
    add(root, 10);
    add(root, 1);
    add(root, 6);
    add(root, 4);
    add(root, 7);
    add(root, 14);
    add(root, 13);

    puts ("da");

    search(root, 13);
    search(root, 6);

    puts ("dass");

    return 0;
}