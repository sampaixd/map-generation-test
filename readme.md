# project endless dungeon

### Usage
The program is precompiled with the file "game", running it you simply type "./game" into the terminal. If you wish to change any values inside the program, you can recompile it running "build.sh" with the command "./build.sh" (Note that you might have to make build.sh an executable by typing "chmod +x build.sh").
A new map will be generated once you start the program, and you can press space to generate a new map


### info

This project uses BSP partitioning to create a map for a video game, see this site for an simple explanation: http://www.roguebasin.com/index.php/Basic_BSP_Dungeon_generation

This project uses recursion to create the map tiles, which makes changing the amount of iterations on the map as simple as changing a single value in the source code. There are many other variables that you can change inside the code that will alter the output, however beware that the map might not generate correctly if you enter bad values.

I only know of one bug in the code, which is that sometimes a corridor will not be generated. I have no idea why.
