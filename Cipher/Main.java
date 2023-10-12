import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

/**
 * this class represents my main class
 */
public class Main {
    static final String path_ciphered = "data/ciphered.txt";
    static final String path_plain = "data/plain.txt";
    static final String path_key = "data/key.txt";
    static final String path_unciphered = "data/unciphered.txt";

    static String keye = "";

    /**
     * this method prompts the user to enter a number between 1 and 7, it calls the selectedMethod method passing the entered number as an argument.
     * If an exception occurs while executing the selectedMethod, it prints the error stack trace and displays an error message to the user.
     * The loop continues until the user enters 7 to exit the program
     * @param args
     */
    public static void main(String[] args) {
        System.out.println("|*************Welcome to the UNCIPHER/DECIPHER tool************|");
        System.out.println("|                                                              |");
        System.out.println("|                                                              |");
        System.out.println("|**************************************************************|");
        int answer = 0;
        do {
            System.out.println("                  What option you choose ? :                   ");
            System.out.println("");
            System.out.println("");
            System.out.println("  *  1) Cipher text file CESAR with given key (CESAR-K) ");
            System.out.println("  *  2) Cipher text file VERNAM with given key (VERNAM-K) ");
            System.out.println("  *  3) Uncipher ciphered text file CESAR with given key (CESAR) ");
            System.out.println("  *  4) Uncipher ciphered text file CESAR without key (CESAR) ");
            System.out.println("  *  5) Uncipher ciphered text file VERNAM with given key (VERNAM) ");
            System.out.println("  *  6) Uncipher ciphered text file VERNAM without key (VERNAM) ");
            System.out.println("  *  7) Quit");
            answer = readInteger("Please type a number (1-7 ONLY) ! ", 1, 7);

            try {
                selectedMethod(answer);
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("Error please relaunch correctly ! ");
            }
        } while (answer != 7);

    }

    /**
     * This method determines which operation should be performed.
     * The answer parameter is used in a switch statement to determine what action should be taken.
     * There are five options which correspond to the encryption and decryption of texts according to
     * two different methods (César and Vernam) as well as the writing of the final result in a file.
     * The user can choose an option by entering the corresponding number and the corresponding
     * operation will be performed accordingly. Operations include entering text and key,
     * validating entries, performing encryption or decryption, and writing the result to a file if the user wishes
     * @param answer determine what action should be taken
     */
    private static void selectedMethod(int answer) {

        switch (answer) {
            case 1 -> {
                System.out.println("CIPHER TEXT CESAR WITH KEY");
                String plainText = askPathPlainFile();
                plainText = Preprocess.sanitizeToAlpha(plainText);
                System.out.println("TEXTE = " + plainText);
                int offset = readInteger("Now write the offset in this terminal in number format then press ENTER (ex 10) : ");
                System.out.println("PLEASE BE PATIENT");
                String cipheredTtext = Cesar.cipherCesarWithKey(plainText, offset);
                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y' || answerOutput == 'y') {
                    try {
                        try (FileWriter fw = new FileWriter(writeInCipheredFile())) {
                            fw.write(cipheredTtext);
                        }
                        System.out.println("The text is now avaible in the file " + path_ciphered);
                    } catch (IOException e) {
                        System.out.println("ERROR ");
                    }
                } else {
                    System.out.println("Before the encode : ");
                    System.out.println(plainText);
                    System.out.println("After the encode : ");
                    System.out.println(cipheredTtext);

                }

            }
            case 2 -> {
                System.out.println("CIPHER TEXT VERNAM WITH KEY");
                String plainText = askPathPlainFile();
                plainText = Preprocess.sanitizeToAlpha(plainText).toUpperCase();
                System.out.println("TEXTE = " + plainText);
                String key = askPathKey();
                //key = Vernam.generateVigenereKey(plainText,key); //doublon
                String cipheredText = Vernam.cipherVernamWithKey(plainText, key);

                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y') {
                    try {
                        Files.write(Path.of(path_ciphered), cipheredText.getBytes());
                        System.out.println("The text is now avaible in the file " + path_ciphered);
                    } catch (IOException e) {
                        System.out.println("Erreur lors de la sauvegarde du message chiffré dans le fichier " + path_ciphered);
                        e.printStackTrace();
                    }
                } else {
                    System.out.println("Before the encode : ");
                    System.out.println(plainText);
                    System.out.println("After the encode : ");
                    System.out.println(cipheredText.toUpperCase());
                }

            }
            case 3 -> {
                System.out.println("UNCIPHER CIPHERED TEXT CESAR WITH KEY ");
                String plainText = askPathCipheredFile();
                int offset = readInteger("Now the offset : ");
                System.out.println("PLEASE BE PATIENT");
                String cipheredTtext = Cesar.uncipherCesarWithKey(plainText, offset);
                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y' || answerOutput == 'y') {
                    try {
                        try (FileWriter fw = new FileWriter(writeInCipheredFile())) {
                            fw.write(cipheredTtext);
                        }
                        System.out.println("The text is now avaible in the file " + path_ciphered);
                    } catch (IOException e) {
                        System.out.println("ERROR ");
                    }
                }else{System.out.println("Before the encode : ");
                System.out.println(plainText);
                System.out.println("After the encode : ");
                System.out.println(cipheredTtext);}

            }
            case 4 -> {
                System.out.println("UNCIPHER CIPHERED TEXT CESAR WITHOUT KEY ");
                String plainText = askPathCipheredFile();
                System.out.println("PLEASE BE PATIENT");
                int offset = Cesar.breakCipher(plainText);
                String decipheredText = Cesar.uncipherCesarWithKey(plainText, offset);

                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y') {
                    try {
                        try (FileWriter fw = new FileWriter(writeInUncipheredFile())) {
                            fw.write(decipheredText);
                        }
                        System.out.println("The text is now avaible in the file " + path_unciphered);
                    } catch (IOException e) {
                        System.out.println("ERROR ");
                    }
                } else {
                    System.out.println("Before the encode : ");
                    System.out.println(plainText);
                    System.out.println("After the encode : ");
                    System.out.println(decipheredText);
                }

            }
            case 5 -> {
                System.out.println("Uncipher ciphered text file VERNAM with given key");
                //String plainText = askPathCipheredFile();
                byte[] byteText = askPathCipheredFileBytes();
                String key = askPathKey();
                String decipheredText = Vernam.uncipherVernamWithKey(byteText, key);

                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y') {
                    try {
                        try (FileWriter fw = new FileWriter(writeInUncipheredFile())) {
                            fw.write(decipheredText);
                        }
                        System.out.println("The text is now avaible in the file " + path_unciphered);
                    } catch (IOException e) {
                        System.out.println("ERROR ");
                    }
                } else {
                  //  System.out.println("Before the encode : ");
                   // System.out.println(new String(byteText));
                    System.out.println("After the encode : ");
                    System.out.println(decipheredText);
                }
            }
            case 6 -> {
                System.out.println("Uncipher ciphered text file VERNAM without key");
                byte[] cipherByte = askPathCipheredFileBytes(); // utiliser pour déchiffrer
                System.out.println("TAILLE CIPHER BYTE - case 6 " + cipherByte.length);


                String alphabetCipherByte = Vernam.convertByteStringToAlphabet(new String(cipherByte)); // utilisé pour les calcule
                int keyLenght = Vernam.findLength(alphabetCipherByte);
                String original = Vernam.findKey(cipherByte,alphabetCipherByte,keyLenght); // doit renvoyer un string

                System.out.println("Do you want to write the output in text file (Y|N then press ENTER)");
                Scanner kbd = new Scanner(System.in);
                char answerOutput = kbd.nextLine().charAt(0);
                if (answerOutput == 'Y') {
                    try {
                        try (FileWriter fw = new FileWriter(writeInUncipheredFile())) {
                            fw.write(original);
                        }
                        System.out.println("The text is now avaible in the file " + path_unciphered);
                    } catch (IOException e) {
                        System.out.println("ERROR ");
                    }
                }else {
                  //  System.out.println("Before the encode : ");
                  //  System.out.println(new String(cipherByte));
                    System.out.println("After the encode : ");
                    System.out.println(original);
                }
            }
            case 7 -> {
                System.out.println("Bye");
            }
            default -> throw new AssertionError();
        }

    }

    /**
     * @return the path of the unciphered.txt file
     * @throws FileNotFoundException
     */
    private static String writeInUncipheredFile() throws FileNotFoundException {
        Scanner kbd = new Scanner(System.in);
        //String url = kbd.nextLine();
        String url = path_unciphered;
        return url;
    }

    /**
     * @return the path of the ciphered.txt file
     * @throws FileNotFoundException
     */
    private static String writeInCipheredFile() throws FileNotFoundException {
        Scanner kbd = new Scanner(System.in);
        //String url = kbd.nextLine();
        String url = path_ciphered;
        return url;
    }

    /**
     * This function asks the user to put his key in a file named "key.txt",
     * then write "OK", the function retrieves the path of the file containing
     * the key, reads its contents using of a FileInputStream object, and stores
     * the content in a "plainProcessText" string, it returns the key which is
     * first processed by Preprocess.sanitizeToAlpha() which
     * removes all non-alphabetic characters
     * @return the key
     */
    private static String askPathKey() {

        String plainProcessText = "";
        try {
            Scanner kbd = new Scanner(System.in);

            do {
                System.out.println("Please put your key in data/key.txt then write OK and press ENTER");
            } while (!kbd.nextLine().equals("OK"));

            // String url = kbd.nextLine();
            String url = path_key;
            FileInputStream file = new FileInputStream(url);
            //renvoie true s'il y a une autre ligne à lire
            try (Scanner scanner = new Scanner(file)) {
                //renvoie true s'il y a une autre ligne à lire
                while (scanner.hasNextLine()) {
                    plainProcessText += scanner.nextLine();
                }
            }
        } catch (IOException e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }

        return Preprocess.sanitizeToAlpha(plainProcessText);
    }

    /**
     * This function asks the user to put their ciphertext in a "data/ciphered.txt"
     * file, then write "OK", it reads the contents of this file and stores it in
     * a variable named "plainProcessText". it reads the contents of the file line
     * by line and stores each line in the "plainProcessText" variable. this variable is returned
     * @return the cipher text in the the ciphered file
     */
    private static String askPathCipheredFile() {

        String plainProcessText = "";
        try {
            Scanner kbd = new Scanner(System.in);

            do {
                System.out.println("Please put your ciphered text in data/ciphered.txt then write OK and press ENTER ");
            } while (!kbd.nextLine().equals("OK"));

            // String url = kbd.nextLine();
            String url = path_ciphered;
            FileInputStream file = new FileInputStream(url);
            //renvoie true s'il y a une autre ligne à lire
            try (Scanner scanner = new Scanner(file)) {
                //renvoie true s'il y a une autre ligne à lire
                while (scanner.hasNextLine()) {
                    plainProcessText += scanner.nextLine();
                }
            }
        } catch (IOException e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }

        return plainProcessText;
    }

    /**
     * This function reads a binary file and returns its contents as an
     * array of bytes using the FileInputStream class
     * @return returns the content as an array of bytes
     */
    private static byte[] askPathCipheredFileBytes() {
        File file = new File(path_ciphered);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            return bytes;
            // faire quelque chose avec les bytes lus...
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;

        /*

        String plainProcessText = "";
        try {
            Scanner kbd = new Scanner(System.in);

            do {
                System.out.println("Please put your plain text in data/ciphered.txt then press OK");
            } while (!kbd.nextLine().equals("OK"));

            // String url = kbd.nextLine();
            String url = path_ciphered;
            FileInputStream file = new FileInputStream(url);
            //renvoie true s'il y a une autre ligne à lire
            try (Scanner scanner = new Scanner(file)) {
                //renvoie true s'il y a une autre ligne à lire
                while (scanner.hasNextLine()) {
                    plainProcessText += scanner.nextLine();
                }
            }
        } catch (IOException e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }

        return plainProcessText.getBytes();
        */

    }

    /**
     * This method asks the user to enter the text to be read in
     * a file named "data/plain.txt" by typing "OK". It then reads
     * the contents of the file, stores it in a string, and returns
     * the string. If an exception is thrown, an error message is
     * displayed and the program exits with error code 1.
     * @return a character string representing the content of the "data/plain.txt" file
     */
    private static String askPathPlainFile() {

        String plainProcessText = "";
        try {
            Scanner kbd = new Scanner(System.in);

            do {
                System.out.println("Please put your plain text in data/plain.txt then write OK and press ENTER");
            } while (!kbd.nextLine().equals("OK"));

            // String url = kbd.nextLine();
            String url = path_plain;
            FileInputStream file = new FileInputStream(url);
            //renvoie true s'il y a une autre ligne à lire
            try (Scanner scanner = new Scanner(file)) {
                //renvoie true s'il y a une autre ligne à lire
                while (scanner.hasNextLine()) {
                    plainProcessText += scanner.nextLine();
                }
            }
        } catch (IOException e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }

        return plainProcessText;
    }

    private static String askPathUnciphered() {

        String plainProcessText = "";
        try {
            Scanner kbd = new Scanner(System.in);

            do {
                System.out.println("Please put your plain text in data/unciphered.txt then write OK and press ENTER");
            } while (!kbd.nextLine().equals("OK"));

            // String url = kbd.nextLine();
            String url = path_unciphered;
            FileInputStream file = new FileInputStream(url);
            //renvoie true s'il y a une autre ligne à lire
            try (Scanner scanner = new Scanner(file)) {
                //renvoie true s'il y a une autre ligne à lire
                while (scanner.hasNextLine()) {
                    plainProcessText += scanner.nextLine();
                }
            }
        } catch (IOException e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }

        return Preprocess.sanitizeToAlpha(plainProcessText);
    }

    /**
     * This method asks the user to enter an integer from the console
     * by displaying a message given as a parameter. If the entry is
     * not an integer, an error message is displayed and the user is
     * prompted to enter a valid number. This loop continues until
     * the user enters a valid integer between 1 and 7, then the method
     * returns the integer.
     *
     * @param message the message display
     * @return the entered integer
     */
    public static int readInteger(String message) {
        Scanner kbd = new Scanner(System.in);
        System.out.println(message);
        while (!kbd.hasNextInt()) {
            kbd.next();
            System.out.println("The input is not a number between 1 and 7 !"
                    + "Retry correctly ...");
            System.out.println(message);
        }
        return kbd.nextInt();
    }

    /**
     * Asks the user to enter an integer between min and max, displaying the given message.
     * If the input is not an integer or the entered number is not between min and max,
     * an error message is displayed and the user is prompted to enter a correct integer.
     *
     * @param message the message to display before prompting the user for input
     * @param min     the minimum integer value allowed
     * @param max     the maximum integer value allowed (inclusive)
     * @return the integer entered by the user
     * @throws IllegalArgumentException if min is greater than max
     */
    public static int readInteger(String message, int min, int max) {
        if (min > max) {
            throw new IllegalArgumentException("The min is bigger than max" + min + " " + max);
        }

        int integer = readInteger(message);
        while (integer < min || integer > max) {
            System.out.println("The integer must be between" + min + " and " + max);
            integer = readInteger(message);
        }
        return integer;
    }
}