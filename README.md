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

## Notes from Day 5
The implementation for the first part was straight forward. Using the ranges I created a list with the
lower and upper bound of each range. Then when checking IDs, if an ID fell within a range, it was marked
as fresh.

For the second part my first approach was to use a hasmap to record all unique IDs in the rages. It was a
naive idea as the program was taking a while, and I remembered that since I'm working with large numbers
(I learned my mistake from day 1 and used ```uint64_t```), it would take a long time or even possibly run
out of memory. So my second approach was instead to "trim" the ranges until I was left with ranges with
unique IDs. For this I came up with the next approach:
- Picking a range from the list, it is compared with all the subsequent ranges in the list.
- If the range is a subrange of another, we can skip it and continue, the numbers in
the range will be included in some next range.
- If the lower bound of the range is within another range, we shift it up so there is no overlap and continue testing with this new range
- If the upper bound of the range is within another range, we shift it down so there is no overlap and dontinue testing with this nwe range.
- If the range is a superset of another range, then we split it into two ranges, such that there's no overlap (like cutting the overlap out). We continue testing with the range at the left, while the one at the right is added to the list of ranges.
- If there's no overlap, we continue testing.
- After testing the current range, a simple substration of the upper and lower limits gives the number of unique IDs in the resulting range.

The only problem I ran into this new algorithm was initially failing to account for the super ranges case,
causing the overlapped portions to be counted twice and resulting in a higher number of unique IDs.

## Notes from Day 6
The first part had a fairly easy implementation. The input is treated like a matrix of values. 
After extracting the values the matrix is transposed.
The operators are extracted and saved in an external string.
Lastly it iterates over each character in the operator string, the index of the operator indicating the
column it is applied to, for which the corresponding operator is applied and the result added to the total
result of the problem.

For the second part the input is treated as if it was transposed as well, so an input:


```
123
456
789
```

Is read as if it was fed

```
147
258
369
```

Similar to part 1, but the transpose is applied to the raw input and not to the matrix of extracted values.

Having this transposed input one value is extracted per line, ignoring spaces. Lines with no numbers mark
where one column ends, so at this point the corresponding operator is applied to obtain the value of the
column and added to the total for the problem.

In summary, both parts have the same approach: they treat the input like a matrix that is transposed for
ease of use, the difference being that in part 1 it is applied to the values, while in the second part it
is applied to the input itself (the raw chars).

## Notes from Day 7
For the first part I used a "buffer" string that keeps track of which cells contain a beam. Starting with a single
beam in the position corresponding to the starting point, whenever a split ```^``` is found in the input, it
checks if the previous cell (the corresponding cell in the buffer) is a beam. If it is, it splits the beam
into the two adjacent cells and clears the current one, adding to the count of splits. Otherwise the cell is
unchanged.

For the second part, my first implementation was to use recursion to traverse all the paths and count how many
there are. However this proved to not work as the process would take too long for it to be practical. So I changed
to work similarly to the first part. In this case a "buffer" is used to count how manybeams overlap in a cell
in a row, or in other words how many paths can be taken to reach a particular cell. 

The algorithm begins by assigning ```1``` to the cell corresponding to the starting point and ```0```
to all other cells, as at this point there is a single path to the cell. It iterates through each row in the input
and when a split is found, the number of paths is added to the number of paths of the two adjacent cells, while
clearing the current one as it is now in the shadow of a split. This is because if a cell has ```n``` paths to
reach it and a beam is split into it overlapping, then there are ```n``` paths from the original cell, plus
the ```m``` paths it took to reach the split that overlapped the beams. The final number of paths is obtained by
adding all the values in the final buffer.

## Notes from Day 8
Today's problem was not too difficult, but still took time time to implement because it required the use of data
structures.

For the first part the algorithm was simple. All positions (vectors) are stored in a list. For this a struct ```JoltBox```
was used that contains the coordinates of each jolt box and an ID for easy access in the list. Once all vectors
have been extracted, all unique pairings of jolt boxes and their distances are obtained. For this a second
struct ```Pair``` was used to store the ID of the two vectors that form the connection and the squared euclidean distance.
Each new pair compares their distance with that of the pair with the longest distance in the list of max pairings,
and if the distance of the new pair is shorter, then it replaces it in the list. The list of max pairings contains
the pairings of jolt boxes with the shortests distances, with a max of 1000 pairings as per the problem's 
requirements. Once all unique pairings have been tested and the list contains the 1000 pairings with the
shortest distances, the list is sorted by distance in ascending order and the circuit is built based on this order,
building first with the shortest paiings available. 

A list of sets is used to represent the circuits. For each
pairing in the list of pairs, we check if any of the jolt boxes are already in any circuit. If neither is in any
circuit then a new one is created with them. If one is already in a circuit and the other isnt, then the jolt
without a circuit is added to the same one. If both are in different circuits, then both circuits are merged.
If both are already in the same circuit, then nothing happens. Once all possible circuits are built, the list
is simply ordered and the size of the 3 largest circuits are multiplied for the answer.

The second part proved to be easier to implement. For this a second list of pairings and circuits is used. In
this case the list of pairs does not have a limit for the number of elements, so it contains all unique pairings,
also sorted by their distances in ascending order. As for the circuits, the same construction algorithm is used,
producing in this case a single circuit containing all jolt boxes since there was no limit to the pairings to use.
However it was modified to return a boolean value to indicate if a new pairing was added to the circuit in order
to keep track of the last pair of jolt boxes connected, so their ```x``` positions could be multiplied for the
answer to the second part.

### Optimization
On revision the solution was otimized. The algorithm is pretty much the same, the difference being that now
a single list of pairs is used for both parts. This one contains all unique pairs and is sorted by the distance
of the pairs after all have been added, avoiding wasted time from modifying elements in the list.

Afterwards to construct the circuits, for the circuit in the first part it simply limits itself to the first 1000
pairs in the list. The second one remains unchanged, except that it uses now the same list.

## Notes from Day 9
The first part was trivial to implement. Once the list of red tiles is extracted, compare the area formed by
each unique pair used as opposite corners and keep the largest area.

The second part seemed more challenging, but the solution fortunately was correct although a little hacky as it
depends on many assumptions about the input. The algorithm is as follows:

1. Similarly to part 1, it tests every unique pair of red tiles serving as oposite corners of the rectangle.
2. Each rectangle is tested against edge of the input. That is, against every pair of adjacent tiles in the
	list (so the edge between tile 1 and tile 2, then tile 2 and tile 3, and so on).
3. To test, it checks if both tiles are entirely to the left, right, above or below the rectangle (including 
	the tiles that make up the edge of the rectangle). If this is the case, continue testing with the next edge.
4. Otherwise we can assume there's an intersection (for example the edge has one end above the rectangle and one below, 
	 cutting the rectangle vertically), in which case the rectangle contains tiles that are not green or red, making it
   an invalid rectangle.
5. If there's no intersection after testing all edges, then the rectangle is valid and we can compare its area to
  the highest one recorded.

This approach gave the correct answer, but it is not entirely correct as it makes many assumptions such as:
	1. The input list of tiles is in order and the order denotes the path to draw a figure's perimeter.
	2. The shape resulting from the tiles doesnt have self intersections.
	3. A rectangle with an intersection is always invalid. This fails to account for cases in which a rectangle
	has many intersections but it still contains only red or green tiles.

## Notes from day 10
For part 1 the solution uses breadth first search. Starting with the lights off of a machine it presses each button
and the result is stored in a queue alongside the number of buttons that have been pressed to reach this combination.
Aftwerwards each button is pressed once on each element of the queue to build the combinations until one is found
to be the desired configuration. In order to speed up the process all combniations found are stored in a set
in order to avoid revisiting combinations already seen.

For the second part a similar approach was attempted. However since this time the configuration for the joltage
has more states per slot than the lights the process takes significantly longer to the point the result for
a single machine hasnt been found, thus I havent been able to solve part 2 so far. I might revisit later.