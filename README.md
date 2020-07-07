Game-Engine-WithSFML
###################################

Game rules 
##################################################################
# Shoot the enemy space ship.                                   ##
# For each ship you get 1 point.                                ##
# If the enemy ship crashes on you, it's game over.             ##
##################################################################

Game Controls	
##################################################################
# Use Arror keys to move                           	        ##
# Space to shoot		                                ##
##################################################################



Things to look into:


* I have created my game engine similar to unity. There are different systems for each 
  component like render system, collision system, physiscs system etc. 
* The Game Engine has a init() and Run() function.
* In init() the predefined game obejcts are initialized.
* I have a instantiate function which will create and return a game object in run time. 
  The parameter is the file location of the prefab/GameObeject. 
* I have created a texture cache, so each time the same texture wants to be loaded it can 
  be fetched from the cache.
* Implemented a destory function with timer(in seconds), which will destory game objects
  after the time is up.
* For the final game, I replaced GLIB with SFML.
 