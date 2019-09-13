operator(*).
operator(+).
operator(-).
operator(/).

maak_vgl([HG|TG], LT, RT) :-
	maak_vgl_inner(TG, LT, HG),
	X is LT,
	X = HG,
	RT is HG.

maak_vgl(G, LT, RT) :-
	maak_vgl_inner2(G, LT, RT),
	X is LT,
	X = RT.

maak_vgl_inner2([HG | TG], LT, RT) :-
	TG = [HTG | []],
	RT = HTG,
	LT = HG.

maak_vgl_inner2([HG|TG], LT, RT) :-
	maak_vgl_inner2(TG, LT2, RT),
	LT = HG + LT2.

maak_vgl_inner2([HG|TG], LT, RT) :-
	maak_vgl_inner2(TG, LT2, RT),
	LT = HG - LT2.
	
maak_vgl_inner2([HG|TG], LT, RT) :-
	maak_vgl_inner2(TG, LT2, RT),
	LT = HG * LT2.
	
maak_vgl_inner2([HG|TG], LT, RT) :-
	maak_vgl_inner2(TG, LT2, RT),
	LT = HG / LT2.

maak_vgl_inner([HG | []], HG, RT).

maak_vgl_inner([HG|TG], LT, RT) :-
	maak_vgl_inner(TG, LT2, RT),
	LT = HG + LT2.

maak_vgl_inner([HG|TG], LT, RT) :-
	maak_vgl_inner(TG, LT2, RT),
	LT = HG - LT2.
	
maak_vgl_inner([HG|TG], LT, RT) :-
	maak_vgl_inner(TG, LT2, RT),
	LT = HG * LT2.
	
maak_vgl_inner([HG|TG], LT, RT) :-
	maak_vgl_inner(TG, LT2, RT),
	LT = HG / LT2.
	
test([H | []], 5).
	