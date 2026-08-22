/*
 * SDBAPP.c
 * --------
 * Application layer: presents the menu, reads the user's choice, and
 * dispatches it to the right SDB_* function.
 *
 * Design notes:
 *  - SDB_APP() only handles the "outer" loop (show menu, read a valid
 *    0-7 choice, exit on 0). It knows NOTHING about how each option is
 *    implemented - that's delegated to SDB_action(), per the spec's
 *    explicit split between the two functions. This is modular design:
 *    each function has exactly one responsibility.
 *  - SDB_action() is a simple switch that calls into SDB.h's public API
 *    and formats the result for the user. It never touches the database
 *    array directly - only through the SDB_* functions - keeping module
 *    boundaries clean (SDBAPP doesn't need to know how SDB stores data).
 */

#include <stdio.h>
#include "STD.h"
#include "SDB.h"
#include "SDBAPP.h"

void SDB_APP(void)
{
    uint8 choice;
    int   convertedCount;
    long  value;

    printf("=====================================\n");
    printf("   Student Database Management App   \n");
    printf("=====================================\n");

    while (true)
    {
        printf("\n1. Add entry\n");
        printf("2. Get used size\n");
        printf("3. Read student data\n");
        printf("4. Get list of all student IDs\n");
        printf("5. Check if ID exists\n");
        printf("6. Delete student data\n");
        printf("7. Check if database is full\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        convertedCount = scanf("%ld", &value);
        while (getchar() != '\n')
        {
            /* flush the rest of the input line, protects against bad input */
        }

        if (convertedCount != 1 || value < 0 || value > 7)
        {
            printf("Invalid choice, try again.\n");
            continue;
        }

        choice = (uint8)value;

        if (choice == 0)
        {
            printf("Exiting... Goodbye!\n");
            break;
        }

        SDB_action(choice);
    }
}

void SDB_action(uint8 choice)
{
    uint32 id;
    uint8  count;
    uint32 idList[SDB_MAX_STUDENTS];
    uint8  i;

    switch (choice)
    {
        case 1:
            SDB_AddEntry();
            break;

        case 2:
            printf("Used size: %u / %d\n", SDB_GetUsedSize(), SDB_MAX_STUDENTS);
            break;

        case 3:
            printf("Enter Student ID to read: ");
            scanf("%u", &id);
            while (getchar() != '\n') { /* flush */ }
            SDB_ReadEntry(id);
            break;

        case 4:
            SDB_GetList(&count, idList);
            if (count == 0)
            {
                printf("Database is empty.\n");
            }
            else
            {
                printf("Student IDs (%u):\n", count);
                for (i = 0; i < count; i++)
                {
                    printf("  - %u\n", idList[i]);
                }
            }
            break;

        case 5:
            printf("Enter Student ID to check: ");
            scanf("%u", &id);
            while (getchar() != '\n') { /* flush */ }
            printf(SDB_IsIdExist(id) ? "ID exists.\n" : "ID does not exist.\n");
            break;

        case 6:
            printf("Enter Student ID to delete: ");
            scanf("%u", &id);
            while (getchar() != '\n') { /* flush */ }
            SDB_DeleteEntry(id);
            break;

        case 7:
            printf(SDB_IsFull() ? "Database is FULL.\n" : "Database is NOT full.\n");
            break;

        default:
            printf("Unknown choice.\n");
            break;
    }
}
