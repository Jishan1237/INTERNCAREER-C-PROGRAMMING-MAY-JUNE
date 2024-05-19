#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 100
#define MAX_HISTORY 100
#define MAX_NAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_CURRENCY_LEN 4

typedef struct {
    int accountNumber;
    char name[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    double balance;
    char currency[MAX_CURRENCY_LEN];
    int locked;
    int loginAttempts;
    char transactionHistory[MAX_HISTORY][100];
    int transactionCount;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

int generateAccountNumber() {
    return 100000 + rand() % 900000;
}

Account* findAccount(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return &accounts[i];
        }
    }
    return NULL;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = generateAccountNumber();
    newAccount.locked = 0;
    newAccount.loginAttempts = 0;
    newAccount.transactionCount = 0;

    printf("Enter your name: ");
    scanf("%s", newAccount.name);
    printf("Enter a password: ");
    scanf("%s", newAccount.password);
    printf("Enter initial balance: ");
    scanf("%lf", &newAccount.balance);
    printf("Enter currency (USD, EUR, INR): ");
    scanf("%s", newAccount.currency);

    if (strcmp(newAccount.currency, "USD") != 0 && strcmp(newAccount.currency, "EUR") != 0 && strcmp(newAccount.currency, "INR") != 0) {
        printf("Invalid currency. Only USD, EUR, and INR are supported.\n");
        return;
    }

    accounts[accountCount++] = newAccount;
    printf("Account created successfully. Your account number is: %d\n", newAccount.accountNumber);
}

void checkBalance(Account* account) {
    printf("Current balance: %s %.2f\n", account->currency, account->balance);
}

void deposit(Account* account) {
    double amount;
    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Deposit amount must be greater than zero.\n");
        return;
    }

    account->balance += amount;
    snprintf(account->transactionHistory[account->transactionCount++], 100, "Deposited %s %.2f", account->currency, amount);
    printf("Deposit successful. Current balance: %s %.2f\n", account->currency, account->balance);
}

void withdraw(Account* account) {
    double amount;
    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Withdrawal amount must be greater than zero.\n");
        return;
    }

    if (amount > account->balance) {
        printf("Insufficient funds.\n");
    } else {
        account->balance -= amount;
        snprintf(account->transactionHistory[account->transactionCount++], 100, "Withdrawn %s %.2f", account->currency, amount);
        printf("Withdrawal successful. Current balance: %s %.2f\n", account->currency, account->balance);
    }
}

void changePassword(Account* account) {
    char currentPassword[MAX_PASSWORD_LEN];
    printf("Enter current password: ");
    scanf("%s", currentPassword);

    if (strcmp(account->password, currentPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", account->password);
    printf("Password changed successfully.\n");
}

void transfer(Account* account) {
    int recipientAccountNumber;
    printf("Enter recipient's account number: ");
    scanf("%d", &recipientAccountNumber);

    Account* recipient = findAccount(recipientAccountNumber);
    if (recipient == NULL) {
        printf("Recipient account not found.\n");
        return;
    }

    double amount;
    printf("Enter transfer amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Transfer amount must be greater than zero.\n");
        return;
    }

    if (amount > account->balance) {
        printf("Insufficient funds.\n");
    } else {
        account->balance -= amount;
        recipient->balance += amount;
        snprintf(account->transactionHistory[account->transactionCount++], 100, "Transferred %s %.2f to account %d", account->currency, amount, recipientAccountNumber);
        printf("Transfer successful. Current balance: %s %.2f\n", account->currency, account->balance);
    }
}

void viewTransactionHistory(Account* account) {
    printf("Transaction history for account number: %d\n", account->accountNumber);
    for (int i = 0; i < account->transactionCount; i++) {
        printf("%s\n", account->transactionHistory[i]);
    }
}

void login() {
    int accountNumber;
    printf("Enter your account number: ");
    scanf("%d", &accountNumber);

    Account* account = findAccount(accountNumber);
    if (account != NULL && !account->locked) {
        char password[MAX_PASSWORD_LEN];
        printf("Enter your password: ");
        scanf("%s", password);

        if (strcmp(account->password, password) == 0) {
            printf("Login successful!\n");
            account->locked = 0;
            account->loginAttempts = 0;

            int option;
            do {
                printf("\nAccount Options:\n");
                printf("1. Check Balance\n");
                printf("2. Deposit\n");
                printf("3. Withdraw\n");
                printf("4. Change Password\n");
                printf("5. Transfer Money\n");
                printf("6. View Transaction History\n");
                printf("7. Logout\n");
                printf("Please select an option: ");
                scanf("%d", &option);

                switch (option) {
                    case 1:
                        checkBalance(account);
                        break;
                    case 2:
                        deposit(account);
                        break;
                    case 3:
                        withdraw(account);
                        break;
                    case 4:
                        changePassword(account);
                        break;
                    case 5:
                        transfer(account);
                        break;
                    case 6:
                        viewTransactionHistory(account);
                        break;
                    case 7:
                        printf("Logged out successfully.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (option != 7);
        } else {
            printf("Invalid password.\n");
            account->loginAttempts++;
            if (account->loginAttempts >= 3) {
                printf("Your account has been locked. Please contact customer support.\n");
                account->locked = 1;
            }
        }
    } else {
        printf("Invalid account number or account locked.\n");
    }
}

int main() {
    srand(time(0));
    int choice;

    while (1) {
        printf("Welcome to the Comprehensive ATM System!\n");
        printf("1. Login\n");
        printf("2. Create an Account\n");
        printf("3. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                createAccount();
                break;
            case 3:
                printf("Thank you for using the Comprehensive ATM System.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
