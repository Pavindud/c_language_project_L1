#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct PayableTax {
    char employee_name[50];
    char department[40];
    char emp_id[12];
    double monthly_salary;
    double epf_amount;       
    double tax_amount;
    double net_salary;       //salary after EPF and tax 
    char bracket_label[30];
};

struct PayableTax records[20];
int recordCount = 0;

void validateSalaryInput(double *salary) {
    do {
        printf(" Enter Monthly Salary (Rs.): ");
        scanf("%lf", salary);

        if (*salary <= 0) {
            printf("\nInvalid! Salary must be greater than 0. Try again.\n");
        }

    } while (*salary <= 0);
}

void getBracketLabel(double salary, char *label) {
    if (salary <= 150000) {
        strcpy(label, "No Tax");
    } 
    else {
        double taxable = salary - 150000;  // monthly taxable amount 

        if (taxable <= 83333) {
            strcpy(label, "6% Bracket");
        }
        else if (taxable <= 125000) {
            strcpy(label, "18% Bracket");
        }
        else if (taxable <= 166667) {
            strcpy(label, "24% Bracket");
        }
        else if (taxable <= 208333) {
            strcpy(label, "30% Bracket");
        }
        else {
            strcpy(label, "36% Bracket");
        }
    }
}

void calculatePayableTax(char name[], char dept[], char id[], 
    
    double salary, double *epf, 
    double *tax, double *net) {
    double taxable;
    *epf = salary * 0.08;

    if (salary <= 150000) {
        *tax = 0.0;
    }
    else {
        taxable = salary - 150000;

        if (taxable <= 83333) {
            *tax = taxable * 0.06;
        } else if (taxable <= 125000) {
            *tax = (83333 * 0.06) + ((taxable - 83333) * 0.18);
        } else if (taxable <= 166667) {
            *tax = (83333 * 0.06) + (41667 * 0.18) + ((taxable - 125000) * 0.24);
        } else if (taxable <= 208333) {
            *tax = (83333 * 0.06) + (41667 * 0.18) + (41667 * 0.24) + ((taxable - 166667) * 0.30);
        } else {
            *tax = (83333 * 0.06) + (41667 * 0.18) + (41667 * 0.24) + (41667 * 0.30) + ((taxable - 208333) * 0.36);
        }
    }

    *net = salary - *epf - *tax;
}

void savePayableRecord(char name[], char dept[], char id[], 
                        double salary, double epf, 
                        double tax, double net) {
                            
    if (recordCount >= 20) {
        printf("\nStorage full! Cannot save more records.\n");
        return;
    }

    //store strings into the struct
    strcpy(records[recordCount].employee_name, name);
    strcpy(records[recordCount].department, dept);
    strcpy(records[recordCount].emp_id, id);

    //Store numeric values
    records[recordCount].monthly_salary = salary;
    records[recordCount].epf_amount     = epf;
    records[recordCount].tax_amount     = tax;
    records[recordCount].net_salary     = net;

    //Get and store bracket label
    getBracketLabel(salary, records[recordCount].bracket_label);

    recordCount++;

    printf("\nRecord saved successfully!\n");
}

void searchByDepartment() {
    char search_dept[40];
    char upper_input[40];
    char upper_stored[40];
    int found = 0;
    int i, j;

    if (recordCount == 0) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n Enter Department to Search: ");
    scanf(" %[^\n]", search_dept);

    // Convert input to uppercase for case-insensitive search
    for (i = 0; search_dept[i]; i++) {
        upper_input[i] = toupper(search_dept[i]);
    }
    upper_input[i] = '\0';

    printf("\n========================================\n");
    printf(" Search Results — Department: %s\n", upper_input);
    printf("========================================\n");

    for (i = 0; i < recordCount; i++) {

        //Convert stored department to uppercase 
        for (j = 0; records[i].department[j]; j++) {
            upper_stored[j] = toupper(records[i].department[j]);
        }
        upper_stored[j] = '\0';

        // Compare using strcmp
        if (strcmp(upper_input, upper_stored) == 0) {
            printf(" Name       : %s\n", records[i].employee_name);
            printf(" Emp ID     : %s\n", records[i].emp_id);
            printf(" Salary     : Rs. %.2f\n", records[i].monthly_salary);
            printf(" EPF (8%%)   : Rs. %.2f\n", records[i].epf_amount);
            printf(" Tax        : Rs. %.2f\n", records[i].tax_amount);
            printf(" Net Salary : Rs. %.2f\n", records[i].net_salary);
            printf(" Bracket    : %s\n", records[i].bracket_label);
            printf("----------------------------------------\n");
            found++;
        }
    }

    if (found == 0) {
        printf(" No employees found in department: %s\n", upper_input);
    } else {
        printf(" Total found: %d employee(s)\n", found);
    }
}

void sortRecordsBySalary() {
    int i, j;
    struct PayableTax temp;

    if (recordCount == 0) {
        printf("\nNo records to sort!\n");
        return;
    }

    // Bubble sort
    for (i = 0; i < recordCount - 1; i++) {
        for (j = 0; j < recordCount - i - 1; j++) {
            if (records[j].monthly_salary > records[j + 1].monthly_salary) {

                // Swap entire structs
                temp            = records[j];
                records[j]      = records[j + 1];
                records[j + 1]  = temp;
            }
        }
    }

    printf("\nRecords sorted by salary (lowest to highest)!\n");
    printf(" Use 'Display All Employees' to view sorted list.\n");
}

void displayAllEmployees() {
    int i;
    if (recordCount == 0) {
        printf("\n No records found!\n");
        return;
    }
    printf("\n========================================\n");
    printf("       ALL EMPLOYEE TAX RECORDS         \n");
    printf("========================================\n");
    printf(" Total Records: %d\n", recordCount);
    printf("========================================\n");
    for (i = 0; i < recordCount; i++) {
        printf("\n Record #%d\n", i + 1);
        printf(" ----------------------------------------\n");
        printf(" Name        : %s\n",        records[i].employee_name);
        printf(" Emp ID      : %s\n",        records[i].emp_id);
        printf(" Department  : %s\n",        records[i].department);
        printf(" Salary      : Rs. %.2f\n",  records[i].monthly_salary);
        printf(" EPF (8%%)    : Rs. %.2f\n", records[i].epf_amount);
        printf(" Tax         : Rs. %.2f\n",  records[i].tax_amount);
        printf(" Net Salary  : Rs. %.2f\n",  records[i].net_salary);
        printf(" Bracket     : %s\n",        records[i].bracket_label);
        printf(" ----------------------------------------\n");
    }
}

void displayPayableMenu() {

    int choice;
    char name[50];
    char dept[40];
    char id[12];
    double salary, epf, tax, net;
    char confirm[5];

    do {
        printf("\n========================================\n");
        printf("         PAYABLE TAX CALCULATOR         \n");
        printf("========================================\n");
        printf(" [1] Calculate Employee Tax\n");
        printf(" [2] Search by Department\n");
        printf(" [3] Sort Records by Salary\n");
        printf(" [4] Display All Employees\n");
        printf(" [5] Back to Main Menu\n");
        printf("========================================\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\n========================================\n");
                printf("       EMPLOYEE TAX CALCULATION         \n");
                printf("========================================\n");

                // Get employee details
                printf(" Enter Employee Name : ");
                scanf(" %[^\n]", name);

                printf(" Enter Department    : ");
                scanf(" %[^\n]", dept);

                printf(" Enter Employee ID   : ");
                scanf(" %s", id);

                //Validate salary
                validateSalaryInput(&salary);

                // Calculate tax and EPF
                calculatePayableTax(name   , dept, id, salary, &epf, &tax, &net);

                // Display results
                printf("\n========================================\n");
                printf("            TAX SUMMARY                 \n");
                printf("========================================\n");
                printf(" Name        : %s\n", name);
                printf(" Emp ID      : %s\n", id);
                printf(" Department  : %s\n", dept);
                printf(" Gross Salary: Rs. %.2f\n", salary);
                printf(" EPF (8%%)    : Rs. %.2f\n", epf);
                printf(" Tax Amount  : Rs. %.2f\n", tax);
                printf(" Net Salary  : Rs. %.2f\n", net);
                printf(" Bracket     : ");

                // Get and print bracket label
                char label[30];
                getBracketLabel(salary, label);
                printf("%s\n", label);
                printf("========================================\n");

                // Ask to save
                printf(" Save this record? (Y/N): ");
                scanf(" %s", confirm);

                if (toupper(confirm[0]) == 'Y') {
                    savePayableRecord(name, dept, id, salary, epf, tax, net);
                } else {
                    printf(" Record not saved.\n");
                }
                break;

            case 2:
                searchByDepartment();
                break;

            case 3:
                sortRecordsBySalary();
                break;

            case 4:
                displayAllEmployees();
                break;

            case 5:
                printf("\n Returning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 5);
}
