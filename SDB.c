/*
 * SDB.c
 * -----
 * Implementation of the Simple Database module.
 *
 * Design notes:
 *  - The database array and its "used size" counter are declared `static`,
 *    meaning they have internal (file) linkage. No other .c file can see
 *    or modify them directly - this is how C fakes "private" data in a
 *    struct/class-less language, and it protects the data from being
 *    corrupted by code outside this module.
 *  - We keep the array packed (no holes): valid entries always occupy
 *    indices [0, SDB_UsedSize). This makes iterating, counting, and
 *    listing trivial, at the cost of a shift on delete (acceptable since
 *    the database is tiny - max 10 entries).
 *  - Input reading is centralized in one static helper (SDB_ReadUint32)
 *    so every field is validated the same way and we don't repeat the
 *    same scanf/flush/validate pattern eight times.
 */

#include <stdio.h>
#include "STD.h"
#include "SDB.h"

/* ---- Private (static) database storage ---- */
static student SDB_Database[SDB_MAX_STUDENTS];
static uint8   SDB_UsedSize = 0;

/*
 * SDB_ReadUint32
 * Reads one unsigned integer from stdin, with a user-facing prompt and
 * a [min, max] range check. Returns true if a valid value was read (and
 * writes it to *out), false otherwise.
 *
 * Why: scanf("%u", ...) alone does not protect against the user typing
 * letters (which leaves garbage in stdin and would break every future
 * read), so we read into a `long` with %ld, check the conversion result,
 * flush the rest of the line, and then range-check.
 */
static bool SDB_ReadUint32(const char *prompt, uint32 min, uint32 max, uint32 *out)
{
    int  convertedCount;
    long value;

    printf("%s", prompt);
    convertedCount = scanf("%ld", &value);

    /* Flush anything left on the input line (including a bad token) so the
       next read in the app starts clean. */
    while (getchar() != '\n')
    {
        /* discard */
    }

    if (convertedCount != 1 || value < (long)min || value > (long)max)
    {
        printf("Invalid input! Value must be between %lu and %lu.\n",
               (unsigned long)min, (unsigned long)max);
        return false;
    }

    *out = (uint32)value;
    return true;
}

/*
 * SDB_FindIndexById
 * Private helper used by several public functions to avoid duplicating
 * the linear-search logic. Not exposed in SDB.h since callers only need
 * to know whether an id exists (SDB_IsIdExist), not its index.
 * Returns the index, or -1 if not found.
 */
static int16 SDB_FindIndexById(uint32 id)
{
    uint8 i;

    for (i = 0; i < SDB_UsedSize; i++)
    {
        if (SDB_Database[i].Student_ID == id)
        {
            return (int16)i;
        }
    }
    return -1;
}

bool SDB_IsFull(void)
{
    return (SDB_UsedSize >= SDB_MAX_STUDENTS) ? true : false;
}

uint8 SDB_GetUsedSize(void)
{
    return SDB_UsedSize;
}

bool SDB_AddEntry(void)
{
    student newStudent;
    uint32  temp;

    if (SDB_IsFull())
    {
        printf("Database is full! Cannot add more students (max %d).\n", SDB_MAX_STUDENTS);
        return false;
    }

    printf("\n--- Add New Student ---\n");

    /* Student ID: read first and check uniqueness before asking for the
       rest of the fields, so we don't waste the user's time on a
       duplicate id. */
    if (!SDB_ReadUint32("Enter Student ID: ", 1, 999999, &temp))
    {
        return false;
    }
    if (SDB_IsIdExist(temp))
    {
        printf("A student with this ID already exists!\n");
        return false;
    }
    newStudent.Student_ID = temp;

    if (!SDB_ReadUint32("Enter Student Year (1-5): ", 1, 5, &temp)) return false;
    newStudent.Student_year = temp;

    if (!SDB_ReadUint32("Enter Course1 ID: ", 1, 999999, &temp)) return false;
    newStudent.Course1_ID = temp;
    if (!SDB_ReadUint32("Enter Course1 Grade (0-100): ", 0, 100, &temp)) return false;
    newStudent.Course1_grade = temp;

    if (!SDB_ReadUint32("Enter Course2 ID: ", 1, 999999, &temp)) return false;
    newStudent.Course2_ID = temp;
    if (!SDB_ReadUint32("Enter Course2 Grade (0-100): ", 0, 100, &temp)) return false;
    newStudent.Course2_grade = temp;

    if (!SDB_ReadUint32("Enter Course3 ID: ", 1, 999999, &temp)) return false;
    newStudent.Course3_ID = temp;
    if (!SDB_ReadUint32("Enter Course3 Grade (0-100): ", 0, 100, &temp)) return false;
    newStudent.Course3_grade = temp;

    /* Only commit to the array once every field passed validation, so we
       never store a half-filled record. */
    SDB_Database[SDB_UsedSize] = newStudent;
    SDB_UsedSize++;

    printf("Student added successfully!\n");
    return true;
}

void SDB_DeleteEntry(uint32 id)
{
    int16 idx = SDB_FindIndexById(id);
    uint8 i;

    if (idx == -1)
    {
        printf("Student with ID %lu not found.\n", (unsigned long)id);
        return;
    }

    /* Shift every following element left by one to close the gap. This
       keeps the array packed (no holes) so SDB_UsedSize always equals the
       exact number of valid entries at indices [0, SDB_UsedSize). */
    for (i = (uint8)idx; i < SDB_UsedSize - 1; i++)
    {
        SDB_Database[i] = SDB_Database[i + 1];
    }

    SDB_UsedSize--;
    printf("Student with ID %lu deleted successfully.\n", (unsigned long)id);
}

bool SDB_ReadEntry(uint32 id)
{
    int16 idx = SDB_FindIndexById(id);

    if (idx == -1)
    {
        printf("Student with ID %lu not found.\n", (unsigned long)id);
        return false;
    }

    printf("\n--- Student Data ---\n");
    printf("Student ID   : %lu\n", (unsigned long)SDB_Database[idx].Student_ID);
    printf("Student Year : %lu\n", (unsigned long)SDB_Database[idx].Student_year);
    printf("Course1 ID   : %lu, Grade: %lu\n",
           (unsigned long)SDB_Database[idx].Course1_ID, (unsigned long)SDB_Database[idx].Course1_grade);
    printf("Course2 ID   : %lu, Grade: %lu\n",
           (unsigned long)SDB_Database[idx].Course2_ID, (unsigned long)SDB_Database[idx].Course2_grade);
    printf("Course3 ID   : %lu, Grade: %lu\n",
           (unsigned long)SDB_Database[idx].Course3_ID, (unsigned long)SDB_Database[idx].Course3_grade);

    return true;
}

void SDB_GetList(uint8 *count, uint32 *list)
{
    uint8 i;

    /* The caller owns 'list' and must size it >= SDB_MAX_STUDENTS. We only
       ever write SDB_UsedSize entries into it and report that count via
       *count, so the caller knows exactly how many entries are valid. */
    for (i = 0; i < SDB_UsedSize; i++)
    {
        list[i] = SDB_Database[i].Student_ID;
    }
    *count = SDB_UsedSize;
}

bool SDB_IsIdExist(uint32 id)
{
    return (SDB_FindIndexById(id) != -1) ? true : false;
}
