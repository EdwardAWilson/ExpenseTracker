#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "trackerFunctions.h"

int main()
{
	time_t s, val = 1;
	struct tm* current_time;
	s = time(NULL);
	current_time = localtime(&s);
	int year = current_time->tm_year + 1900;
	int monthNumber = current_time->tm_mon + 1;
	int day = current_time->tm_mday;
	char* month = monthNumToString(monthNumber);
	
	char fileName[255];
	sprintf(fileName, "Data/%d/%s", year, month);

	FILE *fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		DIR* dir = opendir("Data");

		if (dir)
		{
			closedir(dir);
		}
		else if (ENOENT == errno)
		{
			mkdir("Data", S_IRWXU);
		}

		char yearDirectory[255];
		sprintf(yearDirectory, "Data/%d", year);
		dir = opendir(yearDirectory);

		if (dir)
		{
			closedir(dir);
		}
		else if (ENOENT == errno)
		{
			mkdir(yearDirectory, S_IRWXU);
		}

		FILE *fw = fopen(fileName, "w");
		fclose(fw);
		
		fp = fopen(fileName, "r");
	}

	char buff[255];
	int date = 1;
	char userInput[255];
	system("clear");
	printf("Welcome to Expense Tracker! Type help if you want to see commands\n\n$ ");
	fgets(userInput, 255, stdin);

	while (strcmp(userInput, "exit\n") != 0)
	{
		if (strcmp(userInput, "balance\n") == 0)
		{
			int date = 1;
			double balance = 0;

			while (fscanf(fp, "%s", buff) != EOF)
			{
				if (date)
				{
					date = 0;
				}
				else
				{
					balance += atof(buff);
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
		}

		if (strcmp(userInput, "input expense\n") == 0)
		{
			printf("\nPlease enter the expense for today: ");
			FILE *fw = fopen(fileName, "a");
			fgets(userInput, 255, stdin);
			double cost = -1 * atof(userInput);

			fprintf(fw, "%d %.2f\n", day, cost);
			printf("You have successfully entered $%.2f as an expense for today\n\n", -1 * cost);
			fclose(fw);
		}

		if (strcmp(userInput, "input income\n") == 0)
		{
			printf("\nPlease enter the income for today: ");
			FILE *fw = fopen(fileName, "a");
			fgets(userInput, 255, stdin);
			double income = atof(userInput);

			fprintf(fw, "%d %.2f\n", day, income);
			printf("You have successfully entered $%.2f as income for today\n\n", income);
			fclose(fw);
		}

		if (strcmp(userInput, "input expense previous day\n") == 0)
		{
			printf("\nPlease enter which day to add an expense to: ");
			fgets(userInput, 255, stdin);
			int selectedDay = atoi(userInput);

			printf("Please enter the expense for %s %d %d: ", month, selectedDay, year);
			fgets(userInput, 255, stdin);
			double cost = -1 * atof(userInput);

			FILE *fw = fopen(fileName, "a");
			fprintf(fw, "%d %.2f\n", selectedDay, cost);
			printf("You have successfully entered $%.2f as an expense for %s %d %d\n\n", -1 * cost, month, selectedDay, year);
			fclose(fw);
		}

		if (strcmp(userInput, "input income previous day\n") == 0)
		{
			printf("\nPlease enter which day to add income to: ");
			fgets(userInput, 255, stdin);
			int selectedDay = atoi(userInput);

			printf("Please enter the income for %s %d %d: ", month, selectedDay, year);
			fgets(userInput, 255, stdin);
			double income = atof(userInput);

			FILE *fw = fopen(fileName, "a");
			fprintf(fw, "%d %.2f\n", selectedDay, income);
			printf("You have successfully entered $%.2f as income for %s %d %d\n\n", income, month, selectedDay, year);
			fclose(fw);
		}

		if (strcmp(userInput, "print\n") == 0)
		{
			double balanceEntry[31][64] = {0};
			int balanceLength[31];
			double profit = 0;
			double losses = 0;
			
			double balance = 0;

			while (fscanf(fp, "%s", buff) != EOF)
			{
				int date = atoi(buff);
				fscanf(fp, "%s", buff);
				double entry = atof(buff);

				balanceEntry[date - 1][balanceLength[date - 1]++] = entry;
			}

			printf("\n%s\t\tIncome\t\tExpenses\n", month);
			printf("--------------------------------------------\n");

			for (int i = 0; i < 31; i++)
			{
				if (balanceEntry[i][0] != 0)
				{
					printf("%d\t\t\n", i + 1);
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

			printf("Total\t\t%.2f\t\t%.2f\n", profit, losses);
		
			printf("\n");
			rewind(fp);	
		}

		printf("$ ");
		fgets(userInput, 255, stdin);
	}

	fclose(fp);

	return 0;
}
