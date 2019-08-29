-- Skeleton file for PCF interpreter

-- This sets F# to read from whatever directory contains this source file.
System.Environment.set_CurrentDirectory __SOURCE_DIRECTORY__;;

#load "parser.fsx"

-- This lets us refer to "Parser.Parse.parsefile" simply as "parsefile",
-- and to constructors like "Parser.Parse.APP" simply as "APP".
open Parser.Parse

-- Here I show you a little bit of the implementation of interp. Note how ERRORs
-- are propagated, how rule (6) is implemented, and how stuck evaluations
-- are reported using F#'s sprintf function to create good error messages.
let rec interp = function
	| APP (e1, e2) ->
		match (interp e1, interp e2) with
		| (ERROR s, _)  -> ERROR s        // ERRORs are propagated
		| (_, ERROR s)  -> ERROR s
		| (SUCC, NUM n) -> NUM (n+1)      // Rule (6)
		| (SUCC, v)     -> ERROR (sprintf "'succ' needs int argument, not '%A'" v)

// Here are two convenient abbreviations for using your interpreter.
let interpfile filename = filename		|>	parsefile	|>	interp

let interpstr sourcecode = sourcecode	|>	parsestr	|>	interp


"let twice = fun f -> fun x -> f (f x) in twice twice twice twice succ 0"

74
"(rec d -> fun n -> if iszero n then 0 else succ (succ (d (pred n)))) 37"

37
"(rec sum -> fun x -> fun y -> if iszero x then y else sum (pred x) (succ y)) 37 0"

0
"(rec double -> fun n -> if iszero n then 0 else succ (succ (double (pred n)))) 0"

5
"((fun x -> succ x) (succ 3))"

46
"let minus = rec m -> fun x -> fun y -> if iszero y then x else m (pred x) (pred y) in minus 125 79"

6765
"let plus = rec p -> fun x -> fun y -> if iszero x then y else p (pred x) (succ y) in let fibonacci = rec f -> fun n -> if iszero n then 0 else if iszero (pred n) then 1 else plus (f (pred n)) (f (pred (pred n))) in fibonacci 20"

720
"let plus = rec p -> fun x -> fun y -> if iszero x then y else p (pred x) (succ y) in let times = rec t -> fun x -> fun y -> if iszero x then 0 else plus y (t (pred x) y) in let factorial = rec f -> fun n -> if iszero n then 1 else times n (f (pred n)) in factorial 6"

??
"let minus = rec m -> fun x -> fun y -> if iszero y then x else m (pred x) (pred y) in let divides = rec div -> fun d -> fun n -> if iszero n then false else if iszero (pred n) then true else div d (minus n d) in let divisor = rec ds -> fun n -> fun init -> if divides init (succ n) then init else ds n (succ init) in divisor 36863 2"

true
"let cons = fun x -> fun xs -> fun n -> if iszero n then x else if iszero (pred n) then xs else false in let nil = fun n -> true in let hd = fun f -> f 0 in let tl = fun f -> f 1 in let null = fun f -> f 2 in let equal = rec e -> fun a -> fun b -> if iszero a then iszero b else if iszero b then false else e (pred a) (pred b) in let member = rec m -> fun n -> fun ns -> if null ns then false else if equal n (hd ns) then true else m n (tl ns) in member 4 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 nil)))))"

509
"let Ack = rec A -> fun x -> fun y -> if iszero x then succ y else if iszero y then A (pred x) 1 else A (pred x) (A x (pred y)) in Ack 3 6"

APP (REC ("d", FUN ("n", IF (APP (ISZERO,ID "n"),NUM 0, APP (SUCC,APP (SUCC,APP (ID "d",APP (PRED,ID "n")))))) ),NUM 37)
