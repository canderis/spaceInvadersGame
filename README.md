# spaceInvadersGame

Made for CS 327, by Scott Huffman

This is a simple version of Space Invaders.
Use the Arrow Keys to move the player's ship left and right. Use the Up arrow to shoot.
Try to kill all the enemy ships before they reach the ground to win.

The enemies will sometimes spawn shields to hide behind. These can be destroyed but sometimes it can take more than one hit.

I initially intended to give the enemies the ability to fire back, but ended up implementing shields by mistake and I liked the idea better. I was also going to accelerate the enemies as fewer remained, but I had enough difficulty winning as it was so I left it the same.

How to run:
Run make to build the binary.
run ./game to run the game.
Note:
This requires C++ v11. Assuming your system supports it, make will compile the code correctly.
