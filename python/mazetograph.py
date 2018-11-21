from PIL import Image
import numpy as np

#Opens the Image
im_file = Image.open('mazes/maze1.png')

#Sets the width, height and maze size variables
width = im_file.size[0]
height = im_file.size[1]
size = width * height

#Reads the image pixel information
im_arr = np.array(im_file)

#Prints maze information for debugging
print ('Maze width:', width)
print ('Maze height:', height)
print ('Maze size:', size, '\n')
print (im_arr)

