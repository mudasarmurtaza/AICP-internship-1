#include <iostream>
#include <vector>
using namespace std;

const double BASIC_COMPONENTS_COST = 200.00;
const double ONE_ITEM_DISCOUNT = 0.05;  // 5%
const double TWO_OR_MORE_ITEMS_DISCOUNT = 0.10;  // 10%

// Item information
struct Item {
    string code;
    string description;
    double price;
};

// Initialize item arrays
const Item cases[] = {{"A1", "Compact", 75.00}, {"A2", "Tower", 150.00}};
const Item ram[] = {{"B1", "8 GB", 79.99}, {"B2", "16 GB", 149.99}, {"B3", "32 GB", 299.99}};
const Item hdds[] = {{"C1", "1 TB HDD", 49.99}, {"C2", "2 TB HDD", 89.99}, {"C3", "4 TB HDD", 129.99}};

// Function to display item options
void displayItems(const Item items[], int count) {
    for (int i = 0; i < count; i++) {
        cout << items[i].code << " - " << items[i].description << " ($" << items[i].price << ")" << endl;
    }
}

// Function to calculate the total cost
double calculateTotalCost(double basicCost, const vector<Item>& chosenItems) {
    double totalCost = basicCost;
    for (const Item& item : chosenItems) {
        totalCost += item.price;
    }
    return totalCost;
}

int main() {
    cout << "Welcome to the Online Computer Shop!" << endl;

    vector<Item> chosenItems;

    // Task 1 - Select main components
    cout << "Let's start by selecting the main components." << endl;

    cout << "Category Case items:" << endl;
    displayItems(cases, 2);
    string chosenCase;
    cout << "Please choose one Case (e.g., A1 or A2): ";
    cin >> chosenCase;

    string chosenRAM;
    cout << "Category RAM items:" << endl;
    displayItems(ram, 3);
    cout << "Please choose one RAM (e.g., B1, B2, or B3): ";
    cin >> chosenRAM;

    string chosenHDD;
    cout << "Category Main Hard Disk Drive items:" << endl;
    displayItems(hdds, 3);
    cout << "Please choose one Main Hard Disk Drive (e.g., C1, C2, or C3): ";
    cin >> chosenHDD;

    chosenItems.push_back(cases[chosenCase == "A2" ? 1 : 0]);
    chosenItems.push_back(ram[chosenRAM == "B2" ? 1 : (chosenRAM == "B3" ? 2 : 0)]);
    chosenItems.push_back(hdds[chosenHDD == "C2" ? 1 : (chosenHDD == "C3" ? 2 : 0)]);

    // Output the chosen main items and the total cost
    cout << "Chosen Main Case: " << chosenItems[0].description << endl;
    cout << "Chosen RAM: " << chosenItems[1].description << endl;
    cout << "Chosen Main HDD: " << chosenItems[2].description << endl;

    // Task 2 - Order additional items
    cout << "Now, you can choose additional items if you wish." << endl;

    vector<Item> additionalItems;
    double additionalItemsCost = 0.00;
    char addMoreItems = 'n';

    do {
        char category;
        cout << "Available Categories for Additional Items:" << endl;
        cout << "D - Solid State Drive\nE - Second Hard Disk Drive\nF - Optical Drive\nG - Operating System\n";
        cout << "Enter the category letter (D, E, F, G) or 'N' to stop adding items: ";
        cin >> category;

        if (category == 'N' || category == 'n') {
            break;  // Exit the loop
        }

        const Item* categoryItems = nullptr;
        int itemCount = 0;

        switch (category) {
            case 'D':
            case 'd':
                categoryItems = ram;
                itemCount = 3;
                break;
            case 'E':
            case 'e':
                categoryItems = hdds;
                itemCount = 3;
                break;
            case 'F':
            case 'f':
                categoryItems = cases;
                itemCount = 2;
                break;
            case 'G':
            case 'g':
                categoryItems = cases;
                itemCount = 2;
                break;
            default:
                cout << "Invalid category. Please try again." << endl;
                continue;
        }

        cout << "Category items:" << endl;
        displayItems(categoryItems, itemCount);

        string chosenItem;
        cout << "Please choose an item from the selected category: ";
        cin >> chosenItem;

        for (int i = 0; i < itemCount; i++) {
            if (chosenItem == categoryItems[i].code) {
                additionalItems.push_back(categoryItems[i]);
                additionalItemsCost += categoryItems[i].price;
                break;
            }
        }

        cout << "Do you want to add more items? (Y/N): ";
        cin >> addMoreItems;

    } while (addMoreItems == 'Y' || addMoreItems == 'y');

    // Calculate and display the new total cost with additional items
    double totalCost = calculateTotalCost(BASIC_COMPONENTS_COST, chosenItems) + additionalItemsCost;
    cout << "Chosen Additional Items: ";
    for (const Item& item : additionalItems) {
        cout << item.description << ", ";
    }
    cout << endl;
    cout << "Total Cost with Additional Items: $" << totalCost << endl;

    // Task 3 - Apply discounts
    if (additionalItems.size() == 1) {
        double discountAmount = totalCost * ONE_ITEM_DISCOUNT;
        totalCost -= discountAmount;
        cout << "5% discount applied. You saved $" << discountAmount << endl;
    } else if (additionalItems.size() >= 2) {
        double discountAmount = totalCost * TWO_OR_MORE_ITEMS_DISCOUNT;
        totalCost -= discountAmount;
        cout << "10% discount applied. You saved $" << discountAmount << endl;
    }

    cout << "Final Total Cost after Discounts: $" << totalCost << endl;

    return 0;
}
