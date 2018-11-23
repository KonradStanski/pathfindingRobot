from PIL import Image
import numpy as np


class node:
	def __init__(self, isStart, isEnd, row, col, open):
		self.isStart = isStart
		self.isEnd = isEnd
		self.row = row # y ordinate
		self.col = col # x ordinate
		self.open = open # boolean - open or wall?

		self.RN = (self.row, self.col+1)
		self.LN = (self.row, self.col-1)
		self.UN = (self.row+1, self.col)
		self.DN = (self.row-1, self.col)


def compileNodes(height, width, maze, start, end):
	nodes = {}
	for i in range(width): # all columns
		for j in range(height): # all rows
			if mazeArr[j][i]:
				if (j, i) != start and (j, i) != end:
					nodes[(j, i)] = node(0, j, i, 0)
				elif (j, i) == start:



def main():

    im = Image.open("/home/cmput274/ARCMPUT/arduino/final/274final/python/mazes/maze1_11X11.gif")
    mazeArr = np.array(im)
    width = im.size[0]
    height = im.size[1]
    start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
    end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]


if __name__=="__main__":
	main()