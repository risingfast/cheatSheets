# -*- makefile -*-
# makefile for mysql-c-library project
# Created: 15-Jun-2021
# Geoffrey Jarman
# Log
#       08-Nov-2021 add bookDetails
#       09-Dec-2021 add bookDelRating
#       10-Dec-2021 add bookDelSeries
#       10-Dec-2021 add bookDetails2
# $@ Target file
# $^ Dependency files
# $(CC) Compiler executable
# $(CFLAGS) Compiler options
# $@ Souce file
# $^ Dependent files (dependencies)

# Variables

CC=gcc
CFLAGS=-g -o
SQL2FLAGS=-L/usr/lib/x86_64-linux-gnu

all: cheatSheets

cheatSheets: cheatSheets.c ../shared/rf50.c
	$(CC) $(CFLAGS) $@ $^ $(SQL2FLAGS)

clean:
	rm -f *.o *.s *.i cheatSheets
