//calculates the gcd of two integers using Euclid's algorithm
let rec gcd = function
	| (a, 0)	-> a
	| (a, b)	-> gcd (b, a % b)

//adds two fractions (result is in lowest terms)
let (.+) (a, b) (c, d) = ((a * d + b * c) / gcd ((a * d + b * c), b * d), (b * d) / gcd (a * d + b * c, b * d))

//multiplies two fractions (result is in lowest terms)
let (.*) (a, b) (c, d) = (((a * c) / gcd (a * c, b * d)), (b * d) / gcd (a * c, b * d))
