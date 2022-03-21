#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* monthNumToString(int num)
{
	switch (num)
	{
		case 1:
			return "January";
		case 2:
			return "February";
		case 3:
			return "March";
		case 4:
			return "April";
		case 5:
			return "May";
		case 6:
			return "June";
		case 7:
			return "July";
		case 8:
			return "August";
		case 9:
			return "September";
		case 10:
			return "October";
		case 11:
			return "November";
		default:
			return "December";
	}
}

int monthStringToNum(char* month)
{
	if (strcmp(month, "January") == 0)
	{
		return 1;
	}
	else if (strcmp(month, "February") == 0)
	{
		return 2;
	}
	else if (strcmp(month, "March") == 0)
	{
		return 3;
	}
	else if (strcmp(month, "April") == 0)
	{
		return 4;
	}
	else if (strcmp(month, "May") == 0)
	{
		return 5;
	}
	else if (strcmp(month, "June") == 0)
	{
		return 6;
	}
	else if (strcmp(month, "July") == 0)
	{
		return 7;
	}
	else if (strcmp(month, "August") == 0)
	{
		return 8;
	}
	else if (strcmp(month, "September") == 0)
	{
		return 9;
	}
	else if (strcmp(month, "October") == 0)
	{
		return 10;
	}
	else if (strcmp(month, "November") == 0)
	{
		return 11;
	}
	else
	{
		return 12;
	}
}

void ordinalNumber(int num, char* output)
{
	char* ordinalEnding;

	if (num % 10 == 1)
	{
		ordinalEnding = "st";
	}
	else if (num % 10 == 2)
	{
		ordinalEnding = "nd";
	}
	else if (num % 10 == 3)
	{
		ordinalEnding = "rd";
	}
	else
	{
		ordinalEnding = "th";
	}
	
	if (num == 11 || num == 12 || num == 13)
	{
		ordinalEnding = "th";
	}

	sprintf(output, "%d%s", num, ordinalEnding);
}

int isValidDay(int day, int month)
{
	if (day <= 0)
	{
		return 0;
	}

	if (month == 2)
	{
		if (day < 29)
		{
			return 1;
		}
		return 0;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day < 31)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		if (day < 32)
		{
			return 1;
		}
		return 0;
	}
}

int checkValidDay(int day, int month)
{
	if (isValidDay(day, month))
	{
		return 1;
	}
	else
	{
		printf("Please enter a valid day for the selected month\n");
		return 0;
	}
}

int getUserInput(char* userInput)
{
	fgets(userInput, 255, stdin);

	if (strcmp(userInput, "exit\n") == 0)
	{
		printf("\n");
		return 1;
	}
	else
	{
		return 0;
	}
}
