#include "parser.h"
#include <errno.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/*
 * main.c
 * A simple Command Line Parser.
 * Author : Michael Roberts <mroberts@it.net.au>
 * Last Modification : 11/09/01
 * Modified 11/9/01 by Nick Nelissen, who speparated the main into a separate source
 *	file
 */

void printComStruct(struct Command_struct *com);
static void call_getcwd();

/*
 * This function reads one line of 256 characters from stdin. THis line of
 * characters is then processed as a command line.
 * The resulting array of structures is then displayed to stdout.
 *
 * Arguments :
 *      None.
 *
 * Returns :
 *      An integer representing the exit status.
 *
 */
int main(void)
{
   char *cmd;
   int lc = 0;
   char *c;
   command **commandLine;
   char shellPrompt = '%';
   

   /**
         Program Algorithm
         while(1) {
            1) print the shell prompt
            2) read a line using fgets
            3) analyse the command line
            4) for each job in the command line
               4.1)  if the job is the exit command, 
                     then terminate the program
               4.2)  create child processes (and pipes, redirections etc) 
                     to execute that kob
               4.3)  if the job is a background job (it ended with &)
                     continue    // go back to for loop
               4.4)  wait for the job to finish

         }

   **/
   // Main program loop
   while(1)
   {
      lc = 0;
      cmd = (char *) malloc(CMD_LENGTH);
      // Print shell prompt
      printf("%c", shellPrompt);
      cmd = fgets(cmd, CMD_LENGTH, stdin);
   
      c = index(cmd, '\n');
      *c = '\0';
      printf("Command Line : [%s] [%d]\n", cmd, strlen(cmd));

      commandLine = process_cmd_line(cmd, 1);

      //printComStruct(commandLine[0]);

      // Iterate through the command line and print out
      // Each individual set of commands
      while (commandLine[lc] != NULL) {
         if(strcmp(commandLine[lc]->com_pathname, "exit") == 0)
         {
            printf("Exiting...\n");
            exit(1);
         } else if(strcmp(commandLine[lc]->com_pathname, "prompt") == 0)
         {
            // Adapt this to take the argument as the new prompt
            printf("Enter a new shell prompt: ");
            scanf("%c", &shellPrompt);
            printf("\n%c accepted as the new prompt\n", shellPrompt);
         } else if(strcmp(commandLine[lc]->com_pathname, "pwd") == 0)
         {
            // Print current working directory
            call_getcwd();
         } else if(strcmp(commandLine[lc]->com_pathname, "cd") == 0)
         {
            // Directory walk
            char *directory = commandLine[lc]->argv[1];
            //directory = strtok(NULL, " \n");
            int success;
            // If no input then change directory to default 
            if(directory == NULL)
            {
               printf("NULL directory found. Returning home\n");
               success = chdir("/");
            }else {
               // Else change it to the supplied directory
               printf("%s\n", commandLine[lc]->argv[1]);
               success = chdir(directory);
            }

            // If change directory failed then output error
            if(success == -1)
            {
               fprintf(stderr, "cd failed: %s\n", strerror(errno));
            }
            
            
         }

         //dump_structure(commandLine[lc], lc);
         //print_human_readable(commandLine[lc], lc);
         lc++;
      }

      clean_up(commandLine);
      free(cmd);

   }
   return 0;
}                       /*End of main() */


/*
   Get current working directory
*/
static void call_getcwd()
{
   char * cwd;
   cwd = getcwd(0,0);
   if(!cwd) {
      fprintf(stderr, "getcwd failed: %s\n", strerror(errno));
   }
   else {
      printf("%s\n", cwd);
      free(cwd);
   }
}

void printComStruct(struct Command_struct *com)
{ 
    int i;

    fprintf(stderr,"com_pathname=%s\n", com->com_pathname); 
    fprintf(stderr,"argc=%d\n", com->argc); 
    for(i=0;  com->argv[i]!=NULL; i++) 
        fprintf(stderr,"argv[%d]=%s\n", i, com->argv[i]); 
        fprintf(stderr,"#######\n"); 
        if (com->redirect_in == NULL)
            fprintf(stderr,"redirect_in=NULL\n"); 
        else
            fprintf(stderr,"redirect_in=%s\n", com->redirect_in); 
        if (com->redirect_out == NULL)
            fprintf(stderr,"redirect_out=NULL\n"); 
        else
            fprintf(stderr,"redirect_out=%s\n", com->redirect_out); 
        fprintf(stderr,"com_suffix=%c\n\n", com->com_suffix); 
} 
