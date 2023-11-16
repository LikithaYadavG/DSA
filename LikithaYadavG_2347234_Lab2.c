#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing a menu item in the restaurant
struct MenuItem {
    int id;
    char name[50];
    float price;
    struct MenuItem *next; // Pointer to the next item in the linked list
    struct MenuItem *prev; // Pointer to the previous item in the doubly linked list
};

// Function prototypes
void displayMenu(struct MenuItem *head);
void insertItem(struct MenuItem **head, int id, const char *name, float price);
void deleteItem(struct MenuItem **head, int id);
void sortMenu(struct MenuItem **head);
struct MenuItem* searchItem(struct MenuItem *head, int id);

int main() {
    struct MenuItem *singlyList = NULL;  // Singly linked list
    struct MenuItem *doublyList = NULL;  // Doubly linked list
    struct MenuItem *circularList = NULL;  // Circular linked list
    int mainChoice, listChoice, id;
    char name[50];
    float price;

    do {
        // Display main menu-driven options
        printf("\nRestaurant Management System\n");
        printf("1. Choose Linked List\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                // Choose Linked List
                printf("Choose Linked List Type:\n");
                printf("1. Singly Linked List\n");
                printf("2. Doubly Linked List\n");
                printf("3. Circular Linked List\n");
                printf("Enter your choice: ");
                scanf("%d", &listChoice);

                switch (listChoice) {
                    case 1:
                        // Singly Linked List
                        break;
                    case 2:
                        // Doubly Linked List
                        break;
                    case 3:
                        // Circular Linked List
                        break;
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                        continue; // Go back to the main menu
                }

                do {
                    // Display linked list operations menu-driven options
                    printf("\nLinked List Operations\n");
                    printf("1. Insert Item\n");
                    printf("2. Display Menu\n");
                    printf("3. Delete Item\n");
                    printf("4. Sort Menu\n");
                    printf("5. Search Item\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &mainChoice);

                    switch (mainChoice) {
                      case 1:
    // Insert Item
                    printf("Enter item ID: ");
                    scanf("%d", &id);
                    printf("Enter item name: ");
                    scanf("%s", name);

    // Clear the input buffer
                    while ((getchar()) != '\n'); // Keep reading characters until a newline is encountered

                    printf("Enter item price: ");
                    scanf("%f", &price);

    // Insert into the chosen linked list
                    if (listChoice == 1) {
                    insertItem(&singlyList, id, name, price);
                    } else if (listChoice == 2) {
                     insertItem(&doublyList, id, name, price);
                        } else if (listChoice == 3) {
                    insertItem(&circularList, id, name, price);
                    }
                    break;


                        case 2:
                            // Display Menu
                            if (listChoice == 1) {
                                displayMenu(singlyList);
                            } else if (listChoice == 2) {
                                displayMenu(doublyList);
                            } else if (listChoice == 3) {
                                displayMenu(circularList);
                            }
                            break;

                        case 3:
                            // Delete Item
                            printf("Enter item ID to delete: ");
                            scanf("%d", &id);
                            if (listChoice == 1) {
                                deleteItem(&singlyList, id);
                            } else if (listChoice == 2) {
                                deleteItem(&doublyList, id);
                            } else if (listChoice == 3) {
                                deleteItem(&circularList, id);
                            }
                            break;

                        case 4:
                            // Sort Menu
                            if (listChoice == 1) {
                                sortMenu(&singlyList);
                            } else if (listChoice == 2) {
                                sortMenu(&doublyList);
                            } else if (listChoice == 3) {
                                sortMenu(&circularList);
                            }
                            printf("Menu sorted successfully.\n");
                            break;

                        case 5:
                            // Search Item
                            printf("Enter item ID to search: ");
                            scanf("%d", &id);
                            struct MenuItem *foundItem;
                            if (listChoice == 1) {
                                foundItem = searchItem(singlyList, id);
                            } else if (listChoice == 2) {
                                foundItem = searchItem(doublyList, id);
                            } else if (listChoice == 3) {
                                foundItem = searchItem(circularList, id);
                            }
                            if (foundItem != NULL) {
                                printf("Item found: %s (ID: %d, Price: %.2f)\n", foundItem->name, foundItem->id, foundItem->price);
                            } else {
                                printf("Item not found.\n");
                            }
                            break;

                        case 6:
                            // Back to Main Menu
                            break;

                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }

                } while (mainChoice != 6);

                break;

            case 2:
                // Exit
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (mainChoice != 2);

    // Free allocated memory for each linked list
    // (you need to implement a function to free the memory of each node)

    return 0;
}

// Function to insert an item into the linked list
void insertItem(struct MenuItem **head, int id, const char *name, float price) {
    struct MenuItem *newItem = (struct MenuItem*)malloc(sizeof(struct MenuItem));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->next = NULL;

    if (*head == NULL) {
        *head = newItem;
    } else {
        struct MenuItem *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

// Function to display the menu
void displayMenu(struct MenuItem *head) {
    struct MenuItem *temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Price: %.2f\n", temp->id, temp->name, temp->price);
        temp = temp->next;
    }
}

// Function to delete an item from the linked list
void deleteItem(struct MenuItem **head, int id) {
    struct MenuItem *temp = *head;
    struct MenuItem *prev = NULL;

    // Search for the item with the given ID
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the item is found, delete it
    if (temp != NULL) {
        if (prev == NULL) {
            // If the item is the first node
            *head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Item with ID %d deleted successfully.\n", id);
    } else {
        printf("Item with ID %d not found.\n", id);
    }
}

// Function to sort the menu by item ID (ascending order)
void sortMenu(struct MenuItem **head) {
    if (*head == NULL || (*head)->next == NULL) {
        // If the list is empty or has only one node, it is already sorted
        return;
    }

    struct MenuItem *current = *head;
    struct MenuItem *nextItem = NULL;
    struct MenuItem *temp = NULL;

    // Bubble sort algorithm
    while (current->next != NULL) {
        nextItem = current->next;

        while (nextItem != NULL) {
            if (current->id > nextItem->id) {
                // Swap the nodes
                temp = (struct MenuItem*)malloc(sizeof(struct MenuItem));
                temp->id = current->id;
                strcpy(temp->name, current->name);
                temp->price = current->price;

                current->id = nextItem->id;
                strcpy(current->name, nextItem->name);
                current->price = nextItem->price;

                nextItem->id = temp->id;
                strcpy(nextItem->name, temp->name);
                nextItem->price = temp->price;

                free(temp);
            }

            nextItem = nextItem->next;
        }

        current = current->next;
    }
}

// Function to search for an item by ID
struct MenuItem* searchItem(struct MenuItem *head, int id) {
    struct MenuItem *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp; // Item found
        }
        temp = temp->next;
    }
    return NULL; // Item not found
}
