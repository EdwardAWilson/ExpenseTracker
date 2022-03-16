#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void balance(FILE* fp, char* buff)
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

	return;
}

void inputExpense(char* fileName, int day)
{
	char userInput[255];
	printf("\nPlease enter the expense for today: ");
	FILE *fw = fopen(fileName, "a");

	fgets(userInput, 255, stdin);
	double cost = -1 * atof(userInput);

	fprintf(fw, "%d %.2f\n", day, cost);
	printf("You have successfully entered $%.2f as an expense for today\n\n", -1 * cost);

	fclose(fw);
}

void inputIncome(char* fileName, int day)
{
	char userInput[255];
	printf("\nPlease enter income for today: ");
	FILE *fw = fopen(fileName, "a");

	fgets(userInput, 255, stdin);
	double income = atof(userInput);

	fprintf(fw, "%d %.2f\n", day, income);
	printf("You have successfully entered $%.2f as income for today\n\n", income);

	fclose(fw);
}

void inputExpensePreviousDay(char* fileName, char* month, int year)
{
	char userInput[255];
	printf("\nPlease enter which day to add an expense to: ");
	fgets(userInput, 255, stdin);
	int selectedDay = atoi(userInput);

	printf("Please enter income for %s %d %d: ", month, selectedDay, year);
	FILE *fw = fopen(fileName, "a");
	fgets(userInput, 255, stdin);
	double cost = -1 * atof(userInput);
	fprintf(fw, "%d %.2f\n", selectedDay, cost);
	printf("You have successfully entered $%.2f as an expense for %s %d %d\n\n", -1 * cost, month, selectedDay, year);

	fclose(fw);
}

void inputIncomePreviousDay(char* fileName, char* month, int year)
{
	char userInput[255];
	printf("\nPlease enter which day to add income to: ");
	fgets(userInput, 255, stdin);
	int selectedDay = atoi(userInput);

	printf("Please enter income for %s %d %d: ", month, selectedDay, year);
	FILE *fw = fopen(fileName, "a");
	fgets(userInput, 255, stdin);
	double income = atof(userInput);
	fprintf(fw, "%d %.2f\n", selectedDay, income);
	printf("You have successfully entered $%.2f as income for %s %d %d\n\n", income, month, selectedDay, year);

	fclose(fw);
}

void print(FILE* fp, char* month)
{
	char buff[255];
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

	printf("Total\t\t%.2f\t\t%.2f\n", profit, losses);
		
	printf("\n");
	rewind(fp);	
}
