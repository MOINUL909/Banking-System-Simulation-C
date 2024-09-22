#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define USERNAME "Moinul"
#define PASSWORD "Moinul909"

// Structure to hold account information
typedef struct {
    char name[50];
    char pin[5];
    float balance;
    char transaction_history[100][100]; // Store transaction history
    int transaction_count;
    int account_no; // Account number
} Account;

// Function prototypes
int login();
void create_account(Account accounts[], int *account_count);
void deposit(Account *account);
void withdraw(Account *account);
void transfer(Account accounts[], int account_count, Account *account);
void view_balance(Account *account);
void view_transaction_history(Account *account);
int get_account_index(Account accounts[], int account_count, int account_no);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int account_count = 0;

    // User login
    if (login() == -1) {
        printf("Login failed!\n");
        return 1;
    }

    int choice;
    do {
        printf("\nBanking System Menu\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Funds\n");
        printf("5. View Balance\n");
        printf("6. View Transaction History\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_account(accounts, &account_count); break;
            case 2: {
                int account_no;
                printf("Enter account number: ");
                scanf("%d", &account_no);
                int index = get_account_index(accounts, account_count, account_no);
                if (index != -1) {
                    deposit(&accounts[index]);
                } else {
                    printf("Account not found.\n");
                }
                break;
            }
            case 3: {
                int account_no;
                printf("Enter account number: ");
                scanf("%d", &account_no);
                int index = get_account_index(accounts, account_count, account_no);
                if (index != -1) {
                    withdraw(&accounts[index]);
                } else {
                    printf("Account not found.\n");
                }
                break;
            }
            case 4: {
                int account_no;
                printf("Enter your account number: ");
                scanf("%d", &account_no);
                int index = get_account_index(accounts, account_count, account_no);
                if (index != -1) {
                    transfer(accounts, account_count, &accounts[index]);
                } else {
                    printf("Account not found.\n");
                }
                break;
            }
            case 5: {
                int account_no;
                printf("Enter account number: ");
                scanf("%d", &account_no);
                int index = get_account_index(accounts, account_count, account_no);
                if (index != -1) {
                    view_balance(&accounts[index]);
                } else {
                    printf("Account not found.\n");
                }
                break;
            }
            case 6: {
                int account_no;
                printf("Enter account number: ");
                scanf("%d", &account_no);
                int index = get_account_index(accounts, account_count, account_no);
                if (index != -1) {
                    view_transaction_history(&accounts[index]);
                } else {
                    printf("Account not found.\n");
                }
                break;
            }
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Login function
int login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 0; // Successful login
    }
    return -1; // Failed login
}

// Create a new account
void create_account(Account accounts[], int *account_count) {
    if (*account_count >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached.\n");
        return;
    }

    Account new_account;
    printf("Enter account holder's name: ");
    scanf(" %[^\n]", new_account.name);
    printf("Set a 4-digit PIN: ");
    scanf("%s", new_account.pin);
    new_account.balance = 0.0;
    new_account.transaction_count = 0;
    new_account.account_no = *account_count + 1000; // Generate account number starting from 1000
    accounts[*account_count] = new_account;
    printf("Account created successfully! Your account number is: %d\n", new_account.account_no);
    (*account_count)++;
}

// Deposit money into the account
void deposit(Account *account) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount > 0) {
        account->balance += amount;
        sprintf(account->transaction_history[account->transaction_count++], "Deposited: %.2f", amount);
        printf("Deposit successful! New balance: %.2f\n", account->balance);
    } else {
        printf("Invalid amount.\n");
    }
}

// Withdraw money from the account
void withdraw(Account *account) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        sprintf(account->transaction_history[account->transaction_count++], "Withdrew: %.2f", amount);
        printf("Withdrawal successful! New balance: %.2f\n", account->balance);
    } else {
        printf("Invalid amount or insufficient funds.\n");
    }
}

// Transfer funds to another account
void transfer(Account accounts[], int account_count, Account *account) {
    int target_account_no;
    float amount;
    printf("Enter target account number: ");
    scanf("%d", &target_account_no);
    int target_index = get_account_index(accounts, account_count, target_account_no);

    if (target_index != -1) {
        printf("Enter amount to transfer: ");
        scanf("%f", &amount);
        if (amount > 0 && amount <= account->balance) {
            account->balance -= amount;
            accounts[target_index].balance += amount;
            sprintf(account->transaction_history[account->transaction_count++], "Transferred: %.2f to account %d", amount, target_account_no);
            sprintf(accounts[target_index].transaction_history[accounts[target_index].transaction_count++], "Received: %.2f from account %d", amount, account->account_no);
            printf("Transfer successful! New balance: %.2f\n", account->balance);
        } else {
            printf("Invalid amount or insufficient funds.\n");
        }
    } else {
        printf("Target account not found.\n");
    }
}

// View account balance
void view_balance(Account *account) {
    printf("Current balance for %s (Account No: %d): %.2f\n", account->name, account->account_no, account->balance);
}

// View transaction history
void view_transaction_history(Account *account) {
    printf("Transaction history for %s (Account No: %d):\n", account->name, account->account_no);
    for (int i = 0; i < account->transaction_count; i++) {
        printf("%s\n", account->transaction_history[i]);
    }
}

// Get account index based on account number
int get_account_index(Account accounts[], int account_count, int account_no) {
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_no == account_no) {
            return i;
        }
    }
    return -1; // Account not found
}
