#ifndef _PARSER_H
#define _PARSER_H

/*
 * Parser.h
 * Data structures and various defines for parser.c
 * Author : Michael Roberts <mroberts@it.net.au>
 * Last Update : 15/07/01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*The length of the command line.*/
#define CMD_LENGTH 256

/*Whitespaces that are searched for*/
// nick modified this
//static const char white_space[2] = { (char) 0x20, (char) 0x09 };
static const char white_space[3] = { (char) 0x20, (char) 0x09, (char) 0x00 };

/*The Structure we create for the commands.*/
typedef struct Command_struct
{
   char *com_pathname;		// what is the path of the command
   int argc;				// the number of arguments to the command
   							// including the command itself
   char **argv;				// pointers to string, each string is an argument
   							// for the command, including argument "0". 
   							// the last pointer should be set to NULL.
   int background;
   char *redirect_in;		// if this is not NULL, then the stanard input
   							// is redirected to the given file name
   char *redirect_out;		// if this is not NULL, then the standard output
   							// is redirected to the given file name
   int pipe_to;
   char com_suffix;			// ' ' - no command suffix (last command);
                            // '&' - the command is followed by '&'
                            // ';' - the command is followed by ';';
                            // '|' - the command is followed by '|'.
}
command;


/* Function prototypes added by Nick Nelissen 11/9/2001 */
command ** process_cmd_line(char *cmd,int);
void process_cmd(char *cmd, command * result);
void process_simple_cmd(char *cmd, command * result);
void clean_up(command ** cmd);
void clean_up(command ** cmd);
void clean_up(command ** cmd);

#endif
