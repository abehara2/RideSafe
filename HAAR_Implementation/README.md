The approach with HAAR classifiers is not recommended and is incomplete as using the function ```detectMultiScale``` is not useful or reliable when you are not 
training on your own data set. You don't know training data sizes and if you generate too many anchor boxes with too wide of a variety of sizes, this decreases inference time greatly.
In place of using HAAR I would recommend to use a Single Shot Detector or Faster R-CNN model. The working solution for this project uses an SSD which has a faster inference time
than the Faster R-CNN model.
