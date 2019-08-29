import System.Random.Mersenne

main = print =<< fmap stats (sequence (take m (estimate n)))
    where m = 40
          n = 10000

halton :: Int -> Double
halton i = halton' i 1 0
    where halton' :: Int -> Double -> Double -> Double
          halton' i f r
              | (i > 0) = halton' i' f' r'
              | otherwise = r
              where i' = floor (fromIntegral i / fromIntegral 2)
                    f' = f / fromIntegral 2
                    r' = r + f' * fromIntegral (mod i 2)

haltonList :: [Double]
haltonList = [halton i | i <- [1..]]

mersenne :: IO Double
mersenne = (getStdGen :: IO MTGen) >>= (random :: MTGen -> IO Double)

shift :: (RealFrac a) => [a] -> a -> [a]
shift hs u = map (\x -> (x + u) - fromIntegral (floor (x + u))) hs

estimate :: Int -> [IO Double]
estimate n = [fmap (estimate' . shift (take n (haltonList))) mersenne | i <- [1..]]

estimate' :: [Double] -> Double
estimate' hs = (sum hs') / fromIntegral (length hs')
    where hs' = map exp hs

stats :: [Double] -> (Double, Double)
stats θs = (mean, std)
    where mean = (sum θs) / (fromIntegral (length θs))
          std = sqrt (sum (map (\x -> (x - mean)^2) θs) / (fromIntegral (length θs - 1)))
