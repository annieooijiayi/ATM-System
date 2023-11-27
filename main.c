#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkBalance(FILE *file, const char *today){

}

void withdrawal(FILE *file, const char *today){
    int amount;

    printf("Enter the amount that you wish to withdraw: ");

    while(scanf("%d", &amount) != 1 || amount <= 0){
        printf("Invalid amount. Please try again with positive numbers.\n");
        printf("Enter the amount that you wish to withdraw: ");
    }
}

void deposit(FILE *file, const char *today){
    int amount;
    printf("Enter the amount that you wish to deposit: ");

    while(scanf("%d", &amount) != 1 || amount <= 0){
        printf("Invalid amount. Please try again with positive numbers.\n");
        printf("Enter the amount that you wish to deposit: ");
    }

    fprintf(file, "%s \t Deposit \t %d\n", today, amount);


}

int main()
{
    int pin = 123456, inputPin, count = 0, continueTrans = 1, option;
    FILE *file;
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

    file = fopen("Balance.txt", "a");
    if (file == NULL){
        file =  fopen("Balance.txt", "w");
        if (file == NULL){
            printf("Error opening the file. \n");
            return 1;
        }
    }

    switch (option){
    case 1:
        checkBalance(file, today);
        break;

    case 2:
        withdrawal(file, today);
        break;

    case 3:
        deposit(file, today);
        break;

    }
    fclose(file);

return 0;




}
