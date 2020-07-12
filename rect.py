import numpy as np
import cv2
img = cv2.imread('this2.jpg')
height,width = img.shape[:2]
im_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
retval, im_bw = cv2.threshold(im_gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

image,contours, hierarchy = cv2.findContours(im_bw, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

for i in range(len(contours)):
    rect = cv2.minAreaRect(contours[i])
    #cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), cv2.LINE_4)
    box = cv2.boxPoints(rect)
    box =np.int0(box)
    img = cv2.drawContours(img,[box],0,(0,0,255),5)
    angle = round(rect[2],1)+90
    cv2.imshow('result' + str(i) + '.png', img)
    cv2.imwrite('image222.png',img)
#print contours
print 'h:',height,'w:',width
#print rect[0][1] 
print'\n'
print box
print'\n'
print 'ang:',rect[2]
cv2.waitKey(0)
cv2.destroyAllWindows()
