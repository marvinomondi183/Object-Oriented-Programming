#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class Account {
private:
    string username;
    double balance;

public:
    Account(string name, double initialBalance) {
        username = name;
        balance = initialBalance;
    }

    void showBalance() {
        cout << "\nAccount Name: " << username << endl;
        cout << "Current Balance: $" << balance << endl;
    }

    void updateBalance(double profitLoss) {
        balance += profitLoss;
    }

    double getBalance() {
        return balance;
    }
};

class CurrencyPair {
private:
    string pairName;
    double price;

public:
    CurrencyPair(string name, double startPrice) {
        pairName = name;
        price = startPrice;
    }

    string getPairName() {
        return pairName;
    }

    double getPrice() {
        return price;
    }

    double generateExitPrice() {
        double movement = (rand() % 201 - 100) / 100.0;
        return price + movement;
    }
};

class Trade {
private:
    string pairName;
    string tradeType;
    double entryPrice;
    double exitPrice;
    double lotSize;
    double profitLoss;

public:
    Trade(string pair, string type, double entry, double exitP, double lot) {
        pairName = pair;
        tradeType = type;
        entryPrice = entry;
        exitPrice = exitP;
        lotSize = lot;
        profitLoss = 0;
    }

    double calculateProfitLoss() {
        if (tradeType == "BUY" || tradeType == "buy") {
            profitLoss = (exitPrice - entryPrice) * lotSize * 100;
        } else if (tradeType == "SELL" || tradeType == "sell") {
            profitLoss = (entryPrice - exitPrice) * lotSize * 100;
        } else {
            cout << "Invalid trade type!" << endl;
            profitLoss = 0;
        }

        return profitLoss;
    }

    void displayTrade() {
        cout << "\n--- Trade Result ---" << endl;
        cout << "Pair: " << pairName << endl;
        cout << "Trade Type: " << tradeType << endl;
        cout << "Entry Price: " << entryPrice << endl;
        cout << "Exit Price: " << exitPrice << endl;
        cout << "Lot Size: " << lotSize << endl;
        cout << "Profit/Loss: $" << profitLoss << endl;
    }

    void saveTrade() {
        ofstream file("trade_history.txt", ios::app);

        file << "Pair: " << pairName << endl;
        file << "Trade Type: " << tradeType << endl;
        file << "Entry Price: " << entryPrice << endl;
        file << "Exit Price: " << exitPrice << endl;
        file << "Lot Size: " << lotSize << endl;
        file << "Profit/Loss: $" << profitLoss << endl;
        file << "------------------------" << endl;

        file.close();
    }
};

int main() {
    srand(time(0));

    string name;
    double startingBalance;
    int choice;

    cout << "=== Forex Trading Simulator ===" << endl;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter demo starting balance: $";
    cin >> startingBalance;

    Account user(name, startingBalance);

    CurrencyPair eurusd("EUR/USD", 1.0850);
    CurrencyPair gbpusd("GBP/USD", 1.2650);
    CurrencyPair xauusd("XAU/USD", 2350.00);

    do {
        cout << "\n===== MAIN MENU =====" << endl;
        cout << "1. View Balance" << endl;
        cout << "2. Open Trade" << endl;
        cout << "3. View Trade History" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            user.showBalance();
        }

        else if (choice == 2) {
            int pairChoice;
            string tradeType;
            double lotSize;
            CurrencyPair selectedPair = eurusd;

            cout << "\nChoose Currency Pair:" << endl;
            cout << "1. EUR/USD" << endl;
            cout << "2. GBP/USD" << endl;
            cout << "3. XAU/USD" << endl;
            cout << "Enter choice: ";
            cin >> pairChoice;

            if (pairChoice == 1) {
                selectedPair = eurusd;
            } else if (pairChoice == 2) {
                selectedPair = gbpusd;
            } else if (pairChoice == 3) {
                selectedPair = xauusd;
            } else {
                cout << "Invalid pair selected!" << endl;
                continue;
            }

            cout << "Enter trade type BUY or SELL: ";
            cin >> tradeType;

            cout << "Enter lot size: ";
            cin >> lotSize;

            double entryPrice = selectedPair.getPrice();
            double exitPrice = selectedPair.generateExitPrice();

            Trade trade(
                selectedPair.getPairName(),
                tradeType,
                entryPrice,
                exitPrice,
                lotSize
            );

            double result = trade.calculateProfitLoss();
            user.updateBalance(result);

            trade.displayTrade();
            trade.saveTrade();

            cout << "\nTrade saved successfully." << endl;
            user.showBalance();
        }

        else if (choice == 3) {
            ifstream file("trade_history.txt");
            string line;

            cout << "\n--- Trade History ---" << endl;

            if (!file) {
                cout << "No trade history found." << endl;
            } else {
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            }
        }

        else if (choice == 4) {
            cout << "\nThank you for using the Forex Trading Simulator." << endl;
        }

        else {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
