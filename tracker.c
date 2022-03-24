#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "helpers.h"
#include "operations.h"

int main()
{
	time_t s, val = 1;
	struct tm* current_time;
	s = time(NULL);
	current_time = localtime(&s);
	int year = current_time->tm_year + 1900;
	int monthNumber = current_time->tm_mon + 1;
	int today = current_time->tm_mday;
	char* month = monthNumToString(monthNumber);
	
	char fileName[255];
	sprintf(fileName, "Data/%d/%s", year, month);

	FILE *fp = fopen(fileName, "r+");

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
			balance(fp, buff);	
		}
		else if (strcmp(userInput, "input expense\n") == 0)
		{
			inputToday(fileName, today, 1);
		}
		else if (strcmp(userInput, "input income\n") == 0)
		{
			inputToday(fileName, today, 0);
		}
		else if (strcmp(userInput, "input expense select day\n") == 0)
		{
			inputSelectDay(fileName, month, year, 1);
		}
		else if (strcmp(userInput, "input income select day\n") == 0)
		{
			inputSelectDay(fileName, month, year, 0);
		}
		else if (strcmp(userInput, "print\n") == 0)
		{
			print(fp, month, 1);
		}
		else if (strcmp(userInput, "delete\n") == 0)
		{
			removeEntry(fp, month);
		}
		else
		{
			printf("\nPlease enter a valid command\n\n");
		}

		printf("$ ");
		fgets(userInput, 255, stdin);
	}

	fclose(fp);

	return 0;
}
