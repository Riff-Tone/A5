1. Using the guessing game code provided in our slides, add code to do the following:
- prompt the user for their name
- count the number of guesses for the user
- keep the name and number of guesses in a data structure like a struct
- keep an array of 5 structs to store the current leaders
- when the user quits, the current leaders should be saved to a text file
- when the game is started, the file should be read, if it exists
An example of how the game should play is shown below:

Welcome! Press 'q' to quit or any other key to continue:
x
Please enter your name to start:Jack
8.06225775 is the square root of what number?Guess a value
between 10 and 100: 66
Too high, guess again: Guess a value between 10 and 100: 65
You got it, baby!
You made 2 guesses.
Here are the current leaders:
Jack made 2 guesses
Press 'q' to quit or any other key to continue:
x
Please enter your name to start:Jill
10.00000000 is the square root of what number?Guess a value
between 10 and 100: 100
You got it, baby!
You made 1 guesses.
Here are the current leaders:
Jill made 1 guesses
Jack made 2 guesses
Press 'q' to quit or any other key to continue:
q
Bye Bye!
Welcome! Press 'q' to quit or any other key to continue:
x
Please enter your name to start:Jan
9.27361850 is the square root of what number?Guess a value
between 10 and 100: 85
Too low, guess again: Guess a value between 10 and 100: 86
You got it, baby!
You made 2 guesses.
Here are the current leaders:
Jill made 1 guesses
Jack made 2 guesses
Jan made 2 guesses
Press 'q' to quit or any other key to continue:
x
Please enter your name to start:Joy
8.06225775 is the square root of what number?Guess a value
between 10 and 100: 67
Too high, guess again: Guess a value between 10 and 100: 66
Too high, guess again: Guess a value between 10 and 100: 65
You got it, baby!
You made 3 guesses.
Here are the current leaders:
Jill made 1 guesses
Jack made 2 guesses
Jan made 2 guesses
Joy made 3 guesses
Press 'q' to quit or any other key to continue:
q
Bye Bye!
As with previous assignments, your work will be graded based on functionality (70%)
and readability/clarity/design (30%).
Remember to modify your code incrementally, making small changes and re-testing to
see that you still have a working program.
