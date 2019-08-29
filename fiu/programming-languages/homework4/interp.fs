#load "parser.fsx"
open Parser.Parse

System.Environment.set_CurrentDirectory __SOURCE_DIRECTORY__

let rec subst e s t =
	match e with
	| ID x -> if(x = s) then t else (ID x)
	| NUM n -> NUM n
	| BOOL b -> BOOL b
	| SUCC -> SUCC
	| PRED -> PRED
	| ISZERO -> ISZERO
	| IF (x, y, z) -> IF (subst x s t, subst y s t, subst z s t)
	| APP (x, y) -> APP (subst x s t, subst y s t)
	| FUN (x, y) -> if (x = s) then FUN (x, y) else FUN (x, (subst y s t))
	| REC (x, y) -> if (x = s) then REC (x, y) else REC (x, (subst y s t))
	| _ -> ERROR "ERROR: failed substitution"

let rec interp = function
	| ID x -> ID x
	| NUM n -> NUM n
	| BOOL t -> BOOL t
	| SUCC -> SUCC
	| PRED -> PRED
	| ISZERO -> ISZERO
	| IF (t1, t2, t3) ->
		match (t1, t2, t3) with
		| (ERROR e, _, _) -> ERROR e
		| (_, ERROR e, _) -> ERROR e
		| (_, _, ERROR e) -> ERROR e
		| (x, y, z) -> if(interp x = BOOL true) then (interp y) elif (interp x = BOOL false) then (interp z) else (ERROR (sprintf "ERROR: input '%A' for IF must be boolean" x))
	| APP (e1, e2) ->
		match (interp e1, interp e2) with
		| (ERROR e, _) -> ERROR e
		| (_, ERROR e) -> ERROR e
		| (SUCC, NUM n) -> NUM (n + 1)
		| (SUCC, v) -> ERROR (sprintf "ERROR: input '%A' for SUCC must be an integer" v)
		| (PRED, NUM 0) -> NUM 0
		| (PRED, NUM n) -> NUM (n - 1)
		| (PRED, v) -> ERROR (sprintf "ERROR: input '%A' for PRED must be an integer" v)
		| (ISZERO, NUM 0) -> BOOL true
		| (ISZERO, NUM n) -> BOOL false
		| (ISZERO, v) -> ERROR (sprintf "ERROR: input '%A' for ISZERO must be an integer" v)
		| (FUN (x, y), z) -> interp (subst y x z)
		| (REC (x, y), z) -> APP (interp (REC (x, y)), z)
		| (x, y) -> ERROR (sprintf "ERROR: inputs '%A' and '%A' for APP must be among {SUCC, PRED, ISZERO, FUN, REC}" x y)
	| FUN (x, y) -> FUN (x, y)
	| REC (x, y) -> (subst y x (REC (x, y)))
	| ERROR e -> ERROR e
