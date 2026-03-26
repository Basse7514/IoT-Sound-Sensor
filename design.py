def select_points(intervals):
      intervals.sort( key=lambda x: x[1])
      points = []
      current_points = None
      for start, end in intervals:
           if current_points is None or start > current_points:
              current_points = end
              points.append(current_points)
      return points
intervals = [
       [1,3],
       [2,5],
       [4,6],
       [6,8],
       [7,9],
]
result = select_points(intervals)
print("points =", result)