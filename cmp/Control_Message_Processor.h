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
* File: Control_Message_Processor.h
* ----------------------------------
* This header file contains functions for parsing an XML control message, filtering out the
* Upstream Brokers List and Filtering Query from the message and performing validation using
* Secure Hash Algorithm 1.
*/

#ifndef _CONTROL_MESSAGE_PROCESSOR_H
#define _CONTROL_MESSAGE_PROCESSOR_H

#include "globals2.h"

/*
* @desc Introduces a time-delay.
* @param Number of seconds to delay.
*/
void delay(unsigned int seconds);

/*
* @desc Returns Upstream Brokers List.
* @return String with Upstream Brokers List.
*/
char* UBL();

/*
* @desc Returns Filtering Query.
* @return String with Filtering Query.
*/
char* FQ();

/*
* @desc Computes SHA-1 digest.
* @param The XML control message who's SHA-1 is to be computed.
* @return String with SHA-1 digest of the XML message (with empty SHA-1 element).
*/
char* shafunc(char *buff);

/*
* @desc Parses XML message and validates it. 
* @param The XML control message to be processed.
* @return -1 if the message is invalid. 0 if valid.
*/
int_fast8_t filter(char *buff);

/*
* @desc Calls filter(). For performing further processing.
* @param The XML control message to be processed.
* @return 0.
*/
int process(char *buff);

#endif
