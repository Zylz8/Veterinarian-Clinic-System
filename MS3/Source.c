#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define LENGTH 30
#define STORE_SIZE 100

// Custom data types
struct Product {
    int sku;
    char name[LENGTH + 1];
    double price;
};

struct Store {
    char storeName[LENGTH + 1];
    int productCount;
    struct Product products[STORE_SIZE]; // Array to store products
};

// Function prototypes
int addProduct(struct Product products[], int arrSize);
void displayStore(const struct Store* conv_store, int arrSize);

// Main program
int main(void) {
    // Initialize store
    struct Store conv_store = { "Max Convenience Store", 0, { { 0 } } };

    // Display initial store state
    displayStore(&conv_store, conv_store.productCount);

    // Add products to the store
    conv_store.productCount += addProduct(conv_store.products, STORE_SIZE - conv_store.productCount);

    // Display store state after adding products
    displayStore(&conv_store, conv_store.productCount);

    return 0;
}

// Function definitions
int addProduct(struct Product products[], int arrSize) {
    int i, keepAdding, emptyFound, count = 0;
    do {
        emptyFound = 0;

        // Iterate the product array until the end of the array is reached or an empty element was found
        for (i = 0; i < arrSize && emptyFound == 0; i++) {
            if (products[i].sku == 0) { // Find an empty element (current product “sku” will be zero)
                printf("Enter product information:\n");
                printf(" Name: ");
                scanf(" %30[^\n]", products[i].name); // Store entered value to current product “name” member
                printf(" SKU: ");
                scanf(" %d", &products[i].sku); // Store entered value to current product “sku” member
                printf(" Price: $");
                scanf(" %lf", &products[i].price); // Store entered value to current product “price” member
                count++; // Increment the record counter
                emptyFound = 1; // Toggle flag variable to exit loop
            }
        }

        if (i == arrSize) {
            printf("Warning: Store is full - no more data can be entered!");
            keepAdding = 0;
        }
        else {
            do {
                printf("Add another product? (0=No, 1=Yes): ");
                scanf(" %d", &keepAdding); // Assign input to flag variable keepAdding
                printf("\n");
            } while (keepAdding != 0 && keepAdding != 1);
        }
    } while (keepAdding == 1 && count < arrSize);

    return count; // Return the counter variable to the caller of this function
}

void displayStore(const struct Store* conv_store, int arrSize) {
    int i;
    double storeValue = 0.0;

    printf("+---------------------------------------------+\n");
    printf("%s\n", conv_store->storeName);
    printf("+---------------------------------------------+\n");
    printf("Maximum store size: %d\n", arrSize);
    printf("Products on-hand: %d\n\n", conv_store->productCount);
    printf("---- --------- ------------------------------\n");
    printf("SKU PRICE ($) NAME\n");
    printf("---- --------- ------------------------------\n");

    if (conv_store->productCount == 0) {
        printf("*** No products data available ***\n\n");
    }
    else {
        for (i = 0; i < arrSize; i++) {
            if (conv_store->products[i].sku > 0) {
                printf("%d %9.2lf %s\n", conv_store->products[i].sku, conv_store->products[i].price, conv_store->products[i].name);
                storeValue += conv_store->products[i].price;
            }
        }

        printf("-------------------------------------------\n");
        printf("Total store value: $%.2lf\n\n", storeValue);
    }
}
