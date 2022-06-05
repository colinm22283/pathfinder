#pragma once

// Edit this text to change the help text
const char* HELP_TEXT = R"V0G0N(
HELP TEXT

exit                      Quit the engine

help <page>               Show this help text

bind <kc> <cmd>           Binds a key to run a command
unbind <kc>               Unbind a key

time                      Prints the current time

pin <x> <y>               Pins a node in place
unpin <x> <y>             Unpins a node

setcolor <x> <y> <c>      Sets a nodes color at a position

loadimg <path>            Loads a bmp image on to the grid

set <var> <val>     Sets engine variables
    resx            Sets the horizontal resolution         (int)
    resy            Sets the vertical resolution           (int)

    fpslimit        Sets the frame limiter                 (int)
    fpsoutput       Sets the visibility of the fps output  (bool)
    printkeys       Prints key codes                       (bool)

    linelength      Sets the distance between nodes        (float)
    decay           Sets the time which velocities decay   (float)
    gravity         Sets the amount of gravity             (float)
    wind            Sets the amount of wind                (float)
    bgcolor         Sets the background color              (color)







)V0G0N";