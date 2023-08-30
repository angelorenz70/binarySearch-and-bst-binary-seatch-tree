//Tsieiammetse Angelo C. Rendon
//Binary Search Using Linked List
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct binarySearct{
    char * value;
    struct binarySearct * next;
}bs;

bs * createNode (char * value){
    bs * newNode = (bs *)malloc(sizeof(bs));
    newNode->value = (char *)malloc(sizeof(char) * strlen(value));
    strcpy(newNode->value, value);
    *(newNode->value + strlen(value)) = '\0';
    newNode->next = NULL;

    return newNode;
}

bool proceed(bs * root, char * value){
    return (strcmp(root->value, value) <= 0) ? false : true;
}



bs * insertNode(bs * root, char * value) {
    if (root == NULL || strcmp(root->value, value) >= 0) {
        bs * newNode = createNode(value);
        newNode->next = root;
        return newNode;
    }

    root->next = insertNode(root->next, value);
    return root;
}


int listLength(bs * root){
    if (root == NULL) {
        return 0;
    } else {
        return 1 + listLength(root->next);
    }
}

bs * goToLastNode(bs * root, int i, int size){
    if(i < size - 1){
        return goToLastNode(root->next, i + 1, size);
    }
    return root;
}


bs * goToMidnode(bs * root, int i, char IndexMid){
    if(i < IndexMid){
        return goToMidnode(root->next, i + 1, IndexMid );
    }
    return root;
}


bs *recursiveFindValue(bs *root, char *searchValue, int low, int high) {
    if (low > high) {
        return NULL;
    }

    int mid = low + (high - low) / 2;
    bs *midNode = goToMidnode(root, 0, mid);

    int cmpResult = strcmp(midNode->value, searchValue);
    if (cmpResult == 0) {
        return midNode;
    } else if (cmpResult < 0) {
        return recursiveFindValue(root, searchValue, mid + 1, high);
    } else {
        return recursiveFindValue(root, searchValue, low, mid - 1);
    }
}

bs *findValue(bs *root, char *searchValue) {
    int low = 0;
    bs *holder = root;
    int high = listLength(holder) - 1;

    return recursiveFindValue(root, searchValue, low, high);
}



void display(bs * root){
    if(root == NULL){
        return;
    }
    printf(" %s ",root->value);
    display(root->next);
}

int main()
{
    bs * root = NULL;
    char * value;
    int select;
    printf("Binary Search--------------->\n");
    while(1){
        printf("(1) add a value: \n");
        printf("(2) search a value: \n=====>");
        scanf("%d", &select);
        switch(select){
        case 1:
            value = (char *)malloc(sizeof(char) * 100);
            printf("Enter value: ");
            scanf(" %[^\n]", value);
            *(value + strlen(value)) = '\0';
            root = insertNode(root,value);
            printf("list: ");
            display(root);
            printf("\n\n");
            break;
        case 2:
            value = (char *)malloc(sizeof(char) * 100);
            printf("Enter value: ");
            scanf(" %[^\n]", value);
            *(value + strlen(value)) = '\0';
            bs * found = findValue(root, value);
            display(root);
            (found == NULL) ? printf("\n== %s not found!", value) : printf("\n== at address %p, %s is found!", found, found->value);
            printf("\n\n");
            break;
        default:
            exit(1);
        }

    }

    return 0;
}
