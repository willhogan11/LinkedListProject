// Header file include
#include "employeeHeaderFile.h" 

/*  loadFileToLinkedList: (Called in Main)
This function loads the LinkedList with rows from the Employee textfile */
void loadFileToLinkedList(NEWEMP *head, char buffer[])
{
	FILE *fptr = fopen(FILENAME, READMODE);
	NEWEMP *temp = (NEWEMP*)malloc(sizeof(NEWEMP));
	temp = head;

	/*Opens the File and reads in all employees row by row into the LinkedList*/
    while (!feof(fptr) )
	{
        fgets(buffer, MAXCOUNT, fptr);
		fflush(stdin);
		sscanf(buffer, "%d %s %s %s %s %d %d %d %f %s\n", 
									&temp->id,
									temp->FName, 
									temp->LName,
									temp->empAddr,
									temp->department,
									&temp->dateOfJoining.day, 
									&temp->dateOfJoining.month, 
									&temp->dateOfJoining.year, 
									&temp->annualSalary,
									temp->email); 
									fflush(stdin);

		// Uncomment the DEBUG Definition in the Header file to Exit DEBUG mode that shows that the Contents 
		// were successfully read into the LinkedList from the Employee TextFile
		#ifndef DEBUG
		printf("%d %s %s %s %s %d %d %d %5.2f %s\n", 
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
		#endif

        temp->next = (NEWEMP*)malloc(sizeof(NEWEMP));
        temp = temp->next;
        temp->next = NULL;

	} // End while(!feof(fptr) )

	fclose(fptr);
	system("Pause");

} // End loadFileToLinkedList function




// Login Function: (Called in Main)
/* Firstly all Usernames & Password are loaded in row by row from the Text File into the Login Linked List. 
   User is then prompted for Username 7 Password, if matched, Logged. else re-eneter until correct */
void loginFunction(LOGIN *headLogin, char buffer[])
{
	int i = 0, j = 0, countIncorrect = 0;
	int correctUserName = FALSE, correctPassword = FALSE;
	char uName[MAXNAME + 1];
	char pWord[MAXNAME + 1];
	char t = '\0'; // [MAXCOUNT + 1];

	FILE *fptr;
	LOGIN *login;
	login = (LOGIN*)malloc(sizeof(LOGIN));
	login = headLogin;
	
	fptr = fopen(LOGINFILE, READMODE);

	// Loads in the Usernames and Passwords row by row into the Login Linked List
	while (!feof(fptr) )
	{
		fgets(buffer, MAXCOUNT, fptr);
		sscanf(buffer, "%s %s\n", login->userName, login->passWord);
		fflush(stdin);

		// Comment out '#define DEBUG_USER_PWORD' in the Header File, to View Usernames and passwords on screen
		#ifndef DEBUG_USER_PWORD
			printf("%s %s\n", login->userName, login->passWord);
		#endif

		login->next = (LOGIN*)malloc(sizeof(LOGIN));
		login = login->next;
		login->next = NULL; // Sets next Node to Null once File is Empty
	} // End while

	fclose(fptr);

	system("Pause");
	system("cls");

	login = headLogin;

	// Prompts User for Username and then password
	LOGIN_DETAILS:
	if(countIncorrect > 0)
	{
		// uName[j] = '\0';
		for(i = 0; i < MAXNAME; ++i)
		{
			pWord[i] = 0;
			break;
		}
	} // End if

	puts("PLEASE LOGIN");
	puts(" ________________");
	puts("|Enter a Username|");
	puts("|________________|");
	gets(uName);
	fflush(stdin);
	
	puts(" ________________");
	puts("|Enter a Password|");
	puts("|________________|");
	fflush(stdin);
	
	/*For each character of the password entered, it's converted to a * on screen, but value is stored
	If details entered are correct, user is Welcomed with a Message and is informed that they are logged in. 
	If details entered (Either username or password) are incorrect, user is promted again for their Credentials*/
	do
	{
		t = getch();
		if(t == '\b' && i > 0)
		{
			i--;
			putch(t);
			putch(' ');
			putch(t);
		}	
		else if(t!='\r' && t!='\b')
		{
			putch('*');
			pWord[i] = t;
			i++;
		}
		pWord[i]='\0';
		
	} // End while
	while(t != '\r');

	// login = headLogin;

	do
	{
		if(strcmp(login->userName, uName) == 0 )
		{
			correctUserName = TRUE;
		}
		if(strcmp(login->passWord, pWord) == 0 )
		{
			correctPassword = TRUE;
		}
	}
	while ( (login->next != NULL) && (login = login->next) );

	if (correctUserName == TRUE && correctPassword == TRUE)
	{
		printf("\n\nWelcome %s", uName);
		puts("\nYou are now logged on");
	}
	else
	{
		puts("\nIncorrect Details");
		++countIncorrect;
		goto LOGIN_DETAILS;	
	}
	puts("\n\n\n");
	
} //  End of loginFunction