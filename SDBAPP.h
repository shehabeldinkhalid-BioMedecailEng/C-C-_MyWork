/*
 * SDBAPP.h
 * --------
 * Public interface of the application/menu layer. main.c only needs to
 * know about SDB_APP(); SDB_action() is exposed too since SDB_APP() calls
 * it, but conceptually it's an internal dispatcher for SDB_APP().
 */

#ifndef SDBAPP_H
#define SDBAPP_H

#include "STD.h"

/* Runs the main menu super-loop until the user chooses to exit. */
void SDB_APP(void);

/* Dispatches a single menu choice to the matching SDB_* function and
   prints the appropriate feedback to the user. */
void SDB_action(uint8 choice);

#endif /* SDBAPP_H */
