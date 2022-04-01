#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

void balance(FILE* fp, char* buff)
{
	int date = 1;
	int entry = 0;
	double balance = 0;

	while (fscanf(fp, "%s", buff) != EOF)
	{
		if (date)
		{
			date = 0;
			entry = 1;
		}
		else if (entry)
		{
			balance += atof(buff);
			entry = 0;
		}
		else
		{
			date = 1;
		}
	}

	if (balance >= 0)
	{
		printf("\nYour current balance for this month is: $%.2f\n\n", balance);
	}
	else
	{
		printf("\nYour current balance for this month is: -$%.2f\n\n", -1 * balance);
	}

	rewind(fp);

	return;
}

void inputToday(char* fileName, int day, int expense, int marker)
{	char userInput[255];

	if (expense)
		printf("\nPlease enter the expense for today: ");
	else
		printf("\nPlease enter income for today: ");

	FILE *fw = fopen(fileName, "a");

	if (getUserInput(userInput)) return;
	double fragment;
	
	 if (expense)	
		fragment = -1 * atof(userInput);
	 else
		fragment = atof(userInput);

	fprintf(fw, "%d %.2f %d\n", day, fragment, marker);

	if (expense)
		printf("You have successfully entered $%.2f as an expense for today\n\n", -1 * fragment);
	else
		printf("You have successfully entered $%.2f as income for today\n\n", fragment);

	fclose(fw);
}

void inputSelectDay(char* fileName, char* month, int year, int expense, int marker)
{
	char userInput[255];
	int check = 0;
	int selectedDay;

	while (!check)
	{
		if (expense)
			printf("\nPlease enter which day to add an expense to: ");
		else
			printf("\nPlease enter which day to add income to: ");

		if (getUserInput(userInput)) return;

		selectedDay = atoi(userInput);
		check = checkValidDay(selectedDay, monthStringToNum(month));
	}

	if (expense)
		printf("Please enter an expense for %s %d %d: ", month, selectedDay, year);
	else
		printf("Please enter income for %s %d %d: ", month, selectedDay, year);

	if (getUserInput(userInput)) return;

	FILE *fw = fopen(fileName, "a");
	double fragment;

	if (expense)
		fragment = -1 * atof(userInput);
	else
		fragment = atof(userInput);

	fprintf(fw, "%d %.2f %d\n", selectedDay, fragment, marker);

	if (expense)
		printf("You have successfully entered $%.2f as an expense for %s %d %d\n\n", -1 * fragment, month, selectedDay, year);
	else
		printf("You have successfully entered $%.2f as income for %s %d %d\n\n", fragment, month, selectedDay, year);

	fclose(fw);
}

void print(FILE* fp, char* month, int extra)
{
	char buff[255];
	double balanceEntry[31][64] = {0};
	int balanceLength[31] = {0};
	double profit = 0;
	double losses = 0;
	double balance = 0;

	while (fscanf(fp, "%s", buff) != EOF)
	{
		int date = atoi(buff);
		fscanf(fp, "%s", buff);
		double entry = atof(buff);

		balanceEntry[date - 1][balanceLength[date - 1]++] = entry;	
		fscanf(fp, "%s", buff);	
	}

	printf("\n%s\t\tIncome\t\tExpenses\n", month);
	printf("--------------------------------------------\n");

	for (int i = 0; i < 31; i++)
	{
		if (balanceEntry[i][0] != 0)
		{
			char ordinal[4];
			ordinalNumber(i + 1, ordinal);
			printf("%s\t\t\n", ordinal);
		}

		for (int j = 0; j <= balanceLength[i]; j++)
		{

			if (balanceEntry[i][j] != 0)
			{
				if (balanceEntry[i][j] > 0)
				{
					printf("\t\t%.2f\n", balanceEntry[i][j]);
					profit += balanceEntry[i][j];
				}
				else
				{
					printf("\t\t\t\t%.2f\n", balanceEntry[i][j]);
					losses += balanceEntry[i][j];
				}
			}

		}
				
		if (balanceEntry[i][0] != 0)
		{
			printf("--------------------------------------------\n");
		}
	}

	if (extra)
	{
		printf("Total\t\t%.2f\t\t%.2f\n", profit, losses);
	}
		
	printf("\n");
	rewind(fp);	
}

void removeEntry(FILE* fp, char* month)
{
	char userInput[255];
	char buff[255];
	int selectedDay = 0;
	int check1 = 0;
	int check2 = 0;
	int pos = 0;
	double balanceEntry[31][64] = {0};
	int balanceLength[31] = {0};
	int balancePosition[31][64] = {0};
	print(fp, month, 0);

	while (fscanf(fp, "%s", buff) != EOF)
	{
		int date = atoi(buff);
		fscanf(fp, "%s", buff);
		double entry = atof(buff);

		balanceEntry[date - 1][balanceLength[date - 1]] = entry;
		balancePosition[date - 1][balanceLength[date - 1]++] = pos++;
		fscanf(fp, "%s", buff);
	}
	rewind(fp);

	while (!check1)
	{
		while (!check2)
		{
			printf("\nPlease enter the day which you would like to delete from: ");

			if (getUserInput(userInput)) return;
	
			selectedDay = atoi(userInput);
			check2 = checkValidDay(selectedDay, monthStringToNum(month));
		}

		if (balanceLength[selectedDay - 1] == 0)
		{
			printf("Please enter a day which has entries associated with it.\n");
			check2 = 0;
		}
		else
		{
			check1 = 1;
			printf("\n");
			
			for (int i = 0; i < balanceLength[selectedDay - 1]; i++)
			{
				if (balanceEntry[selectedDay - 1][i] < 0)
					printf("%d:\t\t%.2f\n", i + 1, balanceEntry[selectedDay - 1][i]);	
				else
					printf("%d:\t\t %.2f\n", i + 1, balanceEntry[selectedDay - 1][i]);	
			}

			check2 = 0;
			int selectedEntry = 0;

			while (!check2)
			{
				printf("\nPlease enter the entry you would like to delete: ");

				if (getUserInput(userInput)) return;

				selectedEntry = atoi(userInput);
				if (selectedEntry > 0 && selectedEntry <= balanceLength[selectedDay - 1])
				{
					check2 = 1;
					int count = 0;
					int length = 0;
					unsigned int curpos = 0;

					while (count++ != balancePosition[selectedDay - 1][selectedEntry - 1])
					{
						fscanf(fp, "%s", buff);
						fscanf(fp, "%s", buff);
						fscanf(fp, "%s", buff);
						curpos = ftell(fp) + 1;
					}

					fscanf(fp, "%s", buff);
					length = strlen(buff);
					fscanf(fp, "%s", buff);
					length += strlen(buff) + 3;

					fseek(fp, curpos, SEEK_SET);

					for (int i = 0; i < length; i++)
					{
						fprintf(fp, " ");
					}

					double entry = atof(buff);

					if (entry < 0)
						printf("Successfully deleted entry of -$%.2f\n", -1 * entry);
					else
						printf("Successfully deleted entry of $%.2f\n", entry);
				}
				else
				{
					printf("Please choose from the entries associated with the day.\n");
				}
			}
		}	
	}
	
	rewind(fp);
	printf("\n");
}

void setWeeklyExpense()
{
	char userInput[255];
	char fileName[14] = "Data/Settings";
	int check = 0;
	double weeklyExpense;

	while (!check)
	{
		printf("\nPlease enter the amount per week you would like to spend: ");

		if (getUserInput(userInput)) return;

		weeklyExpense = atof(userInput);
		
		if (weeklyExpense < 0)
		{
			printf("Please enter a valid amount.\n");
		}
		else
		{
			check = 1;
		}
	}

	FILE *fp = fopen(fileName, "r");

	if (fp != NULL)
	{
		fclose(fp);
		remove(fileName);
	}

	fp = fopen(fileName, "w");
	fprintf(fp, "%.2f", weeklyExpense);

	printf("Successfully set $%.2f as weekly expenditure amount.\n\n", weeklyExpense);

	fclose(fp);
}
