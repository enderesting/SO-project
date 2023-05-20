#include <signal.h>

/* function to deal with ctrl+c
 */
void handler();

/* function that prints all operations
 *  and their details every x seconds
 *  with a given x
 */
void write_alarm();