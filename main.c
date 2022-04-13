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



Node *add(Node *root, int key) {
    Node *root2 = root, *root3 = NULL;
    Node *tmp = malloc(sizeof(Node));
    tmp->value = key;
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2->value)
            root2 = root2->less;
        else
            root2 = root2->more;
    }
    //Присваивание указателю на родителя значения указателя root3
    tmp->parent = root3;
    //Присваивание указателю на левое и правое поддерево значения NULL
    tmp->less = NULL;
    tmp->more = NULL;
    //Вставляем узел в дерево 
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


// Минимальный элемент поддерева
Node *TreeMin(Node *root, int *depth) {
    Node *LessNode = root;
    while (LessNode -> less != NULL){
        *depth = *depth + 1;
        LessNode = LessNode -> less;
    }
    return LessNode;
}

// Максимальный элемент поддерева
Node *TreeMax(Node *root, int *depth) {
    Node *MoreNode = root;
    while (MoreNode -> more != NULL){
        *depth = *depth + 1;
        MoreNode = MoreNode -> more;
    }
    return MoreNode;
}


Node *succ(Node *root)
{
    int MinMoreDepth = 0, MaxLessDepth = 0;
    Node *MinMoreNode = NULL , *MaxLessNode = NULL;
//Ищем Минимального среди ветки больших, записываем его глубину
    MinMoreNode = TreeMin(root->more, &MinMoreDepth);
//Ищем Максимальное среди ветки меньших, записываем его глубину
    MaxLessNode = TreeMax(root->less, &MaxLessDepth);
//Для наибольшей эффективности в качестве искомго узла указываем узел с наибольшей глубиной
    printf(" %d to left max\n %d to right min\n", MaxLessDepth, MinMoreDepth);
    if (MinMoreDepth >= MaxLessDepth)
        return MinMoreNode;
    else
        return MaxLessNode;
}



Node *delete(Node *desired) {
// Поиск удаляемого узла по ключу
    Node *TargetNode = desired, *tmp = NULL;
//узел без дочерних элементов
    if ((TargetNode -> less == NULL) && (TargetNode -> more == NULL))
    {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more) tmp -> less = NULL;
        else tmp -> less = NULL;
        free(TargetNode);
    }
//поддерево справа
    if ((TargetNode -> less == NULL) && (TargetNode -> more != NULL)) {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more) tmp -> more = TargetNode -> more;
        else tmp -> less = TargetNode -> more;
        free(TargetNode);
    }
//поддерево слева
    if ((TargetNode -> less != NULL) && (TargetNode -> more == NULL)) {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more) tmp -> more = TargetNode -> less;
        else tmp -> less = TargetNode -> more;
        free(TargetNode);
    }
//2 поддерева
    if ((TargetNode -> less != NULL) && (TargetNode -> more != NULL)) {
        tmp = succ(TargetNode); //При одиновковой глубине указывает на большее 'о'


    //Если перемещаем из большего поддерева
        if (tmp -> less == NULL){
            if (tmp -> parent -> less == tmp)
                tmp -> parent -> less = NULL;
            else
                tmp -> parent -> more = NULL;
        }
            
    //Eсли перемещаем ищ меньшего поддерева
        else if (tmp -> more == NULL){
            if (tmp -> parent-> more == tmp)
                tmp -> parent -> more = NULL;
            else
                tmp -> parent -> less = NULL;
        }

        tmp -> more = TargetNode -> more;
        tmp -> less = TargetNode -> less;

        
        if (TargetNode -> parent -> more == TargetNode)
            TargetNode -> parent -> more = tmp;
        else if (TargetNode -> parent -> less == TargetNode)
            TargetNode -> parent -> less = tmp;
        free(TargetNode);
        
    /*
        tmp -> less = TargetNode -> less;
        tmp -> parent = TargetNode -> parent;
        TargetNode -> parent -> more = tmp;


        TargetNode -> value = tmp -> value;
        if (tmp -> more == NULL)
            tmp -> parent -> less = NULL;
        else tmp -> parent -> less = tmp -> more;

        free(tmp);
    */
    }
    return desired;
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
    int arr[] = {10, 5, 2, 1, 3, 4, 7, 6, 8, 9, 15, 12, 11, 13, 14, 17, 16, 18, 19};
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
                printf("%d deleting\n", desired -> value);
                delete(desired);
                printf("Deleted.\n");
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