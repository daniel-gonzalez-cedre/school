//recursively interleaves two lists
let rec interleave = function
	| ([], [])			-> []
	| (xs, ys)	-> List.head xs :: List.head ys :: (interleave (List.tail xs , List.tail ys))
