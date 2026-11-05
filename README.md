# Bank Management System

A small C++ console starter project for learning basic object-oriented programming and file input/output.

## Included in this starter

- Create an account with an account number and holder name
- List saved accounts and balances
- Record deposits and withdrawals
- Save account data in a local `accounts.txt` file between runs

## Build and run

With a C++17 compiler:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o bank
./bank
```

On Windows, run the compiled `bank.exe` from the project folder.

## Data and limitations

This is a learning demo, not banking software. It stores plain-text data locally and has no authentication, encryption, transaction audit log, or real payment connection. Do not use real or sensitive financial information.

The source currently in this repository is a starter implementation. Review, understand, and adapt it before presenting it as your own project work.
