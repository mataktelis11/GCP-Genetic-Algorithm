from PIL import Image, ImageDraw
import matplotlib.pyplot as plt
import os

'''
COLOR       code    rgb value

yellow:      0     (255,255,0)
red:         1     (255,0,0)
green:       2     (0,128,0)
bleu:        3     (0,0,255)

'''

# points for filling
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

args = arg.split(" ")

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

    # run the floodfill function (similar to 'bucket fill' of gimp/photoshop)
    ImageDraw.floodfill(img, seed, rep_value, thresh=50)

# show the image with the user's default Image Viewer
#img.show()
plt.imshow(img)
plt.show()