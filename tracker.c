#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

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

int main()
{
	time_t s, val = 1;
	struct tm* current_time;
	s = time(NULL);
	current_time = localtime(&s);
	int year = current_time->tm_year + 1900;
	int monthNumber = current_time->tm_mon + 1;
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
	}

	char buff[255];
//	printf("%s\n", fgets(buff, 255, fp));
//	printf("%s\n", fgets(buff, 255, fp));

	return 0;
}
