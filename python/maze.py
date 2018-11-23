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

me = node(1, 0, 4, 5, 1)
print(me.RN)
