import matplotlib.pyplot as plt
from fileoperations import ReadFile, SplitData
import itertools

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 20

header, data = ReadFile("../data/suscep.dat", 0, " ")

font = {'size': 20}
marker = itertools.cycle(('x', '3', '.', '+', '*'))
data = SplitData(0, data)
fig, ax = plt.subplots()
ax.set_xlabel(r"$T$")
ax.set_ylabel(r"$\chi$")
ax.text(1.95, 127, r"$T_{crit}$", fontdict=font)
ax.vlines(2.27, 0, 140)
for element in data:
    L = element[0][0]
    ax.errorbar(element[1], element[2], yerr=element[3], fmt=next(marker),
                label="L=%d" % L)
ax.legend(loc="best", fontsize=15)
fig.tight_layout()
fig.savefig("../plt/suscep.pdf", dpi=300)
