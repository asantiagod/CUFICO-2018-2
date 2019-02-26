from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import numpy as np


def gaussiana(x, amp, cen, wid):
    return amp * np.exp(-(x - cen) ** 2 / wid)


def twoGaussianWithRect(x, amp1, cen1, wid1, amp2, cen2, wid2, m, b):
    return gaussiana(x, amp1, cen1, wid1) + gaussiana(x, amp2, cen2, wid2) + m * x + b


def withGaussiana():
    x = np.load("x_spectra.npy")
    y = np.load("y_spectra.npy")

    init_vals = [120, 10, 5, 130, 30, 8, 1, 1]
    best_vals, covar = curve_fit(twoGaussianWithRect, x, y, p0=init_vals)
    print(best_vals)

    plt.plot(x, y, '.')
    plt.plot(x, twoGaussianWithRect(x, *best_vals))
    plt.show()


if __name__ == '__main__':
    withGaussiana()
