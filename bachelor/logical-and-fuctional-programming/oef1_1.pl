circle(point(1, 2), 5).
circle(point(20, 30), 1).
circle(point(20, 6), 5).
circle(point(9, 5), 6).?- circle(X, Y), R =< 5?- circle(_, R).?- circle(point(20, Y), R).?- circle(P, R), P = point(20, _).