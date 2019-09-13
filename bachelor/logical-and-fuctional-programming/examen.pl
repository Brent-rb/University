notMember(X, []).

notMember(X, [H | T]) :-
	not(X = H),
	notMember(X, T).

checkDifferent([H1 | T1], [H2 | T2]) :-
	notMember(H1, [H2 | T2]);
	checkDifferent(T1, [H2 | T2]).

path(X, Y, [edge(X, Y)]) :-
	edge(X, Y), !.

path(X, Y, L) :-
	edge(X, Z),
	path(Z, Y, L2),
	L = [edge(X, Z) | L2].

twoPaths(X, Y) :-
	path(X, Y, L1),
	path(X, Y, L2),
	checkDifferent(L1, L2).

conc([], T, T).
conc([X|T], T2, [X|T3]) :- 
	conc(T, T2, T3).

preorder(nil, []).

preorder(t(L, X, R), Out) :-
	preorder(L, O1),
	preorder(R, O2),
	conc(O1, O2, L2),
	Out = [X | L2].


search(X, [X | T], T) :- !.
search(X, [H | T], L) :-
	search(X, T, L).

before(X, Y, L) :-
	search(X, L, L1),
	search(Y, L1, _).	