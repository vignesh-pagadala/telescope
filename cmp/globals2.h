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
* File: globals2.h
* ----------------------------------
* Contains all standard and local library functions and global variables.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

// Standard library
#include<stdio.h>
#include<string.h>
#include<expat.h>
#include<stdlib.h>
#include<process.h>
#include<openssl\sha.h>
#include<time.h>

// Local
#include "Control_Message_Processor.h"

extern char *Control_Message_Processor_CONT;
extern uint_fast8_t Control_Message_Processor_Flag;
extern char *Control_Message_Processor_UBL;
extern char *Control_Message_Processor_FQ;
extern char *Control_Message_Processor_SHA1;

#endif
