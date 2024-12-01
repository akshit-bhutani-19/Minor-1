# Import necessary libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, r2_score

# Load your dataset
# Replace 'training_data.csv' and 'testing_data.csv' with the paths to your data files
train_data = pd.read_csv('training_data.csv')
test_data = pd.read_csv('testing_data.csv')

# Separate features and target variable for training data
X_train = train_data.drop(columns=['Tiger_Population_Density'])  # Features
y_train = train_data['Tiger_Population_Density']  # Target variable

# Separate features and target variable for testing data
X_test = test_data.drop(columns=['Tiger_Population_Density'])  # Features
y_test = test_data['Tiger_Population_Density']  # Target variable

# Create a Random Forest Regressor
rf_regressor = RandomForestRegressor(n_estimators=100, random_state=42)

# Train the regressor
rf_regressor.fit(X_train, y_train)

# Make predictions on the test set
y_pred = rf_regressor.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

# Print the results
print(f"Mean Squared Error: {mse:.6f}")
print(f"R-squared Score: {r2:.6f}")

# Optionally, save predictions and true values to a CSV file for analysis
results = pd.DataFrame({'True Values': y_test, 'Predictions': y_pred})
results.to_csv('predictions_vs_true.csv', index=False)
print("Predictions saved to 'predictions_vs_true.csv'.")
