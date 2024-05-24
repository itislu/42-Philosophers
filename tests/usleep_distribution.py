import matplotlib.pyplot as plt
import numpy as np
import glob

# Load data from files
all_diffs = []
thread_files = glob.glob('thread_*.txt')

# Initialize dictionaries to store statistics per thread
mean_diffs = {}
median_diffs = {}
stddev_diffs = {}
min_diffs = {}
max_diffs = {}

for file in thread_files:
    thread_id = int(file.split('_')[1].split('.')[0])
    diffs = np.loadtxt(file)
    all_diffs.extend(diffs)

    # Calculate statistics per thread
    mean_diffs[thread_id] = np.mean(diffs)
    median_diffs[thread_id] = np.median(diffs)
    stddev_diffs[thread_id] = np.std(diffs)
    min_diffs[thread_id] = np.min(diffs)
    max_diffs[thread_id] = np.max(diffs)

# Convert all_diffs to numpy array for overall statistics
all_diffs = np.array(all_diffs)
overall_mean_diff = np.mean(all_diffs)
overall_median_diff = np.median(all_diffs)
overall_stddev_diff = np.std(all_diffs)
overall_min_diff = np.min(all_diffs)
overall_max_diff = np.max(all_diffs)

# Plot overall histogram
plt.figure(figsize=(10, 6))
plt.hist(all_diffs, bins=100, edgecolor='black', alpha=0.7)
plt.axvline(overall_mean_diff, color='r', linestyle='dashed', linewidth=1, label=f'Mean: {overall_mean_diff:.2f} us')
plt.axvline(overall_median_diff, color='g', linestyle='dashed', linewidth=1, label=f'Median: {overall_median_diff:.2f} us')
plt.axvline(overall_min_diff, color='b', linestyle='dashed', linewidth=1, label=f'Min: {overall_min_diff} us')
plt.axvline(overall_max_diff, color='y', linestyle='dashed', linewidth=1, label=f'Max: {overall_max_diff} us')
plt.title('Overall Histogram of Sleep Time Differences')
plt.xlabel('Difference (us)')
plt.ylabel('Frequency')
plt.legend()
plt.grid(True)
plt.savefig('overall_histogram.png')
plt.show()

# Plot overall box plot
plt.figure(figsize=(10, 6))
plt.boxplot(all_diffs, vert=False, patch_artist=True)
plt.title('Overall Box Plot of Sleep Time Differences')
plt.xlabel('Difference (us)')
plt.grid(True)
plt.savefig('overall_boxplot.png')
plt.show()

# Plot thread-specific statistics
thread_ids = sorted(mean_diffs.keys())

plt.figure(figsize=(12, 8))
plt.plot(thread_ids, [mean_diffs[tid] for tid in thread_ids], label='Mean', marker='o')
plt.plot(thread_ids, [median_diffs[tid] for tid in thread_ids], label='Median', marker='o')
plt.plot(thread_ids, [stddev_diffs[tid] for tid in thread_ids], label='Std Dev', marker='o')
plt.plot(thread_ids, [min_diffs[tid] for tid in thread_ids], label='Min', marker='o')
plt.plot(thread_ids, [max_diffs[tid] for tid in thread_ids], label='Max', marker='o')
plt.title('Statistics per Thread')
plt.xlabel('Thread ID')
plt.ylabel('Difference (us)')
plt.legend()
plt.grid(True)
plt.savefig('thread_statistics.png')
plt.show()

# Print the computed overall statistics
print(f"Overall Mean difference: {overall_mean_diff:.2f} us")
print(f"Overall Median difference: {overall_median_diff:.2f} us")
print(f"Overall Standard deviation: {overall_stddev_diff:.2f} us")
print(f"Overall Minimum difference: {overall_min_diff} us")
print(f"Overall Maximum difference: {overall_max_diff} us")
