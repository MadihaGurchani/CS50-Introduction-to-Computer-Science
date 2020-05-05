from cs50 import get_float

# Main program


def main():
    # Convert the user input to cents
    coins = 0
    change = round(get_change() * 100)
    # Check if user input is greater than or equal to 25 cents
    if (change >= 25):
        while (change > 24):
            change = change - 25
            coins += 1
    # Check if user input is greater than or equal to 25 cents
    if (change >= 10):
        while (change > 9):
            change = change - 10
            coins += 1
    # Check if user input is greater than or equal to 5 cents
    if (change >= 5):
        while (change > 4):
            change = change - 5
            coins += 1
    # Check if user input is greater than or equal to 1 cents
    if (change >= 1):
        while (change > 0):
            change = change - 1
            coins += 1
    print(coins)

# Prompt user for input


def get_change():
    while True:
        number = get_float("Change: ")
        if number > 0:
            break
    return float(number)


main()
