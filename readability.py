from cs50 import get_string


def main():
    # Initialization
    letters = 0
    words = 1
    sentences = 0
    # Get User Input
    text = get_string("text: ")
    # length of User Input
    length = len(text)
    # Counting letters, words and sentences.
    for i in range(length):
        # Count letters
        if (text[i].isalpha()):
            letters += 1
        elif (text[i].isspace()):
            words += 1
        elif (text[i] == '.' or text[i] == '?' or text[i] == '!'):
            sentences += 1
    # Average Letters per 100 words
    L = float(100 * ((float(letters) / float(words))))
    # Average Sentences per 100 words
    S = float(100 * ((float(sentences) / float(words))))
    # Using Coleman-Liau index
    index = float(0.0588 * L - 0.296 * S - 15.8)
    # Print appropriate Grade Level
    Count = round(index)
    if (Count < 1):
        print("Before Grade 1")
    elif (Count >= 16):
        print("Grade 16+")
    else:
        print("Grade ", Count)


main()
