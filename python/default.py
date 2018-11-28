from PIL import Image, ImageColor, ImageDraw
import numpy as np



class node:
	def __init__(self, isStart, isEnd, row, col, open):
		self.isStart = isStart
		self.isEnd = isEnd
		self.row = row # y ordinate
		self.col = col # x ordinate
		self.open = open # boolean - open or wall?
		self.spot = (row, col)
		self.parent = None
		self.chosen = None
		# left right up down
		self.neighbours = [(self.row, self.col+1),(self.row, self.col-1),(self.row+1, self.col),(self.row-1, self.col)]

		# self.RN = (self.row, self.col+1)
		# self.LN = (self.row, self.col-1)
		# self.UN = (self.row+1, self.col)
		# self.DN = (self.row-1, self.col)


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
	while(1):
		current = min(open, key=open.get)
		open.pop(current)
		closed.append(current)
		if current == end:
			return(closed)
		neighbours = nodes[current].neighbours
		for i in neighbours:
			if not(i[0] < 0 or i[1] < 0 or i[0] > height or i[1] > width or i in closed or not nodes[i].open) and i not in open:
				nodes[i].parent = current
				open[i] = getCost(start, end, nodes[i].spot)


def distance(a, b):
	trueIf = (abs(a[0]-b[0]) == 0 and abs(a[1]-b[1]) == 1) or (abs(a[0]-b[0])==1 and abs(a[1]-b[1])==0)
	return(trueIf)


def finishPath(steps, end, start, nodes):
	path = []
	flag = True
	count = 0
	x = end[0]
	while(flag):
		# if(distance(steps[i], steps[i+1]) == 1):
		# 	path.append(steps[i+1]))
		path.append(nodes[x].parent)
		x = nodes[x].parent
		if x == start[0]:
			return(path[::-1]+end)

	


def main():
    im = Image.open("/home/cmput274/ARCMPUT/arduino/final/274final/python/mazes/maze2_11X11.gif")
    mazeArr = np.array(im)
    print(mazeArr)
    width = im.size[0]
    height = im.size[1]
    start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
    end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]
    nodes = compileNodes(height, width, mazeArr, start[0], end[0])
    print(end, start)
    # v = findPath(start[0], end[0], nodes, height, width)[::-1]
    # for i in v:
    # 	mazeArr[i[0]][i[1]] = 255

    # print(mazeArr)   
    c = finishPath(findPath(start[0], end[0], nodes, height, width)[::-1], end, start, nodes)
    print(c)
    for i in c:
    	mazeArr[i[0]][i[1]] = 255

    print(mazeArr)
   # out = Image.new(RGB, (width*height), color = 0)

    out = Image.fromarray(mazeArr)
    out.save( "out.PNG")


if __name__=="__main__":
    main()
