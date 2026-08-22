/*
 * main.c
 * ------
 * Entry point. Per the spec, main() does nothing but hand control over
 * to the application layer - it doesn't know anything about menus or
 * the database, keeping it as thin as possible.
 */

#include "STD.h"
#include "SDBAPP.h"

int main(void)
{
    SDB_APP();
    return 0;
}
