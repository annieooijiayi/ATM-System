#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkBalance(){
    FILE *file;
    file = fopen("Balance.txt", "r");
    if (file == NULL){
        file =  fopen("Balance.txt", "w");
        if (file == NULL){
            printf("Error opening the file. \n");
            return 1;
        }
    }

    rewind(file);

    int balance = 0, amount;
    char date[10];
    char type[20];

    while (fscanf(file, " %[^\t] \t %[^\t] \t %d", date, type, &amount) == 3) {
        balance += amount;
    }
    fclose(file);
    return balance;

}

void withdrawal(const char *today){
    int amount, balance;
    FILE *file;

    balance = checkBalance();

    file = fopen("Balance.txt", "a");
    if (file == NULL){
        file =  fopen("Balance.txt", "w");
        if (file == NULL){
            printf("Error opening the file. \n");
            return 1;
        }
    }

    printf("Enter the amount that you wish to withdraw: ");

    while (1){
        while (getchar() != '\n');

        if (scanf("%d", &amount) != 1 || amount <= 0){
            printf("Invalid amount. Please try again with positive numbers.\n");
            printf("Enter the amount that you wish to withdraw: ");
            continue;
        }

        if (amount > balance){
            printf("Insufficient balance. Please try again. \n");
            printf("Enter the amount that you wish to withdraw: ");
        }else{
            break;
        }
    }

    fprintf(file, "%s \t Withdrawal \t %d\n", today, -amount);
    printf("You have withdrawn RM %d.\n", amount);
    fclose(file);
}

void deposit(const char *today){
    int amount;
    FILE *file;

    file = fopen("Balance.txt", "a");
    if (file == NULL){
        file =  fopen("Balance.txt", "w");
        if (file == NULL){
            printf("Error opening the file. \n");
            return 1;
        }
    }

    printf("Enter the amount that you wish to deposit: ");

    while(scanf("%d", &amount) != 1 || amount <= 0){
        printf("Invalid amount. Please try again with positive numbers.\n");
        printf("Enter the amount that you wish to deposit: ");
    }

    fprintf(file, "%s \t Deposit \t %d\n", today, +amount);
    printf("You have deposited RM %d.\n", amount);
    fclose(file);

}

int main()
{
    int pin = 123456, inputPin, count = 0, continueTrans = 1, option, balance;
    time_t now;
    time(&now);

    time_t today_date = time(NULL);
    struct tm *local_time = localtime(&today_date);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", local_time);


    printf("\t\t\t\t                  %s\n",ctime(&now));
    printf("\t\t\t\t\t  =========== Welcome to ATM ===========\n");

    while (pin != inputPin){
        printf("Enter pin number: ");
        scanf("%d", &inputPin);

        if (inputPin != pin){
            printf("Invalid pin number. Please try again.\n");
        }

        count++;
        if (count == 3 && inputPin != pin){
            printf("Sorry, you have entered incorrect pin three times. Your account has been blocked.");
            exit(0);
        }
    }

    do {
        printf(" ===== Menu ===== \n");
        printf("[1] Check balance\n");
        printf("[2] Withdrawal\n");
        printf("[3] Deposit\n");
        printf("[4] Exit\n");
        printf("Please select an option: ");
        scanf("%d", &option);

        while(option < 1 || option > 4){
            printf("Invalid input. Please try again with 1, 2, 3 or 4.\n");
            printf("Please select an option: ");
            scanf("%d", &option);
        }

        switch (option){
        case 1:
            balance = checkBalance();
            printf("Your account balance: RM %d\n", balance);
            break;

        case 2:
            withdrawal(today);
            break;

        case 3:
            deposit(today);
            break;

        case 4:
            printf("See you next time!");
            break;

        }

    }while (option != 4);


return 0;




}
