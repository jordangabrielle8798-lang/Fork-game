if you're using termux I suggest you use the command "cd ~" to get to your main directory

then use the command "mkdir fork" to make a directory to house the game

then use the commands "cd ~/storage/downloads" to get to your downloads and "mv main2.cpp ~/fork" to move it
to the game directory you created

you'll also want clang so run the command "pkg install clang"

after that you can compile any time youre in the game directory and you get there by typing "cd ~/fork"

the compile and run game command is "clang++ main2.cpp -o game && ./game"

and to edit the game you'll need nano which you get from "pkg install nano" then you edit the game with "nano main2.cpp"

in nano use tags like "-c" or "-l" or both to see what line number you're on which is helpful when 
searching for the line number of an error

if you have any questions feel free to join my personal discord channel and ask about anything
https://discord.gg/nXtrFRMs

Updated Nov 15th to connect all rooms inside the mansion using a placeholder bathroom off of the north side of westWingHallExt
