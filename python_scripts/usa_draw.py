from PIL import Image, ImageDraw
import matplotlib.pyplot as plt
import os

'''
COLOR       code    rgb value

yellow:      0     (255,255,0)
red:         1     (255,0,0)
green:       2     (0,128,0)
bleu:        3     (0,0,255)

1 1 1 0 1 0 1 2 0 1 3 2 1 0 0 2 3 2 2 3 3 0 2 3 3 3 1 2 2 1 2 0 1 3 2 0 1 3 2 3 0 2 3 1 0 3 2 0
'''

# points for filling
coors ='''1374,840
439,739
1129,766
168,589
663,565
1824,360
1759,520
1612,1044
1510,868
424,315
1258,496
1360,505
1096,426
973,598
1404,631
1168,955
1903,162
1702,504
1858,324
1393,363
1051,237
1272,864
1143,601
550,162
909,471
280,496
1839,271
1777,475
616,774
1705,327
1674,687
879,204
1482,510
957,774
207,252
1614,441
1861,351
1591,778
870,331
1377,724
898,958
457,544
1789,241
1657,594
241,117
1566,552
1204,309
610,369'''

arg = os.getenv('P')

args = arg.split(" ")

img = Image.open(R"python_scripts/production_usa.png")

for i,l in enumerate(coors.split("\n")):

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

    # add michigan again
    if(i==19):
        ImageDraw.floodfill(img, (1269,213), rep_value, thresh=50)


# show the image
plt.imshow(img)
plt.grid(False)
plt.axis('off')
plt.show()