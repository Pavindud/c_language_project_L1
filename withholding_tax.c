#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS  20
#define RENT_THRESH  100000.0
#define DIV_THRESH   100000.0
#define RENT_RATE    0.10
#define BANK_RATE    0.05
#define DIV_RATE     0.14

struct WithholdingTax {
    char   taxpayer_name[50];
    char   tax_type[30];
    char   nic[15];
    double amount;
    double tax_due;
    char   status[20];
};

struct WithholdingTax whtRecords[MAX_RECORDS];
int whtCount = 0;

double validatePositiveInput(const char *prompt) {
    double value;
    printf("%s", prompt);
    scanf("%lf", &value);

    if (value <= 0) {
        printf("\n\t  Invalid input. Value must be greater than 0.\n");
        printf("\tDo you want to enter the correct value again (Y/N): ");

        char choice[5];
        scanf("%s", choice);

        if (toupper(choice[0]) == 'Y') {
            return validatePositiveInput(prompt);
        } else {
            return -1;
        }
    }
    return value;
}

char validateYesNo(const char *prompt) {
    char input[5];
    printf("%s", prompt);
    scanf("%s", input);

    char upper = toupper(input[0]);

    if (upper == 'Y' || upper == 'N') {
        return upper;
    }

    printf("\t  Invalid input. Please enter Y or N.\n");
    return validateYesNo(prompt);
}

void displayRecordsRecursive(int i) {
    if (i >= whtCount) return;

    printf("\n  Record #%d\n", i + 1);
    printf("  %-20s : %s\n",       "Taxpayer Name", whtRecords[i].taxpayer_name);
    printf("  %-20s : %s\n",       "NIC",           whtRecords[i].nic);
    printf("  %-20s : %s\n",       "Tax Type",      whtRecords[i].tax_type);
    printf("  %-20s : Rs. %.2f\n", "Amount",        whtRecords[i].amount);
    printf("  %-20s : Rs. %.2f\n", "Tax Due",       whtRecords[i].tax_due);
    printf("  %-20s : %s\n",       "Status",        whtRecords[i].status);
    printf("  %s\n", "- - - - - - - - - - - - - - - - - - - -");

    displayRecordsRecursive(i + 1);
}

void printWHTHeader(const char *title) {
    printf("\n+----------------------------------------------------------------+\n");
    char line[70];
    sprintf(line, "| %-62s |", title);
    printf("%s\n", line);
    printf("+----------------------------------------------------------------+\n");
}

void saveWithholdingRecord(const char *name, const char *nic,
                           const char *type, double amount,
                           double tax, const char *status) {
    if (whtCount >= MAX_RECORDS) {
        printf("\n\t  Record limit reached. Cannot save more records.\n");
        return;
    }

    strcpy(whtRecords[whtCount].taxpayer_name, name);
    strcpy(whtRecords[whtCount].nic,           nic);
    strcpy(whtRecords[whtCount].tax_type,      type);
    strcpy(whtRecords[whtCount].status,        status);

    whtRecords[whtCount].amount  = amount;
    whtRecords[whtCount].tax_due = tax;

    whtCount++;
    printf("\n\t  Record saved successfully. (Total records: %d)\n", whtCount);
}

void calculateRentTax() {
    printWHTHeader("RENT TAX");

    char name[50], nic[15];
    char again;

    do {
        printf("\n  Enter taxpayer name        : ");
        scanf(" %[^\n]", name);

        if (strlen(name) == 0) {
            printf("\t  Name cannot be empty.\n");
            continue;
        }

        printf("  Enter NIC number           : ");
        scanf("%s", nic);

        double amount = validatePositiveInput("  Enter your rent amount      : Rs. ");

        if (amount == -1) {
            printf("\n\t  Calculation cancelled.\n");
        } else {
            double tax = 0.0;
            char status[20];

            if (amount <= RENT_THRESH) {
                printf("\n\t  You don't have to pay Rent Tax...\n");
                strcpy(status, "Exempt");
            } else {
                tax = amount * RENT_RATE;

                char result[100] = "You have to pay Rent Tax : Rs. ";
                char taxStr[20];
                sprintf(taxStr, "%.2f", tax);
                strcat(result, taxStr);
                printf("\n  %s\n", result);
                strcpy(status, "Taxable");
            }

            saveWithholdingRecord(name, nic, "Rent", amount, tax, status);
        }

        again = validateYesNo("\n  Do you want to calculate another Rent Tax (Y/N): ");

    } while (again == 'Y');
}

void calculateBankTax() {
    printWHTHeader("BANK INTEREST TAX");

    char name[50], nic[15];
    char again;

    do {
        printf("\n  Enter taxpayer name              : ");
        scanf(" %[^\n]", name);

        if (strlen(name) == 0) {
            printf("\t  Name cannot be empty.\n");
            continue;
        }

        printf("  Enter NIC number                 : ");
        scanf("%s", nic);

        double interest = validatePositiveInput("  Enter your bank interest per year: Rs. ");

        if (interest == -1) {
            printf("\n\t  Calculation cancelled.\n");
        } else {
            double tax = interest * BANK_RATE;

            char output[100];
            sprintf(output, "  You have to pay Bank Interest Tax per year : Rs. %.2f", tax);
            printf("\n%s\n", output);

            saveWithholdingRecord(name, nic, "Bank Interest", interest, tax, "Taxable");
        }

        again = validateYesNo("\n  Do you want to calculate another Bank Interest Tax (Y/N): ");

    } while (again == 'Y');
}

void calculateDividendTax() {
    printWHTHeader("DIVIDEND TAX");

    char name[50], nic[15];
    char again;

    do {
        printf("\n  Enter taxpayer name              : ");
        scanf(" %[^\n]", name);

        if (strlen(name) == 0) {
            printf("\t  Name cannot be empty.\n");
            continue;
        }

        printf("  Enter NIC number                 : ");
        scanf("%s", nic);

        double dividend = validatePositiveInput("  Enter your total dividend per year: Rs. ");

        if (dividend == -1) {
            printf("\n\t  Calculation cancelled.\n");
        } else {
            double tax = 0.0;
            char status[20];

            if (dividend <= DIV_THRESH) {
                printf("\n\t  You don't have to pay Dividend Tax...\n");
                strcpy(status, "Exempt");
            } else {
                tax = dividend * DIV_RATE;

                char result[100] = "You have to pay Dividend Tax per year : Rs. ";
                char taxStr[20];
                sprintf(taxStr, "%.2f", tax);
                strcat(result, taxStr);
                printf("\n  %s\n", result);
                strcpy(status, "Taxable");
            }

            saveWithholdingRecord(name, nic, "Dividend", dividend, tax, status);
        }

        again = validateYesNo("\n  Do you want to calculate another Dividend Tax (Y/N): ");

    } while (again == 'Y');
}

void viewAllWHTRecords() {
    printWHTHeader("ALL WITHHOLDING TAX RECORDS");

    if (whtCount == 0) {
        printf("\n\t  No records saved yet.\n");
        return;
    }

    printf("\n  Total records: %d\n", whtCount);
    printf("  %s\n", "- - - - - - - - - - - - - - - - - - - -");

    displayRecordsRecursive(0);
}

void searchByTaxpayerName() {
    printWHTHeader("SEARCH BY TAXPAYER NAME");

    if (whtCount == 0) {
        printf("\n\t  No records to search.\n");
        return;
    }

    char searchName[50];
    printf("\n  Enter taxpayer name to search : ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    int i;

    for (i = 0; i < whtCount; i++) {
        if (strcmp(whtRecords[i].taxpayer_name, searchName) == 0) {
            if (!found) {
                printf("\n  Results found:\n");
                printf("  %s\n", "- - - - - - - - - - - - - - - - - - - -");
            }
            printf("\n  Record #%d\n", i + 1);
            printf("  %-20s : %s\n",       "Taxpayer Name", whtRecords[i].taxpayer_name);
            printf("  %-20s : %s\n",       "NIC",           whtRecords[i].nic);
            printf("  %-20s : %s\n",       "Tax Type",      whtRecords[i].tax_type);
            printf("  %-20s : Rs. %.2f\n", "Amount",        whtRecords[i].amount);
            printf("  %-20s : Rs. %.2f\n", "Tax Due",       whtRecords[i].tax_due);
            printf("  %-20s : %s\n",       "Status",        whtRecords[i].status);
            printf("  %s\n", "- - - - - - - - - - - - - - - - - - - -");
            found = 1;
        }
    }

    if (!found) {
        char msg[100] = "No records found for: ";
        strncat(msg, searchName, 30);
        printf("\n\t  %s\n", msg);
    }
}

void displayWithholdingMenu() {
    int option;

    do {
        printf("\n+----------------------------------------------------------------+\n");
        printf("|                      WITHHOLDING TAX                          |\n");
        printf("+----------------------------------------------------------------+\n");
        printf("\n\t [1] Rent Tax");
        printf("\n\t [2] Bank Interest Tax");
        printf("\n\t [3] Dividend Tax");
        printf("\n\t [4] View All Records");
        printf("\n\t [5] Search by Taxpayer Name");
        printf("\n\t [6] Exit to Main Menu");
        printf("\n\n  Enter an option to continue -> ");
        scanf("%d", &option);

        switch (option) {
            case 1: calculateRentTax();       break;
            case 2: calculateBankTax();       break;
            case 3: calculateDividendTax();   break;
            case 4: viewAllWHTRecords();      break;
            case 5: searchByTaxpayerName();   break;
            case 6: printf("\n\t  Returning to Main Menu...\n"); break;
            default: printf("\n\t  Invalid option. Please enter 1-6.\n");
        }

    } while (option != 6);
}
