type a' stream =
	Cons of 'a * (unit -> a' stream)

let rec map f Cons(x, xsf) =
	Cons(f x, fun () -> map (f xsf()))
