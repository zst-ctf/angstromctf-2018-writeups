# That's Not My Name...
misc - 40 points

## Challenge 
My friend sent me [this copy](gettysburg.pdf) of Lincoln's inspiring Gettysburg Address, but I can't seem to open it. Something about having the wrong name. Can you help me figure it out?

## Hint
I am not what I seem. A penny for your thoughts?


## Solution

	$ file gettysburg.pdf 
	gettysburg.pdf: Microsoft OOXML

It is a MS Word document file. Rename and open in MS Word

## Flag

	actf{thanks_mr_lincoln_but_who_even_uses_word_anymore}