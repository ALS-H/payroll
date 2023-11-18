#include <iostream>
#include <iomanip>

#define max 50

using namespace std;

class Payroll {
public:
    char name[20];
    int code;
    char designation[20];
    int exp;
    int age;
    int salary;
    char AnyLoan;

    int HRA;
    int PF;
    int tax;
    int MealAllowance;
    int TransportAllowance;
    int MedicalAllowance;
    int LoanBalance;
    int LoanDebit;
    int grosspay;
    int workingHours;
    int DA;

    virtual void calculateSalary() = 0;

    virtual void displayDetails() {
        cout << "Name: " << name << "\nCode: " << code << "\nDesignation: " << designation
             << "\nYears of Experience: " << exp << "\nAge: " << age << "\nSalary: " << salary << endl;
    }

    virtual void displayPayslip() = 0;

    virtual void getInput() = 0;
};

class Employee : public Payroll {
public:
    void calculateSalary() override {
        DA = 1.20 * salary;
        tax = 0.04 * salary;
        PF = 0.12 * salary;
        HRA = salary * 0.27;
        MealAllowance = 300;
        MedicalAllowance = 300;
        TransportAllowance = 300;
        LoanDebit = salary * 0.09;

        if (LoanDebit > LoanBalance) {
            LoanBalance = 0;
            LoanDebit = LoanBalance;
        }

        grosspay = (salary + MealAllowance + MedicalAllowance + TransportAllowance + HRA + DA) -
                   (PF + tax + LoanDebit);
    }

    void displayPayslip() override {
        cout << "\nEarnings :-\n";
        cout << "Basic Pay: " << salary << endl;
        cout << "HRA (27% of Basic): " << HRA << endl;
        cout << "DA (120% of Basic): " << DA << endl;
        cout << "Meal Allowance: " << MealAllowance << endl;
        cout << "Medical Allowance: " << MedicalAllowance << endl;
        cout << "Transport Allowance: " << TransportAllowance << endl;

        cout << "\nDeductions :-\n";
        cout << "PF: " << PF << endl;
        cout << "Tax: " << tax << endl;
        cout << "Loan Status: " << AnyLoan << endl;
        cout << "Loan Debit This Month: " << LoanDebit << endl;
        cout << "Loan Balance: " << LoanBalance << endl;

        cout << "\nTotal Gross Pay: " << grosspay << endl;
    }

    void getInput() override {
        cout << "Name: ";
        cin >> name;
        cout << "Code: ";
        cin >> code;
        cout << "Designation: ";
        cin >> designation;
        cout << "Years of Experience: ";
        cin >> exp;
        cout << "Age: ";
        cin >> age;
        cout << "Enter Working Hours: ";
        cin >> workingHours;

        int sal = workingHours * 300;
        salary = sal;

        cout << "Any Loan (Y/N)? : ";
        cin >> AnyLoan;

        if (AnyLoan == 'Y' || AnyLoan == 'y') {
            cout << "Enter Loan Balance: ";
            cin >> LoanBalance;
        } else {
            LoanBalance = 0;
        }
    }
};

void displayMenu() {
    cout << "***** Payroll Management System 1.0 *****" << endl;
    cout << "Press 1 ----> Insert New Record." << endl;
    cout << "Press 2 ----> Edit a Record." << endl;
    cout << "Press 3 ----> Delete a Record." << endl;
    cout << "Press 4 ----> Search a Record." << endl;
    cout << "Press 5 ----> List The Employee Table." << endl;
    cout << "Press 6 ----> Print Employee PaySlip." << endl;
    cout << "Press 7 ----> Quit Program." << endl;
    cout << "Select Your Option: ";
}

int main() {
    int choice;
    Employee emp[max];
    int num = 0;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                if (num < max) {
                    emp[num] = Employee();
                    emp[num].getInput();
                    emp[num].calculateSalary();
                    num++;
                    cout << "Record Inserted Successfully!!!\n";
                } else {
                    cout << "Maximum number of records reached!\n";
                }
                break;
            }
            case 2: {
                int code;
                cout << "Enter the Job Code to Edit: ";
                cin >> code;

                bool found = false;
                for (int i = 0; i < num; ++i) {
                    if (emp[i].code == code) {
                        emp[i].getInput();
                        emp[i].calculateSalary();
                        cout << "Record Edited Successfully!!!\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found!\n";
                }
                break;
            }
            case 3: {
                int code;
                cout << "Enter the Job Code to Delete: ";
                cin >> code;

                bool found = false;
                for (int i = 0; i < num; ++i) {
                    if (emp[i].code == code) {
                        for (int j = i; j < num - 1; ++j) {
                            emp[j] = emp[j + 1];
                        }
                        num--;
                        cout << "Record Deleted Successfully!!!\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found!\n";
                }
                break;
            }
            case 4: {
                int code;
                cout << "Enter the Job Code to Search: ";
                cin >> code;

                bool found = false;
                for (int i = 0; num; ++i) {
                    if (emp[i].code == code) {
                        emp[i].displayDetails();
                        emp[i].displayPayslip();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found!\n";
                }
                break;
            }
            case 5: {
                for (int i = 0; i < num; ++i) {
                    emp[i].displayDetails();
                }
                break;
            }
            case 6: {
                int code;
                cout << "Enter the Job Code to Display Payslip: ";
                cin >> code;

                bool found = false;
                for (int i = 0; i < num; ++i) {
                    if (emp[i].code == code) {
                        emp[i].displayPayslip();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found!\n";
                }
                break;
            }
            case 7: {
                cout << "Exiting Program...\n";
                return 0;
            }
            default:
                cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
