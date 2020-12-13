#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

string randomId() {
    return to_string(rand() * rand());
};

class Employee {
    string _id;

public:
    string name;
    string surname;
    string departmentId;
    string position;

    Employee(string e_name, string e_surname, string e_departmentId, string e_position) {
        _id = randomId();
        name = e_name;
        surname = e_surname;
        departmentId = e_departmentId;
        position = e_position;
    }

    string id() {
        return _id;
    }
};

typedef map<string, Employee*> Employees;
typedef vector<Employee*> Department;
typedef map<string, Department> Departments;
typedef map<string, double> Salaries;

class HRMS {
    Employees employees;
    Departments departments;
    Salaries salaries;

    string _formatEmployee(Employee* employee) {
        return employee->surname + ", " + employee->name;
    }

    string _formatEmployeeWithSalary(Employee* employee, double salaryToFormat) {
        string salary = to_string(salaryToFormat);
        salary = salary.substr(0, salary.find(".") + 3);

        return _formatEmployee(employee) + " ; salary = " + salary;
    }

    Employee* _findEmpoloyee(string employeeId) {
        Employees::iterator employee = employees.find(employeeId);

        if (employee == employees.end()) {
            throw "Unknown employee with ID: " + employeeId;
        }

        return employee->second;
    }

public:
    HRMS() {
        Employees employees;
        Departments departments;
        Salaries salaries;
    }
 
    void add(Employee & employee, string departmentId, double salary) {
        employees[employee.id()] = &employee;
        salaries[employee.id()] = salary;

        employee.departmentId = departmentId;
        departments[employee.departmentId].push_back(&employee);
    }

    void printDepartment(string departmentId) {
        Departments::iterator departments_it = departments.find(departmentId);

        if (departments_it == departments.end()) {
            cout << "No department found with ID: " << departmentId << endl;
            return;
        }

        Department department = departments_it->second;

        cout << "Department " << departmentId << endl;
        
        for (Employee* employee : department) {
            cout << "\t-" << _formatEmployee(employee) << endl;
        };
    }

    void changeSalary(string employeeId, double salary) {
        Salaries::iterator salaries_it = salaries.find(employeeId);

        if (salaries_it == salaries.end()) {
            cout << "No employee with ID " << employeeId << " found";
            return;
        }

        salaries_it->second = salary;
    }

    void printSalaries() {
        cout << "Salaries:" << endl;

        for (Salaries::iterator salaries_it = salaries.begin(); salaries_it != salaries.end(); ++salaries_it) {
            cout << "\t-" << _formatEmployeeWithSalary(_findEmpoloyee(salaries_it->first), salaries_it->second) << "\n";
        }
    }

    void printSortedSalaries() {
        Salaries::iterator salaries_it = salaries.begin();
     
        typedef pair<string, double> salary_pair;
        vector<salary_pair> pair_vector;

        for (Salaries::iterator salaries_it = salaries.begin(); salaries_it != salaries.end(); ++salaries_it) {
            pair_vector.push_back(make_pair(salaries_it->first, salaries_it->second));
        }
  
        sort(begin(pair_vector), end(pair_vector), [](salary_pair a, salary_pair b) -> const bool {
            return a.second > b.second;
        });

        cout << "Sorted salaries:\n";

        for (salary_pair pair : pair_vector) {
            cout << "\t-" << _formatEmployeeWithSalary(_findEmpoloyee(pair.first), pair.second) << "\n";
        }
    }
};


int main(){
    HRMS hrms;

    Employee employeeA("name A", "surname A", "DEPARTMENT A", "programer");
    Employee employeeB("name B", "surname B", "DEPARTMENT A", "programer");
    Employee employeeC("name C", "surname C", "DEPARTMENT A", "programer");
    Employee employeeD("name D", "surname D", "DEPARTMENT B", "programer");
    Employee employeeE("name E", "surname E", "DEPARTMENT B", "programer");
    Employee employeeF("name F", "surname F", "DEPARTMENT B", "programer");
    Employee employeeG("name G", "surname G", "DEPARTMENT C", "programer");
    Employee employeeH("name H", "surname H", "DEPARTMENT C", "programer");
    Employee employeeI("name I", "surname I", "DEPARTMENT C", "programer");
    Employee employeeJ("name J", "surname J", "DEPARTMENT D", "programer");
    Employee employeeK("name K", "surname K", "DEPARTMENT D", "programer");
    
    hrms.add(employeeA, employeeA.departmentId, 0);
    hrms.add(employeeB, employeeB.departmentId, 23451.23);
    hrms.add(employeeC, employeeC.departmentId, 12534.21);
    hrms.add(employeeD, employeeD.departmentId, 1545.23);
    hrms.add(employeeE, employeeE.departmentId, 13245.12);
    hrms.add(employeeF, employeeF.departmentId, 156874.56);
    hrms.add(employeeG, employeeG.departmentId, 14567.75);
    hrms.add(employeeH, employeeH.departmentId, 0);
    hrms.add(employeeI, employeeI.departmentId, 1897.78);
    hrms.add(employeeJ, employeeJ.departmentId, 0);

    hrms.changeSalary(employeeA.id(), 1000);
    hrms.changeSalary(employeeH.id(), 1111);

    hrms.printDepartment(employeeA.departmentId);
    hrms.printDepartment(employeeD.departmentId);
    hrms.printDepartment(employeeG.departmentId);

    hrms.printSalaries();
    hrms.printSortedSalaries();

    return 0;
}

