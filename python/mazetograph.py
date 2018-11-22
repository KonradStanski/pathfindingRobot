from PIL import Image
import numpy as np

#Opens the Image
im = Image.open('mazes/maze1_11X11.gif')

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
        start = [i, 0]
        #maze_arr[0][i] = 4
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
def search(x, y):
    print('entering maze')
    if grid[x][y] == 2:
        print ('found at %d,%d' % (x, y), '\n')
        return True
    elif grid[x][y] == 1:
        print ('wall at %d,%d' % (x, y))
        return False
    elif grid[x][y] == 3:
        print ('visited at %d,%d' % (x, y))
        return False

    print ('visiting %d,%d' % (x, y))

    # mark as visited
    grid[x][y] = 3

    # explore neighbors clockwise starting by the one on the right
    if ((x < len(grid)-1 and search(x+1, y))
        or (y > 0 and search(x, y-1))
        or (x > 0 and search(x-1, y))
        or (y < len(grid)-1 and search(x, y+1))):
        return True

    return False
search(start[1], start[0])
############################################################




#Prints maze information for debugging
print ('Maze width:', width)
print ('Maze height:', height)
print ('Maze size:', size, '\n')
print ('Maze start:' , start)
print ('Maze end:', end, '\n')
print (maze_arr, '\n')
maze_arr = np.array(im)
print (maze_arr)


# create nearest neighbour pixel structure
# catch edge cases *litteraly*


