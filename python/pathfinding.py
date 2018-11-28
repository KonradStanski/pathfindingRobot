import maze
from PIL import Image, ImageColor, ImageDraw
import numpy as np

class Compass(object):
    def vector(self, a, b):
        """dispatch method"""
        direction = [(b[0]-a[0]), (b[1]-a[1])]
        if direction[0] == -1:
            direction[0] = "m1"
        if direction[1] == -1:
            direction[1] = "m1"
        where = 'direc_'+str(direction[0])+'to'+str(direction[1])
        which = getattr(self, str(where), lambda: "uhoh")
        return which()

    def direc_0tom1(self):
        return "S"

    def direc_0to1(self):
        return "N"

    def direc_1to0(self):
        return "E"

    def direc_m1to0(self):
        return "W"



def directions(finalPath):
    direc = []
    m = Compass()
    for x in range(len(finalPath)-1):
        direc.append(m.vector(finalPath[x], finalPath[x+1]))
    print(direc)


def main():
    mazeArr, start, end, nodes, height, width = maze.mazeInit()  
    maze.findPath(start, end, nodes, height, width)
    finalPath = maze.finishPath(end, nodes)
    maze.outputPath(mazeArr, finalPath)
    directions(finalPath)


if __name__=="__main__":
    main()