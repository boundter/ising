import matplotlib.pyplot as plt
from fileoperations import ReadFile, SplitData
import itertools

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 20

T_crit = 2.27
a = 1.71
b = 1

marker = itertools.cycle(('x', '3', '.', '+', '*'))
header, data = ReadFile("../data/finite.dat", 0, " ")
data = SplitData(0, data)
fig, ax = plt.subplots()
ax.set_ylabel(r"$\chi L^{-a/b}$")
ax.set_xlabel(r"$L^{1/b} t$")
for element in data:
    L = element[0][0]
    t = (element[1] - T_crit)/T_crit
    ax.errorbar(L**(1/b)*t, element[2]*L**(-a/b), yerr=element[3]*L**(-a/b),
                fmt=next(marker), label="L=%d" % L)
ax.legend(loc="best", fontsize=15)
ax.set_xlim(-10., 10.)
fig.tight_layout()
fig.savefig("../plt/finite.pdf", dpi=300)
