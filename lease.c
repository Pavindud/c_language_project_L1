
struct LeasingPayment{
    char customer_name[50];
    char vehicle_type[40];
    char plan_label[20];
    double lease_amount;
    double annual_rate;
    int year;
    double monthly_installment;
};

double calculateMonthlyInstallment(double , double , int);
double findLeasingAmount(double , double , int);
int  validateYearInput(int *yr , int min_year , int max_year);
void searchLeasingCategory(struct LeasingPayment *records[], int count , char search_label[]);
void searchVehicleType(struct LeasingPayment *records[], int count , char vehicle_type[]);
void saveLeasingRecord(struct LeasingPayment *records[], int *count , char name[] , char v_type[] , char plan[] , double amount , double rate , int yrs);
void  displayAllLeasingRecords(struct LeasingPayment *records[], int count);

double calculateMonthlyInstallment(double lease_amount , double annual_rate , int years){
        double r , power , installment;
        int n;
        r = annual_rate/12;
        n = years*12;
        power = pow(r+1 , n);
        installment = lease_amount * r * power / (power - 1);
        return installment;
}
double findLeasingAmount(double monthly_installment , double annual_rate , int years){
        double r , power , principle;
        int n;
        r = annual_rate/12;
        n = years*12;
        power = pow(r+1 , n);
        principle  = monthly_installment * (power-1)/(power*r);
        return principle;
}

int validateYearInput(int *yr, int min_year, int max_year) {
    if (*yr >= min_year && *yr <= max_year) {
        return 1;
    } else {
        printf("Invalid year! Please enter a value between %d and %d.\n", min_year, max_year);
        return 0;
    }
}

void searchLeasingCategory(struct LeasingPayment *records[], int count, char search_label[]) {
    int i = 0;
    char upper_label[20];
    char upper_plan[20];
    int cmp_result;

    for (int j = 0; search_label[j]; j++) {
        upper_label[j] = toupper(search_label[j]);
    }
    upper_label[strlen(search_label)] = '\0';

    while (i < count) {
        for (int k = 0; records[i]->plan_label[k]; k++) {
            upper_plan[k] = toupper(records[i]->plan_label[k]);
        }
        upper_plan[strlen(records[i]->plan_label)] = '\0';

        cmp_result = strcmp(upper_plan, upper_label);
        if (cmp_result == 0) {
            printf("Customer Name: %s\n", records[i]->customer_name);
            printf("Plan: %s\n", records[i]->plan_label);
            printf("Monthly Installment: %.2lf\n", records[i]->monthly_installment);
        }
        i++;
    }
}

void searchVehicleType(struct LeasingPayment *records[], int count, char vehicle_type[]) {
    int i = 0;
    int cmp_result;
    char upper_type[40];
    char upper_vehicle[40];

    for (int j = 0; vehicle_type[j]; j++) {
        upper_type[j] = toupper(vehicle_type[j]);
    }
    upper_type[strlen(vehicle_type)] = '\0';

    while (i < count) {
        for (int k = 0; records[i]->vehicle_type[k]; k++) {
            upper_vehicle[k] = toupper(records[i]->vehicle_type[k]);
        }
        upper_vehicle[strlen(records[i]->vehicle_type)] = '\0';

        cmp_result = strcmp(upper_vehicle, upper_type);
        if (cmp_result == 0) {
            printf("Customer Name: %s\n", records[i]->customer_name);
            printf("Vehicle Type: %s\n", records[i]->vehicle_type);
            printf("Monthly Installment: %.2lf\n", records[i]->monthly_installment);
        }
        i++;
    }
}

void saveLeasingRecord(struct LeasingPayment *records[], int *count, char name[], char v_type[], char plan[], double amount, double rate, int yrs) {
    int idx;
    char temp_label[20];

    if (*count == 20) {
        printf("Array Full. Cannot add more records.\n");
        return;
    } else {
        idx = *count;

        strcpy(records[idx]->customer_name, name);
        strcpy(records[idx]->vehicle_type, v_type);

        strcpy(temp_label, plan);
        strcat(temp_label, "-year plan");
        strcpy(records[idx]->plan_label, temp_label);

        records[idx]->lease_amount = amount;
        records[idx]->annual_rate = rate;
        records[idx]->year = yrs;

        records[idx]->monthly_installment = calculateMonthlyInstallment(amount, rate, yrs);

        (*count)++;
    }
}

void  displayAllLeasingRecords(struct LeasingPayment *records[], int count){
    int i=0;
    char buffer[300];
    while (i < count){
        sprintf(buffer , "Customer Name: %s\nVehicle Type: %s\nPlan: %s\nLease Amount: %.2lf\nAnnual Rate: %.2lf\nYears: %d\nMonthly Installment: %.2lf\n", records[i]->customer_name , records[i]->vehicle_type , records[i]->plan_label , records[i]->lease_amount , records[i]->annual_rate , records[i]->year , records[i]->monthly_installment);
        printf("%s\n", buffer);
        i++;
    }
}

int main() {
    struct LeasingPayment storage[20];
    struct LeasingPayment *records[20];
    int count = 0;
    int choice;

    for (int i = 0; i < 20; i++) {
        records[i] = &storage[i];
    }

    do {
        printf("\n===== Leasing Payment Module =====\n");
        printf("1. Add Leasing Record\n");
        printf("2. Display All Records\n");
        printf("3. Search by Leasing Category\n");
        printf("4. Search by Vehicle Type\n");
        printf("5. Find Leasing Amount (Reverse)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char name[50], v_type[40], plan[20];
            double amount, rate;
            int yrs;

            printf("Enter Customer Name: ");
            scanf(" %[^\n]", name);

            printf("Enter Vehicle Type (Car/Van/Bike): ");
            scanf(" %s", v_type);

            printf("Enter Lease Amount: ");
            scanf("%lf", &amount);

            printf("Enter Annual Rate (e.g. 0.12 for 12%%): ");
            scanf("%lf", &rate);

            printf("Enter Lease Years (1-7): ");
            scanf("%d", &yrs);

            if (validateYearInput(&yrs, 1, 7)) {
                sprintf(plan, "%d", yrs);
                saveLeasingRecord(records, &count, name, v_type, plan, amount, rate, yrs);
                printf("Record saved successfully!\n");
            } else {
                printf("Record not saved. Invalid year.\n");
            }

        } else if (choice == 2) {
            if (count == 0) {
                printf("No records found.\n");
            } else {
                displayAllLeasingRecords(records, count);
            }

        } else if (choice == 3) {
            char search_label[20];
            printf("Enter Plan Label to search (e.g. 3-year plan): ");
            scanf(" %[^\n]", search_label);
            searchLeasingCategory(records, count, search_label);

        } else if (choice == 4) {
            char vehicle_type[40];
            printf("Enter Vehicle Type to search (Car/Van/Bike): ");
            scanf(" %s", vehicle_type);
            searchVehicleType(records, count, vehicle_type);

        } else if (choice == 5) {
            double monthly, rate;
            int yrs;

            printf("Enter Desired Monthly Installment: ");
            scanf("%lf", &monthly);

            printf("Enter Annual Rate (e.g. 0.12 for 12%%): ");
            scanf("%lf", &rate);

            printf("Enter Lease Years (1-7): ");
            scanf("%d", &yrs);

            if (validateYearInput(&yrs, 1, 7)) {
                double principal = findLeasingAmount(monthly, rate, yrs);
                printf("Maximum Lease Amount you can afford: %.2lf\n", principal);
            }

        } else if (choice == 6) {
            printf("Exiting program. Goodbye!\n");

        } else {
            printf("Invalid choice. Please enter 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
