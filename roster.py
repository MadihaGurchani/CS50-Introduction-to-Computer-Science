# TODO
import cs50
from cs50 import SQL
from sys import argv, exit

def main():
     # Check if correct number  of command-line arguments and string given
     if len(argv) < 2:
        print("Dear Muggle, you have inserted an invalid input")
        exit()

     # open the database in a variable and then execute a query that list all the people from a particular house in alphabetical order
     db = SQL("sqlite:///students.db")
     students = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last", argv[1])

     # print each person showing their information and their middle name if they have one
     for student in students:
         if student['middle'] == None:
             print(f"{student['first']} {student['last']}, born {student['birth']}")
         else:
            print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")

     exit(0)

main()