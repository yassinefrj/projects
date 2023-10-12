# 52075_54563_Project

# Secure software development and web security project

A client/server file system storage platform for medical record

FERRAJ Yassine 52075 from the group D121 (With Mister RICHARD)
TAHIRI Ibrahim 54563 from the group D122 (With Mister ABSIL)

## Table of contents

* [General info](#general-info)
* [Technologies](#technologies)
* [Notes](#notes)
* [Setup](#setup)
* [How to use the project](#how-to-use-the-project)


## General info

The goal of this project is to implement a SECURE client / server file system storage, such as
the ones available in NAS systems or in FTP clients. 
Consequently, there are only two types of actors : a server, and a set of clients.
From a general point of view, the server allows
* new clients to register to the system;
* clients to log in the system;
* authenticated clients to store files where there are allowed to;
* authenticated clients to download files if they are allowed to;
* authenticated clients to delete files if they are allowed to.
* authenticated clients to add a contact to its contacts list and share permissions on file with them. 


## Technologies

* OpenSSH (client and server)
* Laravel Framework 9.24.0
* Xampp 8.1.17
* Git Bash (used to clone the project)
* OpenSSL v3.1.1
* Windows 11


## Notes


Please make sure that :

* .\xampp
* .\xampp\php
* .\System32\OpenSSH  
* .\ProgramData\ssh (you need to show your hidden folder by going to explorer options -> View -> Show hidden files, folders and drives)
* .\OpenSSL-Win64\bin
* .\bin (from composer)


are well in your computer path (check your environment variables).

There is an already provided admin login and password for test purposes. You can also find it in sftp_52075_54563/http/database/seeders/UsersTableSeeder.php

* Login: usersftp@gmail.com
* Paswword: Usersftp1!

For the database we don't provide a .sql file. Simply follow the steps here under.

## Setup

- Download the project file from github for example by cloning the repository using 
```
git clone https://git.esi-bru.be/52075/52075_54563_project
```

### Setup OpenSSH

Click on "Windows Icon" -> Write and Open "Settings" -> Apps -> Optinal features -> At the right top click on View features -> Write "openssh server" -> select it by checking the checkbox -> Click on "Next" button -> "Install" button. Then wait until the installation is complete

### Step 1 : verifying the OpenSSH configuration

1) Start your OpenSSH SSH server (on Windows, look for it in the Services pannel) by making a Right click then "start"
2) In order to allow user to connect using a private key, go to ProgramData/ssh/sshd_config, edit it with administrator permission and verify the following :
	- **StrictModes yes** (line has to be uncommented. If not, please remove the "#" and if needed change the "no" to "yes"). 

             StrictModes specifies whether ssh should check user's permissions in their home directory and hosts files before accepting login.

    - **PubkeyAuthentication yes** (line has to be uncommented. If it is not, please remove the "#")
	- **PasswordAuthentication no** (line needs to be uncommented and if it is set to "yes" please change it to "no")
	- comment the last two lines of the file by adding # before each line
3) Restart your OpenSSH server (on Windows, look for it in the Services pannel) by making a Right click then "restart"
4) make the run of your OpenSSH server automatic (on Windows, look for it in the Services pannel)  by making a Right click then "Properties" -> Startup type -> select "automatic"

### Step 2 : configure .env

5) Go to your home folder and create a folder named "usersFolder" 

6) Open the .env file which is at the root of the security project. We'll modify and/or check some sections.

    > DB_PORT=<your MySql port on xampp (usually 3306 but please do verify)>
    >
    > DB_DATABASE=db_secg4 
    >
    > DB_USERNAME=root
    >
    >PATH_TO_KEY="C:/Users/HP/.ssh/" (respect the /)
    > 
    >PATH_AUTHORIZED_KEY='C:\\Users\\HP\\.ssh\\' (respect the \\)
    >
    >HOME_NAME="Yassine"

update PATH_TO_KEY and PATH_AUTHORIZED_KEY with your computer home path, do not forget the .ssh folder even if it do not exist yes
update HOME_NAME with your username windows session that you can find in C:\Users


### Step 3 : configuring xampp

7) Open the xampp control panel, click on the "Config" button next to "Apache" _> "PHP (php.ini)" and uncomment "extension=gd" by removing the ; before the line to be able to read images and captcha ( +/- line 920)

8) Open the xampp control panel, click on the "Config" button next to "Apache" -> "Apache (httpd.conf)", look for "DocumentRoot" until you find these lines :

```
DocumentRoot "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public"
<Directory "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public">
```
Then update them with the path to the "public" folder of the project.

9) Open the xampp control panel, click on the "Config" button next to "Apache" -> "Apache (httpd.conf)"  and Add these lines to read the server certificate:

```
<VirtualHost *:80>
    ServerName localhost
    DocumentRoot "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public"

    SSLEngine on
    SSLCertificateFile "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\server.crt"
    SSLCertificateKeyFile "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\server.key"

    <Directory "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public">
        Options Indexes FollowSymLinks
        AllowOverride All
        Require all granted
    </Directory>
</VirtualHost>

<VirtualHost *:443>
    ServerName localhost
    DocumentRoot "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public"

    SSLEngine on
    SSLCertificateFile "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\server.crt"
    SSLCertificateKeyFile "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\server.key"

    <Directory "C:\Users\HP\Documents\2023\SEC\sftp_56078_56110-main\sftp_56078_56110-main\sftp_56078_56110\public">
        Options Indexes FollowSymLinks
        AllowOverride All
        Require all granted
    </Directory>
</VirtualHost>
```

make sure the both occurences of :
- DocumentRoot
- SSLCertificateFile
- SSLCertificateKeyFile
- Directory


10) Open the xampp control panel, click on the "Config" button next to "Apache" -> "Apache (httpd.conf)", then look for :

```
LoadModule ssl_module modules/mod_ssl.so
```
uncomment it by removing the # before.
If you did not find this previous line, just add it

### Step 4 : Setup openssl

11) To install openssl go to <https://slproweb.com/products/Win32OpenSSL.html>
- search for "Win64 OpenSSL v3.1.1" 
- download the EXE
- install it

update your PATH environment variable and add .\OpenSSL-Win64\bin path 

### Step 5 : installs and updates
  
12) Place yourself at the root of the project (ex : C:\Users\Yassine\Documents\52075_54563_project\sftp_52075_54563) and open your terminal. 
First, we will check if Composer is installed. Please type the following command : 

    > **composer install**
    
If you have an error like "command not found" you need to install Composer.
To install Composer, go to <https://getComposer.org/download> and follow the steps written on this website (Download and run Composer-Setup.exe )

At the same time, you need to make sure the ComposerSetup is in your path in the environment variables (=> you need to have something like C:\ProgramData\ComposerSetup\bin or like C:\Users\Yassine\AppData\Roaming\Composer\vendor\bin)

then re open a terminal at the root of the project and type the previous command


13) Please type in this order, one by one:

    > **composer update**

    > **php artisan config:cache**                            
        => used to create a cache file for the application's configuration files. This cache file will improve the performance when loading the configuration values. This command will first clear any existing configuration cache before regenerating the new cache.

    > **php artisan config:clear**    
        => used to remove the configuration cache file created by the previous command "config:cache". By default this command will delete the bootstrap/cache/config.php file.

    > **php artisan cache:clear**    
        => used to clear the application's cache files. The command defines an optional store parameter which can be used to change which cache store is cleared. By default the store parameter will be set to whatever value is stored in the "cache.default" configuration entry (by default this is "file")

### Step 5 : creation of database

14) Open the xampp control panel and start Apache then the MySql modules., if a prompt pop click on "Allow access"

15) Open your browser and type in : 

    > **https://localhost/phpmyadmin** 

You'll probably see an Privacy error from your navigator because the project use a Self signed certificate, with Microsoft Edge, here is what you need to do :
- click on "Advanced"
- click on Continue to localhost (unsafe)
    
and create a database called "db_secg4"

16) In terminal, place yourself at the root of the project and type : 

    > **php artisan migrate --seed** 
    
-> type "yes" (==> --seed is to be able to have the default datas we made like the admin credentials)



### Step 6 : final connection 

17) Click the link bellow : 

    <https://localhost/>
    
18) You now have everything in hands to use the platform.

## How to use the project

To create an account go to <https://localhost/register>
To active your account, go to <https://localhost/login> and use the admin credentials :

* Login: usersftp@gmail.com
* Paswword: Usersftp1!

To push a file, first thing first is to log in with an NON administrator account, then go to https://localhost/files 

To add a doctor in your contact list go https://localhost/contacts and you need to know the email of the doctor to send him a contact request, then the doctor needs to approuve it.

Finnaly to share a file with your doctor, you need to edit a file that you pushed on the server (https://localhost/files), then select the doctor that you want to share with.
