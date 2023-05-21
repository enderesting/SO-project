/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */

#include <signal.h>

/* function to deal with ctrl+c
 */
void handler();

/* function that prints all operations
 *  and their details every x seconds
 *  with a given x
 */
void write_alarm();