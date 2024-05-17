////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_singal_handler.c
// This File:        my_c_singal_handler.c
// Other Files:      send_signal.c, my_div0_handler.c
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
//  Date: 3rd/May/2024   Commit Message: Finish all the signal handler for p6
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
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const int alarm_timer = 5; // set an alarm that will go off 5 seconds later
int counter = 0;           // counter for the number of time the program receives the specific signal

/* Handles the SIGALRM signal by printing the current process ID and the current time,
 * and then resetting the alarm timer.
 *
 * Pre-conditions: The function is intended to be called as a signal handler linked to
 *                 the SIGALRM signal.
 * param sig - The signal number, expected to be SIGALRM.
 * retval None - This function does not return a value.
 */
void handler_SIGALRM(int sig)
{
  // obtain the current time
  time_t now = time(NULL);
  // check time() return value
  if (time(NULL) == -1)
  {
    printf("Time function fails\n");
    exit(0);
  }
  char *current_time = ctime(&now);
  // check ctime return value
  if (current_time == NULL)
  {
    printf("ctime function fails\n");
  }
  printf("PID: %d CURRENT TIME: %s", getpid(), current_time);
  //
  alarm(alarm_timer);
}

/* Handles the SIGINT signal by showing the number of times SIGUSR1 has been handled
 * and then exits the program.
 *
 * Pre-conditions: The `counter` global variable must be correctly initialized and
 *                 updated elsewhere in the program to reflect the number of times
 *                 SIGUSR1 has been handled.
 * param sig - The signal number, expected to be SIGINT.
 * retval None - This function does not return a value.
 */
void handler_SIGINT(int sig)
{
  printf("SIGINT handled.\nSIGUSR1 was handled %d times. Exiting now.\n", counter);
  exit(0);
}

/* Handles the SIGUSR1 signal by incrementing a global counter and printing a
 * notification message.
 *
 * Pre-conditions: The `counter` global variable must be declared and initialized
 *                 outside this function to track the number of SIGUSR1 signals
 *                 received.
 * param sig - The signal number, expected to be SIGUSR1.
 * retval None - This function does not return a value.
 */
void handler_SIGUSR1(int sig)
{
  counter++; // keep tally of the number of times it receives SIGUSR1
  printf("SIGUSR1 handled and counted!\n");
}

/* Main function for the signal handler program.
 * Sets up signal handlers for SIGALRM, SIGINT, and SIGUSR1,
 * schedules an alarm, and enters an infinite loop to keep the program running to handle signals.
 *
 * Pre-conditions:
 *   - Global variable `alarm_timer` should be set to define the seconds between periodic alarms.
 *   - The functions handler_SIGALRM, handler_SIGINT, and handler_SIGUSR1
 *     must be defined and handle the specific signals.
 *
 * Post-conditions:
 *   - SIGALRM will trigger periodic actions as defined in handler_SIGALRM.
 *   - SIGINT will cause the program to exit cleanly, as managed by handler_SIGINT.
 *   - SIGUSR1 will increment a counter and log the event, managed by handler_SIGUSR1.
 *   - The program continue with an infinite loop until interrupted by a signal.
 *
 * retval int - Returns 0 upon program termination
 */
int main()
{
  // Set up the SIGALRM handler
  struct sigaction act, sa_sigint, sa_sigusr1;
  memset(&act, 0, sizeof(act));
  act.sa_handler = handler_SIGALRM;
  if (sigaction(SIGALRM, &act, NULL) != 0)
  {
    exit(0);
  }

  // Set up the SIGINT handler
  memset(&sa_sigint, 0, sizeof(sa_sigint));
  sa_sigint.sa_handler = handler_SIGINT;
  if (sigaction(SIGINT, &sa_sigint, NULL) != 0)
  {
    exit(0);
  }

  // Set up the SIGUSR1 handler
  memset(&sa_sigusr1, 0, sizeof(sa_sigusr1));
  sa_sigusr1.sa_handler = handler_SIGUSR1;
  sigaction(SIGUSR1, &sa_sigusr1, NULL);
  if (sigaction(SIGUSR1, &sa_sigusr1, NULL) != 0)
  {
    exit(0);
  }
  // Set the initial alarm
  alarm(alarm_timer);

  printf("PID and time print every %d seconds.\n", alarm_timer);
  printf("Type Ctrl-C to end the program.\n");

  // infinite loop
  while (1);
  return 0;
}
