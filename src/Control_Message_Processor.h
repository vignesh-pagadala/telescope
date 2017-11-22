/* Parses an XML file using the expat parser, and filters out UBL and FQ. Validates using SHA-1 hash */

#include<stdio.h>
#include<string.h>
#include<expat.h>
#include<stdlib.h>

// Globals. 
//For storing a copy of the elements contents.
static char *cont;
//Flag for extracting UBL and FQ. 1= ubl, 2 - fq, 3 - sha1
int flag = 0;
// For storing UBL
char *ubl;
// For storing FQ
char *fq;
// For storing SHA-1
char *sha1;


// Element start tags.
void start(void *data, const char *element, const char **Attribute)
{
	// If flag is set, print element name and attributes it has.
	if (flag == 1)
	{
		// Append current element to ubl.
		//printf("Element: %s\n", element);
		strcat(ubl, element);
		strcat(ubl, ":");

		// If attributes are present, append.
		
		if (Attribute[0] != NULL)
		{
			int i;
			//printf("Attributes\n");
			for (i = 0; Attribute[i]; i += 2)
			{
				//printf("%s= '%s'", Attribute[i], Attribute[i + 1]);
				strcat(ubl, Attribute[i]);
				strcat(ubl, "=");
				strcat(ubl, Attribute[i+1]);
				strcat(ubl, ",");
			}
			//printf("\n");
		}
	}

	// Check if the current element is UBL or Filtering Query
	if (strcmp(element, "UBL") == 0)
	{
		// Set flag
		flag = 1;
	}
	if (strcmp(element, "FilteringQuery") == 0)
	{
		// Set flag
		flag = 2;
	}
	if (strcmp(element, "SHA") == 0)
	{
		// Set flag
		flag = 3;
	}
	if (strcmp(element, "ControlMessageLength") == 0)
	{
		// Set flag
		flag = 4;
	}
	
}
// Element end tags.
void end(void* data, const char* element)
{
	if (strcmp(element, "ControlMessageLength") == 0 && flag == 4)
	{
		//printf("%s\n", cont);
		ubl = (char*)malloc(sizeof(char) * atoi(cont));
		*ubl = '\0';
		flag = 0;
	}
	// If flag is set and end tag is encountered for UBL, then reset flag.
	if (flag == 1)
	{
		//printf("Content of element %s was \"%s\"\n", element, cont);
		if (strcmp(element, "UBL") == 0)
		{
			flag = 0;
		}

		// If end tag is encountered for BrokerN
		if (strcmp(element, "Broker1") == 0 || strcmp(element, "Broker2") == 0 || strcmp(element, "Broker3") == 0 || strcmp(element, "Broker4") == 0)
		{
			// Append a \n
			strcat(ubl, "\n");
		}
	}

	if (flag == 2)
	{
		fq = (char*)malloc(sizeof(char) * (strlen(cont) + 1));
		*fq = '\0';
		strcat(fq, cont);
		if (strcmp(element, "FilteringQuery") == 0)
		{
			flag = 0;
		}
	}

	if (flag == 3)
	{
		sha1 = (char*)malloc(sizeof(char) * (strlen(cont)+1));
		*sha1 = '\0';
		strcat(sha1, cont);
		if (strcmp(element, "SHA") == 0)
		{
			flag = 0;
		}
	}
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
	// Create XML_Parser object.
	XML_Parser p = XML_ParserCreate(NULL);
	XML_SetElementHandler(p, start, end);
	XML_SetCharacterDataHandler(p, content);
	if (XML_Parse(p, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR)
	{
		if (XML_GetErrorCode(p) == 9)
			;
		else
		{
			//printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(p)));
		}
	}
	XML_ParserFree(p);
}

// Returns UBL
char* UBL()
{
	return ubl;
}

// Returns a FQ
char* FQ()
{
	return fq;
}

// Test SHA fn - PENDING
char* shafunc(char buff[100000])
{
	return "f24e84445c27fdd906c828ce26a69222329235c4";
}

int process(char buff[100000])
{
	filter(buff, 100000);
	if (strcmp(sha1, shafunc(buff)) == 0)
	{
		printf("Upstream Brokers List: \n%s", UBL());
		printf("\nFiltering Query: %s \n", FQ());

		// Deallocate
		free(sha1);
		free(ubl);
		free(fq);
		return 0;
	}
	else
	{
		free(sha1);
		free(ubl);
		free(fq);
		return -1;
	}
}


