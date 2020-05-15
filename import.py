# TODO
import sqlite3
import csv
import cs50
import os
from cs50 import SQL
from sys import argv, exit

def main():
    # Check if correct number of command-line arguments provided
    if len(argv) != 2:
        print("Incorrect number of coomand line arguments")
        exit(1)
    file = argv[1]
    # if invalid csv file then report error
    if not file.endswith(".csv"):
        print("csv file not entered")
        exit(1)

    # Open the database
    db = cs50.SQL("sqlite:///students.db")

    # Open csv file as dictionary
    with open(argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        # Parsing Name
        for line in reader:
            name = line["name"].split(' ')
            # If middle name exits
            if len(name) == 3:
                # Insert student's first, middle and last name into database
                db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           name[0], name[1], name[2], line["house"], line["birth"])
            # Only First name and Last name exist
            else:
                 db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           name[0], None, name[1], line["house"], line["birth"])
    exit(0)


main()

