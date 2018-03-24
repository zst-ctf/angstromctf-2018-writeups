# Waldo 2
misc - 30 points

## Challenge 
Now I have to find the [Waldo among the Waldos](waldo.zip)! Man, if I looked at these 1 per 5 seconds, it would take me 42 minutes to find the odd man out. There must be a better way...

## Hint
One of these things is not like the other.

## Solution

Many similar files in the zip, and one should have the flag

	$ diff -q --from-file *.jpg
	Files waldo1.jpg and waldo339.jpg differ
	
	$ strings waldo339.jpg 
	actf{r3d_4nd_wh1t3_str1p3s}

## Flag

	actf{r3d_4nd_wh1t3_str1p3s}