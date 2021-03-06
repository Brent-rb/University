revlist(L1, L2) :-
	L1 = [],
	L2 = [].

revlist(L1, L2) :-
	L1 = [X | T],
	conc(L3, .(X, []), L2),
	revlist(T, L3).

conc(L1, L2, L3) :-
	L1 = [],
	L3 = L2.

conc(L1, L2, L3) :-
	L1 = [H1|T1],
	L3 = [H1|L4],
	conc(T1, L2, L4).

member(A, L) :-
	L = [A|_].


member(A, L) :-
	L = [H|T],
	member(A, T).





multirember(X, L1, L2) :-
	L1 = [H1 | T1],
	X = H1,
	multirember(X, T1, L2).

multirember(X, L1, L2) :-
	L1 = [H1 | T1],
	not(X = H1),
	L2 = [H1 | L3],
	multirember(X, T1, L3).

multirember(X, L1, L2) :-
	L1 = [],
	L2 = [].


vervang(X, Y, L1, L2) :-
	L1 = [H1 | T1],
	X = H1,
	L2 = [Y | L3],
	vervang(X, Y, T1, L3).

vervang(X, Y, L1, L2) :-
	L1 = [H1 | T1],
	not(X = H1),
	L2 = [H1 | L3],
	vervang(X, Y, T1, L3).

vervang(X, Y, L1, L2) :-
	L1 = [],
	L2 = [].


verschillend(L1, L2) :-
	L1 = [],
	not(L1 = L2).

verschillend(L1, L2) :-
	L2 = [],
	not(L2 = L1).

verschillend([H1 | T1], [H2 | T2]) :-
	not(H1 = H2);
	verschillend(T1, T2).


islist(L1) :-
	L1 = [];
	L1 = [_ | _].


zonder_dubbels(L1, L2) :-
	L1 = [H1 | T1],
	zonder_dubbels(T1, L3),
	L2 = [H1 | L3],
	not(member(H1, L3)).

zonder_dubbels(L1, L2) :-
	L1 = [H1 | T1],
	zonder_dubbels(T1, L3),
	member(H1, L3),
	L2 = L3.

zonder_dubbels(L1, L2) :-
	L1 = [],
	L2 = [].

lengte(L1, X) :-
	L1 = [],
	X is 0.

lengte(L1, X) :-
	L1 = [H | T],
	lengte(T, Y),
	X is (Y + 1).



even_lengte(L1) :-
	lengte(L1, Y),
	X is Y mod 2,
	X = 0.

oneven_lengte(L1) :-
	not(even_lengte(L1)).

at(I, L, X) :-
	L = [],
	I is 0.

at(I, L, X) :-
	L = [H | T],
	H = X,
	I is 0.

at(I, L, X) :-
	L = [H | T],
	not(H = X),
	at(Y, T, X),
	I is Y + 1.

flatten(L1, L2) :-
	L1 = [],
	L2 = [].

flatten(L1, L2) :-
	L1 = [H1 | T1],
	islist(H1),
	flatten(H1, L3),
	flatten(T1, L4),
	conc(L3, L4, L2).

flatten(L1, L2) :-
	L1 = [H1 | T1],
	not(islist(H1)),
	flatten(T1, L3),
	L2 = [H1 | L3].


rle(L1, L2) :-
	rle_rec(L1, L3, X, C),
	L4 = [X, C | []],
	L5 = [L4 | []],
	conc(L5, L3, L2).

rle_rec(L1, L2, X, C) :-
	L1 = [H1 | T1],
	not(T1 = []),
	rle_rec(T1, L2, Y, K),
	H1 = K,
	C = K,
	X is Y + 1.

rle_rec(L1, L2, X, C) :-
	L1 = [H1 | T1],
	not(T1 = []),
	rle_rec(T1, L3, Y, K),
	not(H1 = K),
	Y = 1,
	L4 = [K | []],
	conc(L4, L3, L2),
	X is 1,
	C = H1.

rle_rec(L1, L2, X, C) :-
	L1 = [H1 | T1],
	not(T1 = []),
	rle_rec(T1, L3, Y, K),
	not(H1 = K),
	not(Y = 1),
	L4 = [Y, K | []],
	L5 = [L4 | []],
	conc(L5, L3, L2),
	X is 1,
	C = H1.

rle_rec(L1, L2, X, C) :-
	L1 = [H1 | T1],
	T1 = [],
	L2 = [],
	X is 1,
	C = H1.

rotate(L, C, L1) :-
	split(L, C, L2, L3),
	conc(L3, L2, L1).

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

