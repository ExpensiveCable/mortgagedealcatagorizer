/*
 * mortgage.c
 *
 *  Created on: 29 Mar 2021
 *      Author: Carl Erik Larsen
 */

#include <stdio.h>
#include <stdlib.h>
#define SSIZE 30 /* maximum SIZE of string, including NUL */
#define LSIZE 15 /* SIZE of list*/

struct deal{ 				// defines a structure that organises the data for each mortgage
		char lender[SSIZE];
		int duration;
		float initial_rate;
		float rate_after;
		int loan_value;
		int fee;
	 };

int main(void) {
	int compare(const void*, const void*); 										// initialises the compare function
	char proceed = 'y'; 														// defines the proceed variable that will regulate if the program will run
	FILE *fin; /* define a file pointer */
	fin = fopen("mortgage.txt", "r"); /* open data.txt file for read */
	struct deal deals[LSIZE]; 													// defines an array of structures named deals that are in the form of deal
	struct deal condition;  													// defines a single structure named condition that is in the form of deal
	printf("---- The original input data ----\n");
	for(int i=0; i<LSIZE; i++) 													// iterates over all of the mortgages in the file
	{
		fscanf(fin, "%s %d %f %f %d %d", deals[i].lender, &deals[i].duration, &deals[i].initial_rate, &deals[i].rate_after, &deals[i].loan_value, &deals[i].fee);
		/* read file and save data to variables */
		printf("%s %d %.2f %.2f %d %d \n", deals[i].lender, deals[i].duration, deals[i].initial_rate, deals[i].rate_after, deals[i].loan_value, deals[i].fee);
		/* print values of variables to screen */
	}
	fclose(fin); /* close file properly */
	qsort(deals, LSIZE, sizeof(struct deal), compare); 							// the qsort functionality is integrated to most efficiently sort the mortgages
	printf("---- The sorted data ---- \n");
	for(int i=0; i<LSIZE; i++) 													// iterates over all of the mortgages in the file
	{
		printf("%s %d %.2f %.2f %d %d \n", deals[i].lender, deals[i].duration, deals[i].initial_rate, deals[i].rate_after, deals[i].loan_value, deals[i].fee);
		/* print values of variables to screen */
	}
	while (proceed == 'y') 														// continues to iterate unless proceed does not equal 'y'
	{
		printf("Do you want to proceed (y/q)?\n"); 								// asks the user if they want to run the code or terminate it
		setbuf(stdout, NULL); 													// buffer to delay the code
		scanf("%s", &proceed); 													// scans the console for a new value of proceed
		if (proceed == 'q') 													// if the user wants to quit the program
		{
			printf("The Program has Terminated\n");
		}
		else if (proceed == 'y')												// if the user wants to run the program
		{
			printf("What are the requirements?\n"); 							// user is asked for the requirements of the mortgages
			setbuf(stdout, NULL);
			int empty = 0; 														// the empty condition is defined and will be used to determine if there are no mortgages fitting the conditions
			scanf("%d %f %f %d %d", &condition.duration, &condition.initial_rate, &condition.rate_after, &condition.loan_value, &condition.fee);
			/* scanf is used assign the input conditions to variables*/
			for(int i=0; i<LSIZE; i++) 											// iterates over each mortgage
			{
				if ((condition.duration <= deals[i].duration) && (condition.initial_rate >= deals[i].initial_rate) && (condition.rate_after >= deals[i].rate_after) && (condition.loan_value <= deals[i].loan_value) && (condition.fee >= deals[i].fee))
				{																// if there are any mortgages satisfying the condition specified above the following code executes to print them
					printf("%s %d %.2f %.2f %d %d \n", deals[i].lender, deals[i].duration, deals[i].initial_rate, deals[i].rate_after, deals[i].loan_value, deals[i].fee);
					/* print values of variables to screen */
					empty = 1; 													// the empty integer is redefined so the condition below is not satisfied
				}

			}
			if (empty == 0) printf("Nothing Found\n"); 							// if the above code has not run and therefore empty is still zero, prints that no mortgages were found

		}
		else
		{
			printf("Please enter a valid input!\n"); 							// if neither 'y' or 'q' were entered
			proceed = 'y'; 														// user is given another chance to enter a valid input
		}
	}
	return 0;
}

int compare(const void * a, const void * b) { 									// defines the function compare which was initialised and called in the main. This is required by qsort
	struct deal * deal_a = (struct deal*)a;  									// a is cast to a deal struct pointer
	struct deal * deal_b = (struct deal*)b;	 									// b is cast to a deal struct pointer
	if (deal_a->initial_rate != deal_b->initial_rate){
		return deal_a->initial_rate - deal_b->initial_rate < 0 ? -1 : 1; 		// Using ternary operator returns one when true and zero when false
	}
	if (deal_a->fee != deal_b->fee){
		return deal_a->fee - deal_b->fee < 0 ? -1 : 1;
	}
	return 0;
}
