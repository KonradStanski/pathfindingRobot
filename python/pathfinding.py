from PIL import Image
import numpy as np

class maze:

	def __init__(self, mapImage):
		self.mapImage = mapImage
		im = Image.open(mapImage)
		mazeArr = np.array(im)
		self.width = im.size[0]
		self.height = im.size[1]

		for i in range(self.width ):
			pixel = im.getpixel((i, 0))
			if pixel == 0:
				self.start = [i, 0]
				break
		for i in range(self.width):
			pixel  = im.getpixel((i, self.height-1))
			if pixel == 0:
				self.end = [self.height-1, i]
		

	class Node:
		def __init__(self, open, G, H, F, X, Y):
			self.G = G
			self.H = H
			self.F = F
			self.X = X
			self.Y = Y
			self.open = isopen
			self.start = isstart
			self.end = isend
		def setF(self):
			self.F = self.H + self.G
	














def sortNodes(nodes):
	for n in nodes:
		if n not in closed:
			open.append(n)
	print(open)


def main():
	print('we here')
	gridSize = input().split() # format: X, Y
	nodes = {}
	for i in range(int(gridSize[0])):
		for j in range(int(gridSize[1])):
			nodes[(i, j)] = Node(0, 0, 0, i, j)
	print(nodes)
	sortNodes(nodes)
	print('enter your starting point')
	start = input()
	print(start)


if __name__ == "__main__":
	main()
