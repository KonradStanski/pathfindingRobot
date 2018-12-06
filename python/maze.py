#/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/

from PIL import Image, ImageColor, ImageDraw
import numpy as np


# Global statement: this is where one can change the name of the input file
im = Image.open("mazes/maze1_medium.gif")


class node:
	def __init__(self, isStart, isEnd, row, col, open):
		self.isStart = isStart
		self.isEnd = isEnd
		self.open = open # boolean - open or wall?
		self.spot = (row, col)
		self.parent = None
		# left right up down
		self.neighbours = [(row, col+1), (row, col-1), (row+1, col), (row-1, col)]


def mazeInit():
	# initializes the logic array from the maze image using the PIL module
	# and numpy array
	mazeArr = np.array(im)
	width = im.size[0]
	height = im.size[1]
	start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
	end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]
	nodes = compileNodes(height, width, mazeArr, start[0], end[0])
	return(mazeArr, start[0], end[0], nodes, height, width)


def compileNodes(height, width, mazeArr, start, end):
	# initializes the dictionary of nodes from their x,y location tuple
	# returns a dictionary where the key is the coordiates and the value is
	# the node object at that location
	nodes = {}
	for i in range(width): # all columns
		for j in range(height): # all rows
			if mazeArr[j][i]: # its true of the values is 1 and the node is closed/ wall
				nodes[(j, i)] = node(0, 0, j, i, 0)  # a closed node
			else: # it's open
				if (j, i) != start and (j, i) != end:
					nodes[(j, i)] = node(0, 0, j, i, 1)
				elif (j, i) != end:  # then it's the start
					nodes[(j, i)] = node(1, 0, j, i, 1)
				else:  # must be the end
					nodes[(j, i)] = node(0, 1, j, i, 1)
	return nodes


def getCost(start, end, me):
	# uses manhattan distance heuristic
	# gets the distance from start in h and to end in g in manhattan distances
	hCost = abs((me[0]-start[0]))+abs((me[1]-start[1]))
	gCost = abs((me[0]-end[0]))+abs((me[1]-end[1]))
	return(hCost+gCost)


def findPath(start, end, nodes, height, width):
	# This implements A*. Based on Sebatian Lague's youtube series on
	# A* implementation.
	open = {} # dictionary of open nodes
	closed = [] # list of closed nodes
	open[start] = getCost(start, end, nodes[start].spot) # get initial node
	while(True):
		current = min(open, key=open.get) # current is least expenisve node in open
		open.pop(current) # remove current node from open
		closed.append(current) # add current node to closed
		if current == end: # check f end reached
			return # if end reached end
		neighbours = nodes[current].neighbours # fetch neighbours
		for i in neighbours:
			# this next if statement checks that the neightbour is in the range of the map
			# and that it is not in open already and also not in closed.
			if (not(i[0] < 0 or i[1] < 0 or i[0] > height or i[1] > width or i in
						closed or not nodes[i].open) and i not in open and i not in closed):
				# get cost and give it a parent
				nodes[i].parent = current
				open[i] = getCost(start, end, nodes[i].spot)


def finishPath(end, nodes):
	# go backwards through the parents of the nodes to get the final path!
	path = []
	x = end
	# go through and creat3e the final list, return the reverse of that.
	while(True):
		path.append(nodes[x].parent)
		x = nodes[x].parent
		if nodes[x].isStart:
			return(path[::-1]+[end])


def outputPath(mazeArr, path):
	# take in the maze array and the final path,
	# make the tiles in maze array which are part of the path white
	# and output to .png
    for i in path:
    	mazeArr[i[0]][i[1]] = 255
    out = Image.fromarray(mazeArr)
    out.save( "out.PNG" )
