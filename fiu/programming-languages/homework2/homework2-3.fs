let rec transpose a =
	match a with
	| []	->	[]
	| x		->	if List.isEmpty((List.head x)) then []
				else (List.map (fun z -> List.head z) x)::(transpose (List.map (fun z -> List.tail z) (x)))
