let rec powerset a =
	match a with
	| []	-> [[]]
	| x		-> (powerset (List.tail x)) @ List.map (fun z -> (List.head x)::z) (powerset (List.tail x))
