/*  LinkedList Assignment for Advanced Procedural Programming, 
	Created by Will Hogan. 
	2nd Year Software Development. */

// Header file include
#include "employeeHeaderFile.h" 


// Main Function Start
main(void)
{
	// Declaration of Required Struct and Pointer Variables
	int userOptions;
	char strBuffer[MAXCOUNT + 1];
	FILE *fptr = fopen(FILENAME, READMODE);
    	NEWEMP *head, *temp;
	LOGIN *headLogin, *tempLogin;
	headLogin = (LOGIN*)malloc(sizeof(LOGIN));
	tempLogin = (LOGIN*)malloc(sizeof(LOGIN));tempLogin = (LOGIN*)malloc(sizeof(LOGIN));
	temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	head = (NEWEMP*)malloc(sizeof(NEWEMP));
	tempLogin->next = NULL;
	headLogin = tempLogin;
    	temp->next = NULL;
	head = temp;

	// Launch Login Function and Load User Credentials into LinkedList from Textfile
	loginFunction(headLogin, strBuffer);

	// Load Linked List with Rows from the Employee Textfile
	loadFileToLinkedList(head, strBuffer);

	do
	{
		switch( userOptions = showMenu() )
		{
			case 1: 
				{
					addEmployee(head);
					break;
				}
			case 2:
				{ 
					searchEmployee(head);
					break;	
				}
			case 3: 
				{
					updateEmployee(head);
					break;
				}
			case 4:
				{
					deleteNode(head);
					break;	
				}
			case 5:
				{
					displayByDepartment(head);
					break;	
				}
			case 6:
				{ 
					employeeReport(head);
					break;	
				}
			case 7:
				{
					listNodes(head);
					break;
				}
			case 8:
				{
					printEmployees(head);
					exit(0);
					break;
				}
			default:
				{
					printf("\nInvalid Selection");
					break;
				}

		} // End switch-Case Statement

	}
	while ( userOptions < 8 );
	// End do While statement

	fflush(stdin);
	system("Pause");
	printf("\n\n\n");

} // End of main
