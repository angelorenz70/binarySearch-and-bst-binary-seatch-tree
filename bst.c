//Tsieiammetse Angelo C. Rendon
//Binary Search Using Linked List
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct binarySearchTress {
    char * value;
    struct binarySearchTress * left;
    struct binarySearchTress * right;
} bst;

bst * newNode(char * value){
    bst * createNode =  (bst *)malloc(sizeof(bst));
    createNode->value = (char *)malloc(sizeof(char) * strlen(value));
    strcpy(createNode->value, value);
    *((createNode->value) + strlen(value)) = '\0';
    createNode->left = NULL;
    createNode->right = NULL;

    return createNode;
}

bst * leafNode(bst * root){
    if(root == NULL){
        return root;
    }
    return leafNode(root->left);
}


//use to convert the character to int
int converToInt(char * number){
    if(strlen(number) == 1){
        return * number - '0';
    }else{
        return atoi(number);
    }
}

//if negative go to left, otherwise
bool destinationNode(char * newData, char * existData){
    return (strcmp(newData, existData) < 0) ? true : false;
}

bst * deleteNode(bst * root, char * deleteValue, bool * deleted){
    if(root != NULL){
        if(strcmp(root->value,deleteValue) == 0){
            bst * holder;
            if(root->right == NULL || root->left == NULL){
                bool leftNull = (root->left == NULL) ? true : false;
                if(leftNull){
                    holder = root->right;
                }else{
                    holder = root->left;
                }

                *deleted = true;

                free(root->value);
                free(root);
                return holder;
            }

            bst * holdNode = leafNode(root->right);
            free(root->value);
            root->value = (char *)malloc(sizeof(char) * strlen(holdNode->value));
            strcpy(root->value, holdNode->value);
            root->right = deleteNode(root->right, holdNode->value, deleted);
        }else{
            if(destinationNode(deleteValue, root->value)){
                root->left = deleteNode(root->left, deleteValue, deleted);
            }else{
                root->right = deleteNode(root->right, deleteValue, deleted);
            }
        }
    }
    return root;
}

bst * insertNode(bst * root, char * data){
    if(root != NULL){
        //left bias
        if(destinationNode(data, root->value)){
            root->left = insertNode(root->left, data);
        }else{
            root->right = insertNode(root->right, data);
        }
        return root;
    }
    return newNode(data);
}

void preOrder(bst * root){
    if(root == NULL){
        return;
    }

    printf(" %s ", root->value);
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    bst * root = NULL;
    char * input;
    int select;

    printf("BINARY SEARCH TREE---------------------------->\n");
    while(1){
        bool deletedValue = false;
        printf("(1) Enter a value\n");
        printf("(2) Delete a value\n");
        printf("select----> ");
        scanf("%d", &select);

        switch(select){
            case 1:
                input = (char *)malloc(sizeof(char) * 1000);
                printf("Enter input: ");
                scanf(" %[^\n]", input);
                input[strlen(input)] = '\0';
                root = insertNode(root, input);
                //holder
                preOrder(root);
                printf("\n\n");
                break;
            case 2:
                input = (char *)malloc(sizeof(char) * 1000);
                printf("Enter input: ");
                scanf(" %[^\n]", input);
                input[strlen(input)] = '\0';

                root = deleteNode(root, input, &deletedValue);

                (deletedValue) ? printf(" %s is successfully deleted \n ", input) : printf(" ");
                preOrder(root);
                printf("\n\n");
                break;
            default:
                exit(1);
        }
    }
    return 0;
}



