// Header file include
#include "employeeHeaderFile.h" 


// The Actual Menu Options Available for the User
int showMenu()
{
	int iChoice;

	do
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t              EMPLOYEE  MENU              \n");
		printf("\t\t _________________________________________\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 1 to Add Employee               |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 2 to Display Employee Details   |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 3 to Update an Employee         |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 4 to Delete an Employee         |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 5 to Display Employees by dept  |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 6 for Employee Report           |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 7 To View All Employees         |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|   Press 8 to Exit                       |\n");
		printf("\t\t|_________________________________________|\n");
		printf("\t\t    \n\n\n\t\tSELECTION = ");

		fflush(stdin);
		scanf("%d", &iChoice );

	}
	while( ( iChoice < 0 ) || ( iChoice > 8 ) ); 
	// End of do/while

	return( iChoice );

} //  End showMenu function



/* This Function Creates a New Employee(Node) and is inserted into the next available slot
in the Linked List. I have Organised it in such a way that the Next Available ID will be Displayed to use
and if an ID is chosen that already exists, an error is thrown and the user is prompted to choose a Valid one. */
void addEmployee(NEWEMP *head)
{
	// Variable Declarations
	int id = 0, length = 0;
	char dotComCheck[MAXNAME + 1] = ".com";
	char dept[MAXNAME + 1];

	// Struct & File Pointer declarations
	FILE *fptr = fopen(FILENAME, APPENDMODE);
	NEWEMP *temp, *newEmployee;
	temp = (NEWEMP*)malloc(sizeof(NEWEMP)); // Allocates size of NEWEMP struct variable 
	temp = head;
	
	// Clear screen to start
	system("cls");

	while(temp->next != NULL)
	{
		temp = temp->next;
		++length; //  Calculates the Length of the Linked List
	}

	// Allocates size of NEWEMP struct variable 
	newEmployee = (NEWEMP*)malloc(sizeof(NEWEMP));

	// Informs the User of the Next Available ID to use
	RE_ENTER_ID:
	printf("\nNext Available id is: %d", length + 1);

	puts("\nEnter an Employee Id: ");
	fflush(stdin);
	scanf("%d", &id);

	// ID validation, If the next available Id offered is not entered, 
	// then an error is thrown and the user is returned to re-enter a Valid ID
	if(id < length + 1)
	{
		puts("Please Enter a Valid ID\n");
		goto RE_ENTER_ID; // Returns User to ReEnter a Valid ID
	}
	else // The Valid Id Becomes the Id for this employee node
	{
		newEmployee->id = id; 
	}

	puts("\nEnter Employee First Name: ");
	fflush(stdin);
	gets(newEmployee->FName);

	puts("\nEnter Employee Last Name: ");
	fflush(stdin);
	gets(newEmployee->LName);

	puts("\nEnter an Employee Address: ");
	fflush(stdin);
	gets(newEmployee->empAddr);


	// Department Validation, If none of available department names are entered, error thrown and user
	// returned to this point and prompted for Another Department Name
	VALID_DEPT:
	puts("\nEnter one of the below Department Names: SHOPFLOOR, BUTCHERS, ADMIN, STOCK, CLOTHES");
	fflush(stdin);
	gets(dept);

	if( (strcmp(dept, "BUTCHERS") == 0) || 
		(strcmp(dept, "ADMIN") == 0) || 
		(strcmp(dept, "SHOPFLOOR") == 0) ||
		(strcmp(dept, "STOCK") == 0) || 
		(strcmp(dept, "CLOTHES") == 0) )
	{
		strcpy(newEmployee->department, dept);
	}
	else
	{
		puts("Please Enter a Valid Department");
		goto VALID_DEPT;
	}

	// Only Numbers allowed to be entered for Day, Month & Year
	VALID_DATE:
	puts("\nEnter Day of Joining: ");
	fflush(stdin);
	if(scanf("%d",  &newEmployee->dateOfJoining.day) != 1)
	{
		puts("Enter a Valid Day\n");
		goto VALID_DATE;
	}
	
	puts("\nEnter Month of Joining: ");
	fflush(stdin);
	if(scanf("%d", &newEmployee->dateOfJoining.month) != 1)
	{
		puts("Enter a Valid Month\n");
		goto VALID_DATE;
	}
	
	puts("\nEnter Year of Joining: ");
	fflush(stdin);
	if(scanf("%d", &newEmployee->dateOfJoining.year)!= 1)
	{
		puts("Enter a Valid Year\n");
		goto VALID_DATE;	
	}

	// Salary Validation, only numbers allowed
	VALID_SALARY:
	puts("\nEnter Employee Salary: ");
	fflush(stdin);
	if(scanf("%f", &newEmployee->annualSalary)!= 1)
	{
		puts("Enter a Salary\n");
		goto VALID_SALARY;
	}

	/* 
	Email validation:
	Only an email address with an '@' sign and a '.com'
	will pass validation, otherwise the user is returned and 
	promted again for a valid email address
	*/
	VALID_EMAIL:
	puts("\nEnter an Email Address: ");
	fflush(stdin);
	scanf("%s", &newEmployee->email);

	// Throws error if no @ sign in the email
	if(!strrchr(newEmployee->email, '@') )
	{
		puts("You Must an '@' symbol in your email address");
		goto VALID_EMAIL;
	}

	// Throws an error if no .com in the email
	if(!strstr(newEmployee->email, dotComCheck) )
	{
		puts("You Must have a '.com' in your email address");
		goto VALID_EMAIL;
	}

	puts("\nNew Employee Successfully Entered");

	// Creates a Next Employee node and sets it to NULL
	newEmployee->next = NULL;
	temp->next = newEmployee;

	puts("\n\n\n");
	system("Pause");

} // End of addEmployee Function


// Search Employee Function:
/*
	Allows for a User to Search by Id number, Last or First Name
	irrespective of Caps on or off. 
	The full details of the given employee(s) are displayed on screen 
*/
void searchEmployee(NEWEMP *head)
{
	int id = 0, choice = 0;
	char name[MAXNAME + 1];
	NEWEMP *temp;
	temp = (NEWEMP*)malloc(sizeof(NEWEMP)); 
	temp = head; 

	system("cls");
	printf("Press 1 to search by ID or 2 to Search by Name\n");

	scanf("%d", &choice);
	fflush(stdin);

	if(choice == 1)
	{
		puts("\nSearch by Employee ID: ");
		scanf("%d", &id);
		fflush(stdin);

		while( temp != NULL )
		{
			if( temp->id == id ) 
			{
				printf("\n------------------EMPLOYEE DETAILS-----------------\n");
				printf("\nId: %d\nFirst Name: %s\nLast Name: %s\nAddress: %s\nDepartment: %s\nDate Joined: %d-%d-%d\nSalary: %5.2f\nEmail: %s", 
													temp->id, 
													temp->FName,
													temp->LName,
													temp->empAddr,
													temp->department,
													temp->dateOfJoining.day, 
													temp->dateOfJoining.month, 
													temp->dateOfJoining.year, 
													temp->annualSalary, 
													temp->email); 
			} // End if( temp->id == id )

			temp = temp->next;

		} // End while( temp != NULL )
	}
	else if(choice == 2)
	{
		puts("\nSearch by Employee First OR Last name: ");
		gets(name);
		fflush(stdin);

		while( temp != NULL )
		{
			if( (stricmp(temp->FName, name) == 0) || stricmp(temp->LName, name) == 0) 
			{
				printf("\n------------------EMPLOYEE DETAILS-----------------\n");
				printf("\nId: %d\nFirst Name: %s\nLast Name: %s\nAddress: %s\nDepartment: %s\nDate Joined: %d-%d-%d\nSalary: %5.2f\nEmail: %s", 
													temp->id, 
													temp->FName,
													temp->LName,
													temp->empAddr,		
													temp->department,
													temp->dateOfJoining.day, 
													temp->dateOfJoining.month, 
													temp->dateOfJoining.year, 
													temp->annualSalary, 
													temp->email); 
			} // End if( temp->id == id )

			temp = temp->next;

		} // End while( temp != NULL )
	}
	else
	{
		puts("Please Enter 1 or 2 only");
	}

	puts("\n\n\n");
	system("Pause");

} // End of searchEmployee function



//  Employee / Node Deletion:
/*  User must know the ID of the Employee, prior to entering the Delete Function. 
	Note: Deleting by Name could have hazardous consequences, should two users with the same name come up, 
	so with this in mind, i have opted to omit this part from the Delete Function. 
	I have however included something similar in the Update Employee Section, to show working code where search by id or name is present. */
void deleteNode(NEWEMP* head)
{ 
	// Declaration of types of Variables, Pointers and Struct size allocation
	int tempId;
	char strBuffer[MAXCOUNT + 1];
	FILE *fptr;
	NEWEMP *temp1, *old_temp;
	temp1 = (NEWEMP*)malloc(sizeof(NEWEMP));
	old_temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	temp1 = head;

	// User asked to input an Id
	puts("Enter an Id to Delete: ");
	fflush(stdin);
	scanf("%d", &tempId);

	// Scans through each Node for a Match, if match Found, node is removed. 
	while(temp1->next != NULL)
	{
		if(temp1->id == tempId)
		{
			old_temp->next = temp1->next;
		}
		old_temp = temp1;
		temp1 = temp1->next;
	}
	old_temp->next = NULL;

	puts("\nNode Deleted\n");
	system("Pause");

} // End of deleteFromEnd function


// Display by Department
// Displays all employees in order of Department
void displayByDepartment(NEWEMP *head)
{
	int butcherMarked = FALSE, adminMarked = FALSE, clothesMarked = FALSE, stockMarked = FALSE, shopFloorMarked = FALSE;
	NEWEMP *temp;
	temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	temp = head;

	system("cls");

	puts("-----------------------------------------");
	puts("    DISPLAY EMPLOYEES BY DEPARTMENT");
	puts("-----------------------------------------");

	/*This and following sections, checks each Department Name and Prints out each Employee (node) for that Department
	When a Department has been Listed, a True Flag is marked for that department, the node is pointed to the beginning
	and the Search begins again for the next department name. The Flag Eliminates Duplicate Departments being returned*/
	if ( (strcmp(temp->department, "BUTCHERS") == 0) )
	{
		puts("\nBUTCHERS DEPARTMENT:");
		do 
		{
			if ( (strcmp(temp->department, "BUTCHERS") == 0) )
			{
				printf("%s %s\n", temp->FName, temp->LName);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );
		butcherMarked = TRUE;
	} //  End if ( (strcmp(temp->department, "BUTCHERS") == 0) )

	temp = head; // Resets the Head node to point at the start again

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nADMIN DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "ADMIN") == 0) )
			{
				printf("%s %s\n", temp->FName, temp->LName);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );
		adminMarked = TRUE;
	} // End if

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nSHOPFLOOR DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "SHOPFLOOR") == 0) )
			{
				printf("%s %s\n", temp->FName, temp->LName);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );
		shopFloorMarked = TRUE;
	}// End if

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nSTOCK DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "STOCK") == 0) )
			{
				printf("%s %s\n", temp->FName, temp->LName);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );
		stockMarked = TRUE;
	}// End if

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nCLOTHES DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "CLOTHES") == 0) )
			{
				printf("%s %s\n", temp->FName, temp->LName);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );
		clothesMarked = TRUE;
	}// End if
	
	puts("\n\n\n");
	system("Pause");
	
} // End void displayByDepartment(NEWEMP *head)



// Employee Report:
/* Calculates the Following:
   1. Headcount for each Department
   2. Total Salary for each department
   3. Bonuses (if any) for each Department
   4. Total Outlay for each Department (Salary + Bonuses)
*/
void employeeReport(NEWEMP *head)
{
	/*The Integer and Float Array's store the Values for each Department, ie countStaff[0] is Butchers Dept, countStaff[1] Admin Dept and so on
	Again the same approach applies for the Total Salary, Bonuses and Outlay*/

	int printOption = 0;
	int butcherMarked = FALSE, adminMarked = FALSE, clothesMarked = FALSE, stockMarked = FALSE, shopFloorMarked = FALSE;
	int countStaff[] = {0,0,0,0,0};
	float totalSalary[] = {0,0,0,0,0};
	float totalBonus[] = {0,0,0,0,0};
	float totalOutlay[] = {0,0,0,0,0};

	FILE *fptr = fopen(PRINTREPORT, WRITEMODE); // File pointer for Creating the Employee Report Print out
	NEWEMP *temp;
	temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	temp = head;

	system("cls");
	puts("-----------------------------------------");
	puts("     EMPLOYEE FINANCIAL REPORT");
	puts("-----------------------------------------");

	if ( (strcmp(temp->department, "BUTCHERS") == 0) )
	{
		puts("\nBUTCHERS DEPARTMENT:");
		do 
		{
			if ( (strcmp(temp->department, "BUTCHERS") == 0) )
			{
				++countStaff[0]; // Butcher Department
				totalSalary[0] += temp->annualSalary; // Adds up the Salaries for each person in that Department
				if(2015 - temp->dateOfJoining.year > 10) // If the Person is 10 or more years Employed, Give an Extra 5% of Salary
				{
					totalBonus[0] += (temp->annualSalary * .05);
				}
				// If the Person is Between 5 and 10 years Employed, Give an Extra 4% of Salary
				else if(2015 - temp->dateOfJoining.year > 5 && 2015 - temp->dateOfJoining.year < 10)
				{
					totalBonus[0] += (temp->annualSalary * .04);
				}
				// If the Person is less than 4 years employee or more years Employed, Give an Extra 3% of Salary
				else if(2015 - temp->dateOfJoining.year < 5)
				{
					totalBonus[0] += (temp->annualSalary * .03);
				}
				// Calculates the Total Salaries Plus bonuses for Each department
				totalOutlay[0] += (temp->annualSalary + totalBonus[0]);
			} // End if
		}
		while ( (temp->next != NULL) && (temp = temp->next) ); // Loops through Each node, while The next one is not null
		// End do/while

		// Prints to Screen all information for that Department
		printf("Number of Employees: %d\n", countStaff[0]);
		printf("Total Salary: %5.2f\n", totalSalary[0]);
		printf("Total Bonuses: %5.2f\n", totalBonus[0]); 
		printf("Total Outlay: %5.2f\n", totalOutlay[0]);
		butcherMarked = TRUE;
	} // End if

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nADMIN DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "ADMIN") == 0) )
			{
				++countStaff[1];
				totalSalary[1] += temp->annualSalary;
				if(2015 - temp->dateOfJoining.year > 10)
				{
					totalBonus[1] += (temp->annualSalary * .05);
				}
				else if(2015 - temp->dateOfJoining.year > 5 && 2015 - temp->dateOfJoining.year < 10)
				{
					totalBonus[1] += (temp->annualSalary * .04);
				}
				else if(2015 - temp->dateOfJoining.year < 5)
				{
					totalBonus[1] += (temp->annualSalary * .03);
				}
				totalOutlay[1] += (temp->annualSalary + totalBonus[1]);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );

		printf("Number of Employees: %d\n", countStaff[1]);
		printf("Total Salary: %5.2f\n", totalSalary[1]);
		printf("Total Bonuses: %5.2f\n", totalBonus[1]); 
		printf("Total Outlay: %5.2f\n", totalOutlay[1]);
		adminMarked = TRUE;
	}

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nSHOPFLOOR DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "SHOPFLOOR") == 0) )
			{
				++countStaff[2];
				totalSalary[2] += temp->annualSalary;
				if(2015 - temp->dateOfJoining.year > 10)
				{
					totalBonus[2] += (temp->annualSalary * .05);
				}
				else if(2015 - temp->dateOfJoining.year > 5 && 2015 - temp->dateOfJoining.year < 10)
				{
					totalBonus[2] += (temp->annualSalary * .04);
				}
				else if(2015 - temp->dateOfJoining.year < 5)
				{
					totalBonus[2] += (temp->annualSalary * .03);
				}
				totalOutlay[2] += (temp->annualSalary + totalBonus[2]);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );

		printf("Number of Employees: %d\n", countStaff[2]);
		printf("Total Salary: %5.2f\n", totalSalary[2]);
		printf("Total Bonuses: %5.2f\n", totalBonus[2]); 
		printf("Total Outlay: %5.2f\n", totalOutlay[2]);
		shopFloorMarked = TRUE;
	}

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nSTOCK DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "STOCK") == 0) )
			{
				++countStaff[3];
				totalSalary[3] += temp->annualSalary;
				if(2015 - temp->dateOfJoining.year > 10)
				{
					totalBonus[3] += (temp->annualSalary * .05);
				}
				else if(2015 - temp->dateOfJoining.year > 5 && 2015 - temp->dateOfJoining.year < 10)
				{
					totalBonus[3] += (temp->annualSalary * .04);
				}
				else if(2015 - temp->dateOfJoining.year < 5)
				{
					totalBonus[3] += (temp->annualSalary * .03);
				}
				totalOutlay[3] += (temp->annualSalary + totalBonus[3]);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );

		printf("Number of Employees: %d\n", countStaff[3]);
		printf("Total Salary: %5.2f\n", totalSalary[3]);
		printf("Total Bonuses: %5.2f\n", totalBonus[3]); 
		printf("Total Outlay: %5.2f\n", totalOutlay[3]);
		stockMarked = TRUE;
	}

	temp = head;

	if ( (butcherMarked == TRUE  || adminMarked == TRUE || clothesMarked == TRUE || stockMarked == TRUE || shopFloorMarked == TRUE) )
	{
		puts("\nCLOTHES DEPARTMENT:");
		do
		{
			if ( (strcmp(temp->department, "CLOTHES") == 0) )
			{
				++countStaff[4];
				totalSalary[4] += temp->annualSalary;
				if(2015 - temp->dateOfJoining.year > 10)
				{
					totalBonus[4] += (temp->annualSalary * .05);
				}
				else if(2015 - temp->dateOfJoining.year > 5 && 2015 - temp->dateOfJoining.year < 10)
				{
					totalBonus[4] += (temp->annualSalary * .04);
				}
				else if(2015 - temp->dateOfJoining.year < 5)
				{
					totalBonus[4] += (temp->annualSalary * .03);
				}
				totalOutlay[4] += (temp->annualSalary + totalBonus[4]);
			}
		}
		while ( (temp->next != NULL) && (temp = temp->next) );

		printf("Number of Employees: %d\n", countStaff[4]);
		printf("Total Salary: %5.2f\n", totalSalary[4]);
		printf("Total Bonuses: %5.2f\n", totalBonus[4]); 
		printf("Total Outlay: %5.2f\n", totalOutlay[4]);
		clothesMarked = TRUE;
	}

	puts("\n");

	temp = head;


	/*The User is given an Option after reviewing the Employee Financial Report
	to print to file:
		1. Prints to File
		2. Returns the User to the Main Menu */
	do
	{
		puts("Press 1 to Print to File for Records\n");
		puts("Press 2 to Return to Main Menu\n");
		scanf("%d", &printOption);
		fflush(stdin);

		switch(printOption)
		{
			case 1:		
				if(fptr == NULL){
					puts("\nError with file");
					exit(0);
				}
				fprintf(fptr, "BUTCHERS DEPARTMENT\nNumber of Employees: %d\nTotal Salary: %5.2f\nTotal Bonuses: %5.2f\nTotal Outlay %5.2f\n\n", 
														countStaff[0], totalSalary[0], totalBonus[0], totalOutlay[0]);
				fprintf(fptr, "ADMIN DEPARTMENT\nNumber of Employees: %d\nTotal Salary: %5.2f\nTotal Bonuses: %5.2f\nTotal Outlay %5.2f\n\n", 
														countStaff[1], totalSalary[1], totalBonus[1], totalOutlay[1]);
				fprintf(fptr, "SHOPFLOOR DEPARTMENT\nNumber of Employees: %d\nTotal Salary: %5.2f\nTotal Bonuses: %5.2f\nTotal Outlay %5.2f\n\n", 
														countStaff[2], totalSalary[2], totalBonus[2], totalOutlay[2]);
				fprintf(fptr, "STOCK DEPARTMENT\nNumber of Employees: %d\nTotal Salary: %5.2f\nTotal Bonuses: %5.2f\nTotal Outlay %5.2f\n\n", 
														countStaff[3], totalSalary[3], totalBonus[3], totalOutlay[3]);
				fprintf(fptr, "CLOTHES DEPARTMENT\nNumber of Employees: %d\nTotal Salary: %5.2f\nTotal Bonuses: %5.2f\nTotal Outlay %5.2f", 
														countStaff[4], totalSalary[4], totalBonus[4], totalOutlay[4]);
				fclose(fptr);
				puts("Successfully Printed to File\n");
				break;

			case 2:
				return;
				break;
		}
	
	}while(printOption < 0 || printOption > 2);
	// End do/while

	puts("\n\n\n");
	system("Pause");

} // End of dispEmpsByDept function



 //An Extra Useful Function (Option 7 in Menu) that Lists each Employees, ID, Name(s) and Department
 //and Gives the Total amount of Employees working in the Company
 //Has Proven quiet useful, especially when doing a quick search
void listNodes (NEWEMP *head)
{
	int length = 0;
	NEWEMP *temp;
	temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	temp = head;

	system("cls");

	while( temp->next != NULL )
	{
		printf("Id: %d Name: %s %s Department: %s\n", temp->id, temp->FName, temp->LName, temp->department);
		temp = temp->next;
		++length;

	}// while( temp->next != NULL ); // End while( temp->next != NULL )

	printf("\n\nThere are %d Employees in this company\n\n", length);

	puts("\n\n\n");
	system("Pause");

} //  End listNodes function




/*  updateEmployee Function: 
	Allows user to Update: Address, Department or Salary
	By Means of: ID or Name
	The Details of the Employee Found, remains on screen to make things easier for updating
	and any changes made will be Demonstrated, as the users details are re-displayed on screen showing any alterations */
void updateEmployee(NEWEMP * head)
{
	int choice = 0, userId = 0, updateChoice = 0;
	char name[MAXNAME];
	NEWEMP *foundUser = (NEWEMP *)malloc(sizeof(NEWEMP));
	
	system("cls");
	do
	{
		printf("Press 1 to search by ID or 2 to Search by Name\n");
		scanf("%d", &choice);
		fflush(stdin);
		if(choice == 1)
		{
			do
			{
				printf("\nGive the user Id: ");
				scanf("%d", &userId);
			}
			while(userId < 0); // Validation for minus values
			{
				foundUser = findEmployee(head, userId, NULL);
				break;
			}
		}
		else if(choice == 2)
		{
			printf("\nEnter an Employees Surname: ");
			scanf("%s", name);
			foundUser = findEmployee(head, 0, name);
			break;
		}
	}
	while(choice < 1 || choice > 2);
	// End do/while

	if(foundUser == NULL)
	{
		printf("No User found with credentials entered");
		return;
	}
	else
	{
		showEmployeebByPointer(foundUser, "\n-----------CURRENT EMPLOYEE DETAILS-----------------\n");

		do
		{
			fflush(stdin);
			puts("\n\n");
			puts("-----------------------------------------------------");
			printf("Choose from below methods for Updating the Employee\n");
			puts("1. Update Address");
			puts("2. Update Department");
			puts("3. Update Salary");

			scanf("%d", &updateChoice);
			fflush(stdin);
			
			// Options for Updating Employee
			switch(updateChoice)
			{
				case 1:
					puts("Enter the new Address");
					gets(foundUser->empAddr);
					break;
				case 2:
					puts("Enter the new Department");
					gets(foundUser->department);
					break;
				case 3:					
					puts("Enter the new Salary");
					scanf("%f", &(foundUser->annualSalary));
					break;
			}
		}while(updateChoice < 1 && updateChoice > 3); // End do/while
	}//end else user choice
	
	showEmployeebByPointer(foundUser, "\n-----------UPDATED EMPLOYEE DETAILS-----------------\n");
	
	puts("\n\n");
	system("pause");
}


// Prints out the Actual Updated Employee Node
void showEmployeebByPointer(NEWEMP * foundUser, char updateMsg[])
{
	puts(updateMsg);	
	printf("\nId: %d\nFirst Name: %s\nLast Name: %s\nAddress: %s\nDepartment: %s\nDate Joined: %d-%d-%d\nSalary: %5.2f\nEmail: %s", 
										foundUser->id, 
										foundUser->FName,
										foundUser->LName,
										foundUser->empAddr,		
										foundUser->department,
										foundUser->dateOfJoining.day, 
										foundUser->dateOfJoining.month, 
										foundUser->dateOfJoining.year, 
										foundUser->annualSalary, 
										foundUser->email); 

} // End of showEmployeebByPointer function




/* FindEmployee: function to search and return pointer to found user based on id or name */
NEWEMP * findEmployee(NEWEMP * head, int userId, char userName[])
{
	NEWEMP *tmpEmp = head;

	while(tmpEmp != NULL)
	{
		if(userId != 0 && tmpEmp->id == userId)
		{
			return tmpEmp;
		}
		else if(userId == 0 && stricmp(tmpEmp->LName, userName) == 0)
		{
			return tmpEmp;
		}
		tmpEmp = tmpEmp->next;
	}
	return NULL;

}//end NEWEMP * findEmployee(NEWEMP * head, int userId, char userName[])





// Print employees: Prints the Actual Values of the LinkedlIst to File
void printEmployees(NEWEMP * head)
{
	NEWEMP *tmpEmp = head;
	int iCnt = -1;
	
	while(tmpEmp != NULL)
	{
		if(++iCnt == 0) 
		{
			writeFile(FILENAME, WRITEMODE, tmpEmp);
		}
		else
		{
			writeFile(FILENAME, "a+", tmpEmp);
		}
		tmpEmp = tmpEmp->next;
	}

}// End void printEmployees(NEWEMP * head)



/* writeFile Function: Prepares the printEmployees function by putting in employee nodes
into the file pointer */
void writeFile(char fileName[], char modifier[], NEWEMP *newEmployee)
{
	FILE *fptr = fopen(fileName, modifier);
	if(fptr == NULL)
	{
		puts("Can't access the file, exit");
	}
	fprintf(fptr, "%d %s %s	%s %s %d %d	%d %f %s\n", 
					newEmployee->id,
					newEmployee->FName,
					newEmployee->LName,
					newEmployee->empAddr,
					newEmployee->department,
					newEmployee->dateOfJoining.day,
					newEmployee->dateOfJoining.month,
					newEmployee->dateOfJoining.year,
					newEmployee->annualSalary, 
					newEmployee->email);

	fclose(fptr);

} //  End void writeFile function