import System.Random
import Data.Time.Clock

main::IO()
main = getContents >>= putStrLn . unlines . map (wordList . factoring . readInt) . words

readInt::String -> Int
readInt = read

replace::String -> String
replace ('[':']':xl) = "fail\n"
replace a = a

wordList::[Int] -> String
wordList [] = "fail\n"
wordList l = unlines $ map show l

factoring::Int -> [Int]
factoring n = splitter n 2

splitter::Int -> Int -> [Int]
splitter n m
  | m > n = []
  | (mod n m) == 0 = m:splitter (quot n m) m
  | isPrime n < 10 = [n]
  | otherwise = splitter n (m+1)

isPrime::Int -> Int
isPrime p = do
  let a = take 100 $ randomsR p (mkStdGen 4294967291)
  foldr (+) 0 $ map (isFermat p) a

findD::Int -> Int -> (Int,Int)
findD r d
  | mod d 2 == 0 = findD (r+1) $ quot d 2
  | otherwise = (d, r)

-- isMillerRabin::Int->(Int,Int)->Int->[Int] ->Int
-- isMillerRabin _ _ x [] = 0
-- isMillerRabin _ _ 1 _ = 1
-- isMillerRabin p (d, r) x (a:al) = do
--   let x =

millerRabinInner::Int->Int->Int->Int
millerRabinInner x n 0 = 1
millerRabinInner x n r
  | xx == 1 = 1
  | xx == n-1 = 0
  | otherwise = millerRabinInner xx n (r-1)
  where
    xx = mod (x ^ 2) n


isFermat::Int->Int->Int
isFermat p a
-- Is giving us an error at too large p, ex
-- 199774 ^ (4294967291-1) mod 4294967291
  | mod (a ^ (p-1)) p == mod a p = 0
  | otherwise = 1

randomsR::(RandomGen g) => Int -> g -> [Int]
randomsR p g = let (value,ng) = randomR (2,p-2) g in value:(randomsR p ng)
