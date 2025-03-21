import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow import keras
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
model = keras.Sequential([
    keras.layers.Dense(16, activation='relu', input_shape=(X_train.shape[1],)),
    keras.layers.Dense(8, activation='relu'),
    keras.layers.Dense(1, activation='sigmoid')  # Binary classification
])

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(X_train, y_train, epochs=20, batch_size=8, validation_data=(X_test, y_test))

# Save the model for deployment
model.save("fire_detection_model.h5")