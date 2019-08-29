main = partA

partA = sequence (map print (parse list []))
    where list = (uSeq (randuSeq length [] seed))
          seed = 3
          length = 20002

partB = sequence (map print (triples list []))
    where list = (randuSeq length [] seed)
          seed = 3
          length = 1002

randu :: (Integral a) => a -> a
randu 1 = mod (65539 ^ 1000) (2 ^ 31)
randu x = mod (65539 * x) (2 ^ 31)

randuSeq :: (Integral a) => a -> [a] -> a -> [a]
randuSeq 1 seq seed = [randu seed]
randuSeq n seq seed = (randu (head rs)):rs
    where rs = randuSeq (n-1) seq seed

uSeq :: (Integral a, Fractional b) => [a] -> [b]
uSeq rs = [(fromIntegral r) / (fromIntegral (2 ^ 31)) | r <- rs]

parse :: (Fractional a, Ord a) => [a] -> [(a, a)] -> [(a, a)]
parse [] result = result
parse (x:[]) result = result
parse (x:y:[]) result = result
parse (x:y:z:us) result
    | (0.5 <= y) && (y <= 0.51) = parse (y:z:us) ((x, z):result)
    | otherwise = parse (y:z:us) result

triples :: (Num a) => [a] -> [(a, a, a)] -> [(a, a, a)]
triples [] result = result
triples (x:[]) result = result
triples (x:y:[]) result = result
triples (x:y:z:rs) result = triples (y:z:rs) ((x, y, z):result)
