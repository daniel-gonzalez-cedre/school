--returns 1
List.head[1;2;3]

--returns [2;3]
List.tail[1;2;3]

--List.map applies a function to all of the elements of a list
--returns the resulting list of the same length as the original
List.map (fun n -> n*n) [1;2;3;4]

--List.filter applies a prediccate to each element of a list
--returns the resulting list, which is a sublist of the original
List.filter (fun x -> x%2 = 0) [1..100]

--List.reduce uses a binary function, associating to the left, and applying it to every left-pair of elements in the list
--returns a single value of the type of elements of the list
List.reduce (*) [1..10]