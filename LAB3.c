
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

Node *createNode(int value) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("Malloc error\n");
    exit(0);
  }
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->value = value;
  return newNode;
}
Node *insertNode(Node *root, int value) {
  if (root == NULL) {
    root = createNode(value);
  } else if (value < root->value) {
    root->left = insertNode(root->left, value);
  } else {
    root->right = insertNode(root->right, value);
  }
  return root;
}
// functie pentru afisarea arborelui
void inorderTraversal(Node *root) {
  if (root == NULL)
    return;
  inorderTraversal(root->left);
  printf("%d ", root->value);
  inorderTraversal(root->right);
}

int depth(Node *node) {
  if (node == NULL)
    return 0;
  else {
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);

    if (leftDepth > rightDepth)
      return (leftDepth + 1);
    else
      return (rightDepth + 1);
  }
}

Node *search(Node *root, int key) {
  if (root == NULL || root->value == key)
    return root;

  if (root->value < key)
    return search(root->right, key);

  return search(root->left, key);
}

void printLeaves(Node *node) {
  if (node == NULL)
    return;

  if (node->left == NULL && node->right == NULL) {
    printf("%d ", node->value);
    return;
  }

  if (node->left != NULL)
    printLeaves(node->left);

  if (node->right != NULL)
    printLeaves(node->right);
}

void deleteTree(Node *node) {
  if (node == NULL)
    return;

  deleteTree(node->left);
  deleteTree(node->right);

  printf("\n Stergerea nodului: %d", node->value);
  free(node);
}

void printTree(Node *node, int space) {
  int i;

  if (node == NULL)
    return;

  space += 10;

  printTree(node->right, space);

  printf("\n");
  for (i = 10; i < space; i++)
    printf(" ");
  printf("%d\n", node->value);

  printTree(node->left, space);
}
void print2D(struct Node *root) { printTree(root, 0); }

int main(void) {
  Node *root = NULL;
  Node *searchResult = NULL;
  int choice, value, key;

  while (1) {
    printf("\n1. Introducerea elementelor  \n2. Calcularea adancimii arborelui \n3. Cautarea unui nod \n4. Calcularea adancimii unui nod \n5. "
           "Calcularea inaltimii \n"
           "6. Afisarea frunzelor \n7. Curatirea elementelor arborelui \n8. Afisarea arborelui \n9. Exit \n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Introduceti valoarea de inserat: ");
      scanf("%d", &value);
      root = insertNode(root, value);
      break;
    case 2:
      printf("Adancimea arborelui este: %d", depth(root));
      break;
    case 3:
      printf("Introduceți cheia pentru a căuta: ");
      scanf("%d", &key);
      searchResult = search(root, key);
      if (searchResult == NULL)
        printf("Cheia nu era gasita \n");
      else
        printf("Cheia e gasita \n");
      break;
    case 4:
      printf("Introduceți cheia pentru a găsi adâncimea: ");
      scanf("%d", &key);
      searchResult = search(root, key);
      if (searchResult == NULL)
        printf("Cheia nu era gasita \n");
      else
        printf("Adancimea nodului este: %d", depth(searchResult));
      break;
    case 5:
      printf("Introduceti cheia pentru a gasi înaltimea: ");
      scanf("%d", &key);
      searchResult = search(root, key);
      if (searchResult == NULL)
        printf("Cheia nu era gasita \n");
      else
        printf("Inaltimea nodului este %d", depth(searchResult) - 1);
      break;
    case 6:
      printf("Frunzele arborelui sunt: ");
      printLeaves(root);
      break;
    case 7:
      deleteTree(root);
      root = NULL;
      printf("\n Arborele era sters  ");
      break;
    case 8:
      printf("Arborele binar este: \n");
      print2D(root);
      break;
    case 9:
      exit(0);
    default:
      printf("Invalid choice \n");
    }
  }

  return 0;
}

