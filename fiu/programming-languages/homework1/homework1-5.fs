//copied from part 3
let rec interleave = function
	| ([], [])			-> []
	| (xs, ys)	-> List.head xs :: List.head ys :: (interleave (List.tail xs , List.tail ys))

//copied from part 4
let rec gencut (n, xs) = 
	match (n, xs) with
	| (_, [])	->	([], [])
	| (0, xs)	->	([], xs)
	| (n, xs)	->	(List.head xs :: fst (gencut (n - 1, List.tail xs)), snd (gencut (n - 1, List.tail xs)))

//copied from part 4
let cut xs = (gencut (List.length xs / 2, xs))

//first cuts the given list into two equal-length sublists, then interleaves them
let shuffle xs = interleave (cut xs)
