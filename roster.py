# TODO
import sqlite3
import cs50
from cs50 import SQL
from sys import argv, exit

def main():
     # Check if correct number  of command-line arguments and string given
     if not len(argv) == 2 and isinstance(argv[1],str):
         print("Incorrect input")
         exit(1)

     # Open database
     db = cs50.SQL("sqlite:///datas.db")
     # Order correctly
     data = db.execute("SELECT * FROM datas WHERE house = (?) ORDER BY last", argv[1])

     # Print data correctly
     for row in data:
        if row["middle"] == None:
            print(f"{data['first']} {data['last']}, born {data['birth']}")
        else:
            print(f"{data['first']} {data['middle']} {data['last']}, born {data['birth']}")
     exit(0)

main()