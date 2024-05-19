#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int quantity;
    double price;
} InventoryItem;

InventoryItem inventory[MAX_ITEMS];
int itemCount = 0;

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }

    InventoryItem newItem;
    newItem.id = itemCount + 1; // Simple auto-increment ID

    printf("Enter item name: ");
    scanf("%s", newItem.name);
    printf("Enter item quantity: ");
    scanf("%d", &newItem.quantity);
    printf("Enter item price: ");
    scanf("%lf", &newItem.price);

    inventory[itemCount++] = newItem;
    printf("Item added successfully with ID %d.\n", newItem.id);
}

void displayItems() {
    if (itemCount == 0) {
        printf("No items in inventory.\n");
        return;
    }

    printf("Inventory items:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("ID: %d, Name: %s, Quantity: %d, Price: %.2lf\n", 
               inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void searchItem() {
    char query[NAME_LENGTH];
    printf("Enter item ID or name to search: ");
    scanf("%s", query);

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == atoi(query) || strcmp(inventory[i].name, query) == 0) {
            printf("Found item - ID: %d, Name: %s, Quantity: %d, Price: %.2lf\n", 
                   inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found.\n");
    }
}

void updateItem() {
    int id;
    printf("Enter item ID to update: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%lf", &inventory[i].price);
            printf("Item updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }
}

void deleteItem() {
    int id;
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            printf("Item deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }
}

void displayMenu() {
    printf("\nInventory Management System\n");
    printf("1. Add Item\n");
    printf("2. Display Items\n");
    printf("3. Search Item\n");
    printf("4. Update Item\n");
    printf("5. Delete Item\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                updateItem();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
