from PIL import Image
import numpy as np
from time import sleep
#==========================================this file is not necessary for function of program====================================
#===================================================it just does a cool animation================================================
#Opens the Image
im = Image.open('mazes/maze2_11X11.gif')

#Reads the image pixel information INDEXING IS ****(Y,X)****
maze_arr = np.array(im)


#Sets the width, height and maze size variables
width = im.size[0]
height = im.size[1]
size = width * height

#find start and end assuming start on top and end on botom
# find first start
for i in range(width):
    pixel = im.getpixel((i,0))
    if pixel == 0:
        start = [0, i]
        break

# find first end
for i in range(width):
    pixel = im.getpixel((i,height-1))
    if pixel == 0:
        end = [height-1, i]
        maze_arr[height-1][i] = 2
        break


##########################################################
# always turn  finding algorithm / just for fun?
grid = maze_arr
path = []
def search(x, y):
    print('entering maze')
    if grid[x][y] == 2:
        path.append([y, x])
        print ('found at %d,%d' % (x, y), '\n')
        return True
    elif grid[x][y] == 1:
        print ('wall at %d,%d' % (x, y))
        return False
    elif grid[x][y] == 3:
        path.append([y, x])
        print ('visited at %d,%d' % (x, y))
        return False

    print ('visiting %d,%d' % (x, y))
    path.append([y, x])
    # mark as visited
    grid[x][y] = 3

    # explore neighbors clockwise starting by the one on the right
    if ((x < len(grid)-1 and search(x+1, y))
        or (y > 0 and search(x, y-1))
        or (x > 0 and search(x-1, y))
        or (y < len(grid)-1 and search(x, y+1))):
        return True

    return False
search(start[0], start[1])
############################################################

moves = []
for i in range(len(path)-1):
    xdist = path[i+1][0] - path[i][0]
    ydist = path[i+1][1] - path[i][1]
    print("i is:", i, "xdist: ", xdist, "ydist: ", ydist)


#small animation
maze_arr = np.array(im)
for i in range(len(path)-1):
    x = path[i][0]
    y = path[i][1]
    maze_arr[x][y] = 4
    print(maze_arr)
    sleep(0.1)


#Prints maze information for debugging
print ('Maze width:', width)
print ('Maze height:', height)
print ('Maze size:', size, '\n')
print ('Maze start:' , start)
print ('Maze end:', end, '\n')
#print (maze_arr, '\n')
#maze_arr = np.array(im)
#print (maze_arr)
print (path)
print( moves )
