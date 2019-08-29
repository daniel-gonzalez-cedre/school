main = sequence (map print (haltonList 2 1000))

primes :: (Integral a) => [a]
primes = 2 : primes'
    where isPrime (p:ps) n = p^2 > n || (mod n p /= 0 && isPrime ps n)
          primes' = 3 : filter (isPrime primes') [5, 7..]

halton :: Int -> Int -> Double 
halton b i = halton' b i 1 0
    where halton' :: Int -> Int -> Double -> Double -> Double
          halton' b i f r
              | (i > 0) = halton' b i' f' r'
              | otherwise = r
              where i' = floor (fromIntegral i / fromIntegral b)
                    f' = f / fromIntegral b
                    r' = r + f' * fromIntegral (mod i b)

haltonList :: Int -> Int -> [[Double]]
haltonList s n = [[halton b i | b <- (take s primes)] | i <- [1..n]]
