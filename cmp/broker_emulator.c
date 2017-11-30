#include "Control_Message_Processor.h"
#include<stdio.h>

int main()
{
  // For reading from file-system.
  /*
  //Create buffer to store XML file.
	char buff[100000];
	// Read file into buffer.
	FILE *fp;
	fp = fopen("XML_Test_File.xml", "r");
	if (fp == NULL)
	{
		printf("Failed to open file\n");
	}
	// Load file contents to the buffer.
	fread(buff, sizeof(char), 100000, fp);
	// Close file
	fclose(fp);
  */
  // Unit tests.
	char buff2[10000];
	char validMsg[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>e3f7c8de36bd352dce47a43d0a334df877ce2631</SHA1></CRL_MESSAGE>";
	char invalidMsg[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>a14f51c827d71674d746a30dd68ae32fba8f5c36</SHA1></CRL_MESSAGE>";
	
	strcpy(buff2, validMsg);
	//strcpy(buff2, invalidMsg);

	// Call process()
	int p = process(buff2);
	printf("\n%d", p);
	getch();

	return 0;
}
