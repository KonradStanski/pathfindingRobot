from PIL import Image
import numpy as np

#Opens the Image
im_file = Image.open('mazes/maze1_11X11.gif')

#Reads the image pixel information
bin_maze = np.array(im_file)

#Sets the width, height and maze size variables
width = im_file.size[0]
height = im_file.size[1]
size = width * height

#Prints maze information for debugging
print ('Maze width:', width)
print ('Maze height:', height)
print ('Maze size:', size, '\n')
print (bin_maze)

# create nearest neighbour pixel structure
# catch edge cases *litteraly*


