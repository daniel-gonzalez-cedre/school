let rec transpose a =
	match a with
	| []	->	[]
	| x		->	if List.isEmpty((List.head x)) then []
				else (List.map List.head x)::(transpose (List.map List.tail (x)))

let rec inner x = function
	| []	->	0
	| y::ys	->	List.head x * y + inner (List.tail x) ys

let rec multiply = function
	| ([], _)			->	[]
	| (x::xs, y)	->	List.map (inner x) (transpose y) :: multiply (xs, y)
