////////////////////////////////////////////////////////////////////////////////
// Main File:        my_div0_handler.c
// This File:        my_div0_handler.c
// Other Files:      my_c_signal_handler.c, send_signal.c
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
//  Date:3rd/May/2024   Commit Message: Finish the signal handler for the calculation divided by 0
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
#include <string.h>
#include <signal.h>
#include <unistd.h>

int counter = 0; // a total count of how many division operations were successfully completed

/* Handles the SIGINT signal (typically generated by Ctrl-C).
 *
 * Pre-conditions:
 *   - The `counter` global variable should be initialized and maintained properly throughout
 *     the program's execution to track the number of successful operations.
 * Parameters:
 *   sig - The signal number received by the handler. Expected to be SIGINT.
 * Return Value:
 *   None - This function does not return a value
 */
void handler_SIGINT(int sig)
{
  printf("\nTotal number of operations completed successfully: %d\n", counter);
  printf("The program will be terminated.\n");
  exit(0); // gracefully exit the program
}

/* Handles the SIGFPE signal, which is triggered by an erroneous arithmetic
 * operation such as division by zero.
 *
 * Pre-conditions:
 *   - The `counter` global variable should be initialized and updated properly throughout
 *     the program to track the number of successful operations.
 * Parameters:
 *   sig - The signal number received by the handler, expected to be SIGFPE.
 * Return Value:
 *   None - This function does not return a value.
 */
void handler_SIGFPE(int sig)
{
  printf("Error: a division by 0 operation was attempted.\n");
  printf("Total number of operations completed successfully: %d\n", counter);
  printf("The program will be terminated.\n");
  exit(0); // gracefully exit the program
}

/* Main function of the program. This function sets up signal handlers for SIGFPE
 * and SIGINT signals and continuously processes user input to perform integer division,
 * calculating both quotient and remainder.
 *
 * Preconditions:
 *   - Signal handlers handler_SIGFPE and handler_SIGINT must be defined properly.
 *   - Global variable 'counter' should be declared to track the number of successful
 *     division operations.
 * Postconditions:
 *   - If setting up any of the signal handlers fails, the program will exit with status 0.
 *   - If any input reading failure, the program will exit with status 1.
 *   - Continuously calculates and prints the result of division operations as long as
 *     correct input is provided.
 * Return Value:
 *   int - Returns 0 under normal operation
 */
int main()
{
  struct sigaction act;
  // Set up the SIGFPE handler
  memset(&act, 0, sizeof(act));
  act.sa_handler = handler_SIGFPE;
  // check whether we can set the handler successfully
  if (sigaction(SIGFPE, &act, NULL) != 0)
  {
    exit(0);
  }

  // Set up the SIGINT handler
  memset(&act, 0, sizeof(act));
  act.sa_handler = handler_SIGINT;
  // check whether we can set the handler successfully
  if (sigaction(SIGINT, &act, NULL) != 0)
  {
    exit(0);
  }

  char input[100];
  int num1, num2, result, remainder;
  while (1)
  {
    // get the input integers
    printf("Enter first integer: ");
    // cannot get the first integer
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      printf("fgets function fails");
      exit(1);
    }
    num1 = strtol(input, NULL, 10);
    printf("Enter second integer: ");
    // cannot get the second integer
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      printf("fgets function fails");
      exit(1);
    }
    num2 = strtol(input, NULL, 10);

    // Calculate the quotient and remainder of doing the integer division operation: int1 / int2
    result = num1 / num2;
    remainder = num1 % num2;
    printf("%d / %d is %d with a remainder of %d\n", num1, num2, result, remainder);

    counter++; // increment the number of division operations were successfully completed
  }
  return 0; // success
}
