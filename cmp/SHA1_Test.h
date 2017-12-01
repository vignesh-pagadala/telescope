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
*
* This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit
* (http://www.openssl.org/).
*
* File: SHA1_Test.h
* ----------------------------------
* An implementation of Secure Hash Algorithm 1, used to validate an XML control message. Takes in a 
* complete XML message as a parameter, strips the existing SHA-1 in the message and uses the remaining
* portion of the message to compute a SHA-1 digest.
*/

#include<stdio.h>
#include<string.h>
#include<expat.h>
#include<stdlib.h>
#include<process.h>
#include<openssl\sha.h>
#include<time.h>

// For introducing time-delay.
void delay2(unsigned int seconds)
{
	int elapsed = time(0) + seconds;
	while (time(0) < elapsed);
}

int shafuncTest(char *buff, char* sha)
{
	// Use 'buff' to generate a SHA-1 hash and return it.
	// Process 'buff' and strip existing SHA-1 from it. 
	uint_fast16_t Buffer_Length = strlen(buff) + 1;

	// Create temporary buffer to hold 'buff'.
	char *testbuf = (char*)malloc(sizeof(char*) * Buffer_Length);
	if (testbuf == NULL)
	{
		perror("Error: Could not allocate memory for testbuf. \n Terminating program...");
		delay2(1);
		exit(0);
	}
	strcpy(testbuf, buff);


	uint_fast8_t shaflag = 0;
	uint_fast16_t kc = 0;

	// Create buffer 'testbuf2' to hold the XML message without SHA-1 digest.
	char *testbuf2 = (char*)malloc(sizeof(char*) * Buffer_Length);
	if (testbuf2 == NULL)
	{
		perror("Error: Could not allocate memory for testbuf2. \n Terminating program...");
		delay2(1);
		exit(0);
	}
	// Strip existing SHA-1 from testbuf and store in testbuf2.
	char shatag[7];
	for (uint_fast16_t l = 0; testbuf[l] != '\0'; l++)
	{
		for (uint_fast16_t k = 0; k < 5; k++)
		{
			shatag[k] = shatag[k + 1];
		}
		shatag[5] = testbuf[l];
		shatag[6] = '\0';
		if (strcmp(shatag, "<SHA1>") == 0)
		{
			testbuf2[kc] = testbuf[l];
			kc++;
			shaflag = 1;
		}

		if (strcmp(shatag, "</SHA1") == 0)
		{
			testbuf2[kc] = '<';
			kc++;
			testbuf2[kc] = '/';
			kc++;
			testbuf2[kc] = 'S';
			kc++;
			testbuf2[kc] = 'H';
			kc++;
			testbuf2[kc] = 'A';
			kc++;
			shaflag = 0;
		}
		if (shaflag == 0)
		{
			testbuf2[kc] = testbuf[l];
			kc++;
		}
	}
	testbuf2[kc] = '\0';
	free(testbuf);

	// Process digest for testbuf2 string and return.
	const char* testhash = (const char*)testbuf2;
	unsigned char *hash = (unsigned char*)malloc(sizeof(char*) * (SHA_DIGEST_LENGTH * 2 + 1));
	if (hash == NULL)
	{
		perror("Error: Could not allocate memory for hash. \n Terminating program...");
		delay2(1);
		exit(0);
	}

	SHA_CTX context;
	SHA1_Init(&context);
	SHA1_Update(&context, testhash, strlen(testhash));
	SHA1_Final(hash, &context);

	char *digest = (char*)malloc(sizeof(char*)*(SHA_DIGEST_LENGTH * 2 + 1));
	if (digest == NULL)
	{
		perror("Error: Could not allocate memory for digest. \n Terminating program...");
		delay2(1);
		exit(0);
	}
	for (uint_fast8_t i = 0; i < SHA_DIGEST_LENGTH; i++)
		sprintf(&digest[i * 2], "%02x", (unsigned int)hash[i]);
	free(testbuf2);
	free(hash);

	if (strcmp(digest, sha) == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
