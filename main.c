#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30
typedef struct treeNode
{
    int key;
    char tara[50];
    char capitala[50];
    char suprafata[50];
    int populatia;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;
treeNode *create_node(char *tara, char *capitala, char *suprafata, int populatia, int key)
{
    treeNode *root = malloc(sizeof(treeNode));
    if(root != NULL)
    {
        strcpy(root->tara, tara);
        strcpy(root->capitala, capitala);
        strcpy(root->suprafata, suprafata);
        root->populatia = populatia;
        root->key = key;
    }
    return root;
}
treeNode *insert_node(treeNode *root, int i)
{
    if(root)
    {
        int k;
        printf("Insert left?\n0 - no\n1 - yes\n");
        scanf("%d", &k);
        if(k == 1)
        {
            char tara[MAX];
            char cap[MAX];
            char sup[MAX];
            int pop;
            int key;
            printf("Elementul %d = \n", i);
            printf("Key: ");
            scanf("%d", &key);
            printf("Tara: ");
            scanf(" %s", &tara);
            printf("Capitala: ");
            scanf(" %s", &cap);
            printf("Suprafata: ");
            scanf(" %s", &sup);
            printf("Populatia: ");
            scanf("%d", &pop);
            root->left = create_node(tara, cap, sup, pop, key);
            insert_node(root->left, i++);
        }
        printf("Insert right?\n0 - no\n1 - yes\n");
        scanf("%d", &k);
        if(k == 1)
        {
            char tara[MAX];
            char cap[MAX];
            char sup[MAX];
            int pop;
            int key;
            printf("Elementul %d = \n", i);
            printf("Key: ");
            scanf("%d", &key);
            printf("Tara: ");
            scanf(" %s", tara);
            printf("Capitala: ");
            scanf(" %s", cap);
            printf("Suprafata: ");
            scanf(" %s", sup);
            printf("Populatia: ");
            scanf("%d", &pop);
            root->right = create_node(tara, cap, sup, pop, key);
            insert_node(root->right, i++);
        }
    }
}
void printtabs(int numtabs)
{
    for(int i=0; i<numtabs; i++)
    {
        printf("\t");
    }
}
void _print_tree(treeNode *root, int level)
{
    if(root == NULL)
    {
        printtabs(level);
        printf("----empty----\n");
        return;
    }
    printtabs(level);
    printf("|------------|\n");
    printtabs(level);
    printf("|%s\n", root->tara);
    printtabs(level);
    printf("|%s\n", root->capitala);
    printtabs(level);
    printf("|%.2f km2\n", root->suprafata);
    printtabs(level);
    printf("|%d loc\n", root->populatia);
    printtabs(level);
    printf("|------------|\n");
    printtabs(level);

    printf("left\n");
    _print_tree(root->left, level+1);
    printtabs(level);
    printf("right\n");
    _print_tree(root->right, level+1);
    printtabs(level);
    printf("done\n");
}
void print_tree(treeNode *root)
{
    _print_tree(root, 0);
}
void find_node(treeNode *root, int key)
{
    if(root == NULL)
        return;
    if(root->key == key)
    {
        printf("Nodul a fost gasit: \n");
        printf("|------------|\n");
        printf("|%s\n", root->tara);
        printf("|%s\n", root->capitala);
        printf("|%s km2\n", root->suprafata);
        printf("|%d loc\n", root->populatia);
        printf("|------------|\n");
        return;
    }
    else
    {
        find_node(root->left, key);
        find_node(root->right, key);
    }
}
void print_node(treeNode *root)
{
    printf("%d, ", root->key);
}
void parc_SVD(treeNode *current_node)
{
    if(current_node)
    {
        parc_SVD(current_node->left);
        print_node(current_node);
        parc_SVD(current_node->right);
    }
}
void parc_SDV(treeNode *current_node)
{
    if(current_node)
    {
        parc_SDV(current_node->left);
        parc_SDV(current_node->right);
        print_node(current_node);
    }
}
void parc_VSD(treeNode *current_node)
{
    if(current_node)
    {
        print_node(current_node);
        parc_VSD(current_node->left);
        parc_VSD(current_node->right);
    }
}
int adancime_DFS(treeNode *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int lDepth = adancime_DFS(root->left);
        int rDepth = adancime_DFS(root->right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}
int inaltime_BFS(treeNode *root)
{
    if(root ==NULL)
        return 0;
    else
    {
        int lHeight = inaltime_BFS(root->left);
        int rHeight = inaltime_BFS(root->right);
        if(lHeight >= rHeight)
            return lHeight+1;
        else return rHeight+1;
    }
}
void mirror_tree(struct treeNode* root)
{
    if (root == NULL) return;
    else
    {
        struct treeNode* temp;
        temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirror_tree(root->left);
        mirror_tree(root->right);
    }
}

void clear_tree(treeNode *root)
{
    if (root == NULL) return;
    clear_tree(root->left);
    clear_tree(root->right);
    root->key = 0;
    strcpy(root->tara, "NULL");
    strcpy(root->capitala, "NULL");
    strcpy(root->suprafata, "NULL");
    root->populatia = 0;
}
void free_tree(treeNode *root) {
   if (root == NULL) return;
   free_tree(root->left);
   free_tree(root->right);
   printf("Node deleted\n");
   free(root);
}
//void return_arr(treeNode* root, int arr[], int index)
//{
//    if (root == NULL)
//        return;
//
//    // traverse the left subtree
//    return_arr(root->left, arr, index);
//
//    // traverse the right subtree
//    return_arr(root->right, arr, index);
//
//    // store the value of the current node in the array
//    arr[index] = root->key;
//    index++;
//}
//void print_arr(int *arr, int n)
//{
//    for(int i=0; i<n; i++)
//    {
//        printf("%d, ", *(arr+i));
//    }
//}





void store_inorder(treeNode* root, int* arr, int* index_ptr)
{
    if (root == NULL)
        return;
    store_inorder(root->left, arr, index_ptr);
    arr[*index_ptr] = root->key;
    (*index_ptr)++;
    store_inorder(root->right, arr, index_ptr);
}

treeNode* sorted_array_to_bst(int* arr, int start, int end)
{
    if (start > end)
        return NULL;
    int mid = (start + end)/2;
     treeNode* root = (treeNode*)malloc(sizeof(treeNode));
    root->key = arr[mid];
    root->left = sorted_array_to_bst(arr, start, mid - 1);
    root->right = sorted_array_to_bst(arr, mid + 1, end);
    return root;
}

treeNode* balance_tree(treeNode* root)
{
    int n = 0;
    int* arr = (int*)malloc(sizeof(int)*n);
    store_inorder(root, arr, &n);
    return sorted_array_to_bst(arr, 0, n-1);
}
void show_menu();
int main()
{
    treeNode *root = NULL;
    show_menu();
    int n;
    scanf("%d", &n);
    do
    {
        int num;
        switch(n)
        {
        case 1:
        {
            if(root == NULL)
            {
                char tara[MAX];
                char cap[MAX];
                char sup[MAX];
                int pop;
                int key;
                printf("Elementul 1 = \n");
                printf("Key: ");
                scanf("%d", &key);
                printf("Tara: ");
                scanf(" %s", &tara);
                printf("Capitala: ");
                scanf(" %s", &cap);
                printf("Suprafata: ");
                scanf(" %s", &sup);
                printf("Populatia: ");
                scanf("%d", &pop);
                root = create_node(tara, cap, sup, pop, key);
                insert_node(root, 2);
            }
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            print_tree(root);
            break;
        }
        case 3:
        {
            system("cls");
            int key_search;
            printf("Key = ");
            scanf("%d", &key_search);
            find_node(root, key_search);
            break;
        }
        case 4:
        {
            system("cls");
            parc_SVD(root);
            printf("\n");
            break;
        }
        case 5:
        {
            system("cls");
            parc_VSD(root);
            printf("\n");
            break;
        }
        case 6:
        {
            system("cls");
            parc_SDV(root);
            printf("\n");
            break;
        }
        case 7:
        {
            system("cls");
            printf("Adancimea arborelui este : %d\n", adancime_DFS(root));
            break;
        }
        case 8:
        {
            system("cls");
            printf("Inaltimea arborelui este: %d\n", inaltime_BFS(root));
            break;
        }
        case 9:
        {
            root = balance_tree(root);
            break;
        }
        case 10:
        {
            system("cls");
            mirror_tree(root);
            break;
        }
        case 11:
        {
            clear_tree(root);
            break;
        }
        case 12:
        {
            free_tree(root);
            root = NULL;
            printf("Tree deleted!!!\n");
            break;
        }
        }
        show_menu();
        scanf("%d", &n);
    }
    while(n != 0);
    return 0;
}
void show_menu()
{
    printf("----------------------------------------------------\n");
    printf("|1) Citirea de la tastatura a elementelor arborelui|\n");
    printf("----------------------------------------------------\n");
    printf("|2) Afisarea la consola a elementelor arborelui    |\n");
    printf("----------------------------------------------------\n");
    printf("|3) Cautarea unui nod in baza campului cheie si    |\n"
           "|  afisarea campurilor nodului gasit               |\n");
    printf("----------------------------------------------------\n");
    printf("|4) Parcurgerea arborelui in inordine  SVD         |\n");
    printf("----------------------------------------------------\n");
    printf("|5) Parcurgerea arborelui in preordine VSD         |\n");
    printf("----------------------------------------------------\n");
    printf("|6) Parcurgerea arborelui in postordine   SDV      |\n");
    printf("----------------------------------------------------\n");
    printf("|7) Parcurgerea arborelui in adancime( DFS)        |\n");
    printf("----------------------------------------------------\n");
    printf("|8) Parcurgerea arborelui in largime ( BFS)        |\n");
    printf("----------------------------------------------------\n");
    printf("|9) Balansarea arborelui                           |\n");
    printf("----------------------------------------------------\n");
    printf("|10)Oglindirea arborelui (orice nod copil drept,   |\n"
    "|  devine un nod copil stang                       |\n");
    printf("----------------------------------------------------\n");
    printf("|11)Curatirea elementelor arborelui                |\n");
    printf("----------------------------------------------------\n");
    printf("|12)Eliberarea memoriei arborelui                  |\n");
    printf("----------------------------------------------------\n");
}

