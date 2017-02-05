import matplotlib.pyplot as plt
import numpy as np
from fileoperations import ReadFile
import os

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 20

files = os.listdir("../data/")
M_100_files = []
for element in files:
    if element[:5] == "M_100":
        M_100_files.append("../data/" + element)

fig, ax = plt.subplots()
ax.set_xlabel(r"$t$[sweeps]")
ax.set_ylabel(r"m")
order = 0
for element in M_100_files:
    header, [t, E, M] = ReadFile(element, 1, " ")
    m = np.abs(M/(header['L']**2))
    m -= np.mean(m)
    m_hat = np.fft.fft(m)
    m_hat_abs = np.abs(m_hat)**2
    corr = np.fft.ifft(m_hat_abs)
    corr /= M.size
    corr = np.real(corr)
    ax.plot(t, M/header["L"]**2, label="T=%.1f" % header["T"],
            zorder=header["T"])

labels = ax.get_legend_handles_labels()
labels = list(map(list, zip(*labels)))
labels = sorted(labels, key=lambda x: float(x[1][2:5]))
labels = list(map(list, zip(*labels)))
lgd = ax.legend(labels[0], labels[1], bbox_to_anchor=(0., 1.02, 1., .102),
                loc=3, ncol=4, mode="expand", borderaxespad=0., fontsize="13")
ax.set_ylim(-1.2, 1.2)
fig.tight_layout()
fig.savefig("../plt/evolution.pdf", bbox_extra_artists=(lgd,), dpi=300,
            bbox_inches='tight')
