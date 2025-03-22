import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras import layers, callbacks
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# Load dataset (sensor readings from Fire Alarm Device)
data = pd.read_csv("fire_sensor_data.csv")  # Your collected data

# Features: flame sensor, gas levels, temperature
X = data[['flame', 'gas_level', 'temperature']]
y = data['fire_alert']  # 1 = Fire, 0 = No Fire

# Split data into training & testing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Scale features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Define an AI Model
model = tf.keras.Sequential([
    layers.Dense(32, activation='relu', input_shape=(X_train.shape[1],)),
    layers.Dense(16, activation='relu'),
    layers.Dense(8, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Early stopping and model checkpoint
early_stopping = callbacks.EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)
model_checkpoint = callbacks.ModelCheckpoint("best_fire_detection_model.h5", save_best_only=True)

# Train the model
model.fit(X_train, y_train, epochs=50, batch_size=8, validation_data=(X_test, y_test), 
          callbacks=[early_stopping, model_checkpoint])

# Save the final model
model.save("final_fire_detection_model.h5")
