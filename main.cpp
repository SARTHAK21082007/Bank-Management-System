#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Account {
    int number{};
    std::string name;
    double balance{};

    void show() const {
        std::cout << number << " | " << name << " | Rs. "
                  << std::fixed << std::setprecision(2) << balance << '\n';
    }
};

class Bank {
    std::vector<Account> accounts;
    const std::string fileName = "accounts.txt";

    void load() {
        std::ifstream file(fileName);
        Account a;
        while (file >> a.number) {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '|');
            std::getline(file, a.name, '|');
            if (file >> a.balance) accounts.push_back(a);
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void save() const {
        std::ofstream file(fileName);
        for (const auto& a : accounts)
            file << a.number << '|' << a.name << '|'
                 << std::fixed << std::setprecision(2) << a.balance << '\n';
    }

    int find(int number) const {
        for (std::size_t i = 0; i < accounts.size(); ++i)
            if (accounts[i].number == number) return static_cast<int>(i);
        return -1;
    }

    int readNumber(const std::string& prompt) const {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void create() {
        int number = readNumber("Account number: ");
        if (find(number) >= 0) {
            std::cout << "That account number already exists.\n";
            return;
        }
        std::string name;
        std::cout << "Account holder name: ";
        std::getline(std::cin, name);
        if (name.empty() || name.find('|') != std::string::npos) {
            std::cout << "Use a non-empty name without the | character.\n";
            return;
        }
        accounts.push_back({number, name, 0.0});
        save();
        std::cout << "Account created.\n";
    }

    void list() const {
        if (accounts.empty()) {
            std::cout << "No accounts saved.\n";
            return;
        }
        for (const auto& a : accounts) a.show();
    }

    void changeBalance(bool deposit) {
        int index = find(readNumber("Account number: "));
        if (index < 0) {
            std::cout << "Account not found.\n";
            return;
        }
        double amount;
        std::cout << "Amount in Rs.: ";
        if (!(std::cin >> amount) || amount <= 0) {
            std::cout << "Enter an amount greater than zero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!deposit && amount > accounts[index].balance) {
            std::cout << "Insufficient balance.\n";
            return;
        }
        accounts[index].balance += deposit ? amount : -amount;
        save();
        std::cout << "New balance: Rs. " << std::fixed << std::setprecision(2)
                  << accounts[index].balance << '\n';
    }

public:
    Bank() { load(); }
    void run() {
        while (true) {
            std::cout << "\nBank Management System - Demo\n"
                      << "1. Create account\n2. List accounts\n"
                      << "3. Deposit\n4. Withdraw\n5. Exit\n";
            switch (readNumber("Choose: ")) {
                case 1: create(); break;
                case 2: list(); break;
                case 3: changeBalance(true); break;
                case 4: changeBalance(false); break;
                case 5: return;
                default: std::cout << "Choose 1 to 5.\n";
            }
        }
    }
};

int main() {
    Bank bank;
    bank.run();
    return 0;
}
