fibbonacci(X, F) :-
	X = 1,
	F = 1.

fibbonacci(X, F) :-
	X = 0,
	F = 1.

fibbonacci(X, F) :-
	Y is X - 1,
	fibbonacci(Y, A),
	Z is Y - 1,
	fibbonacci(Z, B),
	F is A + B.

macht(X, N, V) :-
	N = 0,
	V is 1.

macht(X, N, V) :-
	N = 1,
	V is X.

macht(X, N, V) :-
	N >= 2,
	Y is X * X,
	A is N - 2,
	macht(X, A, Z),
	V is Y * Z.

priem(X) :-
	not(checkDiv(X, X)).

checkDiv(X, Y) :-
	Y < X,
	Y > 1,
	Z is X mod Y,
	Z = 0.

checkDiv(X, Y) :-
	Y > 2,
	Z is Y - 1,
	checkDiv(X, Z).

trap(N, A) :-
	N = 0,
	A is 1.

trap(N, A) :-
	N = 1,
	A is 1.

trap(N, A) :-
	N < 0,
	A is 0.

trap(N, A) :-
	B is N - 1,
	C is N - 2,
	trap(B, X),
	trap(C, Y),
	A is X + Y.


bsum(X, Y, Z) :-
	bsum_inner(X, Y, 0, Z).

bsum_inner(X, Y, IC, Z) :- 
	X = [H1 | T1],
	Y = [H2 | T2],
	bsum_sum(H1, H2, IC, OC, H3),
	bsum_inner(T1, T2, OC, A),
	Z = [H3 | A].

bsum_inner(X, Y, IC, Z) :-
	X = [],
	Y = [],
	IC = 1,
	Z = [1].

bsum_inner(X, Y, IC, Z) :-
	X = [],
	Y = [],
	IC = 0,
	Z = [].

bsum_sum(B1, B2, IC, OC, R) :-
	xor(B1, B2, T1),
	xor(T1, IC, R),
	get_oc(B1, B2, IC, OC).

xor(B1, B2, B3) :-
	B1 = 1,
	B2 = 1,
	B3 = 0.

xor(B1, B2, B3) :-
	not(B1 = B2),
	B1 = 1;
	B2 = 1,
	B3 = 1.

xor(B1, B2, B3) :-
	B1 = 0,
	B2 = 0, 
	B3 = 0.

get_oc(B1, B2, IC, OC) :-
	B1 = 1,
	B2 = 1,
	OC is 1.

get_oc(B1, B2, IC, OC) :-
	not(B1 = B2),
	B1 = 1,
	IC = 1,
	OC is 1.

get_oc(B1, B2, IC, OC) :-
	not(B1 = B2),
	B2 = 1,
	IC = 1,
	OC is 1.

get_oc(B1, B2, IC, OC) :-
	not(B1 = B2),
	B1 = 1,
	IC = 0,
	OC is 0.

get_oc(B1, B2, IC, OC) :-
	not(B1 = B2),
	B2 = 1,
	IC = 0,
	OC is 0.

get_oc(B1, B2, IC, OC) :-
	B1 = 0,
	B2 = 0,
	OC is 0.

no_doubles(SL, CSL) :-
	SL = [H | T],
	no_doubles_inner(T, H, L),
	CSL = [H | L].

no_doubles_inner(L, C, CSL) :-
	L = [],
	CSL = [].

no_doubles_inner(L, C, CSL) :-
	L = [H | T],
	H = C,
	no_doubles_inner(T, C, CSL).

no_doubles_inner(L, C, CSL) :-
	L = [H | T],
	not(H = C),
	no_doubles_inner(T, H, L1),
	CSL = [H | L1].

maketree(L, T) :-
	mergeSort(L, SL),
	no_doubles(SL, CSL),
	maketree_inner(CSL, T).

maketree_inner(L, T) :-
	L = [],
	T = nil.

maketree_inner(L, T) :-
	lengte(L, A),
	getIndex(A, I),
	divList(L, I, LL, M, RR),
	maketree_inner(LL, TL),
	maketree_inner(RR, TR),
	T = t(TL, M, TR).

lengte(L1, X) :-
	L1 = [],
	X is 0.

lengte(L1, X) :-
	L1 = [H | T],
	lengte(T, Y),
	X is (Y + 1).

divList(L, I, L1, M, L2) :-
	I = -1,
	L1 = [],
	L = [H | T],
	M = H,
	L2 = [].

divList(L, I, L1, M, L2) :-
	divList_inner(L, I, L1, M, L2, 1).

divList_inner(L, I, L1, M, L2, CI) :-
	L = [],
	L2 = [].

divList_inner(L, I, L1, M, L2, CI) :-
	CI = I,
	L = [H | T],
	M = H,
	L1 = [],
	NI is CI + 1,
	divList_inner(T, I, _, _, L2, NI).

divList_inner(L, I, L1, M, L2, CI) :-
	CI < I,
	L = [H | T],
	NI is CI + 1,
	divList_inner(T, I, L3, M, L2, NI),
	L1 = [H | L3].

divList_inner(L, I, L1, M, L2, CI) :-
	CI > I,
	L = [H | T],
	NI is CI + 1,
	divList_inner(T, I, _, _, L3, NI),
	L2 = [H | L3].

getIndex(L, I) :-
	L = 1, 
	I = -1.

getIndex(L, I) :-
	L > 2,
	oneven(L),
	X is L + 1,
	I is X / 2.

getIndex(L, I) :-
	L >= 2,
	even(L),
	I is L / 2.


even(L) :-
	not(oneven(L)).

oneven(L) :-
	Y is L mod 2,
	Y = 1.

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
	lengte(L1, 1),
	L2 = L1.

mergeSort(L1, L2) :-
	mergeSplit(L1, LL, RR),
	mergeSort(LL, SL),
	mergeSort(RR, SR),
	mergeMerge(SL, SR, L2).





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
	H1 < H2,
	mergeMerge(T1, L2, L4),
	L3 = [H1 | L4].

mergeMerge(L1, L2, L3) :-
	L1 = [H1 | T1],
	L2 = [H2 | T2],
	not(H1 < H2),
	mergeMerge(L1, T2, L4),
	L3 = [H2 | L4].

intree(W, T) :-
	T = t(L, M, R),
	W = M.

intree(W, T) :-
	T = t(L, M, R),
	W > M,
	intree(W, R).

intree(W, T) :-
	T = t(L, M, R),
	W < M,
	intree(W, L).


height(T, N) :-
	T = nil,
	N is 0.

height(T, N) :-
	T = t(L, M, R),
	height(L, LN),
	height(R, RN),
	LN > RN,
	N is LN + 1.

height(T, N) :-
	T = t(L, M, R),
	height(L, LN),
	height(R, RN),
	LN =< RN,
	N is RN + 1.

layout_tree(T1, T2) :-
	height(T1, H),
	RH is H + 1,
	layout_tree_inner(T1, T2, 0, RH, _).

layout_tree_inner(T1, T2, I, H, C) :-
	T1 = nil,
	T2 = nil,
	C is I.

layout_tree_inner(T1, T2, I, H, C) :-
	T1 = t(TL, MM, TR),
	layout_tree_inner(TL, TL2, I, H, CL),
	I2 is CL + 1,
	layout_tree_inner(TR, TR2, I2, H, RL),
	C = RL,
	height(T1, HH),
	HRL is H - HH,
	T2 = t(TL2, MM, TR2, I2, HRL).

hanoi(N) :-
	hanoi_inner(N, 'bronstok', 'doelstok', 'hulpstok').

hanoi_inner(COUNT, ORIGIN, TARGET, HELP) :-
	COUNT = 1,
	write('Verplaats 1 schijf van '),
	write(ORIGIN),
	write(' naar '),
	write(TARGET),
	write('.'),
	nl.

hanoi_inner(COUNT, ORIGIN, TARGET, HELP) :-
	COUNT > 1,
	COUNT2 is COUNT - 1,
	hanoi_inner(COUNT2, ORIGIN, HELP, TARGET),
	hanoi_inner(1, ORIGIN, TARGET, HELP),
	hanoi_inner(COUNT2, HELP, TARGET, ORIGIN).
