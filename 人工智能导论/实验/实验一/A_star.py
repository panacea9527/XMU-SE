from queue import PriorityQueue

def manhattan_distance(state, goal):
    distance = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                continue
            for x in range(3):
                for y in range(3):
                    if state[i][j] == goal[x][y]:
                        distance += abs(i - x) + abs(j - y)
    return distance

def get_neighbors(state):
    moves = []
    zero_position = [(index, row.index(0)) for index, row in enumerate(state) if 0 in row][0]
    i, j = zero_position
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right
    for di, dj in directions:
        if 0 <= i + di < 3 and 0 <= j + dj < 3:
            new_state = [list(row) for row in state]  # Deep copy
            new_state[i][j], new_state[i + di][j + dj] = new_state[i + di][j + dj], new_state[i][j]
            moves.append((new_state, (di, dj)))
    return moves

def reconstruct_path(came_from, current):
    total_path = [current]
    while current in came_from:
        current = came_from[current]
        total_path.insert(0, current)
    return total_path

def a_star(start, goal):
    open_set = PriorityQueue()
    open_set.put((0, start))
    came_from = {}
    g_score = {str(start): 0}
    f_score = {str(start): manhattan_distance(start, goal)}

    while not open_set.empty():
        _, current = open_set.get()

        if current == goal:
            return reconstruct_path(came_from, str(current))

        for neighbor, _ in get_neighbors(current):
            tentative_g_score = g_score[str(current)] + 1
            if str(neighbor) not in g_score or tentative_g_score < g_score[str(neighbor)]:
                came_from[str(neighbor)] = str(current)
                g_score[str(neighbor)] = tentative_g_score
                f_score[str(neighbor)] = tentative_g_score + manhattan_distance(neighbor, goal)
                if not any(neighbor == n[1] for n in open_set.queue):
                    open_set.put((f_score[str(neighbor)], neighbor))

    return False

start = [[2, 8, 3], [1, 6, 4], [7, 0, 5]]
goal = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]

path = a_star(start, goal)
if path:
    for step in path:
        print(step)
else:
    print("No solution found.")
