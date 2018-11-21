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
        print('start coord:', i, 0)
        maze_arr[0][i] = 2
        break

# find first end
for i in range(width):
    pixel = im.getpixel((i,height-1))
    if pixel == 0:
        print('end coord:', i, height-1)
        maze_arr[height-1][i] = 3
        break







#Prints maze information for debugging
print ('Maze width:', width)
print ('Maze height:', height)
print ('Maze size:', size, '\n')
print (maze_arr)

# create nearest neighbour pixel structure
# catch edge cases *litteraly*


