--the second of these lines uses an anonymous function to accomplish the same thing.
let succ1 n = n + 1;;
let succ2 = fun n -> n + 1;;

--cos is the library cosin(x) function
let cos_squared x =
	let c = cos x
	c * c;;

--remember that prefix operators take precedence over all infix operators
