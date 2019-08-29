let rec inner x = function
	| []	->	0
	| [y]	->	List.head x * y
	| y::ys	->	List.head x * y + inner (List.tail x) ys
