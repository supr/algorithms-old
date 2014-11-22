/* 
Question:
given a vector of points:
# points = [(timestamp, value), ...]

# assume all timestamp % 5 == 0
# [(1000, 4.5), (1005, 10), (1020, 60), ... ]

interpolate the missing points

e.g.:
# [(1000, 0), (1005, 1), (1015, 3)] -> [(1000, 0), (1005, 1), (1010, 2), (1015, 3)]
*/