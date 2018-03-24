# Slots
misc - 90 points

## Challenge 

defund is building a casino empire. Break his [slot machine](slots.py), which is running at `web.angstromctf.com:3002`.

## Hint
Good luck!

## Solution

The slot machine is rigged. It will never strike because of this code (it reassigns line2 until it has no combos).

	while payout(line2):
		line2 = line()


Looking more into it, the only possible exploit will be the input `float()` cast.

We can make weird inputs such as `1e-100`, `+inf`, `-inf` and in particular `nan`...

	$ nc web.angstromctf.com 3002
	Welcome to Fruit Slots!
	We've given you $10.00 on the house.
	Once you're a high roller, we'll give you a flag.
	You have $10.00.
	Enter your bet: nan
	🍈 : 🍒 : 🍌
	🍈 : 🍊 : 🍇 ◀
	🍊 : 🍊 : 🍌
	You lost everything.
	Wow, you're a high roller!
	A flag: actf{fruity}

## Flag

	actf{fruity}