type Exp =
    Num of int
  | Neg of Exp
  | Sum of Exp * Exp
  | Diff of Exp * Exp
  | Prod of Exp * Exp
  | Quot of Exp * Exp

type 'a option = None | Some of 'a

let rec evaluate = function
	| Num n -> Some n
	| Neg e ->
		match evaluate e with
		| Some x -> Some (-x)
		| _ -> None
	| Prod (e1,e2) ->
		match evaluate e1, evaluate e2 with
		| Some l, Some m -> Some (l * m)
		| _ -> None
	| Quot (e1,e2) ->
		match evaluate e1, evaluate e2 with
		| Some l, Some 0 -> None
		| Some l, Some m -> Some(l / m)
		| _ -> None
	| Sum (e1, e2) ->
		match evaluate e1, evaluate e2 with
		| Some l, Some m -> Some(l + m)
		| _ -> None
	| Diff (e1, e2) ->
		match evaluate e1, evaluate e2 with
		| Some l, Some m -> Some(l - m)
		| _ -> None;;
