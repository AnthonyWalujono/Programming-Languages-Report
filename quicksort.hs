module Main where
main = do
    contents <- readFile "data.txt"
    print "Data loaded. Doing Quick Sorting.."
    let newcontents = quicksort contents
    writeFile "quicksorted.txt" newcontents
    print "Sorting done"
quicksort :: Ord a => [a] -> [a]
quicksort []     = []
quicksort (p:xs) = (quicksort smaller) ++ [p] ++ (quicksort bigger)
    where
        smaller  = filter (< p) xs
        bigger = filter (>= p) xs
