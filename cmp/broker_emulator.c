/*
* Copyright (c) 2012-2014  Kirill Belyaev
* kirillbelyaev@yahoo.com
* kirill@cs.colostate.edu
* TeleScope - XML Message Stream Broker/Replicator Platform
* This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send
* a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*
* Author: Vignesh M. Pagadala
* Vignesh.Pagadala@colostate.edu
* Last update: December 2nd, 2017
*
* File: broker_emulator.c
* ----------------------------------
* This file contains valid and invalid test-vectors for testing Control_Message_Processor's functionality.
*/

#include "globals2.h"

int main()
{
	// Test vectors for control message processing.

	// 1. Valid message.
	char validMsg[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>af54662f0e3ada437df84af8a70c8b54c329840d</SHA1></CRL_MESSAGE>";
	printf("\n1. Valid message:\n %s\n\n", validMsg);
	process(validMsg);
	printf("\n\n");

	// 2. Invalid message: Has incorrect SHA-1 digest.
	char invalidMsg[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>a14f51c827d71674d746a30dd68ae32fba8f5c36</SHA1></CRL_MESSAGE>";
	printf("\n2. Invalid message (incorrect SHA-1 digest):\n %s\n\n", invalidMsg);
	process(invalidMsg);
	printf("\n\n");

	// 3. Invalid message: Not well-formed - bad ending.
	char invalidMsg2[] = "<ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>a14f51c827d71674d746a30dd68ae32fba8f5c36";
	printf("\n3. Invalid message (not well-formed with bad ending):\n %s\n\n", invalidMsg2);
	process(invalidMsg2);
	printf("\n\n");

	// 4. Invalid message: Not well-formed - tag imbalance (FilteringQuery's closing tag is missing). Has correct digest.
	char invalidMsg3[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40<SHA1>937d544be89f5380468bd0f3081d4ae6d93796bd</SHA1></CRL_MESSAGE>";	
	printf("\n4. Invalid message (not well-formed with open/close tag imbalance):\n %s\n\n", invalidMsg3);
	process(invalidMsg3);
	printf("\n\n");

	// 5. Invalid message: Has missing elements. In the following test-vector, 'RootBrokerID' is missing. Has correct digest.
	char invalidMsg4[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>06a6efc6ff7a93e097ccac6d12dff48ab4e6c3e3</SHA1></CRL_MESSAGE>";
	printf("\n5. Invalid message (missing elements - RootBrokerID missing):\n %s\n\n", invalidMsg4);
	process(invalidMsg4);
	printf("\n\n");

	// 6. Invalid message: Contents of some elements (except UBL and FQ) are empty. In the following example, ChildBrokerID's contents are missing. Has correct digest.
	char invalidMsg5[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID></ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>1b04d4e5a5bd6ea16a2bef7a06cdd337fc8521bc</SHA1></CRL_MESSAGE>";
	printf("\n6. Invalid message (empty elements - ChildBrokerID empty):\n %s\n\n", invalidMsg5);
	process(invalidMsg5);
	printf("\n\n");

	// 7. Valid message.
	char validMsg2[] = "<CRL_MESSAGE length =\"0005130\"><ControlMessageLength>0005130</ControlMessageLength><ControlMessageID>ID0032</ControlMessageID><RootBrokerID>192.148.540.110:67400</RootBrokerID><ChildBrokerID>122.148.122.132:57850</ChildBrokerID><UBL><Broker1 IP = \"119.82.47.138\" Port = \"8040\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND35</FilteringQuery><SHA1>199969a3d3bd35a096996a2e410c0624b7251cd1</SHA1></CRL_MESSAGE>";
	printf("\n7. Valid message:\n %s\n\n", validMsg2);
	process(validMsg2);
	printf("\n\n");
	

	// Unit tests for SHA-1 validation.

	// 1. Authentic message. 
	char authMsg1[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>af54662f0e3ada437df84af8a70c8b54c329840d</SHA1></CRL_MESSAGE>";
	char shamsg[] = "af54662f0e3ada437df84af8a70c8b54c329840d";
	if (strcmp(shafunc(authMsg1), shamsg) == 0)
	{
		printf("The message \n\n %s \n\n is valid.\n\n\n", authMsg1);
	}
	else
	{
		printf("The message \n\n %s \n\n is invalid.\n\n\n", authMsg1);
	}

	// 2. Forged message.
	char forgedMsg1[] = "<CRL_MESSAGE length =\"0000500\"><ControlMessageLength>0000500</ControlMessageLength><ControlMessageID>CM0002</ControlMessageID><RootBrokerID>192.168.100.1:50000</RootBrokerID><ChildBrokerID>192.168.102.1:55550</ChildBrokerID><UBL><Broker1 IP = \"129.82.47.138\" Port = \"80\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND40</FilteringQuery><SHA1>a14f51c827d71674d746a30dd68ae32fba8f5c36</SHA1></CRL_MESSAGE>";
	char shamsg2[] = "a14f51c827d71674d746a30dd68ae32fba8f5c36";
	if (strcmp(shafunc(forgedMsg1), shamsg2) == 0)
	{
		printf("The message \n\n %s \n\n is valid.\n\n\n", authMsg1);
	}
	else
	{
		printf("The message \n\n %s \n\n is invalid.\n\n\n", forgedMsg1);
	}

	// 3. Authentic message.
	char authMsg2[] = "<CRL_MESSAGE length =\"0005130\"><ControlMessageLength>0005130</ControlMessageLength><ControlMessageID>ID0032</ControlMessageID><RootBrokerID>192.148.540.110:67400</RootBrokerID><ChildBrokerID>122.148.122.132:57850</ChildBrokerID><UBL><Broker1 IP = \"119.82.47.138\" Port = \"8040\" NameID = \"alpha\" Priority = \"60\"></Broker1><Broker2 IP = \"129.82.47.234\" Port = \"8080\" NameID = \"beta\" Priority = \"10\"></Broker2><Broker3 IP = \"129.82.47.242\" Port = \"5050\" NameID = \"gamma\" Priority = \"5\"></Broker3><Broker4 IP = \"129.82.47.230\" Port = \"8888\" NameID = \"delta\" Priority = \"0\"></Broker4></UBL><FilteringQuery>Industry = IND35</FilteringQuery><SHA1>199969a3d3bd35a096996a2e410c0624b7251cd1</SHA1></CRL_MESSAGE>";
	char shamsg3[] = "199969a3d3bd35a096996a2e410c0624b7251cd1";
	if (strcmp(shafunc(authMsg2), shamsg3) == 0)
	{
		printf("The message \n\n %s \n\n is valid.\n\n\n", authMsg1);
	}
	else
	{
		printf("The message \n\n %s \n\n is invalid.\n\n\n", authMsg2);
	}

	getchar();
	return 0;
}
