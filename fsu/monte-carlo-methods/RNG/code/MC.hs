import System.Random.Mersenne

main = print =<< fmap stats (sequence (take m (estimate n)))
    where m = 40
          n = 10000

mersenne :: IO Double
mersenne = (getStdGen :: IO MTGen) >>= (random :: MTGen ->  IO Double)

mersenneList :: [IO Double]
mersenneList = [mersenne | i <- [1..]]

estimate :: Int -> [IO Double]
estimate n = [fmap ((\x -> x / (fromIntegral n)) . sum . (map exp)) (sequence (take n mersenneList)) | i <- [1..]]

stats :: [Double] -> (Double, Double)
stats θs = (mean, std)
    where mean = (sum θs) / (fromIntegral (length θs))
          std = sqrt (sum (map (\x -> (x - mean)^2) θs) / (fromIntegral (length θs - 1)))
