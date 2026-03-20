## SO_LONG (=^･ω･^=)
this is a 2d game i made using only C with a help of a custom library called MLX. I used my previous project [get_next_line](https://github.com/yabuawad/get_next_line) (that basically reads from a text file into a buffer) to read any map for the game from the file and turn it into movable pixled images.  
the game basically has a single player with some collectables and an exit door to end the game!  

![banner](assets/banner.png)

## some game rules handled in code:
~the game is playable using WASD keys  
~the player should collect all collectables to be able to exit from the door,otherwise you can't  
~a valid map should be surrounded with walls (1s) and must be closed  
~a valid map should not have more than one player  
~a valid map should not have more than one exit door  
~the player can not exit from the door without taking every collectable existed  
~a valid map should have all collectables reachable as well as the exit door(Ex:one collectable surrounded by walls make it impossiable to reach it)  
~if not all collectables are collected,the player can walk over the exit door  

## map format 
```bash
111111
1P0C01
100001
1C0E01
111111
```
## symbols:
1 -> Wall  
0 -> empty space(walkable area)  
P -> player  
E -> exit  
C -> collectables  
## lets play the game ^^
first clone my repo  
```bash
git clone git@github.com:yabuawad/so_long.git so_long
cd so_long
```
then youll need to compile the custom library
```bash
cd minilibx-linux
make
```
then compile the project using the Makefile
```bash
cd ..
make
```
then run it like this
```bash
./so_long maps/map3.ber
```
you can use any map you want from the ones left in the `Maps` file or even create your own map! just make sure it aligns with the rules above!
and thats it enjoy :))
