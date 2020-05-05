from cs50 import get_int


def main():
    # Get correct height from use
    height = get_positive_int()
    # Make pyramid
    for row in range(height + 1):
        # iterate over each row
        if (row > 0):
            sign = height - row
            print(" " * sign, end="")
        # iterate over each colum
        for colum in range(row):
            print("#", end="")
        # Move to next line
        print()


def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break
    return n


main()
