
#define VAT 0.18
#define SSCL 0.025

struct SSCL_Tax{
    char bsName[50];
    char goodCategory[50];
    int regNumber;
    double goodsValues;
    double salesTax;
    double vatAmount;
    double ssclAmount;
};

struct SSCL_Tax s[100];
int count=0;

//functions
double calculateSSCL(double, int);
double calculateVAT(double, double);
double calculateSaleTax(double, double);
void displayCal(struct SSCL_Tax record);
void displayAllBusinesses();
struct SSCL_Tax processCategory(struct SSCL_Tax r, const char *, int);
void filterByCategory();


int main(){
    int x,c;
    char ch;
    while(1==1){
        int cat1,cat2;
        printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_SSCL Tax Calculator_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        printf("\t\t 1.Calculate new tax\n");
        printf("\t\t 2.View saved records\n");
        printf("\t\t 3.Filter by Category\n");
        printf("\t\t 4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &cat2);
        switch(cat2){
        case 1:
            while(1==1){
                printf("Enter the business name: ");
                while ((c = getchar()) != '\n' && c != EOF);
                fgets(s[count].bsName, sizeof(s[count].bsName), stdin);
                s[count].bsName[strcspn(s[count].bsName, "\n")] = 0;
                printf("Enter the registration number: ");
                scanf("%d",&s[count].regNumber);
                printf("Enter the total sales for the year (Rs): ");
                scanf("%lf", &s[count].goodsValues);
                if(s[count].goodsValues<60000000){
                    printf("The sales amount does not exceed the taxable limit of Rs. 60,000,000.");
                    break;
                }
                printf("The business categories:\n");
                printf("\t\t 1.Importers\n");
                printf("\t\t 2.Manufacturers\n");
                printf("\t\t 3.Service Providers\n");
                printf("\t\t 4.Wholesalers and Retailers\n");
                printf("\t\t 5.Other\n");
                printf("Enter your category(1/2/3/4/5): ");
                scanf("%d", &cat1);
                switch(cat1){
                case 1:
                    s[count] = processCategory(s[count], "Importers", 100);
                    count++;
                    break;
                case 2:
                    s[count] = processCategory(s[count], "Manufacturers", 85);
                    count++;
                    break;
                case 3:
                    s[count] = processCategory(s[count], "Service Providers", 100);
                    count++;
                    break;
                case 4:
                    printf("Are you a distributor (Y/N)?: ");
                    scanf(" %c", &ch);
                    if(ch=='y'||ch=='Y'){
                        s[count] = processCategory(s[count], "Wholesalers and Retailers", 25);
                        count++;
                        break;
                    }else{
                        s[count] = processCategory(s[count], "Wholesalers and Retailers", 50);
                        count++;
                        break;
                    }
                case 5:
                default:
                    printf("SSCL tax does not apply to this category.\n");
                }
                printf("Do you want to calculate another tax?: \n");
                printf("\t\t 1.Yes\n");
                printf("\t\t 2.No\n");
                scanf("%d", &x);
                if(x==2){
                    break;
                }

            }
            break;
        case 2:
            displayAllBusinesses();
            break;
        case 3:
            filterByCategory();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid selection.\n");
            }
        }


return 0;
}

double calculateSSCL(double goodValues,int x){
    return (goodValues*x/100)*SSCL;
}

double calculateVAT(double goodValues, double sscl){
    return (goodValues+sscl)*VAT;
}

double calculateSaleTax(double sscl, double vat){
    return (sscl+vat);
}

void displayCal(struct SSCL_Tax record){
    printf("\n======================================================\n");
    printf("                SSCL TAX BREAKDOWN                    \n");
    printf("======================================================\n");
    printf("Business name:       %s\n", record.bsName);
    printf("Register number:      %d\n", record.regNumber);
    printf("Category:              %s\n\n", record.goodCategory);
    printf("1. Original Goods Value       : Rs. %.2lf\n", record.goodsValues);
    printf("2. SSCL Tax (2.5%%)            : Rs. %.2lf\n", record.ssclAmount);
    printf("3. VAT (18%%)                  : Rs. %.2lf\n", record.vatAmount);
    printf("------------------------------------------------------\n");
    printf("   TOTAL TAX PAYABLE         : Rs. %.2lf\n", record.salesTax);
    printf("======================================================\n\n");
}

void displayAllBusinesses(){
    printf("\n======================================================\n");
    printf("               ALL SAVED SSCL RECORDS                 \n");
    printf("======================================================\n");
    if(count==0){
        printf("No records found. Please calculate a tax first.\n");
        printf("======================================================\n\n");
    }else{
        for(int i=0; i<count; i++){
            printf("Record #%d\n", i + 1);
            printf("Business Name    : %s\n", s[i].bsName);
            printf("Register Number  : %d\n", s[i].regNumber);
            printf("Category         : %s\n", s[i].goodCategory);
            printf("Total SSCL Tax   : Rs. %.2lf\n", s[i].ssclAmount);
            printf("------------------------------------------------------\n");
        }

    }printf("\n");


}
struct SSCL_Tax processCategory(struct SSCL_Tax r, const char *categoryName, int percentage){
    strcpy(r.goodCategory, categoryName);
    r.ssclAmount = calculateSSCL(r.goodsValues,percentage);
    r.vatAmount = calculateVAT(r.goodsValues,r.ssclAmount);
    r.salesTax = calculateSaleTax(r.ssclAmount,r.vatAmount);
    displayCal(r);

    return r;

};

void filterByCategory() {
    char searchCategory[40];
    int found = 0,c;

    printf("\n======================================================\n");
    printf("                FILTER BY CATEGORY                    \n");
    printf("======================================================\n");

    if (count == 0) {
        printf("No records found. Please calculate a tax first.\n");
        printf("======================================================\n\n");
        return;
    }

    printf("Enter the category to search (e.g., Importers): ");
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(searchCategory, sizeof(searchCategory), stdin);
    searchCategory[strcspn(searchCategory, "\n")] = 0;

    printf("\n--- Search Results for '%s' ---\n", searchCategory);

    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].goodCategory, searchCategory) == 0) {
            printf("Business Name    : %s\n", s[i].bsName);
            printf("Register Number  : %d\n", s[i].regNumber);
            printf("Total Tax        : Rs. %.2lf\n", s[i].salesTax);
            printf("------------------------------------------------------\n");
            found = 1;
        }
    }

    if (found == 0) {
        printf("No businesses found in this category.\n");
    }
    printf("\n");
}

