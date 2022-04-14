#include <stdio.h>
#include <stdlib.h>
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


//Добавление узла в дерево
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


//Поиск и возвращение узла в деерве
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

//Элемент наиболее пригодный для удаления
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


//Удаление узла
Node *delete(Node *desired) {
// Поиск удаляемого узла по ключу
    Node *TargetNode = desired, *tmp = NULL;
//узел без дочерних элементов
    if ((TargetNode -> less == NULL) && (TargetNode -> more == NULL))
    {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more) 
            tmp -> more = NULL;
        else 
            tmp -> less = NULL;
        free(TargetNode);
    }
//поддерево справа
    if ((TargetNode -> less == NULL) && (TargetNode -> more != NULL)) {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more) 
            tmp -> more = TargetNode -> more;
        else 
            tmp -> less = TargetNode -> more;
        free(TargetNode);
    }
//поддерево слева
    if ((TargetNode -> less != NULL) && (TargetNode -> more == NULL)) {
        tmp = TargetNode -> parent;
        if (TargetNode == tmp -> more)
            tmp -> more = TargetNode -> less;
        else 
            tmp -> less = TargetNode -> less;
        free(TargetNode);
    }
//2 поддерева
    if ((TargetNode -> less != NULL) && (TargetNode -> more != NULL)) {
        tmp = succ(TargetNode); //При одиновковой глубине указывает на большее
    //Если перемещается соседний элемент больший чем удаляемый узел
        if (tmp -> parent -> more == tmp)
            tmp -> less = TargetNode -> less;
    //Если перемещается соседний элемент меньший чем удаляемый узел
        else if (tmp -> parent -> less == tmp)
            tmp -> more = TargetNode -> more;

        else {
        //Если перемещаем элемент из большего поддерева
            if (tmp -> less == NULL) {
                if (tmp -> parent -> less == tmp)
                    tmp -> parent -> less = NULL;
                else
                    tmp -> parent -> more = NULL;
            }
        //Eсли перемещаем элемент из меньшего поддерева
            else if (tmp -> more == NULL) {
                if (tmp -> parent-> more == tmp)
                    tmp -> parent -> more = NULL;
                else
                    tmp -> parent -> less = NULL;
            }

            tmp -> more = TargetNode -> more;
            tmp -> less = TargetNode -> less;

        }

        if (TargetNode -> parent -> more == TargetNode)
            TargetNode -> parent -> more = tmp;
        else if (TargetNode -> parent -> less == TargetNode)
            TargetNode -> parent -> less = tmp;
        free(TargetNode);
        
    }
    return desired;
}


//Прямой обход
void preorder(Node *root)
{
    if (root == NULL)
        return;
    if (root != NULL)
        printf("%d ", root -> value);
    preorder(root -> less);
    preorder(root -> more);
}


//Обратный ход
void postorder(Node *root)
{
    if (root == NULL)
        return;
    postorder(root -> less);
    postorder(root -> more);
    if (root -> value)
        printf("%d ", root -> value);
}

//Освобождение памяти
void TreeFree(Node *root)
{
    if (root == NULL)
        return;
    TreeFree(root -> less);
    TreeFree(root -> more);
    if (root -> value)
        printf("free %d \n", root -> value);
    root -> less = NULL;
    root -> more = NULL;
    root -> parent = NULL;
    free(root);
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

//Перемещение из массива в бинарное дерево
void FromArray(int *arr, int size, Node *root) {
    int i = 0;
    root->value = arr[i];
    root->parent = NULL;
    root->less = root->more = NULL;
    i++;
    for (i; i < size; i++) {
        add(root, arr[i]);
    }
}


void Menu(){
    printf("/=====================/\n");
    printf("         Menu\n");
    printf("/=====================/\n");
    printf("1. Add\n");
    printf("2. Search\n");
    printf("3. Search and delete\n");
    printf("4. Forward order\n");
    printf("5. Backward order\n");
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
        system("cls");
        Menu();
        scanf("%d", &choise);
        switch (choise) {
        case 1:
            printf("element>>");
            scanf("%d", &value);
            add(root, value);
            break;
        
        case 2:
            printf("element>>");
            scanf("%d", &value);
            search(root, value);
            break;
        
        case 3:
            printf("element>>");
            scanf("%d", &value);
            Node *desired = search(root, value);
            if (desired){
                printf("%d Deleting\n", desired -> value);
                delete(desired);
                printf("Deleted.\n");
            }
            break;
        
        case 4:
            preorder(root);
            printf("\n");
            break;
        
        case 5:
            postorder(root);
            printf("\n");
            break;
        
        case 0:
            printf("Stop...\n");
            TreeFree(root);
            printf("Stopped.\n");
            break;
        
        default:
            printf("Invalid input\n");
            exit(0);
        }
        
    }
    return 0;
}