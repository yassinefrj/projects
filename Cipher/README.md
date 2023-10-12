# INFORMATIONS
## 52075_54563_LABO1
FERRAJ Yassine 52075 from the group D121 (With Mister RICHARD)

TAHIRI Ibrahim 54563 from the group D122 (With Mister ABSIL)

# HOW TO BUILD
After pull/clone the project and 
being in the repository that contain .git, just use those 2 following commands in a shell :


```bash
javac *.java
```
```bash
java Main
```

# HOW TO USE
Make sure to have a ciphered text CESAR (data/ciphered.txt) before uncipher with CESAR (also for VERNAM but in byte format, we used new String(byte[] cipheredText) before save in the file)

for instance to run the cryptanalysis of Vernan run the following command, you should first either put a ciphered byte text in data/ciphered.txt or to have ciphered using the program then press you press 6 + ENTER to start unciphering 

Every informations that you want to provide yourself should be in a GIVEN file with the extension.txt that you can find in the data folder

1. To cipher a plain text using CESAR CIPHER, press 1 then ENTER
2. To cipher a plain text using VERNAM CIPHER, press 2 then ENTER
3. To uncipher a text ciphered by CESAR and with a GIVEN KEY press 3 then ENTER
4. To uncipher a text ciphered by CESAR without knowing the key press 4 then ENTER
5. To uncipher a text ciphered by VERNAM and with a GIVEN KEY press 5 then ENTER
6. To uncipher a text ciphered by VERNAM without knowing the key press 6 then ENTER

Then just follow the instructions :)

To exit press 7

Thank u !