<h1>Simple client/server application</h1>
<p>The server stores and processes data, and the client receives and displays it. The client application sends a random number to the server in a loop - a new number is sent on each iteration. After sending this number, the application reads the server's response, displays it on the screen and sleeps for 1 second. First you need to start the server and then the client. Otherwise, the client will not be able to connect to the server.</p>
<h3>How to use it</h3>
<p>Simply run the setup script :</p>
<pre>
<code>make server && make client</code>
</pre>
<pre>
<code>./server</code>
</pre>
<br>
<br>
<p>And in another terminal window :</p>
<pre>
<code>./client</code>
</pre>
