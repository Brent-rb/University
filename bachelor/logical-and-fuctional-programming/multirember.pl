multiremberStar(X, [], []):- !.

multiremberStar(X, [[H2 | T2] | T], List) :-
	multiremberStar(X, [H2 | T2], SubList),
	multiremberStar(X, T, CarList),
	List = [SubList | CarList], !.

multiremberStar(X, [X | T], List) :- 
	multiremberStar(X, T, List), !.

multiremberStar(X, [H | T], List) :- 
	multiremberStar(X, T, CarList),
	List = [H | CarList], !.

