
#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    int price;
    int stock;
};

void displayProducts(Product products[], int size) {
    cout << "\n===== SMART VENDING MACHINE =====\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << products[i].name
             << " | Price: " << products[i].price
             << " IQD | Stock: " << products[i].stock << endl;
    }

    cout << "0. Cancel transaction\n";
}

void insertMoney(int &balance) {
    int amount;

    cout << "\nEnter money (0 to finish): ";

    while (true) {
        cin >> amount;

        if (amount == 0) break;

        if (amount < 0) {
            cout << "Invalid amount! Try again: ";
            continue;
        }

        balance += amount;
        cout << "Current balance: " << balance << " IQD\n";
        cout << "Enter more money (0 to finish): ";
    }
}

void refundMoney(int &balance) {
    if (balance > 0) {
        cout << "\nRefunding: " << balance << " IQD\n";
        cout << "Please collect your money.\n";
        balance = 0;
    }
}

void buyProduct(Product products[], int size, int &balance) {
    int choice;

    while (true) {
        displayProducts(products, size);

        cout << "\nEnter product number: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Transaction cancelled.\n";
            refundMoney(balance);
            return;
        }

        if (choice < 1 || choice > size) {
            cout << "Invalid product number!\n";
            continue;
        }

        int index = choice - 1;

        if (products[index].stock == 0) {
            cout << "Sorry! This product is out of stock.\n";
            continue;
        }

        if (balance < products[index].price) {
            cout << "Insufficient money!\n";
            cout << "You need "
                 << products[index].price - balance
                 << " IQD more.\n";
            insertMoney(balance);
            continue;
        }

        balance -= products[index].price;
        products[index].stock--;

        cout << "\nPurchase successful!\n";
        cout << "Dispensing " << products[index].name << "...\n";
        cout << "Please collect your product.\n";

        refundMoney(balance);
        return;
    }
}

int main() {
    Product products[5] = {
        {"Water", 500, 10},
        {"Juice", 1000, 8},
        {"Chips", 750, 6},
        {"Chocolate", 1500, 5},
        {"Biscuits", 1000, 7}
    };

    int balance = 0;
    char again;

    cout << "Welcome to Smart Vending Machine!\n";

    do {
        balance = 0;

        cout << "\nPlease insert your money.\n";
        insertMoney(balance);

        if (balance > 0) {
            buyProduct(products, 5, balance);
        } else {
            cout << "No money inserted.\n";
        }

        cout << "\nDo you want another transaction? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    cout << "\nThank you for using our machine!\n";

    return 0;
}
