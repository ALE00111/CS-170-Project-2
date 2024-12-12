import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Loading CSV file
data = pd.read_csv("forwardselection.csv", header=None, delimiter= ' ')

# Checking the content of the CSV 
print("Data loaded:")
print(data.head())


classifications = data.iloc[0, :].values  #classification array

# Extracting the two features
feature_x = data.iloc[1, :].values  
#feature_y = data.iloc[3, :].values 

#color the points based on classification
colors = ['blue' if cls == 1 else 'red' for cls in classifications]

# Checking the lengths of the features
print(f"Length of feature_x: {len(feature_x)}")
#print(f"Length of feature_y: {len(feature_y)}")
#print(type(feature_y))

#Check the extracted features
print(f"Feature X: {feature_x}")
#print(f"Feature Y: {feature_y}")

#Creating the plot
#plt.scatter(feature_x, feature_y, c=colors, edgecolor='black')
plt.scatter(feature_x, [0] * len(feature_x), c=colors, edgecolor='black')

# Add labels and title
plt.title('Titanic Dataset Plot')
plt.xlabel('Feature 2')
#plt.ylabel('Feature 3')

# Set axis limits to ensure data points are between 0 and 1
plt.xlim(0, 1)
#plt.ylim(0, 1)

# Display the plot
plt.show()
