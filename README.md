# legendary-waffle
Just some experiments with game development. I'm trying to make a networked roguelike. 

# Build

The game uses CMake, so you can just run
`cmake ./ && make`
from the root directory.

It's built using ncurses, so you need to have that installed.

You might need to fiddle with the CMakeLists file a bit since for some reason it has different opinions on how exactly it wants to require ncurses on Linux and OSX. Sorry about that, it's a side project, I haven't gotten around to fix it. 

# Run

Simply run 
`bin/LegendaryWaffle 2> wherever/you/want`
(debug output goes on stderr so you need to redirect it, or it will mess with the game's funky flow)

At the moment you can't do very much with it yet except collect various food, but future versions will allow for more interaction with the environment, possibly a combat system, and legendary waffles.
