#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "C:\Users\acer\Desktop\Projects\Test\linkedList\singly.hpp"

using namespace std;

/////////////////////////////////////
// Employee
class Employee
{
private:
    string name;
    int age, yearOfJoining, salary;

public:
    Employee()
    {
        name = "undefined";
        age = yearOfJoining = salary = 0;
    }

    Employee(string name, int age, int yearOfJoining, int salary)
    {
        this->name = name;
        this->age = age;
        this->yearOfJoining = yearOfJoining;
        this->salary = salary;
    }

    void display()
    {
        cout << "Name: " << name << "\nAge: " << age << "\nWorking Since: " << yearOfJoining << "\nSalary: " << salary << '\n';
    }

    friend bool isWorkingSinceLong(Employee);
};

/////////////////////////////////////
// Utils
void iterateDB(Employee element)
{
    element.display();
    cout << setw(100) << setfill('-') << '\n';
}

bool isWorkingSinceLong(Employee element)
{
    // Private data is accessible because of being a friend function
    return element.yearOfJoining <= 2005;
}

/////////////////////////////////////
// Main
int main(void)
{
    // Linked list to store all employee records
    SinglyList<Employee> database;

    // Putting test data in the linked list
    database
        .append(Employee("Amin Painter", 26, 2020, 45000))
        .append(Employee("Asgar Contractor", 28, 2014, 34000))
        .insert(Employee("Abbas Nadvi", 30, 2005, 25000), 1)
        .prepend(Employee("Adeel Hakim", 52, 2004, 50000))
        .prepend(Employee("Adnan Saifullah", 54, 2000, 55000));

    // Create a new linked list to store employee records who are working since before 2005
    SinglyList<Employee> databaseFiltered = database.filter(isWorkingSinceLong);

    // Print the filtered data using forEach method of SinglyList, because
    // cout << databaseFiltered OR databaseFiltered.display()
    // won't work unless << operator is overloaded for Employee class
    databaseFiltered.forEach(iterateDB);

    return 0;
}