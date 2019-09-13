member(A, L) :-
	L = [H|T],
	member(A, T).

member(A, L) :-
	L = [A|_].

member2(A, L) :-
	L = [A | _].

member2(A, L) :-
	L = [H | T],
	member2(A, T).

derp(banaan).
derp(appel).
geenappel(banaan).
geenappel(peer).
derp(peer).


test(X) :-
	not(geenappel(X)),
	derp(X).
