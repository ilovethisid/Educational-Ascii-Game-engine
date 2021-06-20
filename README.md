# EAG Engine

***This engine is available for Microsoft Windows ONLY***

The EAG engine stands for Educational Ascii Game engine, which allows users to create games easily and quickly using c++. 
Users can easily create games by utilizing classes and functions provided by game engines, while simultaneously increasing their application power and understanding of game engines for c++.

**`Documentation`** |
------------------- |
[![Documentation](https://img.shields.io/badge/wiki-Manual_and_tutorial-informational.svg)](https://github.com/ilovethisid/Educational-Ascii-Game-engine/wiki/) |

## Key features

The EAG engine offers 
1. ASCII graphics libraries
2. Physics engines
3. Keyboard listeners
4. Database & Sound

capabilities.

### 1. ASCII graphics libraries

  The ASCII graphics library provides a function that displays objects on the screen and draws simple shapes (lines, squares, circles, etc.)
This function allows the user to draw simple shapes in the console window. 
Due to the nature of the game engine, it is not focused on a single genre of games and is made applicable to many games.

### 2. Physics engines

  The physical engine provides the ability to consider physical interactions such as rigidbody and collision for objects, as in Unity.
For example, you can use a collision to make enemies disappear when they are hit by a bullet, and adjust velocity to make objects move.

### 3. Keyboard listeners

  The keyboard listener is implemented as a thread and can receive input from multiple keys simultaneously, and can be entered into various states, such as once pressed and pressed.

### 4. Database & Sound

Additional convenience features include support for databases to record information and store information needed to implement the game, and support for sound-related functions to play custom music, etc.

## Install

To install the current release, there are two options:

1.   Simply clone this repository in your own project directory.
You will need
[Git](https://git-scm.com/downloads) 
to clone repository:

```shell
$ git clone https://github.com/ilovethisid/Educational-Ascii-Game-engine.git
```

2.   An alternative way is to download 
[zip file](https://github.com/ilovethisid/Educational-Ascii-Game-engine/archive/refs/heads/main.zip)
and upzip into your project directory.

#### *Try your first EAG engine based game*

After you have installed EAG engine into your own project directory, just simply add one line at the top of your source code:

```cpp
#include "./Educational-Ascii-Game-engine/game_loop.h"
```

For more examples, see the
[EAG engine tutorials](https://github.com/ilovethisid/Educational-Ascii-Game-engine/wiki/Tutorial-part-0-%3A-Introduction/).

## Contribution guidelines

**If you want to contribute to EAG engine, be sure to review the
[contribution guidelines](CONTRIBUTING.md). This project adheres to EAG engine's
[code of conduct](CODE_OF_CONDUCT.md). By participating, you are expected to
uphold this code.**

**We use [GitHub issues](https://github.com/ilovethisid/Educational-Ascii-Game-engine/issues) for tracking requests and bugs.**

The EAG engine project strives to abide by generally accepted best practices in
open-source software development:

[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.0%20adopted-ff69b4.svg)](CODE_OF_CONDUCT.md)

## Useful tool

*   [Ascii-painter](https://github.com/eu90h/ascii-painter)

## License

[MIT License](LICENSE)
