import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load the CSV file
data = pd.read_csv("forwardselection.csv", header=None, delimiter= ' ')

# Check the content of the CSV to understand its structure
print("Data loaded:")
print(data.head())  # This will show the first few rows

# If the CSV file has 2 rows, we need to transpose the data
# Transpose the data so that each row represents a feature (if not already correct)
#data = data.transpose()

# Check the transposed data
#print("Transposed Data:")
#print(data.head())

# Now extract the two features (assuming each row represents a feature)
feature_x = data.iloc[0, :].values  # First row for x-axis 
feature_y = data.iloc[1, :].values # Second row for y-axis

# Check the lengths of the features
print(f"Length of feature_x: {len(feature_x)}")
print(f"Length of feature_y: {len(feature_y)}")
print(type(feature_y))

# Check the extracted features
print(f"Feature X: {feature_x}")
print(f"Feature Y: {feature_y}")

# Create the plot
#plt.scatter(feature_x, feature_y, c=)
plt.scatter(feature_x, feature_y, c='blue', edgecolor='black')

# Plot feature_y with another color
plt.scatter(feature_y, feature_x, c='red', edgecolor='black')

# Add labels and title
plt.title('Small Dataset Plot')
plt.xlabel('Feature 4')
plt.ylabel('Feature 5')

# Set axis limits to ensure data points are between 0 and 1
plt.xlim(0, 1)
plt.ylim(0, 1)

# Display the plot
plt.show()
