import matplotlib.pyplot as plt
from fileoperations import ReadFile, SplitData
import itertools
import numpy as np

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 20

header, data = ReadFile("../data/T_crit.dat", 0, " ")

font = {'size': 20}
marker = itertools.cycle(('x', '3', '.', '+', '*'))
data = SplitData(0, data)
fig, ax = plt.subplots()
ax.set_xlabel(r"$T$")
ax.set_ylabel(r"$\langle\vert m \vert\rangle$")
ax.vlines(2.27, 0, 1.1)
ax.text(2.3, 1., r"$T_{crit}$", fontdict=font)
for element in data:
    L = element[0][0]
    m = np.abs(element[2])/L**2
    ax.errorbar(element[1], element[2], yerr=element[3], fmt=next(marker),
                label="L=%d" % L)
ax.set_xlim(0.5, 4.)
ax.set_ylim(0., 1.1)
ax.legend(loc="best", fontsize=15)
fig.tight_layout()
fig.savefig("../plt/mean.pdf", dpi=300)
