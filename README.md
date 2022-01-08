# Software-Engineering-1-Focus-Domination-Board-Game

## GAME EXPLANATION
The aim of this project was to design and implement a C application to play the board game Focus/Domination. For this to work, the two players had
to be co-located and play from the same machine. The objective of each player is to make moves and capture pieces in such a way that their opponent 
have no moves remaining. We assume the game has only two players with each player represented by a colour (red or green). Each of the players have 18 tokens
which are initially placed on a board with the three squares in each corner removed. This forms our 6×6 board with 1×4 extensions on each side. The overall
rules of the game can be found on Wikipedia- https://en.wikipedia.org/wiki/Focus_(board_game)

## GAME IMPLEMENTATION
To get started, I used two custom data structures (struct). The first struct was used to represent each player and the second struct was used to represent
the squares on the board. I used constants (enums) to represent the colour that was associated with each of the players. Then I implemented an 8*8 two dimensional
(2D array) to represent the board. The positions {(0,0), (0,1), (1,0), (0,5), (0,6), (1,7), (7,0), (6,0), (7,1), (7,7), (7,6), (6,7)} could not contain any piece/stack.
 We started using an array to implement our stack but as we progressed the project it was more useful to use a dynamic data structure such as a linked list to 
 represent our stack.

## LEARNING FROM PROJECT
I found the project quite tough although I did find that being able to re-watch the lectures
online helped majorly in understanding each part of the program provided.
I struggled in working out how to declare a winner of the game and also how to allow the user
to re-enter their accumulated pieces (i.e. the pieces removed from the square when the square exceeded five elements).
I also struggled a bit with linked lists but I got the hang of them after a while and found them very interesting to learn about.

I found the project quite challenging yet also quite fun. I feel like this project was a lot more entertaining than the first one to 
code also. I feel like this project has improved my understanding on how to deal well with linked lists, for loops, enums, structs, if 
statements, while loops and also mainly functions.

