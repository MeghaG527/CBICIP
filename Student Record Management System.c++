#include <fstream> 
#include <iostream> 
#include <iomanip> 
#include <string.h> 
 
using namespace std; 
 
void printTableHeader() { 
    cout << left << setw(15) << "Reg No." 
         << left << setw(20) << "Name" 
         << left << setw(10) << "CSE1001" 
         << left << setw(10) << "CSE1002" 
         << left << setw(15) << "Proctor ID" << endl; 
    cout << string(70, '-') << endl; 
} 
 
void printStudentDetails(string regNo, string name, string cse1001, string cse1002, string proctorID) { 
    cout << left << setw(15) << regNo 
         << left << setw(20) << name 
         << left << setw(10) << cse1001 
         << left << setw(10) << cse1002 
         << left << setw(15) << proctorID << endl; 
} 
 
int main() 
{ 
    char data[15]; 
    int n = 0, option = 0; 
    string empty = "00"; 
    string proctor = ""; 
 
    while (option != 4) { 
        cout << "\nAvailable operations:\n1. Add New Student\n2. Show Student Details\n3. Delete Student Details\n4. Exit\nEnter option: "; 
        cin >> option; 
 
        if (option == 1) { 
            cout << "Enter the number of students: "; 
            cin >> n; 
 
            for (int i = 0; i < n; i++) { 
                ofstream outfile; 
                outfile.open("Example.txt", ios::app); 
                 
                cout << "Enter your registration number: "; 
                cin >> data; 
                outfile << data << "\t"; 
 
                cout << "Enter your name: "; 
                cin >> data; 
                int len = strlen(data); 
 
                while (len < 15) { 
                    data[len] = ' '; 
                    len++; 
                } 
                outfile << data << "\t"; 
                 
                outfile << empty << "\t"; 
                outfile << empty << "\t"; 
 
                cout << "Enter your proctor ID: "; 
                cin >> proctor; 
 
                outfile << proctor << endl; 
            } 
        } 
 
        else if (option == 2) { 
            ifstream infile("Example.txt", ios::in); 
            if (!infile) { 
                cout << "No student records found!" << endl; 
            } else { 
                printTableHeader(); 
                string regNo, name, cse1001, cse1002, proctorID; 
                while (infile >> regNo >> name >> cse1001 >> cse1002 >> proctorID) { 
                    printStudentDetails(regNo, name, cse1001, cse1002, proctorID); 
                } 
                infile.close(); 
            } 
        } 
 
        else if (option == 3) { 
            cout << "Enter the registration number of the student to delete: "; 
            string regNoToDelete; 
            cin >> regNoToDelete; 
 
            ifstream infile("Example.txt", ios::in); 
            ofstream tempFile("Temp.txt", ios::out); 
 
            string regNo, name, cse1001, cse1002, proctorID; 
            bool found = false; 
            while (infile >> regNo >> name >> cse1001 >> cse1002 >> proctorID) { 
                if (regNo != regNoToDelete) { 
                    tempFile << regNo << "\t" << name << "\t" << cse1001 << "\t" << cse1002 << "\t" << proctorID << endl; 
                } else { 
                    found = true; 
                } 
            } 
 
            infile.close(); 
            tempFile.close(); 
 
            remove("Example.txt"); 
            rename("Temp.txt", "Example.txt"); 
 
            if (found) { 
                cout << "Student record deleted successfully." << endl; 
            } else { 
                cout << "No such registration number found!" << endl; 
            } 
        } 
 
        else if (option == 4) { 
            cout << "Exiting program." << endl; 
        } else { 
            cout << "Invalid option! Please try again." << endl; 
        } 
    } 
}