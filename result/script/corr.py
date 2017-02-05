import matplotlib.pyplot as plt
import numpy as np
from fileoperations import ReadFile, SplitData

plt.rcParams["figure.figsize"] = [8, 10]
plt.rcParams["font.size"] = 20

files = [20, 60, 100]
for i in files:
    header, data = ReadFile("../data/corr_%d.dat" % i, 1, " ")
    data = SplitData(0, data)
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.set_xlabel(r"$t$[sweeps]")
    ax1.set_ylabel(r"Corr(t)")
    ax2.set_xlabel(r"$t$[sweeps]")
    ax2.set_ylabel(r"Corr(t)")
    for element in data:
        [t, T, M] = element
        T = T[0]
        m = M/(header['L']**2)
        m -= np.mean(m)
        m = np.abs(m)
        m_hat = np.fft.fft(m)
        m_hat_abs = np.abs(m_hat)**2
        corr = np.fft.ifft(m_hat_abs)
        corr /= M.size
        corr = np.real(corr)
        ax1.semilogy(t[:int(M.size/2)], corr[:int(M.size/2)], label="T=%.1f"
                     % T)
        if T == 2.3 or T == 2.2:
            next(ax2._get_lines.prop_cycler)['color']
            continue
        ax2.semilogy(t[:int(M.size/2)], corr[:int(M.size/2)], label="T=%.1f"
                     % T)
    lgd = ax1.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=5,
                     mode="expand", borderaxespad=0., fontsize="13")
    ax2.set_xlim(0., 50.)
    fig.tight_layout()
    fig.savefig("../plt/corr_%d.pdf" % i, bbox_extra_artists=(lgd,), dpi=300,
                bbox_inches='tight')

"""
header, data = ReadFile("../data/corr_60.dat", 1, " ")
data = SplitData(0, data)
fig, ax = plt.subplots()
ax.set_xlabel(r"$t$[sweeps]")
ax.set_ylabel(r"Corr(t)")
for element in data:
    [t, T, M] = element
    T = T[0]
    m = M/(header['L']**2)
    m -= np.mean(m)
    m = np.abs(m)
    m_hat = np.fft.fft(m)
    m_hat_abs = np.abs(m_hat)**2
    corr = np.fft.ifft(m_hat_abs)
    corr /= M.size
    corr = np.real(corr)
    ax.loglog(t[:int(M.size/2)], corr[:int(M.size/2)], label="T=%.1f" % T)
ax.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=5, mode="expand",
          borderaxespad=0., fontsize="13")
fig.tight_layout()
plt.show()
"""
