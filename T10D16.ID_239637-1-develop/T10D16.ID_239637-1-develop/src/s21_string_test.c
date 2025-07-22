#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
#ifdef STRLEN_TESTS
    s21_strlen_test();
#endif

#ifdef STRCMP_TESTS
    s21_strcmp_test();
#endif

#ifdef STRCPY_TESTS
    s21_strcpy_test();
#endif

#ifdef STRCAT_TESTS
    s21_strcat_test();
#endif

#ifdef STRCHR_TESTS
    s21_strchr_test();
#endif

#ifdef STRSTR_TESTS
    s21_strstr_test();
#endif

#ifdef STRTOK_TESTS
    s21_strtok_test();
#endif
    return 0;
}

void s21_strlen_test() {
    const char *str1 = "";
    const char *str2 = "R";
    const char *str3 = "Hello World!";

    int len = s21_strlen(str1);
    printf("TEST1: input: \"%s\" wait answer = 0\noutput = %d\n", str1, len);
    if (len == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");
    len = s21_strlen(str2);
    printf("TEST2: input: \"%s\" wait answer = 1\noutput = %d\n", str2, len);
    if (len == 1)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");
    len = s21_strlen(str3);
    printf("TEST3: input: \"%s\" wait answer = 12\noutput = %d\n", str3, len);
    if (len == 12)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strcmp_test() {
    const char *str1 = "";
    const char *str2 = "Hello World!";

    int result = s21_strcmp(str1, str2);
    printf("TEST1: input: \"%s\" \"%s\" wait answer = -72\noutput = %d\n", str1, str2, result);
    if (result == -72)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *str3 = "HELLO";
    const char *str4 = "HELLO";
    result = s21_strcmp(str3, str4);
    printf("TEST2: input: \"%s\" \"%s\" wait answer = 0\noutput = %d\n", str3, str4, result);
    if (result == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *str5 = "Maksim";
    const char *str6 = "Maasha";
    result = s21_strcmp(str5, str6);
    printf("TEST3: input: \"%s\" \"%s\" wait answer = 10\noutput = %d\n", str5, str6, result);
    if (result == 10)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *str7 = "A";
    const char *str8 = "K";
    result = s21_strcmp(str7, str8);
    printf("TEST4: input: \"%s\" \"%s\" wait answer = -10\noutput = %d\n", str7, str8, result);
    if (result == -10)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strcpy_test() {
    char str1[20];
    const char *str2 = "Hello World!";

    printf("TEST1: input: \"(null)\" \"%s\" wait answer = \"Hello World!\"\n", str2);
    s21_strcpy(str1, str2);
    printf("output = \"%s\"\n", str1);
    if (s21_strcmp(str1, str2) == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str3[20];
    const char *str4 = "M";

    printf("TEST2: input: \"(null)\" \"%s\" wait answer = \"M\"\n", str4);
    s21_strcpy(str3, str4);
    printf("output = \"%s\"\n", str3);
    if (s21_strcmp(str3, str4) == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str5[20];
    const char *str6 = "";

    printf("TEST3: input: \"(null)\" \"%s\" wait answer = \"\"\n", str6);
    s21_strcpy(str5, str6);
    printf("output = \"%s\"\n", str5);
    if (s21_strcmp(str5, str6) == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strcat_test() {
    char str1[20] = "";
    const char *str2 = "Hello World!";

    printf("TEST1: input: \"%s\" \"%s\" wait answer = \"Hello World!\"\n", str1, str2);
    s21_strcat(str1, str2);
    printf("output = \"%s\"\n", str1);
    if (s21_strcmp(str1, "Hello World!") == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str3[20] = "Hello";
    const char *str4 = "!";

    printf("TEST1: input: \"%s\" \"%s\" wait answer = \"Hello!\"\n", str3, str4);
    s21_strcat(str3, str4);
    printf("output = \"%s\"\n", str3);
    if (s21_strcmp(str3, "Hello!") == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str5[20] = "Hello World";
    const char *str6 = ", AI!";

    printf("TEST1: input: \"%s\" \"%s\" wait answer = \"Hello World, AI!\"\n", str5, str6);
    s21_strcat(str5, str6);
    printf("output = \"%s\"\n", str5);
    if (s21_strcmp(str5, "Hello World, AI!") == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strchr_test() {
    const char *str1 = "Hello World!";
    char target1 = 'o';
    char *result = NULL;
    printf("TEST1: input: \"%s\" \"%c\" wait answer = \"o World!\"\n", str1, target1);
    result = s21_strchr(str1, target1);
    printf("output = \"%s\"\n", result);
    if (*result == 'o')
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char target2 = 'a';
    result = NULL;
    printf("TEST2: input: \"%s\" \"%c\" wait answer = \"(null)\"\n", str1, target2);
    result = s21_strchr(str1, target2);
    printf("output = \"%s\"\n", result);
    if (result == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *str2 = "";
    char target3 = 'o';
    result = NULL;
    printf("TEST3: input: \"%s\" \"%c\" wait answer = \"(null)\"\n", str2, target3);
    result = s21_strchr(str2, target3);
    printf("output = \"%s\"\n", result);
    if (result == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strstr_test() {
    const char *str1 = "Hello World!";
    const char *target1 = "orl";
    char *result = NULL;
    printf("TEST1: input: \"%s\" \"%s\" wait answer = \"orld!\"\n", str1, target1);
    result = s21_strstr(str1, target1);
    printf("output = \"%s\"\n", result);
    if (s21_strcmp(result, "orld!") == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *target2 = "loser";
    result = NULL;
    printf("TEST2: input: \"%s\" \"%s\" wait answer = \"(null)\"\n", str1, target2);
    result = s21_strstr(str1, target2);
    printf("output = \"%s\"\n", result);
    if (result == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *target3 = "";
    result = NULL;
    printf("TEST3: input: \"%s\" \"%s\" wait answer = \"Hello World!\"\n", str1, target3);
    result = s21_strstr(str1, target3);
    printf("output = \"%s\"\n", result);
    if (result == str1)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *target4 = "W";
    result = NULL;
    printf("TEST4: input: \"%s\" \"%s\" wait answer = \"World!\"\n", str1, target4);
    result = s21_strstr(str1, target4);
    printf("output = \"%s\"\n", result);
    if (result == (char *)&str1[6])
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    const char *str2 = "";
    const char *target5 = "Hello World!";
    result = NULL;
    printf("TEST4: input: \"%s\" \"%s\" wait answer = \"(null)\"\n", str2, target5);
    result = s21_strstr(str2, target5);
    printf("output = \"%s\"\n", result);
    if (result == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strtok_test() {
    char str1[] = "Hello, world! How are you?";
    const char *delim1 = " ,!?";
    char *result = NULL;
    printf("TEST1: input: \"%s\" \"%s\"\n", str1, delim1);
    result = s21_strtok(str1, delim1);
    int k = 0;
    while (result != NULL) {
        printf("token = \"%s\"\n", result);
        k++;
        result = s21_strtok(NULL, delim1);
    }
    if (k == 5)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");
    char str2[] = "Hello, world! How are you?";
    const char *delim2 = ";";
    result = NULL;
    printf("TEST2: input: \"%s\" \"%s\" \n", str2, delim2);
    result = s21_strtok(str2, delim2);
    k = 0;
    while (result != NULL) {
        printf("token = \"%s\"\n", result);
        k++;
        result = s21_strtok(NULL, delim2);
    }
    if (k == 1)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str3[] = "Hello, world! How are you?";
    const char *delim3 = "";
    result = NULL;
    printf("TEST3: input: \"%s\" \"%s\"\n", str3, delim3);
    result = s21_strtok(str3, delim3);
    k = 0;
    while (result != NULL) {
        printf("token = \"%s\"\n", result);
        k++;
        result = s21_strtok(NULL, delim3);
    }
    if (k == 1)
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    char str4[] = "";
    const char *delim4 = " ,!?";
    result = NULL;
    printf("TEST4: input: \"%s\" \"%s\"\n", str4, delim4);
    result = s21_strtok(str4, delim4);
    k = 0;
    while (result != NULL) {
        k++;
        printf("token = \"%s\"\n", result);
        result = s21_strtok(NULL, delim4);
    }
    if (k == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
}
