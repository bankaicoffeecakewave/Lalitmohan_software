import cv2

imb = cv2.imread(r"/home/lalit/opencv/trial.jpeg") #r convert the text inside quotes into raw text #

text = "NAME-Lalit,RollNo-123ID0904"

ordi = (85,270)

font = cv2.FONT_HERSHEY_SIMPLEX

fntscl = 0.4

col_or = (0,0,0)

txt_thic = 1

cv2.namedWindow('IMAGE',cv2.WINDOW_NORMAL)
cv2.resizeWindow('IMAGE',400,400)
imb = cv2.putText(imb,text,ordi,font,fntscl,col_or,txt_thic,cv2.LINE_AA)
cv2.imshow('IMAGE',imb)
cv2.waitKey(0)
cv2.destroyAllWindows()
