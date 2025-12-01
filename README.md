# Advent of Code 2025
This is my working repo for the solutions for Advent of Code 2025.

## Notes from Day 1
Developing the algorithm for the first part was trivially easy. At first glance it looked like it was a simple modulo operation with '%'.
The algorithm simply adds or substracts the number of turns (depending on the direction), and with a modulo operation we can set the dial's position back within the range of 0-99. A simple comparison and counter tells us each time the dial lands in 0.

Three cases were deviced to count the times the dial passed or landed on 0: going overflow, going underflow, and turning to 0 without either.

For the second part we work with the dial position before correcting back into 0-99, meaning we have positions over 99 and under 0.

For the first case, turning the dial right (adding turns), it was trivially easy. Since it went from positive numbers to positive numbers, we just need to count each time it passes over a multiple of 100 (since 100 is mapped back to 0), which is easily calculated with a division of int values.

For the second case, turning the dial left (substracting turns), turned to be more challending. Similarly, each time the dial position goes over a multiple of -100 we add one to the number of times it went over 0. But since the dial always starts on a non-negative number, I assumed I also had to an additional 1 to account going from positive to negative. This turned out to not be the case, as I failed to account for the case in which the dial was already on 0, causing to add an already accounted pass over 0.

The third case, turning left but not underflowing, I failed to account until the end. This is the case when the dial goes from non zero to zero (turning left), without actually passing over it, or exaclty landing on it.

The implementation of the solution proved to be more difficult than I expected partially because I was also under the impression that the % operator in C++ is not a modulo operator, but rather a remainder operator, meaning the logic of the program broke when dealing with negative numbers. Once I learned of this blunder I was finally able to solve the second part, although I am surprised it somehow did not break the solution for the first part of the problem.

