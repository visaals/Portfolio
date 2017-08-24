========================================================================
    CONSOLE APPLICATION : Lab4v2 Project Overview
========================================================================

Nirek Sharma 444306
Visaal Ambalam 444490
John Bisognano 443578

README Lab4
 
Errors we ran into:
1.     We had trouble managing our corner cases on row and column 7. The project would build but it would register the 7th row and column would 
		not allows any valid moves. We realized the error was that the way we were cycling through our polar coordinate implementation. We went counterclockwise 
		from the right and broke the loop if it a space was out of bounds, so the 7th row and column would always break the valid move method. We fixed it by
		implementing some if statements to handle the special corner cases.
2.     Reading board from text file was difficult at first. It was tricky to read in empty game pieces because we made the text file store the displays of 
		the game pieces in order. The displays would be “ “ (empty space) for the empty pieces, so we had to manage those special cases as well. Also we had 
		trouble storing the color of each game piece. We used enums and ran into a headache trying to convert an enum to a color and making sure the gamepiece was 
		constructed properly. We fixed it by using stringToCol function.
3.     The first line of each saved text file was the name of the game itself. Then, underneath were the actual board pieces and coordinates. We ran into 
		errors in assuming that the first line would be skipped once read and the coordinates would read in. Instead, the file reading code was breaking due 
		to the game name being read as a board piece. To combat this we put and if statement that if the game name was read in correctly, a board would print 
		and then it would move to the next line via use of an isstringstream and the getline function to start filling in the pieces.
4.     We had a ton warnings because we were using doubles to index into our vectors because we calculated the index with polar coordinates
		so we had to go back and static cast those doubles to unsigned ints. We also had some warnings saying all our control flows were not complete and so added proper control flows.

 COPY CONTROL:
 
We never had to use a copy constructor at all because we never recreated an instance of any one of our games. Each game object (NineAlmonds, MagicSquare, Reversi)
 would be destructed after the game was saved or not saved. Conversely, if we were to create a parallel game to be run while the original version of the game is 
 running we would need a copy constructor to create that parallel instance of a game. 

We did not use a copy assignment operator, but if we did, we would use a it to create multiple copies of the same game at once so that we can update each game 
	 in real time with the copy assignment operator.

We did not use move constructors in our project. However, because copy construction/copy assignment operators are expensive due to time/memory constraints, 
	we could instead use move constructors or move assignment operators

We did not use any destructors in the project as a result of not using any of the constructors but we would have used destructors to remove instances of 
	copied implementations of the classes.


COMMAND LINE: 

One problem we ran into when inputting information into our game was when we typed a point followed by another point (e.g. 2,2 1,4) 
	the turn method would read in both points and we would not receive an invalid input message. This was fixed by adding a getline() function call 
	when reading in the user’s move. 

Additionally, when starting the program, if we entered the program name followed by nothing, the program would crash. However, this was 
	fixed by adding a simple if statement to check the value of argc (the number of arguments). When fixed, it returns the input message. 

As was the case in our previous labs, incorrectly formatted inputs (not pair of integers within the board size) for the player turns returned correct error 
	message for the incorrectly formatted input. 

When reading in the reversi game from the previously saved game, we added a line to compare the inputted users names and the saved user names. 
	If the names aren’t the same it asks to overwrite the game or to not, if they are (irrespective of order) the game plays with the next player resuming their move. 

When testing done and stalemate cases, we found that the game would always return done even in some cases of stalemate because done 
	was always checked first before stalemate. Once we switched to checking stalemate first, our program worked appropriately.

We rigorously tested the games to completion and successfully received the appropriate message in the cases of stalemate and success. 

We also tested other command line inputs for starting the game to make sure the usage message was shown
in any case where the user inputted incorrectly formatted input. 



