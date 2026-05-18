

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct clientData
{
    int acctNum;
    char name[30];
    double balance;
};

void addAccount(FILE *fp);
void display(FILE *fp);
void deposit(FILE *fp);
void withdraw(FILE *fp);
void search(FILE *fp);
void deleteAccount(FILE *fp);

int main()
{
    FILE *fp;
    int choice;

    struct clientData blank = {0, "", 0};

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        fp = fopen("bank.dat", "wb");

        for (int i = 0; i < SIZE; i++)
            fwrite(&blank, sizeof(struct clientData), 1, fp);
    }

    fclose(fp);

    fp = fopen("bank.dat", "rb+");

    do
    {
        printf("\n===== BANK MANAGEMENT =====\n");
        printf("1. Add Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addAccount(fp);
            break;

        case 2:
            display(fp);
            break;

        case 3:
            deposit(fp);
            break;

        case 4:
            withdraw(fp);
            break;

        case 5:
            search(fp);
            break;

        case 6:
            deleteAccount(fp);
            break;

        case 7:
            printf("Program Ended.\n");
            break;

        default:
            printf("Invalid Choice!\n");
        }

    } while (choice != 7);

    fclose(fp);

    return 0;
}

void addAccount(FILE *fp)
{
    struct clientData c;

    printf("Enter Account Number: ");
    scanf("%d", &c.acctNum);

    printf("Enter Name: ");
    scanf("%s", c.name);

    printf("Enter Balance: ");
    scanf("%lf", &c.balance);

    fseek(fp, (c.acctNum - 1) * sizeof(struct clientData), SEEK_SET);

    fwrite(&c, sizeof(struct clientData), 1, fp);

    printf("Account Added Successfully.\n");
}


void display(FILE *fp)
{
    struct clientData c;

    rewind(fp);

    printf("\nAccNo\tName\tBalance\n");

    while (fread(&c, sizeof(struct clientData), 1, fp))
    {
        if (c.acctNum != 0)
        {
            printf("%d\t%s\t%.2lf\n",
                   c.acctNum,
                   c.name,
                   c.balance);
        }
    }
}

void deposit(FILE *fp)
{
    int acc;
    double amt;
    struct clientData c;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    fseek(fp, (acc - 1) * sizeof(struct clientData), SEEK_SET);

    fread(&c, sizeof(struct clientData), 1, fp);

    if (c.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%lf", &amt);

    c.balance += amt;

    fseek(fp, -sizeof(struct clientData), SEEK_CUR);

    fwrite(&c, sizeof(struct clientData), 1, fp);

    printf("Deposit Successful.\n");
}

void withdraw(FILE *fp)
{
    int acc;
    double amt;
    struct clientData c;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    fseek(fp, (acc - 1) * sizeof(struct clientData), SEEK_SET);

    fread(&c, sizeof(struct clientData), 1, fp);

    if (c.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%lf", &amt);

    if (amt > c.balance)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    c.balance -= amt;

    fseek(fp, -sizeof(struct clientData), SEEK_CUR);

    fwrite(&c, sizeof(struct clientData), 1, fp);

    printf("Withdrawal Successful.\n");
}

void search(FILE *fp)
{
    int acc;
    struct clientData c;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    fseek(fp, (acc - 1) * sizeof(struct clientData), SEEK_SET);

    fread(&c, sizeof(struct clientData), 1, fp);

    if (c.acctNum == 0)
    {
        printf("Account Not Found!\n");
    }
    else
    {
        printf("\nAccount Number : %d\n", c.acctNum);
        printf("Name           : %s\n", c.name);
        printf("Balance        : %.2lf\n", c.balance);
    }
}

void deleteAccount(FILE *fp)
{
    int acc;

    struct clientData blank = {0, "", 0};

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    fseek(fp, (acc - 1) * sizeof(struct clientData), SEEK_SET);

    fwrite(&blank, sizeof(struct clientData), 1, fp);

    printf("Account Deleted Successfully.\n");
}
