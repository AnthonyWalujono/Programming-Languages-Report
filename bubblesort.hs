module Main where
main = do
    contents <- readFile "data.txt"
    print "Data loaded. Sorting.."
    let newcontents = bubblesort contents
    writeFile "./data_new_ghc" newcontents
    print "Sorting done"
bubblesort :: (Ord a) => [a] -> [a]
bubblesort []      = []
bubblesort (x0:xs) = case bubble x0 xs of
   (xs', True)  -> bubblesort xs'
   (xs', False) -> xs'
   where bubble x1 (x2:xs) | x1 <= x2  = merge x1 False $ bubble x2 xs
                           | otherwise = merge x2 True  $ bubble x1 xs
         bubble x1 []                  = ([x1], False)
         merge x s (xs, s') = (x:xs, s || s')
