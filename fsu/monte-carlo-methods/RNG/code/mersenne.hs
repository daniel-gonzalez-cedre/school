import System.Random.Mersenne

main = (sequence . (map print)) =<< (sequence (f (take n mersenneList)))
    where f = pairs
          n = 1002

mersenne :: IO Double
mersenne = (getStdGen :: IO MTGen) >>= (random :: MTGen -> IO Double)

mersenneList :: [IO Double]
mersenneList = [mersenne | i <- [1..]]

pairs :: (Show a) => [IO a] -> [IO [a]]
pairs [] = []
pairs (x:[]) = []
pairs (x:y:ms) = (sequence [x, y]):(pairs ms)

triples :: (Show a) => [IO a] -> [IO [a]]
triples [] = []
triples (x:[]) = []
triples (x:y:[]) = []
triples (x:y:z:ms) = (sequence [x, y, z]):(triples ms)
