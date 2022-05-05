# Importing the pillow library's
# desired modules


'''
kitrino:0 (255,255,0)
kokkino:1 (255,0,0)
prasino:2 (0,128,0)
ble:3 (0,0,255)


0 3 2 3 1 0 3 1 0 2 1 3 2 2 1 2 Number of valid edges: 42

Solution found on iteration k=95679
'''


from PIL import Image, ImageDraw
import os

coors ='''196,23
114,89
333,74
399,83
257,132
326,131
284,180
88,263
143,245
220,245
321,273
320,329
358,328
273,365
312,364
380,432'''


arg = os.getenv('P')
    
#arg = '''2 0 3 0 1 2 0 2 3 2 3 0 1 1 3 1'''

#arg = '''0 3 1 2 2 0 3 2 1 0 1 2 3 0 1 2'''


args = arg.split(" ")

# Opening the image (R prefixed to
# string in order to deal with '\'
# in paths)
img = Image.open(R"map.png")



for i,l in enumerate(coors.split("\n")):
    #print(l)
    vals = l.split(",")
    
    seed = (int(vals[0]),int(vals[1]))
    
    if(args[i]=="0"):
        rep_value = (255, 255, 0)
    elif(args[i]=="1"):
        rep_value = (255, 0, 0)
    elif(args[i]=="2"):
        rep_value = (0, 128, 0)
    elif(args[i]=="3"):
        rep_value = (0, 0, 255)

    ImageDraw.floodfill(img, seed, rep_value, thresh=50)



# Displaying the image
img.show()

