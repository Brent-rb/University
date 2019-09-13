wordt_vastbenoemd(X) :-
    publiceert(X),
    heeft_projectonderzoek(X),
    geeft_goed_les(X).

publiceert(X) :-
    doet_onderzoek(X),
    rapporteert_onderzoek(X).

heeft_projectonderzoek(X) :-
    doet_projectvoorstellen(X),
    krijgt_projecten(X).

geeft_goed_les(X) :-
    bereidt_lessen_voor(X),
    goede_lesgever(X),
    krijgt_goede_evaluaties(X).
