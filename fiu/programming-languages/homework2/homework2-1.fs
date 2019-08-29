let rec cartesian (a, b) = 
	match (a, b) with
	| ([], _)		-> []
	| (x::xs, y)	-> (List.map (fun z -> (x, z)) y) @ cartesian (xs, y)
