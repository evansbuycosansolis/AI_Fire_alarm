converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save the model
with open("fire_detection_model.tflite", "wb") as f:
    f.write(tflite_model)