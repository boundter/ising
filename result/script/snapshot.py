import matplotlib.pyplot as plt
from fileoperations import ReadFile
import matplotlib.cm as cm

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 20

files = [1., 2., 2.2, 2.3, 2.5, 3., 4.]
for i in files:
    header, data = ReadFile("../data/snap_100_%.3f.dat" % i, 1, " ")
    fig, ax = plt.subplots()
    ax.set_xlabel(r"$x$")
    ax.set_ylabel(r"$y$")
    cax = ax.imshow(data, extent=(0, 100, 0, 100), interpolation='none',
                    cmap=cm.Greys)
    fig.tight_layout()
    fig.savefig("../plt/snapshot_%.3f.pdf" % i, dpi=300)
