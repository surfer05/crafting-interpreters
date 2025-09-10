#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---  Data Structures ---

// Defines a node in the doubly-linked list.
typedef struct Node
{
    struct Node *prev; // Pointer to the previous node.
    char *data;        // Pointer to a heap-allocated string.
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
    printf("\n");

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

// ------ Functions Implementations ---

/**
 * @brief Allocates and initializes a new, empty list.
 * @return A pointer to the newly created DoublyLinkedList.
 */
DoublyLinkedList *createList()
{
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    if (list == NULL)
    {
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
void insertNode(DoublyLinkedList *list, const char *data)
{
    if (list == NULL)
        return;

    // Create the new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        perror("Failed to allocate memory for new node");
        return;
    }

    // Allocate memory for the string data and copy it
    newNode->data = strdup(data); // strdup allocates memory and copies the string
    if (newNode->data == NULL)
    {
        perror("Failed to duplicate string for new node");
        free(newNode);
        return;
    }

    // Wire up the new node
    newNode->next = list->head;
    newNode->prev = NULL;

    // If the list isn't empty, update the old head's prev pointer
    if (list->head != NULL)
    {
        list->head->prev = newNode;
    }

    // The new node is now the head
    list->head = newNode;
}

/**
 * @brief Searches for a node containing the given string.
 * @param list The list to search in.
 * @param data The string to find.
 * @return A pointer to the found node, or NULL if not found.
 */
Node* findNode(DoublyLinkedList *list, const char *data) {
    if (list==NULL) return NULL;

    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // NOT Found
}

/**
 * @brief Finds and deletes a node with the specified data from the list.
 * @param list The list to delete from.
 * @param data The string data of the node to delete.
 */
void deleteNode(DoublyLinkedList *list, const char *data) {
    if (list == NULL || list->head == NULL) return;

    Node *nodeToDelete = findNode(list, data);

    // If the node wasn't found, there's nothing to do.
    if (nodeToDelete == NULL) {
        return;
    }

    // Case 1: The node to delete is the head of the list.
    if (nodeToDelete == list->head) {
        list->head = nodeToDelete->next;
    }

    // Case 2: Update the 'next' pointer of the previous node.
    // (If nodeToDelete->prev is not NULL)
    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    // Case 3: Update the 'prev' pointer of the next node.
    // (If nodeToDelete->next is not NULL)
    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    // Finally, free the meory for the string and the node itself.
    free(nodeToDelete->data);
    free(nodeToDelete);
}


/**
 * @brief Prints the contents of the list from head to tail.
 * @param list The list to print.
 */
void printList(DoublyLinkedList *list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *current = list->head;
    printf("List contents: [");
    while(current != NULL) {
        printf("\"%s\" ", current->data);
        current = current->next;
    }
    printf("]\n");
}

/**
 * @brief Frees all memory associated with the list, including all nodes and their data.
 * @param list The list to free.
 */
void freeList(DoublyLinkedList *list) {
    if (list == NULL) return;

    Node *current = list->head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->data); // Free the string
        free(current); // Free the node
        current = nextNode;
    }

    free(list); // Finally, free the list structure itself.
}