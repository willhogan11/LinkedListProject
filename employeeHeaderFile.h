#ifndef __employeeMain_h

	// Declaration of Definitions
	#define __employeeMain_h
	#define FILENAME "employeeDetails.txt"
	#define LOGINFILE "loginDetails.txt"
	#define PRINTREPORT "employeeReport.txt"
	#define WRITEMODE "w"
	#define READMODE "r"
	#define APPENDMODE "a"
	#define APPENDEXTRA "a+"
	#define MAXNAME 25
	#define MAXADDR 200
	#define MAXCHOICE 2
	#define MAXCOUNT 8000
	#define MAXEMAIL 40 
	#define TRUE 1
	#define FALSE 0
	#define DEBUG
	#define DEBUG_USER_PWORD


	// Include Declarations
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <Windows.h> 
	#include <math.h>
	#include <conio.h>
	#include <time.h>


	// Struct Declarations & Structure
	struct loginDetails
	{
		char userName[MAXNAME + 1];
		char passWord[MAXNAME + 1];
		struct loginDetails *next;
	};

	struct date 
	{
		int day;
		int month;
		int year;
	};

	struct employeeDetails
	{
		int id;
		char FName[MAXNAME + 1];
		char LName[MAXNAME + 1];
		char empAddr[MAXADDR + 1];
		char department[MAXNAME + 1];
		struct date dateOfJoining;
		float annualSalary;
		char email[MAXEMAIL + 1];
		struct employeeDetails *next;
	};


	// Typedef declarations
	typedef struct employeeDetails NEWEMP;
	typedef struct loginDetails LOGIN;


	// Function Declarations
	int showMenu();
	void addEmployee(NEWEMP *head);
	void searchEmployee(NEWEMP *head);
	void deleteNode(NEWEMP* head);
	void displayByDepartment(NEWEMP *head);
	void listNodes (NEWEMP *head);
	void employeeReport(NEWEMP *head);
	void updateEmployee(NEWEMP *head);
	void loginFunction(LOGIN *headLogin, char buffer[]);
	void printEmployees(NEWEMP * head);
	void writeFile(NEWEMP *head);
	void loadFileToLinkedList(NEWEMP *head, char buffer[]);
	void showEmployeebByPointer(NEWEMP * foundUser, char[]);
	NEWEMP * findEmployee(NEWEMP * head, int userId, char userName[]);
	
#endif // End if __employeeMain_h