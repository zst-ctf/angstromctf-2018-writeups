# Source Me 2
web - 50 points

## Challenge 
Your goal hasn't changed. [Log in](http://web.angstromctf.com:7000/).

## Hint
Look at the title. Also, lots of md5s for common passwords are known.

## Solution

From source, we see the javascript

	var checkLogin = function () {
        var password = document.getElementById("password").value;
        if (document.getElementById("uname").value != "admin"){
            console.log(uname);
            document.getElementById("message").innerHTML = "Only admin user allowed!";
            return;
        } else {
            var passHash = md5(password);
            if (passHash == "bdc87b9c894da5168059e00ebffb9077"){
                window.location = "./login.php?user=admin&pass=" + password;
            } else {
                document.getElementById("message").innerHTML = "Incorrect Login";
            }
        }
        return;
    }

We can retrieve the password using crackstation: https://crackstation.net/

	bdc87b9c894da5168059e00ebffb9077	md5	password1234

Log in

	Welcome, admin. Here is your flag: actf{md5_hash_browns_and_pasta_sauce}

## Flag

	actf{md5_hash_browns_and_pasta_sauce}
