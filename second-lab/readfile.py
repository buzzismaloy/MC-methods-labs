import matplotlib.pyplot as plt


def read_file(filename):
    trajectories = []
    with open(filename, 'r') as file:
        trajectory = []
        for line in file:
            line = line.strip()
            if line:
                x, y, z = map(int, line.split(','))
                trajectory.append((x, y, z))
            else:
                if trajectory:
                    trajectories.append(trajectory)
                    trajectory = []
    if trajectory:
        trajectories.append(trajectory)

    return trajectories


trajectories_1000 = read_file("/home/buzzismaloy/University_shit/6th-term/monte-karlo/second-lab/trajectories_1000.txt")
fig = plt.figure(figsize=(12, 6))
ax = fig.add_subplot(121, projection='3d')
for traj in trajectories_1000:
    x, y, z = zip(*traj)
    ax.plot(x, y, z, marker='o')
ax.set_title('Random Walks (1000 Steps)')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

trajectories_10000 = read_file(
    "/home/buzzismaloy/University_shit/6th-term/monte-karlo/second-lab/trajectories_10000.txt")
ax = fig.add_subplot(122, projection='3d')
for traj in trajectories_10000:
    x, y, z = zip(*traj)
    ax.plot(x, y, z, marker='o')
ax.set_title('Random Walks (10000 Steps)')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

#plt.savefig('trajectory_plot.png')  # Сохранить график в файл
#plt.close()  # Закрыть график
plt.tight_layout()
plt.show()
