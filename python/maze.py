from PIL import Image, ImageColor, ImageDraw
import numpy as np


im = Image.open("mazes/maze2_11X11.gif")


class node:
	def __init__(self, isStart, isEnd, row, col, open):
		self.isStart = isStart
		self.isEnd = isEnd
		self.open = open # boolean - open or wall?
		self.spot = (row, col)
		self.parent = None
		# left right up down
		self.neighbours = [(row, col+1),(row, col-1),(row+1, col),(row-1, col)]


def mazeInit():
	mazeArr = np.array(im)
	width = im.size[0]
	height = im.size[1]
	start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
	end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]
	nodes = compileNodes(height, width, mazeArr, start[0], end[0])
	return(mazeArr, start[0], end[0], nodes, height, width)


def compileNodes(height, width, mazeArr, start, end):
	nodes = {}
	for i in range(width): # all columns
		for j in range(height): # all rows
			if mazeArr[j][i]: # its true of the values is 1 and the node is closed
				nodes[(j, i)] = node(0, 0, j, i, 0) # a closed node
			else: # it's open
				if (j, i) != start and (j, i) != end:
					nodes[(j, i)] = node(0, 0, j, i, 1)
				elif (j, i) != end: # then it's the start
					nodes[(j, i)] = node(1, 0, j, i, 1)
				else: # must be the end
					nodes[(j, i)] = node(0, 1, j, i, 1)
	return nodes


def getCost(start, end, me):
	hCost = abs((me[0]-start[0]))+abs((me[1]-start[1]))
	gCost = abs((me[0]-end[0]))+abs((me[1]-end[1]))
	return(hCost+gCost)


def findPath(start, end, nodes, height, width):
	open = {}
	closed = []
	open[start] = getCost(start, end, nodes[start].spot)
	while(True):
		current = min(open, key=open.get)
		open.pop(current)
		closed.append(current)
		if current == end:
			return
		neighbours = nodes[current].neighbours
		for i in neighbours:
			if not(i[0] < 0 or i[1] < 0 or i[0] > height or i[1] > width or i in closed or not nodes[i].open) and i not in open:
				nodes[i].parent = current
				open[i] = getCost(start, end, nodes[i].spot)


def finishPath(end, nodes):
	path = []
	x = end
	while(True):
		path.append(nodes[x].parent)
		x = nodes[x].parent
		if nodes[x].isStart:
			return(path[::-1]+[end])


def outputPath(mazeArr, path):
    for i in path:
    	mazeArr[i[0]][i[1]] = 255
    out = Image.fromarray(mazeArr)
    out.save( "out.PNG")

# def main():
#     im = Image.open("mazes/maze1_11X11.gif")
#     mazeArr = np.array(im)
#     width = im.size[0]
#     height = im.size[1]
#     start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
#     end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]
#     nodes = compileNodes(height, width, mazeArr, start[0], end[0])
#     findPath(start[0], end[0], nodes, height, width)
#     c = finishPath(end, nodes)
#     outputPath(mazeArr, c)


# if __name__=="__main__":
# 	main()
