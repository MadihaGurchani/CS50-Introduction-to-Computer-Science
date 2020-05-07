import csv
from sys import argv, exit


def main():
    # Check if correct user input
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    else:
        STRs = []
        persons = []
        # Open csv file ....with means we don't have to close the file
        with open(argv[1]) as csv_file:
            reader = csv.DictReader(csv_file)
            # Make list of all STRs
            STRs = reader.fieldnames[1:]
            # Insert people in the person list
            for line in reader:
                persons.append(line)

        # Make a dictionary of STRs as keys and 0 as values
            Max_STRs = dict.fromkeys(STRs, 0)

        # Open sequence file
        with open(argv[2]) as sequence_file:
            # Takes the first line of the file since it is only needed
            sequence = sequence_file.readline()
            # Iterate over all STRs in the csv file
            for STR in STRs:
                STR_length = len(STR)
                total = 0
                # Iterate over the sequence to find consecutive max repeats
                for i in range(len(sequence)):
                    # set counter to 0 again
                    counter = 0
                    if sequence[i: i + STR_length] == STR:
                        # Increment counter to take in account first repition
                        counter += 1
                        # Now compare with other values to take maximum repition
                        while sequence[i: i + STR_length] == sequence[i + STR_length: i + (2 * STR_length)]:
                            counter += 1
                            i += STR_length
                        # Check if maximum consecutive repeats
                    if counter > total:
                        total = counter
                # Change value to maximum of the secific STR key in dictionary
                Max_STRs[STR] = total

        # Iterate ove people profiles to check if they have all the STR maximum repeats
        for people in persons:
            match = 0
            # Iterate over all the STRs in the STR list
            for STR in STRs:
                if int(people[STR]) == Max_STRs[STR]:
                    match += 1
                else:
                    break

            # If all matches found
            if match == len(STRs):
                print(people['name'])
                exit(0)
        # Else failure and no match found
        print("No match")
        exit(1)


main()
