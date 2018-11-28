import maze

def main():
    im = Image.open("/home/cmput274/ARCMPUT/arduino/final/274final/python/mazes/maze1_11X11.gif")
    mazeArr = np.array(im)
    width = im.size[0]
    height = im.size[1]
    start = [(0, i) for i in range(width) if im.getpixel((i, 0)) == 0]
    end = [(height-1, i) for i in range(width) if im.getpixel((i, height-1)) == 0]
    nodes = maze.compileNodes(height, width, mazeArr, start[0], end[0])  
    maze.findPath(start[0], end[0], nodes, height, width)
    mazeOfinishPath(end, nodes)



if __name__=="__main__":
    main()