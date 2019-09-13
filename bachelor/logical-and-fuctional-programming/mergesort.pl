split(L1, X, L2, L3) :-
	X = 0,
	L3 = L1,
	L2 = [].

split(L1, X, L2, L3) :-
	L1 = [H | T],
	Y is X - 1,
	split(T, Y, L4, L5),
	L2 = [H | L4],
	L3 = L5.

mergeSort(L1, L2) :-
	lengte(L1, X),
	X > 1,
	mergeSplit(L1, L3, L4),
	mergeSort(L3, L5),
	mergeSort(L4, L6),
	mergeMerge(L5, L6, L2).

mergeSort(L1, L2) :-
	lengte(L1, 1),
	L2 = L1.



mergeSplit(L1, L2, L3) :-
	lengte(L1, X),
	Y is X mod 2,
	Y = 0,
	Z is X / 2,
	split(L1, Z, L2, L3).

mergeSplit(L1, L2, L3) :-
	lengte(L1, X),
	Y is X mod 2,
	Y = 1,
	Z is X - 1,
	A is Z / 2,
	split(L1, A, L2, L3).


mergeMerge(L1, L2, L3) :-
	L1 = [],
	L3 = L2.

mergeMerge(L1, L2, L3) :-
	L2 = [],
	L3 = L1.

mergeMerge(L1, L2, L3) :-
	L1 = [H1 | T1],
	L2 = [H2 | T2],
	lengte(H1, X),
	lengte(H2, Y),
	X < Y,
	mergeMerge(T1, L2, L4),
	L3 = [H1 | L4].

mergeMerge(L1, L2, L3) :-
	L1 = [H1 | T1],
	L2 = [H2 | T2],
	lengte(H1, X),
	lengte(H2, Y),
	not(X < Y),
	mergeMerge(L1, T2, L4),
	L3 = [H2 | L4].

