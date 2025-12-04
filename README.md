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

## Notes from Day 2
This problem was challenging as well.

My first mistake was not understanding what the problem asked for. Given the range n-m, I first 
thought I only had to check if n or m were invalid IDs, it wasnt until I started getting wrong values that I noticed they were ranges for the IDs to test.

After that clarification my approach to the problem was to find the factors for the number of 
digits in each ID to make easier finding and testing the blocks of digits for invalid IDs. So 
if an ID could be, for example, be separated into blocks of 2, 3, 5 digits, then I could simply
create a substring with the first block of size n and compare it with the rest of blocks of 
size n in the string. For the first part it was trivial as it only needed to be tested for block 
sizes half the length of the ID. When testing the blocks, if there's a mismatch, then I can 
continue testing with the next block size. If all block sizes mismatched, then it is a valid ID. 
Otherwise it is invalid, and the number could be parsed into a numeric value.

This is where I found the biggest issue I ran into in this problem. I was parsing the strings 
into ints, failing to account for values that were too big for an int, unintentionally 
overflowing them and causing the final sum to be off. This was fixed by changing the 
corresponding datatypes into uint64_t.

The second issue I ran into, although a lesser one, was that I failed to account for EoL and 
EoF when parsing the input, causing the last range in the list to not be processed. This was 
fixed by simply processing the last recorded range outside of the for loop that extracts and 
processes.

## Notes from Day 3
This problem was easier to solve as I didn't run into many technical difficulties.

For the first part the algorithm was fairly easy. Starting with a number ```ab``` with digits ```a``` 
and ```b```, before comparing with any number of the input first, first we compare ```b``` with ```a```.
If ```b > a``` then we shift ```b``` to the position of ```a```, since no matter whan digit ```n``` 
takes the previous place of ```b```, it will result in a number ```bn > ab```. If not, then we compare
```b``` with ```n``` and replace ```b``` if ```n > b```.

For the second part we start by creating a candidate number using the last (rightmost) 12 digits 
of the input. From there we check the digits of the input (excluding the last 12). When picking 
a digit ```n```, we compare it first with the leftmost digit of the candidate. If it is smaller, 
then we can safely discard it. Otherwise, adding it to the candidate will make it larger. To add
it we the digit ```n``` take the place of the first digit ```a```. Having ```a``` as a leftover
we compare it to the next digit and the same rules are applied. If it is equal or larger, it takes
its place and have that next digit ```b``` be tested in the same way to the digit to its right.
This process continues until some digit is discarded at some point. The process goes from right to
left to more easily keep the order in which the digits appear in the input as well as keeping
the largest digits as leftmost as possible to get the largest number possible.

## Notes from Day 4
This day's problem was easy to solve as it is simply a convolution. The implementation for the first part
was fairly easy. 
Representing the input as a board the algorithm just iterates over every cell, and for each cell it 
iterates over the 8 adjacent ones. If it counts 4 rolls, then we continue to the next cell. If it scans
all adjacent cells and finds less than 4 rolls, then the count of free increments. The behavior was
slightly changed later for the second part to also change the value of the cell from ```@``` to ```x```
(and also count ```x``` as a roll) to make easier the removal of free rolls.

For the second part, having the rolls that should be removed marked it was simply a matter of iterating
the board and changing any ```x``` to ```.```, then searching new rolls to remove with the implementation
of the first part and once again changing any ```x``` to ```.```, until no rolls were left to remove 
(that is, the implementation of the first part 
returns ```0```).