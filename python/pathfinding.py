class Node:
	def _init__(self, G, H, F, X, Y):
		self.G = G
		self.H = H
		self.F = F
		self.X = X
		self.Y = Y
	def setF(self):
		self.F = self.H + self.G

def main():
	print('we here')
	gridSize = input().split() # format: X, Y
	nodes = {}
	for i in range(X):
		for j in range(Y):
			nodes[(i, j)] = Node(0, 0, 0, i, j)
	print(nodes)

if __name__ == "main":
	main()
