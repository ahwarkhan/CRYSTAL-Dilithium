import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Load CSV data
data = pd.read_csv('results.csv')

# Extract data
groups = data['VERSION']
keygen_times = data['KEYGEN(ms)']
sign_times = data['SIGN(ms)']
verify_times = data['VERIFY(ms)']

# Bar chart settings
bar_width = 0.25
index = np.arange(len(groups))

plt.figure(figsize=(10, 6))

# Plot bars for KeyGen, Sign, Verify
plt.bar(index - bar_width, keygen_times, width=bar_width, label='KeyGen', color='skyblue')
plt.bar(index, sign_times, width=bar_width, label='Sign', color='lightgreen')
plt.bar(index + bar_width, verify_times, width=bar_width, label='Verify', color='salmon')

# Labels and formatting
plt.xlabel('Schemes', fontsize=12)
plt.ylabel('Time (ms)', fontsize=12)
plt.title('Performance Comparison: Optimized Dilithium II vs General Schemes', fontsize=14)
plt.xticks(index, groups.tolist(), rotation=15)
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Save and display
plt.tight_layout()
plt.savefig('pqc_comparison.png')
plt.show()

print("Grouped bar chart saved as pqc_comparison.png")
