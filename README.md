# Check connect-4 winning positions

We discussed what is the best and shortest algorithm to check the winning positions in a connect-4 game.
My argument was that it's faster to check the whole board every time.
Stefan's argument was that it's easier to check only each player's turn.
So I wrote this code to see how much different the solutions are.

Turns out that with a given set of helper functions, checking only each player's turn is smaller.
But it uses one more helper function than checking the whole board every time.
So there is no clear winner :)

The solution here includes test-code for all the 4 patterns, including spaces in all the four directions.
And I _did_ find some errors in my code during testing!
