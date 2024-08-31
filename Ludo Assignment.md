# University of Colombo School of Computing
## SCS 1301 - Data Structures and Program Design using C

# LUDO-like UCSC

### Take Home Assignment

**Saturday, July 27, 2024**

Submission Deadline: September 01, 2024 @ 2355Hrs
Softcopy Submission: To UGVLE
Viva Dates: September 02 to 13, 2024
Grade Value: 30% out of 100% of the module

## 1. Ludo and Friends

### 1.1 Traditional Ludo

LUDO is a board game for two (2) to four (4) players inspired by the ancient Indian cross and circle board game Pachisi. Ludo differs from Pachisi by including six (6) sided dice to make moves on the Ludo board. The structure of the Ludo board is given in Figure 1.

As shown in Figure 1, the traditional LUDO board consists of multiple areas and cells that enable the dynamics of the game. The areas of the board are as follows:

- There are a maximum of four (4) players in the game, and each player is assigned a color as Red (R), Yellow (Y), Green (G), and Blue (B).
- Each player has a base of its color and has four pieces named 1 to 4. For example, the four Green pieces are named G1, G2, G3, and G4.
- Each piece is placed at the base at the beginning of the game, and when the player can move a piece from the base, it will be first moved to the cell marked with an 'X' of the respective color.
- There are 52 standard and 20 color-specific cells on the board. The standard cells include the cells marked with a colored circle and the colored cells marked with an 'X'. The color-specific cells are the five cells for each color that connects to 'Home'.
- The five colored cells connecting to 'Home' are called the 'Home Straight' for that color.
- The colored circles beneath the color-specific 'Home straight' is called the 'Approach' cell. This cell marks the point where a color-specific piece can move from the standard cells to the home straight.
- Each piece starts from its respective base and moves through the board to its respective home. When a piece reaches home, the piece is removed from the game.

[Figure 1: Ludo Board]

The game of Ludo uses a six-sided dice. Each player rolls the dice to identify who will be the first to roll. The player who rolls the highest will be the first to roll. After that, the dice is passed to the player to the left. For example, if R rolled the dice, the next player to roll would be G. A single round is where each player rolls the dice once. The dice passes clockwise (to the left-hand side) in each round of play. Once the first player to roll the dice is determined, the gameplay rules are as follows:

Rule 1: The face value of the dice is observed, and a piece is moved by the number of cells represented by the face value.

Rule 2: To move a piece from the base to the starting square 'X', the player must obtain a six (6) by rolling the dice.

Rule 3: At the beginning of the game, no piece belonging to any player will be on the standard cells unless a player has rolled a six.

Rule 4: When a six is rolled, a player may move a piece from the base to X or move a piece already in the standard area by six cells. When a six is rolled, the player gets a second roll. If a six is rolled in, the second roll and third roll are also given. However, if a six is rolled for the third consecutive time, the roll is ignored, and the dice passes to the next player.

Rule 5: When moving through the cells, a piece can jump over another piece. This other piece can be a piece of the same color or an opponent piece.

Rule 6: When moving through the cells, if a piece lands on a cell occupied by a piece belonging to an opposing player, that piece is considered captured, and the opposing player's piece is returned to the base.

Rule 7: When moving through cells, if the piece lands on a cell occupied by a piece belonging to the player itself, such a move is not permitted, and if there are no other pieces in play in the board to that can make the move, the roll is ignored and dice passes to the next player.

Rule 8: After moving a piece from the base to X, the piece's movement is in a clockwise direction.

Rule 9: If a piece is to land or pass the 'Approach' cell, the next cells after passing the 'Approach' cell will be the cells in the home straight.

Rule 10: Once a piece is in the home straight, the player must roll the exact number to reach home.

Rule 11: The first player to bring all its pieces home wins the game. The game may continue to find second, third, and fourth places.

### 1.2 LUDO-CS

LUDO-CS is an extension to the traditional rules of Ludo detailed above. The extensions make the game more exciting and enable more strategy. The rules are given below. Please note that if the rules mentioned above in the traditional Ludo are not mentioned in the rules given below, those rules are not changed from the traditional version of Ludo. Following are the new and extended rules from the traditional rules of Ludo.

Rule CS-1: Rule 8 of traditional rules are extended so a piece can move clockwise and counter-clockwise through the board. The direction to move is determined by a coin toss after the piece has been moved to X from the base when a six is thrown. After moving to X, the coin toss would take place and if heads was received, the piece would move in a clockwise direction as in the traditional game, and if a tail was received, the piece moved in the counterclockwise direction. When moving counterclockwise, a piece can only move into the home straight if it passes the approach cell for the second time.

Rule CS-2: Rule 6 of the traditional rules are extended by allowing the capturing player another roll as a bonus for capturing an opponent piece.

Rule CS-3: Rule 7 of the traditional is extended so that a piece belonging to the same player can land in the same cell. If such happens, it is called a block. No opponent piece can jump over the block. However, the opponent pieces can move up to the adjacent cells of either side if the value of the roll will take the piece past the block. For example, let's assume G1 is in cell 0, and there is a block by R1 and R2 in cell 4. If G rolls 6, that would take him to cell 6, which G1 cannot do due to the block. In such a case, G1 can move up until cell 3. No other partial movement is possible.

Rule CS-4: If a block is created by two pieces moving in the opposite direction, the block (e.g. two or more pieces together) shall move in the direction of the longest distance from home. When the block moves, all pieces in the block are moved by the number of positions equal to the die roll value divided by the number of pieces participating in the block.

Rule CS-5: If any group of pieces are moved as a part of a block, when the block is broken by moving an individual piece from the block, its direction will be the original direction of the piece when it was placed in X.

Rule CS-6: If any player has a blockade and rolls six consecutively three (3) times, in such cases, the blockade has to be broken by the player by removing all pieces, baring one by moving them in their original direction by six units cumulatively.

Rule CS-7: Rule 9 is modified such that a piece can enter the home straight if and only if it has at least captured one opponent piece during its movement through the board.

Rule CS-8: A blockade of the same size can capture a blockade. All such captured pieces shall return to the base. The number of captures for each piece participating in the capturing blockade will be incremented by one (1).

Rule CS-9: If any piece is captured and returned to base, all information in that piece will be reset.

Rule CS-10: The game has a mystery cell in the standard path. The mystery cell should appear on the board after two rounds have passed from pieces in the standard path. The mystery cell can occur randomly at any cell location in the standard path (52 cells) on a cell that, at the time of spawning, has no pieces on it. Once the mystery cell has appeared, it will remain in the same cell for four rounds and reappear at another random location. Mystery cells cannot appear in the same place consecutively.

Rule CS-11: If a piece lands on the Mystery cell, it will randomly select one of the six options below and teleport the piece into the specified location.

1. Bhawana
2. Kotuwa
3. Pita-Kotuwa
4. Base
5. X of the piece color
6. Approach of the piece color

Bhawana, Kotuwa, and Pita-Kotuwa is the 9th, 27th, and 46th cell respectively from the yellow approach cell. The cell identified in the yellow approach cell is considered zero (0).

Rule CS-12: If a piece is teleported to Bhawana, one of two things can happen: the piece may get energized by the aura or get sick due to the aura.

- If the piece gets energized, when the piece moves after a roll within the next four rounds, the movement will be double the value of the roll.
- If the piece gets sick, when the piece moves after a roll within the next four rounds, the movement will be half the value of the roll.

Rule CS-14: If a piece is teleported to Pita-Kotuwa, it needs clarification, and if it is moving in a clockwise direction, it will change its direction to counterclockwise. If it were moving in the counterclockwise direction, it would be teleported to Kotuwa.

Rule CS-15: Effects of Bhawana, Kotwa, and Pita-Kotuwa will only apply if the piece is teleported via a mystery cell. No effects will occur if a piece lands on such a cell without teleport.

## 2. Program Requirements

For this assignment, you are required to develop a simulation of the LUDO-CS game detailed above. The simulation game will run without any user interaction. This means once the executable file is run (e.g. ./a.out), the game simulates the behaviour of the players and produces the results.

### 2.1 Behaviour of Player

There are four (4) players in the game. Each player has a defined behaviour, and you are required to program each player's behaviour as given below.

#### 2.1.1 Red Player

The red player is a very aggressive player who prioritises capturing opponent pieces rather than winning the game. The behaviour of this player is as follows:

- When the dice is rolled, if any opponent piece can be captured by moving the specified number of cells in the dice, the red player would prioritise capturing the opponent piece. If more than one piece can be captured by moving different red pieces, red prioritises capturing the opponent piece closest to its home.
- Red will always keep one piece in the standard path and will not take another piece to the path from the base unless it cannot capture any piece by moving six cells. In such a case, a piece would be transferred to X.
- Red will always avoid creating blocks unless it is unavoidable.

#### 2.1.2 Green Player

The green player prioritises winning by blocking. It will not look to capture opponent pieces more than what is required to enter the home straight. The behaviour of this player is as follows:

- Green always likes to keep an empty base. Therefore, any pieces in the base will be moved to X whenever a six is thrown, if there are any pieces in the base unless moving six cells enables green to create a block.
- Green always prioritises moving its other pieces home before breaking a block. Green always attempts to move forward using the block move explained in Rule CS-4.
- Green will only break a block when other pieces are in front of it if and only if the value of the roll cannot be performed by green using the pieces in front of the block.

#### 2.1.3 Yellow Player

The yellow player always prioritises winning. It will not look to capture opponent pieces more than what is required to enter the home straight. The behaviour of this player is as follows:

- Yellow always like to keep an empty base. Therefore, anytime a six is thrown, if there are any pieces in the base, they will be moved to X.
- If no piece is in the base or has rolled a value that cannot transfer a piece from base to X, Yellow will prioritise the pieces that need captures first to see whether any opponent piece is within range. If such a piece is within range then the capture will take place.
- In case no captures could be done, Yellow moves the piece closest to its home by the number specified in the roll.

#### 2.1.4 Blue Player

The blue player is a random player that prioritises mystery cells. The behaviour of the player is as follows:

- The blue player always moves in a cyclic manner. That is, if B1 is moved in the current round, B2 is considered in the next and so on.
- If the piece to be moved is movable, the blue player prioritizes landing on the mystery cell if it is moving counterclockwise.
- If the piece to be moved is movable, the blue player prioritizes avoiding landing on the mystery cell if it is moving clockwise.

### 2.2 Deliverables

You are required to implement LUDO-CS as per the specification given in this section and the Rules in Section 1 using the C programming language.

- The program does not require any graphical user interfaces, and only a command line output is sufficient.
- The program should have three code files containing the types used in the program, the game logic, and the main function which executes the code.
- The output status messages required in the simulation should be in the form specified in Section 3.
- The code should be submitted as a single zip archive in the format <your index>.zip
- The code should accompany a report written in latex and it should contain the following:
  1. The structures used to represent the board and pieces.
  2. Justification for the used structures.
  3. Discussion of the efficiency of your program with justification.

## 3 Auxiliary Information

### 3.1 Required Output Messages

#### Before Game Begins
The following messages must be output for each player:
```
The red player has four (04) pieces named R1, R2, R3, and R4.
```

#### Once the First Player is Chosen
The following messages must be output for each player:
```
[colour 1] rolls <value>
[colour 2] rolls <value>
[colour 3] rolls <value>
[colour 4] rolls <value>
[colour *a] player has the highest roll and will begin the game.
The order of a single round is [colour *a], [colour *a + left], [colour *a + 2 left], and [colour *a + 3 left].
```

#### Once a Dice is Rolled by a Player
Once the dice are rolled, the following message should be output for the relevant player:
```
[Color X] player rolled [value].
```

#### Action After the Roll of Dice
Many actions can happen when the pieces are moved, as shown below:
- “Base” to the starting point “X”.
- Piece on the standard path can move cells specified by the dice value.
- Piece may be blocked.
- Piece might capture another piece.
- Piece may land on a mystery cell and teleport to another cell.

The customized output messages for each scenario above are given below:

##### “Base” to the starting point “X”
```
[Color X] player moves piece X[Name] to the starting point.
[Color X] player now has [Number]/4 on pieces on the board and [Number]/4 pieces on the base.
```

##### Piece on the standard path can move cells specified by the dice value
```
[Color X] moves piece X from location L1 to L2 by [value] units in [clockwise/counter-clockwise] direction.
```

##### Piece is blocked
```
[Color X] piece [Name] is blocked from moving from L1 to L2 by [Color X/Y] piece [Name].
[Color X] does not have other pieces on the board to move instead of the blocked piece. Ignoring the throw and moving on to the next player.
[Color X] does not have other pieces on the board to move instead of the blocked piece. Moved the piece to square L3 which is the cell before the block.
```

##### Piece captures another piece
```
[Color X] piece [Name] lands on square L1, captures [Color Y] piece [Name], and returns it to the base.
[Color X] player now has [Number]/4 on pieces on the board and [Number]/4 pieces on the base.
```

#### After Each Round
After each round, the status of each player has to be shown as given below:
```
[Color X] player now has [Number]/4 on pieces on the board and [Number]/4 pieces on the base.
============================
Location of pieces [Color x]
============================
Piece [Name] -> L1 or Base or Home.
The mystery cell is at L1 and will be at that location for the next <N> values.
```

#### Piece lands on a mystery cell and teleport to another cell
```
[Color X] player lands on a mystery cell and is teleported to <location>.
[Color X] piece [name] teleported to Bhawana.
[Color X] piece [name] teleported to Kotuwa.
[Color X] piece [name] teleported to Pita-Kotuwa.
[Color X] piece [name] teleported to Approach.
[Color X] piece [name] teleported to X.
[Color X] piece [name] teleported to Base.
[Color X] piece [name] feels energized, and movement speed doubles.
[Color X] piece [name] feels sick, and movement speed halves.
[Color X] piece [name] attends briefing and cannot move for four rounds.
[Color X] piece [name] is movement-restricted and has rolled three consecutively. Teleporting piece [name] to base.
The [Color X] piece [name], which was moving clockwise, has changed to moving counterclockwise.
The [Color X] piece [name] is moving in a counterclockwise direction. Teleporting to Kotuwa from Pita-Kotuwa.
```

#### Mystery Cells
A mystery cell has spawned in location L1 and will be at this location for the next four rounds.

#### Upon Winning
```
[Color X] player wins!!!
```

### Legend
The following meanings are to be used when interpreting the variables of the required output messages:
- Color X / Color Y = red, yellow, blue, or green
- Number = 0, 1, 2, 3, and 4
- Value = 1, 2, 3, 4, 5, and 6
- Name = 1, 2, 3, and 4
- L1/L2 = square ID of the path

When considering the square ID, each white square and the coloured square has to be numbered. All squares on the white path, including the starting squares. The numbering starts with the Yellow starting square and continues clockwise on the white path. The numbering starts with zero (0) and ends at 51. The coloured squares in the home path beyond the “Approach” are to be named [colour]homepath[cell number]. Cell number starts with zero (0).