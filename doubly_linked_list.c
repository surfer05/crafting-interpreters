#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---  Data Structures ---

// Defines a node in the doubly-linked list.
typedef struct Node
{
    char *data;        // Pointer to a heap-allocated string.
    struct Node *prev; // Pointer to the previous node.
    struct Node *next; // Pointer to the next node.
} Node;

// Defines the doubly-linked list itself.
typedef struct DoublyLinkedList
{
    Node *head; // Pointer to the first node in the list.
} DoublyLinkedList;

// --- Function Prototypes ---

DoublyLinkedList *createList();
void insertNode(DoublyLinkedList *list, const char *data);
Node *findNode(DoublyLinkedList *list, const char *data);
void deleteNode(DoublyLinkedList *list, const char *data);
void printList(DoublyLinkedList *list);
void freeList(DoublyLinkedList *list);

// --- Main Function ( Test Suite ) ---

int main()
{
    // 1. Create a new list
    DoublyLinkedList *list = createList();
    printf("Created an empty list.\n\n");

    // 2. Insert items
    printf("--- Testing Insertion --- \n");
    insertNode(list, "Apple");
    insertNode(list, "Banana");
    insertNode(list, "Cherry");
    insertNode(list, "Date");
    printf("Inserted: Date, Cherry, Banana, Apple\n");
    printList(list);
    print("\n");

    // 3. Find items
    printf("--- Testing Find--- \n");
    Node *foundNode = findNode(list, "Banana");
    if (foundNode != NULL)
    {
        printf("Found \"Banana\" in the list .\n");
    }
    else
    {
        printf("Could not find \"Banana\" in the list .\n");
    }

    Node *notFoundNode = findNode(list, "Grape");
    if (notFoundNode != NULL)
    {
        printf("Found \"Grape\" in the list.\n");
    }
    else
    {
        printf("Could not find \"Grape\" in the list.\n");
    }
    printf("\n");

    // 4. Delete items
    printf("--- Testing Deletion ---\n");

    // Delete from the middle
    printf("Deleting \"Cherry\" (middle element)...\n");
    deleteNode(list, "Cherry");
    printList(list);

    // Delete the head
    printf("Deleting \"Date\" (head element)...\n");
    deleteNode(list, "Date");
    printList(list);

    // Delete the tail
    printf("Deleting \"Apple\" (tail element)...\n");
    deleteNode(list, "Apple");
    printList(list);

    // Try to delete an item that doesn't exist
    printf("Attempting to delete \"Grape\" (non-existent)...\n");
    deleteNode(list, "Grape");
    printList(list);

    // Delete the last remaining item
    printf("Deleting \"Banana\" (last element)...\n");
    deleteNode(list, "Banana");
    printList(list);
    printf("\n");

    // 5. Clean up all memory
    printf(" --- Freeing List --- \n");
    freeList(list);
    printf("List memory has been freed.\n");
    return 0;
}


// ------ Functions Impelmentations ---

/**
 * @brief Allocates and initializes a new, empty list.
 * @return A pointer to the newly created DoublyLinkedList.
 */
DoublyLinkedList* createList() {
    DoublyLinkedList *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        perror("Failed to allocate memory for list ");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}


/**
 * @brief Creates a new node and inserts it at the head of the list.
 * @param list The list to insert into.
 * @param data The string data to store. The function creates a heap-allocated copy.
 */
void insertNode(DoublyLinkedList *list, const char *data) {
    if (list == NULL) return;

    // Create the new node
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        return;
    }

    
}