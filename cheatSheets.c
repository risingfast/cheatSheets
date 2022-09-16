/*  cheatSheets.c - CGI to show cheat sheets on the cheatSheets.html webpage
 *  Author: Geoffrey Jarman
 *  Started: 15-Oct-2021
 *  References:
 *      http://www6.uniovi.es/cscene/topics/web/cs2-12.xml.html
 *  Log:
 *      15-Oct-2021 started
 *      20-Oct-2021 replace strcmp() with strstr() in if{} tree
 *      20-Oct-2021 create fPrintSheet() common file writer
 *      20-Oct-2021 decode the URL filter component with fUrlDecode()
 *      22-Oct-2021 add MySQL cheatsheet
 *      22-Oct-2021 remove the commented debug code
 *      24-Oct-2021 comment URL encoding debug printf statements
 *      11-Feb-2022 add Assembly to the list of sheets
 *      06-Mar-2022 split C and Cpp into Clang and Cpp separately
 *      13-Apr-2022 add GCP cheat sheet logic
 *      14-Apr-2022 add Apache2 cheat sheet logic
 *      20-Apr-2022 add Networks cheat sheet logic
 *      21-Apr-2022 add Yaml and Json cheat sheet logic
 *      30-Apr-2022 add Arduino
 *      03-May-2022 add case-insensitive string comparison in fprintSheet()
 *      05-May-2022 change sheets to sheet in each filename
 *      06-Aug-2022 add the Microsoft cheatsheet
 *      15-Sep-2022 add Access-Control-Allow-Origin: * CORS http header
 *  Enhancements:
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../shared/rf50.h"

#define MAXLEN 1024

char caText[MAXLEN] = {'\0'};
char caTextFltr[MAXLEN] = {'\0'};
char caAction[MAXLEN] = {'\0'};
char *sAction = NULL;
char caFilter[MAXLEN] = {'\0'};
char *sFilter = NULL;
char caFilterTemp[MAXLEN] = {'\0'};
char *sParams = NULL;
char *sSubstring = NULL;
char caDelimiter[] = "&";

void fPrintSheet(FILE *, char *, char *);

int main(void) {

    int i;

// print the html content type header and CORS header block -----------------------------------------------------------

    printf("Content-type: text/html\n");
    printf("Access-Control-Allow-Origin: *\n\n");

// check for a NULL query string --------------------------------------------------------------------------------------

//    setenv("QUERY_STRING", "action=Json&Filter=dummmy", 1);

    sParams = getenv("QUERY_STRING");

    if(sParams == NULL) {
        printf("\n");
        printf("Query string is empty. Terminating program");
        printf("\n\n");
        return 1;
    }

//    printf("QUERY_STRING: %s", getenv("QUERY_STRING"));
//    printf("\n\n");

//  get the content from QUERY_STRING and tokenize based on '&' character----------------------------------------------

    sSubstring = strtok(sParams, caDelimiter);
    sscanf(sSubstring, "action=%s", caAction);
    sAction = caAction;

    sSubstring = strtok(NULL, caDelimiter);
    sscanf(sSubstring, "filter=%s", caFilterTemp);

// parse the QUERY_STRING for each argument: Action and Filter --------------------------------------------------------

    strcpy(caFilter, fUrlDecode(caFilterTemp));
    sFilter = caFilter;

//    printf("Unencoded: %s", sFilter);
//    printf("\n\n");

// test if Null or All or non-Null values should be shown -------------------------------------------------------------

    if (getenv("QUERY_STRING") == NULL) {
        printf("\n\n");
        printf("No parameter string passed");
        printf("\n\n");
    }
    else if (strstr(getenv("QUERY_STRING"), "Assembly") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Assembly.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Assembly.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Web") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Web.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Web.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Clang") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Clang.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Clang.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Cpp") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Cpp.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Cpp.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Microsoft") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Microsoft.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.MySQL.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "MySQL") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.MySQL.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.MySQL.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Networks") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Networks.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Networks.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Perl") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Perl.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Perl.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Regex") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Regex.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Regex.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Linux") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Linux.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Linux.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Vi") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Vi.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Vi.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Git") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Git.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Git.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Markdown") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Markdown.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Markdown.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Python") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Python.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Python.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Oracle") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Oracle.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Oracle.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "VsCode") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Web.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Web.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "GCP") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.GCP.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.GCP.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Apache2") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Apache2.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Apache2.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Yaml") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Yaml.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Yaml.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "Arduino") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.Arduino.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.Arduino.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    else if (strstr(getenv("QUERY_STRING"), "JSON") != NULL) {
        FILE *f;
        f = fopen("cheatSheet.JSON.txt", "r");
        if (f == NULL) {
            printf("Error - cannot open file cheatSheet.JSON.txt for reading");
            printf("\n\n");
        }
        else {
            fPrintSheet(f, caText, sFilter);
        }
    }
    return 0;
}

void fPrintSheet(FILE *f, char *caText, char *caFilter)
{
    while (fgets(caText, MAXLEN, f) != NULL) {
        strcpy(caTextFltr, caText);
        if ((strstr(toUpperStr(caTextFltr), toUpperStr(caFilter)) != NULL) || (strlen(caFilter) == 0)) {
            printf("%s", caText);
        }
    }
    fclose(f);
}
