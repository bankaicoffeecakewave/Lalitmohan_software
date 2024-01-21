import cv2 as cv
import numpy as np

path = "/home/lalit/opencv/background.jpg"
img = cv.imread(path)
text = "NAME-Lalit Mohan Naik, RollNo-123ID0904"
ordi = (115,250)

font = cv.FONT_HERSHEY_SIMPLEX

fntscl = 0.4

col_or = (0,0,0)

txt_thic = 1

pts = np.array([[150,30],[120,100],[195,100]],dtype=np.int32) #triangle coordinates
pts = pts.reshape((3,1,2))

pou =np.array([[50,150],[79,125],[110,150],[100,185],[60,185]],np.int32) #pentagon coordinates

prn = np.array([[135,140],[165,120],[195,140],[195,172],[165,190],[135,172]]) #hexagon coordinates

imb = cv.putText(img,text,ordi,font,fntscl,col_or,txt_thic,cv.LINE_AA)
cv.rectangle(img,(250,50),(310,110),(180,0,51),-1)  #square coordinates
cv.rectangle(img,(250,50),(310,110),(0,0,0),4)
cv.polylines(img,[pts],isClosed = True,color = (0,0,0),thickness= 7)
cv.fillPoly(img,[pts],(0,0,240))

cv.polylines(img,[pou],isClosed = True,color = (0,0,0),thickness= 7)
cv.fillPoly(img,[pou],(195,0,127))

cv.polylines(img,[prn],isClosed = True,color = (0,0,0),thickness= 7)
cv.fillPoly(img,[prn],(0,175,0))
img = cv.imshow("Image",img)
cv.waitKey(0)
cv.destroyAllWindows()