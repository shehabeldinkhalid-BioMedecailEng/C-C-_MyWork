/*
 * SDB.h
 * -----
 * Public interface of the "Simple Database" module.
 * This is the ONLY file other modules (like SDBAPP.c) are allowed to
 * include in order to talk to the database. The actual storage (the array
 * of students) is kept private inside SDB.c (static), which enforces
 * encapsulation: nobody outside this module can touch the raw data except
 * through these functions.
 */

#ifndef SDB_H
#define SDB_H

#include "STD.h"

/* Database capacity limits, as required by the spec (min 3, max 10). */
#define SDB_MAX_STUDENTS 10
#define SDB_MIN_STUDENTS 3

typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 Course1_ID;
    uint32 Course1_grade;
    uint32 Course2_ID;
    uint32 Course2_grade;
    uint32 Course3_ID;
    uint32 Course3_grade;
} student;

/* Checks whether the database has reached SDB_MAX_STUDENTS. */
bool SDB_IsFull(void);

/* Returns how many students are currently stored. */
uint8 SDB_GetUsedSize(void);

/* Prompts the user for a full student record and adds it if valid & not full. */
bool SDB_AddEntry(void);

/* Removes the student with the given id, if it exists. */
void SDB_DeleteEntry(uint32 id);

/* Prints the student with the given id. Returns true if found. */
bool SDB_ReadEntry(uint32 id);

/* Fills 'list' (caller-owned buffer, must hold >= SDB_MAX_STUDENTS uint32s)
   with all stored ids, and writes how many into *count. */
void SDB_GetList(uint8 *count, uint32 *list);

/* Checks whether a student with the given id already exists. */
bool SDB_IsIdExist(uint32 id);

#endif /* SDB_H */
