/* This program parses an XML file using the expat parser, and filters out the elements, attributes and the contents 
of each element, and prints it out in a readable format. */

#include<stdio.h>
#include<string.h>
#include<expat.h>

// Global! For storing a copy of the elements contents.
static char *cont;

// Element start tags. 
int start(void *data, const char *element, const char **Attribute)
{
	// Print current element.
	printf("Element: %s\n", element);
	// If attributes are present, print.
	if (Attribute[0] != NULL)
	{
		int i;
		printf("Attributes\n");
		for (i = 0; Attribute[i]; i += 2)
		{
			printf("%s= '%s'", Attribute[i], Attribute[i + 1]);
		}
		printf("\n");
	}
}
// Element end tags.
void end(void* data, const char* element)
{
	printf("Content of element %s was \"%s\"\n", element, cont);
}

// For getting contents within each element.
void content(void *data, const char *content, int length)
{
	char *temp = malloc(length);
	strncpy(temp, content, length);
	temp[length] = '\0';
	cont = (void *)temp;
	cont = temp;
}
void filter(char *buff, size_t buff_size)
{
	// Load xml file contents 
	FILE *fp;
	fp = fopen("C:/Users/Vignesh/source/repos/Project2/Debug/test.xml", "r");
	if (fp == NULL)
	{
		printf("Failed to open file\n");
	}
	// Create XML_Parser object.
	XML_Parser p = XML_ParserCreate(NULL);
	XML_SetElementHandler(p, start, end);
	XML_SetCharacterDataHandler(p, content);
	memset(buff, 0, buff_size);

	// Load file contents to the buffer.
	fread(buff, sizeof(char), buff_size, fp);
	if (XML_Parse(p, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR)
	{
		if (XML_GetErrorCode(p) == 9)
			;
		else
		{
			printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(p)));
		}
	}
	fclose(fp);
	XML_ParserFree(p);
}

//Testing
int main(int argc, char **argv)
{
	char buf[100000];
	filter(buf, 100000);
	getch();
	return 0;
}