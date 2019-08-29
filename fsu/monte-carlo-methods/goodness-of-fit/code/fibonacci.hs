main = print (kolmogorovSmirnov fibonacci 1000)

fibonacci :: [Int]
fibonacci = 1:1:[n | i <- [2..], let n = mod (fibonacci !! (i-1) + fibonacci !! (i-2)) (2 ^ 31)]

kolmogorovSmirnov seq n = max (maximum dPlus) (maximum dMinus)
    where dPlus = [(fromIntegral k) / (fromIntegral n) - fromIntegral (seq' !! (k - 1)) | k <- [1..n]]
          dMinus = [fromIntegral (seq' !! (k - 1)) - (fromIntegral (k - 1)) / (fromIntegral n) | k <- [1..n]]
          seq' = take n seq
