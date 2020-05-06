from scipy.stats import pearsonr
import matplotlib.pyplot as plt


fig_2d = plt.figure()
ax = fig_2d.add_subplot(131)

x = [10, 50, 30, 70, 80, 60, 90, 40, 10, 20, 30, 50, 60]
y = [4, 5, 2, 6, 6, 8, 7, 2, 7, 3, 5, 1, 3]

ax.scatter(x, y, c='g', marker='o')

ax.set_xlabel('Zeitdauer X (in Minuten)')
ax.set_ylabel('Aggressivitätsmaß Y')

r_xy, _ = pearsonr(x, y)
print('Korrelationskoeffizienten: %.3f\n' % r_xy)

x_boys = [x[idx] for idx in range(7)]
y_boys = [y[idx] for idx in range(7)]

ax_boys = fig_2d.add_subplot(132)
ax_boys.scatter(x_boys, y_boys, c='b', marker='o')

ax_boys.set_xlabel('Zeitdauer X (in Minuten)')
ax_boys.set_ylabel('Aggressivitätsmaß Y')
ax_boys.set_title('Jungen')

r_xy_boys, _ = pearsonr(x_boys, y_boys)
print('Korrelationskoeffizienten Jungen: %.3f\n' % r_xy_boys)

x_girls = [x[idx] for idx in range(7, 13)]
y_girls = [y[idx] for idx in range(7, 13)]

ax_girls = fig_2d.add_subplot(133)
ax_girls.scatter(x_girls, y_girls, c='r', marker='o')

ax_girls.set_xlabel('Zeitdauer X (in Minuten)')
ax_girls.set_ylabel('Aggressivitätsmaß Y')
ax_girls.set_title('Mädchen')

r_xy_girls, _ = pearsonr(x_girls, y_girls)
print('Korrelationskoeffizienten Mädchen: %.3f\n' % r_xy_girls)

plt.show()
