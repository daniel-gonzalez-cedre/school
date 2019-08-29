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

//copied from part 5
let shuffle xs = interleave (cut xs)

//counts how many shuffles it will take to make two lists equal to eachother
let rec countaux (xs, ys) = 
	if xs = ys then 1
	else 1 + countaux (shuffle xs, ys)

//counts how many shuffles will return a deck of n cards to its original order
//number of shuffles for a deck of 52 cards is 8!
let countshuffles n = countaux (shuffle [1 .. n], [1 .. n])
