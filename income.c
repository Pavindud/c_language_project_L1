#include <stdio.h>
#include <string.h>

#define PERSONAL_RELIEF 1800000.0
#define MAX 20
struct IncomeTax {
    char   taxpayer_name[50];
    char   tax_category[30];  
    char   nic[15];
    double annual_income;
    double tax_amount;
    int    tax_year;
};

struct IncomeTax records[MAX];
int recordCount = 0;

//convert character to uppercase 
char charToUpper(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

//check income input is valid
void validateIncomeInput(double *income) {
    do {
        printf("  Enter Annual Income (Rs.): ");
        scanf("%lf", income);
        if (*income <= 0)
            printf("\n  Invalid! Income must be greater than 0. Try again.\n");
    } while (*income <= 0);
}

//tax type labeling
void getBracketLabel(double annual_income, char *label) {
    double taxable = annual_income - PERSONAL_RELIEF;

    if      (taxable <= 0)       strcpy(label, "Tax Exempt");
    else if (taxable <= 1000000) strcpy(label, "Salaried (6%)");
    else if (taxable <= 1500000) strcpy(label, "Salaried (18%)");
    else if (taxable <= 2000000) strcpy(label, "Self-Employed (24%)");
    else if (taxable <= 2500000) strcpy(label, "Self-Employed (30%)");
    else                         strcpy(label, "Self-Employed (36%)");
}

//income tax calculation
double calculateIncomeTax(double annual_income) {
    double taxable = annual_income - PERSONAL_RELIEF;
    double tax     = 0.0;

    if (taxable <= 0) return 0.0;

    if (taxable <= 1000000) {
        tax = taxable * 0.06;
    } else if (taxable <= 1500000) {
        tax = (1000000 * 0.06) + ((taxable - 1000000) * 0.18);
    } else if (taxable <= 2000000) {
        tax = (1000000 * 0.06) + (500000 * 0.18) + ((taxable - 1500000) * 0.24);
    } else if (taxable <= 2500000) {
        tax = (1000000 * 0.06) + (500000 * 0.18) + (500000 * 0.24) + ((taxable - 2000000) * 0.30);
    } else {
        tax = (1000000 * 0.06) + (500000 * 0.18) + (500000 * 0.24) + (500000 * 0.30) + ((taxable - 2500000) * 0.36);
    }

    return tax;
}

//putting taxpayer record into global array
void saveIncomeRecord(char name[], char nic[], int year,
                      double income, double tax) {

    if (recordCount >= MAX) {
        printf("\n  Storage full! Cannot save more records.\n");
        return;
    }

    strcpy(records[recordCount].taxpayer_name, name);
    strncpy(records[recordCount].nic, nic, 14); 
    records[recordCount].nic[14] = '\0';

    records[recordCount].annual_income = income;
    records[recordCount].tax_amount    = tax;
    records[recordCount].tax_year      = year;

    getBracketLabel(income, records[recordCount].tax_category);

    recordCount++;
    printf("\n  Record saved successfully! Total records: %d\n", recordCount);
}

//search record
void searchByNIC() {
    char query[15], upper_query[15], upper_stored[15];
    int  found = 0, i, j;

    if (recordCount == 0) {
        printf("\n  No records found!\n");
        return;
    }

    printf("\n  Enter NIC to Search: ");
    scanf("%14s", query);

    if (strlen(query) < 9) {
        printf("\n  Invalid NIC! Must be at least 9 characters.\n");
        return;
    }
    for (i = 0; query[i]; i++) upper_query[i] = charToUpper(query[i]);
    upper_query[i] = '\0';

    printf("\n  ========================================\n");
    printf("   Search Results - NIC: %s\n", upper_query);
    printf("  ========================================\n");

    for (i = 0; i < recordCount; i++) {

        //convert stored NIC to uppercase
        for (j = 0; records[i].nic[j]; j++) upper_stored[j] = charToUpper(records[i].nic[j]);
        upper_stored[j] = '\0';

        if (strcmp(upper_query, upper_stored) == 0) {   //check if NIC matches
            printf("  Name        : %s\n",       records[i].taxpayer_name);
            printf("  NIC         : %s\n",       records[i].nic);
            printf("  Year        : %d\n",       records[i].tax_year);
            printf("  Gross Income: Rs. %.2f\n", records[i].annual_income);
            printf("  Relief      : Rs. %.2f\n", PERSONAL_RELIEF);
            printf("  Taxable     : Rs. %.2f\n", records[i].annual_income - PERSONAL_RELIEF);
            printf("  Tax Due     : Rs. %.2f\n", records[i].tax_amount);
            printf("  Bracket     : %s\n",       records[i].tax_category);
            printf("  ----------------------------------------\n");
            found++;
        }
    }

    if (found == 0)
        printf("  No record found for NIC: %s\n", upper_query);
    else
        printf("  Total found: %d record(s)\n", found);
}

//sort records by annual income
void sortByAnnualIncome() {
    int i, j;
    struct IncomeTax temp;

    if (recordCount == 0) {
        printf("\n  No records to sort!\n");
        return;
    }

    for (i = 0; i < recordCount - 1; i++) {
        for (j = 0; j < recordCount - i - 1; j++) {
            if (records[j].annual_income > records[j + 1].annual_income) {
                temp           = records[j];        /* swap records */
                records[j]     = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }

    printf("\n  Records sorted by income (lowest to highest)!\n");
    printf("  Use 'Display All Records' to view sorted list.\n");
}

//display all taxpayer records
void displayIncomeSummary() {
    int i;

    if (recordCount == 0) {
        printf("\n  No records found!\n");
        return;
    }

    printf("\n  ========================================\n");
    printf("        ALL INCOME TAX RECORDS           \n");
    printf("  ========================================\n");
    printf("  Total Records: %d\n", recordCount);
    printf("  ========================================\n");

    for (i = 0; i < recordCount; i++) {
        printf("\n  Record #%d\n", i + 1);
        printf("  ----------------------------------------\n");
        printf("  Name        : %s\n",       records[i].taxpayer_name);
        printf("  NIC         : %s\n",       records[i].nic);
        printf("  Year        : %d\n",       records[i].tax_year);
        printf("  Bracket     : %s\n",       records[i].tax_category);
        printf("  Gross Income: Rs. %.2f\n", records[i].annual_income);
        printf("  Relief      : Rs. %.2f\n", PERSONAL_RELIEF);
        printf("  Taxable     : Rs. %.2f\n", records[i].annual_income - PERSONAL_RELIEF);
        printf("  Tax Due     : Rs. %.2f\n", records[i].tax_amount);
        printf("  ----------------------------------------\n");
    }
}

//sub menu
void displayIncomeMenu() {
    int    choice;
    char   name[50], nic[15], confirm[5];
    int    year;
    double income, tax;
    char   label[30];

    do {
        printf("\n  ========================================\n");
        printf("          INCOME TAX CALCULATOR          \n");
        printf("  ========================================\n");
        printf("  [1] Calculate Income Tax\n");
        printf("  [2] Search by NIC\n");
        printf("  [3] Sort Records by Income\n");
        printf("  [4] Display All Records\n");
        printf("  [5] Back to Main Menu\n");
        printf("  ========================================\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\n  ========================================\n");
                printf("         INCOME TAX CALCULATION          \n");
                printf("  ========================================\n");

                printf("  Enter Taxpayer Name : ");
                scanf(" %49[^\n]", name);

                printf("  Enter NIC           : ");
                scanf("%14s", nic);

                printf("  Enter Tax Year      : ");
                scanf("%d", &year);

                validateIncomeInput(&income);       /* validate using pointer */

                tax = calculateIncomeTax(income);
                getBracketLabel(income, label);

                printf("\n  ========================================\n");
                printf("              TAX SUMMARY                \n");
                printf("  ========================================\n");
                printf("  Name        : %s\n",       name);
                printf("  NIC         : %s\n",       nic);
                printf("  Year        : %d\n",       year);
                printf("  Gross Income: Rs. %.2f\n", income);
                printf("  Relief      : Rs. %.2f\n", PERSONAL_RELIEF);
                printf("  Taxable     : Rs. %.2f\n", income - PERSONAL_RELIEF);
                printf("  Tax Due     : Rs. %.2f\n", tax);
                printf("  Bracket     : %s\n",       label);
                printf("  ========================================\n");

                printf("  Save this record? (Y/N): ");
                scanf(" %s", confirm);

                if (charToUpper(confirm[0]) == 'Y')
                    saveIncomeRecord(name, nic, year, income, tax);
                else
                    printf("  Record not saved.\n");
                break;

            case 2: searchByNIC();          break;
            case 3: sortByAnnualIncome();   break;
            case 4: displayIncomeSummary(); break;
            case 5: printf("\n  Returning to Main Menu...\n"); break;
            default: printf("\n  Invalid choice. Try again.\n");
        }

    } while (choice != 5);
}
