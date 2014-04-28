#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <string.h>

#define ASSERT_MESSAGE_SIZE 1024

static char message[ASSERT_MESSAGE_SIZE];
static int testsRun = 0;
static int testsFailure = 0;

#define fail() do { \
    snprintf(message, ASSERT_MESSAGE_SIZE, \
            "%s:%d: fail", \
            __FILE__, __LINE__); \
    return 1; \
} while (0)

#define assertTrue(condition) do { \
    if (!condition) { \
        snprintf(message, ASSERT_MESSAGE_SIZE, \
                "%s:%d: fail", \
                __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

#define assertEqual_int(expected, actual) do { \
    if (expected != actual) { \
        snprintf(message, ASSERT_MESSAGE_SIZE, \
                "%s:%d: expected:'%d', actual:'%d'", \
                __FILE__, __LINE__, expected, actual); \
        return 1; \
    } \
} while (0)

#define assertEqual_str(expected, actual) do { \
    if (strcmp(expected, actual)) { \
        snprintf(message, ASSERT_MESSAGE_SIZE, \
                "%s:%d: expected:'%s', actual:'%s'", \
                __FILE__, __LINE__, expected, actual); \
        return 1; \
    } \
} while (0)

#define assertEqual_ptr(expected, actual) do { \
    if (expected != actual) { \
        snprintf(message, ASSERT_MESSAGE_SIZE, \
                "%s:%d: expected:'%p', actual:'%p'", \
                __FILE__, __LINE__, expected, actual); \
        return 1; \
    } \
} while (0)

#define runTest(test) do { \
    int result = test(); \
    testsRun++; \
    testsFailure += result; \
    printf("%s: %s ... %s\n", __FILE__, #test, result==0 ? "PASSED" : "FAILED"); \
    if (result != 0) { \
        printf("\t%s\n", message); \
    } \
} while (0)

#define reportTestResult() do { \
    printf("\n%d tests, %d failures\n\n", testsRun, testsFailure); \
} while(0)

#endif /* MINUNIT_H */
