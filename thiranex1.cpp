#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Marks: " << marks << endl;
    }
};

// ➕ Add Student
void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "✅ Student Added Successfully!\n";
}

// 📄 Display Students
void displayStudents() {
    Student s;
    ifstream file("students.txt");

    cout << "\n--- Student Records ---\n";

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// ❌ Delete Student
void deleteStudent(int id) {
    Student s;
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << "🗑️ Student Deleted (if existed)\n";
}

// ✏️ Update Student
void updateStudent(int id) {
    Student s;
    fstream file("students.txt", ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "✏️ Record Updated!\n";
            file.close();
            return;
        }
    }

    cout << "❌ Student not found!\n";
    file.close();
}

// 🎯 Main Menu
int main() {
    int choice, id;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Update Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            deleteStudent(id);
            break;

        case 4:
            cout << "Enter ID to update: ";
            cin >> id;
            updateStudent(id);
            break;

        case 5:
            cout << "👋 Exiting...\n";
            break;

        default:
            cout << "❌ Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
