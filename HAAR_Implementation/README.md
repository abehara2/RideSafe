The approach with HAAR classifiers is not recommended as using the function ```detectMultiScale``` is not useful or reliable when you are not 
training on your own data set. You don't know training data truth sizes and if you generate too many anchor boxes with too wide of a variety of sizes, this decreases inference time greatly. Decreasing the scale of bounding boxes from 1.3 to 1.0 decreases inference by around 0.5 seconds per frame.
In place of using HAAR I would recommend to use a Single Shot Detector or Faster R-CNN model. The working solution for this project uses an SSD which has a faster inference time
than the Faster R-CNN model and is far more useful in a project where time is of the essence.
