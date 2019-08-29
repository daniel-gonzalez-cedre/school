--this returns a list of all possible insertions of x into a given list
let rec insert x = function
	| []	->	[[x]]
	| y::ys	->	(x::y::ys)::(List.map (fun zs -> y::zs)(insert x ys))

let rec appmap f = function
	| []	->	[]
	| x::xs	->	f x @ appmap f xs

let rec permute = function
	| []	->	[[]]
	| x::xs	->	appmapp (insert x) (permute xs)
