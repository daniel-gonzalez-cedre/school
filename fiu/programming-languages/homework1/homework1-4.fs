//recursively cuts a list into two sublists where n is the length of the first sublist
let rec gencut (n, xs) = 
	match (n, xs) with
	| (_, [])	->	([], [])
	| (0, xs)	->	([], xs)
	| (n, xs)	->	(List.head xs :: fst (gencut (n - 1, List.tail xs)), snd (gencut (n - 1, List.tail xs)))

//cuts a list into two equal-length sublists using gencut
let cut xs = (gencut (List.length xs / 2, xs))
