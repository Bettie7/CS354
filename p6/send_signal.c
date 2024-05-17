////////////////////////////////////////////////////////////////////////////////
// Main File:        send_signal.c
// This File:        send_signal.c
// Other Files:      my_c_signal_handler.c, my_div0_handler.c
// Semester:         CS 354 Lecture 2      SPRING 2024
// Grade Group:      gg3  (See canvas.wisc.edu/groups for your gg#)
// Instructor:       deppeler
//
// Author:           Yuwei Guo
// Email:            ygguo@wisc.edu
// CS Login:         yuweig
//
/////////////////////////// SEARCH LOG ////////////////////////////////
// Online sources: do not rely web searches to solve your problems,
// but if you do search for help on a topic, include Query and URLs here.
// IF YOU FIND CODED SOLUTIONS, IT IS ACADEMIC MISCONDUCT TO USE THEM
//                               (even for "just for reference")
// Date:   Query:                      URL:
// ---------------------------------------------------------------------
//
//
//
//
//
// AI chats: save a transcript.  No need to submit, just have available
// if asked.
/////////////////////////// COMMIT LOG  //////////////////////////////
//  Date and label your work sessions, include date and brief description
//  Date:3rd/May/2024   Commit Message: Finish sending signal part for p6
//  -------------------------------------------------------------------
//
//
//
//
//
///////////////////////// OTHER SOURCES OF HELP //////////////////////////////
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
// Date:   Name (email):   Helped with: (brief description)
// ---------------------------------------------------------------------------
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/* Main function for the send_signal program which sends specific signals to a process.
 *
 * Pre-conditions:
 *   - The program must be executed with exactly three arguments, including the program name.
 * Post-conditions:
 *   - Sends a SIGUSR1 or SIGINT to the process identified by the provided PID.
 *
 * param argc - The number of command-line arguments.
 * param argv - An array of character pointers listing all the arguments.
 *
 * retval int - Returns 0 on success, or exits with 1 on any error condition.
 */
int main(int argc, char *argv[])
{
  // Check if the correct number of command-line arguments is provided
  if (argc != 3)
  {
    printf("Usage: send_signal <signal type> <pid>\n");
    exit(1);
  }
  // obtain the argument for PID
  int pid = atoi(argv[2]);
  int signal;

  // determine the signal type based on the command-line argument
  if (strcmp(argv[1], "-u") == 0)
  {
    signal = SIGUSR1;
  }
  else if (strcmp(argv[1], "-i") == 0)
  {
    signal = SIGINT;
  }
  else
  {
    exit(1);
  }

  // Send the determined signal to the process with the specified PID
  if (kill(pid, signal) == -1)
  {
    // when sending the signal fails, exit
    exit(1);
  }

  return 0; // success
}
