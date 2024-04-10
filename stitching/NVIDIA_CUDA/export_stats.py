import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("./FPS_CUDA_FINAL.csv")
fig, ax = plt.subplots(figsize=(20, 16))
ax.tick_params(axis='both', labelsize=60)
ax.plot(data["Frame"], data["SMA"], marker='o', linestyle='-', label='SMA')
ax.plot(data["Frame"], data["WMA"], marker='o', linestyle='-', label='WMA')
ax.grid(linewidth=4)
ax.set_xlabel("Frames", fontsize=70)
ax.set_ylabel("FPS", fontsize=70)
ax.legend(title='Result with window size 1000', fontsize=45, title_fontsize=60, loc='lower right')
plt.savefig("../CUDA_FPS_trend.png", bbox_inches='tight')