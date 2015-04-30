# LinkedListProject

##Summary
I have created a working Employee Linked List model. 

A user will need to know their credentials in order to gain access to the system, once correct details have been validated
the user will be able to select from 8 options within the Menu, including exit. All required menu options for this project
have been met, however i did include a ListNodes function, which i felt was very beneficial for completing quick searches.

## File Information
I have opted for 4 seperate files within my Project;

	employeeMain.c - Which contains only the main function and within that, function calls. 
 	allFunctions.c - Which contains all my functions for the project
	loadDetailsToList.c - which has two functions for loading Employee details (Login Credentials & Employee Details)
			      Directly into Linked lists from Textfiles. 
	employeeHeaderFile.h - Contains all my definitions / Includes / Typedefs / Structs etc
	
##Instructions for Use:
Please note: I have completed this project using Visual Studio 2010 and as you may know, there are issues regarding
the placement and location of variable / struct declarations inside functions. 
Also in order to view all details correctly on screen and therefore enchance the users experience
it is advisable to increase the command line screen size significantly. 

I have created an Employee textfile that holds 12 records that will be loaded into the linked list and 3 Login Users

* Run Program
* Log In using user Credentials
* Select from the 8 Menu Options available
*	1 Add Employee - Adds a new Employee(node) to the Linked List
*	2 Display Employee Details - Allows a user to search for en Employee by ID of First / last name (case insensitive)
*	3 Update an Employee - Allows a user to search for Emp first, than can update Address, Department or Salary
*	4 Delete an Employee - Allows the user to delete by id only (see above note)
*	5 Display Employees by dept - Shows each Department and all employees names in each one
*	6 Employee Report - Shows each Departments Financial summary (Headcount, Salary, Bonuses & Total Outlay)
		* There is an option at the end to print details to file, Press 1 to do so, 2 to return to menu

*	7 View All Employees - Displays all employees id, names and departments
*	8 Exit - Finishes the program and upon exit, prints all / changes to the linked list out to file
