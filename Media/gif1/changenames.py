import os

i=0
for filename in os.listdir("."):
    if filename.endswith(".png"):
        newfilename="frame-"+str(i)+".png"
        #print(filename)
        #print(newfilename)
        os.rename(filename,newfilename)
        i+=1