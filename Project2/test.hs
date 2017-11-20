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

isFermat::Int->Int->Int
isFermat p a
-- Is giving us an error at too large p, ex
-- 199774 ^ (4294967291-1) mod 4294967291
  | mod (a ^ (p-1)) p == mod 1 p = 0
  | otherwise = 1

randomsR::(RandomGen g) => Int -> g -> [Int]
randomsR p g = let (value,ng) = randomR (2,p-1) g in value:(randomsR p ng)
