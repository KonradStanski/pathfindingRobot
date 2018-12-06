#/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/
import maze
import pyToArd as pta
from PIL import Image, ImageColor, ImageDraw
import numpy as np


class Compass(object):
    # based on my curious search for how to so a switch case type
    # deal in python. based on suggestions at:
    # https://stackoverflow.com/questions/60208/replacements-for-switch-statement-in-python
    # returns the compass rose directions for the rover to complete the path
    def vector(self, a, b):
        # take in the direction, make it a string, and call the appropriate
        # finction.
        direction = [(b[0]-a[0]), (b[1]-a[1])]
        if direction[0] == -1:
            direction[0] = "m1"
        if direction[1] == -1:
            direction[1] = "m1"
        where = 'direc_'+str(direction[0])+'to'+str(direction[1])
        which = getattr(self, str(where), lambda: "Invalid Path!")
        return which()
    # the collection of functions that return the appropriate direction.
    def direc_0tom1(self):
        return "W"

    def direc_0to1(self):
        return "E"

    def direc_1to0(self):
        return "S"

    def direc_m1to0(self):
        return "N"


def directions(finalPath):
    # call the dispatch method to get a string on compass directions
    # based on the solved path. return a tring of directions.
    direc = []
    m = Compass()
    for x in range(len(finalPath)-1):
        direc.append(m.vector(finalPath[x], finalPath[x+1]))
    return direc


def main():
    # Here, we will read in the values neccecary to navigate the maze using the
    # "API" created in maze.py, where all A* and algorithms are abstracted.
    # Then create the compass direction string and send it using pyToArd.py
    mazeArr, start, end, nodes, height, width = maze.mazeInit()
    maze.findPath(start, end, nodes, height, width)
    finalPath = maze.finishPath(end, nodes)
    maze.outputPath(mazeArr, finalPath)
    # get output string
    pathArr = directions(finalPath)
    print("path length is: ", len(pathArr))
    pathStr = ''.join(pathArr)
    print("path is: ", pathStr)
    # output string to arduino
    try:
        pta.writeToArd(pathStr)
    except:
        # something wrong with bluetooth...
        print("ERROR: Unable to send string")


if __name__=="__main__":
    main()
