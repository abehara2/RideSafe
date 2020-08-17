import numpy as np
import cv2

inWidth = 300
inHeight = 300
WHRatio = inWidth / float(inHeight)
inScaleFactor = 0.007843
meanVal = 127.5

#hard coded focal length
focalLength = 552*24/12

#load ssd model and weights
prototxt = "ssd_mobilenet_v1_coco.pbtxt"
weights = "frozen_inference_graph.pb"

#set minimum confidence value
thr = 0.5

if __name__ == "__main__":
    #load network
    net = cv2.dnn.readNetFromTensorflow(weights, prototxt)
    swapRB = True

    #define classnames and average heights for distance calculation
    classNames = { 0: 'background',
        1: 'person', 2: 'bicycle', 3: 'car', 4: 'motorcycle', 5: 'airplane', 6: 'bus',
        7: 'train', 8: 'truck', 9: 'boat', 10: 'traffic light', 11: 'fire hydrant',
        13: 'stop sign', 14: 'parking meter'}
    heights = {1: 65, 3:67}

    #initialize capture
    capture = cv2.VideoCapture(0)

    while capture.isOpened():
        # Capture frame-by-frame
        ret, frame = capture.read()
        blob = cv2.dnn.blobFromImage(frame, inScaleFactor, (inWidth, inHeight), (meanVal, meanVal, meanVal), swapRB)
        net.setInput(blob)
        detections = net.forward()

        cols = frame.shape[1]
        rows = frame.shape[0]

        for i in range(detections.shape[2]):
            confidence = detections[0, 0, i, 2]
            if confidence > thr:
                class_id = int(detections[0, 0, i, 1])
                if (not class_id in classNames):
                    continue

                #retrieve bounding box coordinates
                xLeftBottom = int(detections[0, 0, i, 3] * cols)
                yLeftBottom = int(detections[0, 0, i, 4] * rows)
                xRightTop   = int(detections[0, 0, i, 5] * cols)
                yRightTop   = int(detections[0, 0, i, 6] * rows)
                distance = 0
                height = 0

                #generate appropriate label with distance calculation
                if (not class_id in heights):
                    label = classNames[class_id]
                else:
                    height = yRightTop - yLeftBottom
                    distance = (heights[class_id]*focalLength/(12*(height)))
                    label = classNames[class_id] + ": " + str(distance) + " ft"
                labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)

                color = (0,255,0)

                #determine if instance of object is too close
                if ((distance < 5 and distance != 0) or (height >= rows - 50)):
                    print(classNames[class_id] + " is close" )
                    color = (0,0,255)

                #plot bounding box and label
                cv2.rectangle(frame, (xLeftBottom, yLeftBottom), (xRightTop, yRightTop),color)
                yLeftBottom = max(yLeftBottom, labelSize[1])
                cv2.putText(frame, label, (xLeftBottom, yLeftBottom),cv2.FONT_HERSHEY_SIMPLEX, 0.5, color)

        #show image
        cv2.imshow("detections", frame)
        if cv2.waitKey(1) >= 0:
            break
#release and destroy
capture.release()            
cv2.destroyAllWindows()