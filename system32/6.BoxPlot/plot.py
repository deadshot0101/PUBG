import numpy as np
import matplotlib.pyplot as plt

# Data for age
data = [13, 15, 16, 16, 19, 20, 20, 21, 22, 22, 25, 25, 25, 25, 30, 33, 33, 35, 35, 
        35, 35, 36, 40, 45, 46, 52, 70]

# (a) Mean and Median
mean_age = np.mean(data)
median_age = np.median(data)

# (b) Mode
mode_age = max(set(data), key=data.count)

# (c) Midrange (average of min and max)
midrange = (min(data) + max(data)) / 2

# (d) First (Q1) and Third (Q3) Quartiles
q1 = np.percentile(data, 25)
q3 = np.percentile(data, 75)

# (e) Five-number summary (min, Q1, median, Q3, max)
five_number_summary = [min(data), q1, median_age, q3, max(data)]

# (f) Boxplot
plt.figure(figsize=(8, 6))
plt.boxplot(data, vert=False)
plt.title('Boxplot of Age Data')
plt.xlabel('Age')
plt.show()

(mean_age, median_age, mode_age, midrange, q1, q3, five_number_summary)


# Generate the boxplot with annotations

plt.figure(figsize=(10, 6))
plt.boxplot(data, vert=False)

# Title and labels
plt.title('Boxplot of Age Data with Statistical Values')
plt.xlabel('Age')

# Annotating the five-number summary
plt.text(min(data) - 3, 1, f"Min: {min(data)}", verticalalignment='center', color='blue')
plt.text(q1 - 3, 1, f"Q1: {q1:.2f}", verticalalignment='center', color='blue')
plt.text(median_age - 3, 1, f"Median: {median_age}", verticalalignment='center', color='blue')
plt.text(q3 - 3, 1, f"Q3: {q3:.2f}", verticalalignment='center', color='blue')
plt.text(max(data) + 1, 1, f"Max: {max(data)}", verticalalignment='center', color='blue')

# Showing the plot
plt.show()

# Values to be displayed
mean_age, median_age, mode_age, midrange, q1, q3, five_number_summary
