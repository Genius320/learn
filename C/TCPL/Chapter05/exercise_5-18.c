/*
	Date: 2018.3.5
	Author: 刘臣轩
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME,
    PARENS,
    BRACKETS };

void dcl();
void dirdcl();
int gettoken();
void errormsg(char* s);

char out[1000];
int tokentype;

char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
bool prevtoken = false;

int main()
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl()
{
    int ns;
    for (ns = 0; gettoken() == '*';)
        ++ns;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl()
{
    int type;
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            errormsg("error: missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        errormsg("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returing");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void errormsg(char* s)
{
    printf("%s", s);
    prevtoken = true;
}

#include <ctype.h>

int getch();
void ungetch(int c);

int gettoken()
{
    if (prevtoken) {
        prevtoken = false;
        return tokentype;
    }
    int c;
    char* p = token;
    while ((c = getch()) == '\t' || c == ' ')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*(p++) = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*(p++) = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

#define BUFLEN 100
char buf[BUFLEN];
int bufp = 0;

int getch()
{
    return (bufp == 0) ? getchar() : buf[--bufp];
}
void ungetch(int c)
{
    if (bufp >= BUFLEN)
        printf("error: buffer overflow");
    else
        buf[bufp++] = c;
}
