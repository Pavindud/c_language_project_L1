#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "payable.c"
#include "income.c"
#include "SSCL.c"
#include "withholding_tax.c"
#include "lease.c"


#define MAX 20

int main() {
    int choice;

    do {
        printf("\n========================================\n");
        printf("   SRI LANKA TAX & LEASING CALCULATOR  \n");
        printf("========================================\n");
        printf(" [1] Withholding Tax\n");
        printf(" [2] Payable Tax\n");
        printf(" [3] Income Tax\n");
        printf(" [4] SSCL Tax\n");
        printf(" [5] Leasing Payment\n");
        printf(" [6] Exit\n");
        printf("========================================\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
				   displayWithholdingMenu(); 
				   break;
            case 2: 
				   displayPayableMenu();    
				   break;
            case 3: 
				   displayIncomeMenu();      
				   break;
            case 4: 
				   displaySSCLMenu(); 
				   break;
            case 5: 
				   displayLeasingMenu();
				   break;
            case 6:
                printf("\n Exiting... Goodbye!\n\n");
                break;
            default:
                printf("\n Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
