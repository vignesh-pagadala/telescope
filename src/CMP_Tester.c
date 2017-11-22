// Testing Control_Message_Processor.

#include "Control_Message_Processor.h"
#include<stdio.h>
int main()
{
	//Create buffer to store XML file.
	char buff[100000];

	// Read file into buffer.
	FILE *fp;

	fp = fopen("C:/Users/Vignesh/source/repos/Project2/Debug/XML_Test_File.xml", "r");
	if (fp == NULL)
	{
		printf("Failed to open file\n");
	}

	// Load file contents to the buffer.
	fread(buff, sizeof(char), 100000, fp);

	// Close file
	fclose(fp);

	// Call process()
	int p = process(buff);
	printf("\n%d", p);
	getch();

	return 0;
}
