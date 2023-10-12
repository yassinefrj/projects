import java.util.stream.IntStream;

/**
 * Vernam CLass
 */
public class Vernam {
    static String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    /**
     * Generates a Vigenere key with the given plainText and key
     * the key will have the same length as the plainText
     * @param plainText the plain text used to generate the key.
     * @param key the initial key used as a base for the generated key.
     * @return the generated Vigenere key.
     * @throws IllegalArgumentException if the key is longer than the plainText.
     */
    public static String generateVigenereKey(String plainText, String key) {
        int plainLength = plainText.length();
        if (key.length() > plainText.length()) {
            throw new IllegalArgumentException("The key should be smaller than the plainText");
        }
        int index = 0;
        while (key.length() != plainText.length()) {
            if (plainLength == index) {
                index = 0;
            }
            key += key.charAt(index);
            index++;
        }
        return key.toUpperCase();
    }

    // convertir toutes les lettres en binaire
    // faire l'opération inverse

    // convertir toutes les lettres en binaire
    // xor
    // xor
    // reconvertir en lettre

    /**
     * Encrypts a message using the Vernam Cipher algorithm with a given key.
     * The method generates a Vigenere key from the given key and repeats it to cover the length of the message.
     * It then performs an XOR operation between the bytes of the message and the bytes of the key to obtain the cipher text.
     * @param message the message to be encrypted
     * @param key the key used to encrypt the message
     * @return the encrypted message
     * @throws IllegalArgumentException if the key is longer than the message
     */
    public static String cipherVernamWithKey(String message, String key) {
        // 1. copier la clé jusqu'à couvrir tout le texte
        key = generateVigenereKey(message,key);
        //System.out.println("CLE = " + key);
        // 2. faire message.indice lettre i MOD key.indice lettre i


        //byte
        byte[] messagebyte = message.getBytes();
        byte[] ketByte = key.getBytes();

        //xor
        byte[] cipherByte = new byte[messagebyte.length];

        for(int i=0; i < messagebyte.length;i++){
            cipherByte[i] = (byte) (messagebyte[i] ^ ketByte[i]);
        }
        //string
        String cipherText = new String(cipherByte);
       //System.out.println("CIPHER BYTE " + cipherText);

      // convertByteStringToAlphabet(cipherText);

        return cipherText;
    }


    /**
     * This method deciphers a byte array using the Vernam cipher algorithm, given a key in the form of a String.
     * It generates a Vigenere key using the input cipher byte array and the given key.
     * Then, it performs an XOR operation between each byte of the cipher array and the corresponding byte of the Vigenere key array.
     * Finally, it returns the original text as a String.
     * @param cipherByte The byte array to be deciphered.
     * @param key The key to be used for deciphering, in the form of a String.
     * @return The original text, deciphered from the input cipher byte array using the Vernam cipher algorithm.
     */
    public static String uncipherVernamWithKey(byte[] cipherByte, String key) {
        key = generateVigenereKey(new String(cipherByte),key);
        //xor
        byte[] ketByte = key.getBytes();
        byte[] originalByte = new byte[cipherByte.length];
        for(int i=0; i < cipherByte.length;i++){
            originalByte[i] = (byte) (cipherByte[i] ^ ketByte[i]);
        }
        //String
        //System.out.println("ORIGINAL " + new String(originalByte));
        String originalText = new String(originalByte);
        return originalText;
    }

    /*
    //3. déchiffrer
        // V1. byte
        String orignalMessage = "";
        key = generateVigenereKey(cipherText,key);
        for(int i = 0; i < cipherText.length(); i++){
            orignalMessage+= (char) (cipherText.charAt(i) ^ key.charAt(i));
        }
        System.out.println("ORIGINAL = " + orignalMessage);
        //return orignalMessage;

        return orignalMessage;
     */



        // Chiffrement du message avec la clé
     /*   public static String cipherVernamWithKey(String message, String key) {
            StringBuilder encryptedMessageBuilder = new StringBuilder();
            for (int i = 0; i < message.length(); i++) {
                // Chiffrement de chaque caractère en XOR avec le caractère correspondant de la clé
                char c = (char) (message.charAt(i) ^ key.charAt(i));
                encryptedMessageBuilder.append(c);
            }
            // Encodage du message chiffré en base64
            byte[] encryptedMessageBytes = encryptedMessageBuilder.toString().getBytes();
            String base64Encoded = Base64.getEncoder().encodeToString(encryptedMessageBytes);
            return base64Encoded;
        }

    // Déchiffrement du message avec la clé
    public static String uncipherVernamWithKey(String encryptedMessage, String key) {
        // Décodage du message chiffré en base64
        byte[] encryptedMessageBytes = Base64.getDecoder().decode(encryptedMessage);
        StringBuilder decryptedMessageBuilder = new StringBuilder();
        for (int i = 0; i < encryptedMessageBytes.length; i++) {
            // Déchiffrement de chaque octet en XOR avec l'octet correspondant de la clé
            byte b = (byte) (encryptedMessageBytes[i] ^ key.charAt(i % key.length()));
            decryptedMessageBuilder.append((char) b);
        }
        return decryptedMessageBuilder.toString();
    }

    */


    public static String decipherFromTheFile(String cipherMessage, String key){

        return "";
    }

    /**
     * This method initializes a String array of given length with empty strings.
     * @param length The length of the String array to be initialized.
     * @return A String array of given length with empty strings.
     */
    private static String[] initSousText(int length){
        String[] sousText = new String[length];
        // 2.initialisation pour eviter une erreur au +=
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            sousText[num_sousText] = "";
        }
        return sousText;
    }

    /**
     * This method initializes a two-dimensional byte array of given length and maximum subtext size.
     * @param length The length of the two-dimensional byte array to be initialized.
     * @param cipherByte The byte array to calculate the maximum subtext size.
     * @return A two-dimensional byte array of given length and maximum subtext size.
     */
    private static byte[][] initSousTextByte(int length,byte[] cipherByte){
        int tailleMaxSoustext = (int) (cipherByte.length/length);
        tailleMaxSoustext++; // pour  tjr aller à la fin

        System.out.println("Taille tab 2D " + length + " - " + tailleMaxSoustext);
        byte[][] sousText = new byte[length][tailleMaxSoustext];
        // 2.initialisation pour eviter une erreur au +=
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            for(int i=0; i< tailleMaxSoustext; i++){
               // sousText[num_sousText][i] = (byte) i;
            }
        }
        return sousText;
    }

    /**
     * This method fills a String array with subtexts of a given length extracted from a cipher text.
     * @param cipherText The cipher text from which subtexts will be extracted.
     * @param initedSubText The String array to be filled with subtexts.
     * @param length The length of the subtexts to be extracted.
     * @return A String array filled with subtexts of a given length extracted from a cipher text.
     */
    private static String[] fillSubText(String cipherText,String[] initedSubText,int length){
        // 3. creation des sous text
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            //System.out.println("Sous texte " + (num_sousText+1));

            for(int index=0; index < cipherText.length()/length || ((index*length)+num_sousText) < cipherText.length(); index++){
                initedSubText[num_sousText]+= cipherText.charAt((index*length)+num_sousText);
                // S.T 1 = 0,4,8,12,16
                // S.T 2 = 1,5,9,13,17
                // S.T 3 = 2,6,10,14,18
                // S.T 4 = 3,7,11,15,19
            }
        }
        return initedSubText;
    }

    /**
     * This method fills a 2D byte array with subtexts of a given length extracted from a cipher byte array.
     * @param cipherByte The cipher byte array from which subtexts will be extracted.
     * @param initedSubText The 2D byte array to be filled with subtexts.
     * @param length The length of the subtexts to be extracted.
     * @return A 2D byte array filled with subtexts of a given length extracted from a cipher byte array.
     */
    private static byte[][] fillSubTextByte(byte[] cipherByte,byte[][] initedSubText,int length){
        System.out.println("TAILLE CIPHER BYTE - fillSubTextByte " + cipherByte.length);
        // 3. creation des sous text
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            // System.out.println("Sous texte " + (num_sousText+1));

            int cpt = 0;
            for(int index=0; index < cipherByte.length/length || ((index*length)+num_sousText) < cipherByte.length; index++){
                int posCipherByte = (index*length)+num_sousText;
                initedSubText[num_sousText][cpt]+= cipherByte[posCipherByte];
                cpt++;

                // S.T 1 = 0,4,8,12,16
                // S.T 2 = 1,5,9,13,17
                // S.T 3 = 2,6,10,14,18
                // S.T 4 = 3,7,11,15,19
            }
        }
        return initedSubText;
    }

    private static void showSubText(String[] subtext, int length){
        for (int num_sousText=0; num_sousText < length; num_sousText++){
             System.out.println("Sous texte " + (num_sousText+1));
             System.out.println(subtext[num_sousText]);
        }
    }

    /**
     * Computes the coincidence index for each subtext in the array.
     * @param subText an array of strings representing the subtexts
     * @param length the length of the subtext array
     * @return an array of doubles representing the coincidence index for each subtext
     */
    private static Double[] computeCoincidenceIndex(String[] subText, int length){
        Double[] sousTextIndiceCoincidence = new Double[length];
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            sousTextIndiceCoincidence[num_sousText] = coincidenceAnalysis(subText[num_sousText]);
        }
        return sousTextIndiceCoincidence;
    }

    private static void showSubTextCoincidenceIndex(Double[] subTextCoincidenceIndice, int length){
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            System.out.print("Sous texte " + (num_sousText+1) + "- Coincidence Indice = ");
            System.out.println(subTextCoincidenceIndice[num_sousText]);
        }
    }


    /**
     * Computes the average coincidence index for a given key length based on the coincidence index of each subtext.
     * @param subTextCoincidenceIndex an array of Double values representing the coincidence index of each subtext.
     * @param length an integer representing the length of the key.
     * @return a Double value representing the average coincidence index for the given key length.
     */
    private static Double makeAverageOfSubTextCoincidenceIndex(Double[] subTextCoincidenceIndex, int length){
        double sum = 0.0;
        System.out.println("\t for KeyLenght " + length );
        for (int num_sousText=0; num_sousText < length; num_sousText++){
            System.out.println("sub_text number " + (num_sousText+1) + " IC = " + subTextCoincidenceIndex[num_sousText]);
            sum+= subTextCoincidenceIndex[num_sousText];
        }
        double moyenne = sum/length;
        return moyenne;
    }

    /**
     * This method finds the length of the key used to encrypt a message with Vernam cipher.
     * It does this by calculating the coincidence index for key lengths between 1 and 50,
     * and then returning the key length with the highest coincidence index.
     * @param cipherText the encrypted message.
     * @return the length of the key used to encrypt the message.
     */
    public static int findLength(String cipherText){
        // 8. Suppose length between 1 to 50
        int length = 50;
        Double[] coincidenceIndexForLength1to50 = new Double[length];
        for(int keyLength = 1, indice = 0; keyLength <= length; keyLength++, indice++){
            coincidenceIndexForLength1to50[indice] = breakVernamLenght4GivenSupposeLength(cipherText,keyLength);
        }

        // 9. Show all of the C - I
        for(int keyLength = 1, indice = 0; keyLength <= length; keyLength++, indice++){
            System.out.println("For keyLenght = " + keyLength + " - C-I = " + coincidenceIndexForLength1to50[indice]);
        }

        // 10. Take the more close to 0.065 C - I and consider it is the key lenght
        int keyLength = -1;
        boolean find = false;


        double max = 0.0;
        for(int indice = 0; indice < length; indice++){
            if(coincidenceIndexForLength1to50[indice] > max){
                find = true;
                keyLength = (indice+1);
                max = coincidenceIndexForLength1to50[indice];
            }
        }

        if(find){
            // 11. Show to key length
            System.out.println("La cle est de taille " + keyLength + " avec comme valeur " + coincidenceIndexForLength1to50[keyLength-1]);
        }else{
            System.out.println("Ce text n'a pas été chiffré avec Vernam cipher");
        }
        return keyLength;

    }

    /*if(!find){
            double min_1 = 0.065;
            double max_1 = 1;
            for(int indice = 0; indice < 10; indice++){
                if(coincidenceIndexForLength1to50[indice] < max_1 && coincidenceIndexForLength1to50[indice] > min_1){
                    find = true;
                    keyLength = (indice+1);
                    break;
                }
            }
        }*/

    /**
     * This method takes a String byteString as input, where each character represents a byte value,
     * and converts it into a String of letters from the alphabet.
     * @param byteString the input string consisting of byte values represented as characters
     * @return a String of letters from the alphabet obtained by mapping
     * each byte value to its corresponding letter
     */
    public static String convertByteStringToAlphabet(String byteString){
        String alphabetString = "";
        for(int i=0; i < byteString.length(); i++){
            alphabetString+= alphabet.charAt(byteString.charAt(i) % 26);
        }
       // System.out.println("Alphatbet String = " + alphabetString);
        return alphabetString;
    }

    /**
     * Computes the average coincidence index for a given Vernam cipher text and a supposed key length.
     * @param cipherText the Vernam cipher text to analyze.
     * @param length the supposed key length.
     * @return the average coincidence index for the given Vernam cipher text and supposed key length.
     */
    private static Double breakVernamLenght4GivenSupposeLength(String cipherText,int lenght){ // taille de 17
        // 1. Supposons que la clé est de taille de 4, on créer 4 sous text

        // 2.initialisation pour eviter une erreur au +=
        String[] sousText = initSousText(lenght);

        // 3. creation des sous text
        sousText = fillSubText(cipherText,sousText,lenght);

        //4. Affichage des sous text
      //  showSubText(sousText,lenght);

        //5. Calculer indice de coincidence pour chacun des sous texte
        Double[] sousTextIndiceCoincidence = computeCoincidenceIndex(sousText,lenght);

        //6. Affichage des indices de coicindences pour chacun des sous texte
       // showSubTextCoincidenceIndex(sousTextIndiceCoincidence,lenght);

        //7. Moyenne des indices de coincidences
        double averageCoincidenceIndexForTheGroup = makeAverageOfSubTextCoincidenceIndex(sousTextIndiceCoincidence,lenght);

        return averageCoincidenceIndexForTheGroup;
    }

    /**
     * This method calculates the coincidence index of a given cipher text.
     * It is calculated as the sum of the products of the number of times each letter in the alphabet
     * appears in the text, multiplied by one less than the total number of its occurrences,
     * divided by the product of the length of the text and one less than its length.
     * @param cipherText the cipher text to analyze
     * @return the coincidence index of the cipher text
     */
    public static double coincidenceAnalysis(String cipherText) {
        double sum = 0;
        for (int i = 0; i < alphabet.length(); i++) {
            int apparition = sumApparition(cipherText, alphabet.charAt(i));
            sum += (apparition * (apparition - 1));
        }
        return sum / (cipherText.length() * (cipherText.length() - 1));
    }

    /**
     * Computes the number of times a given letter appears in a given ciphertext.
     * @param cipherText the ciphertext to analyze
     * @param letter the letter to count the appearances of
     * @return the number of times the letter appears in the ciphertext
     */
    public static int sumApparition(String cipherText, char letter) {
        int sum = 0;
        for (int i = 0; i < cipherText.length(); i++) {
            if (cipherText.toUpperCase().charAt(i) == Character.toUpperCase(letter)) {
                sum++;
            }
        }
        return sum;
    }

    /**
     * This method finds the key used to encrypt the input cipher text, given the cipher byte array, the cipher text and the key length.
     * @param cipherByte the byte array containing the encrypted message.
     * @param cipherText the encrypted text.
     * @param keyLength the length of the encryption key.
     * @return the original, decrypted message.
     */
    public static String findKey(byte[] cipherByte, String cipherText, int keyLenght){
        //1. Create K (keylght) subtext with cipherText
        String[] sousText = initSousText(keyLenght);
        sousText = fillSubText(cipherText,sousText,keyLenght);

        //1. Create K (keylght) subtext with cipherByte
        byte[][] sousTextByte = initSousTextByte(keyLenght,cipherByte);
        sousTextByte = fillSubTextByte(cipherByte,sousTextByte,keyLenght);

        //2. Compute kay square test on each subtext to get the shift (indice letter used for xor)
        int[] shift = new int[keyLenght];
        for(int i=0; i< keyLenght; i++){
            System.out.print("Sous text" + i + " = ");
            shift[i] = breakCipher(sousText[i],sousTextByte[i]);
        }

        //3. uncipher all sub text
        String[] uncipherSubText = uncipherAllSubtext(sousTextByte,shift);

        //4. assemble all subText
        String original = regroupementDesCesarSousTexte(uncipherSubText);

        return original;
    }

    /**
     * Propabilité d'appartion de chaque lettre de l'alaphabet anglais.
     */
    static double[] englishLettersProbabilities3= {0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697,
            0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.001,
            0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.00074};


    /**
     * This method returns an array of frequencies of observed letters in the input message.
     * @param message the string to analyze.
     * @return an array of longs, where each element represents the frequency of a letter in the message.
     */
    public static long[] observedLettersFrequencies(String message) {
        return IntStream.rangeClosed('A', 'Z')//maybe upperCase
                .mapToLong(letter -> countLetter((char) letter, message))
                .toArray();
    }

    /**
     * Counts the number of occurrences of a specified letter in a given message.
     *
     * @param letter  The character to count occurrences of.
     * @param message The string to search for occurrences of the character.
     * @return The number of times the character occurs in the string.
     */
    public static long countLetter(char letter, String message) {
        return message.chars()
                .filter(character -> character == letter)
                .count();
    }


    /**
     * Computes the chi-squared statistic for the goodness of fit between the observed frequencies
     * `lettersFrequencies` and the expected frequencies `expectedFrequencies`.
     *
     * @param expectedFrequencies An array of expected frequencies.
     * @param lettersFrequencies  An array of observed frequencies.
     * @return The chi-squared statistic.
     */
    public static double chiSquareCompute(double[] expectedFrequencies, long[] lettersFrequencies) {
        double resultat = 0.0;
        for (int i = 0; i < expectedFrequencies.length; i++) {

            // long soustraction = (long) (lettersFrequencies[i] - expectedFrequencies[i]);
            long soustraction = (long) (expectedFrequencies[i]- lettersFrequencies[i]);
            soustraction *= soustraction;
            soustraction /= expectedFrequencies[i];
            resultat += soustraction;

        }

        return resultat;
    }

    /**
     * Given a ciphertext as a string and a corresponding ciphertext as a byte array,
     * this method performs a brute-force attack to break the Vernam cipher on a single subtext.
     * It computes the chi-square statistic for each possible shift, selects the one that yields the lowest chi-square value,
     * and returns the corresponding shift.
     * @param oneSubText The ciphertext as a string.
     * @param oneSubTextByte The ciphertext as a byte array.
     * @return The shift that yields the lowest chi-square value.
     */
    public static int breakCipher(String oneSubText, byte[] oneSubTextByte) {
        //System.out.println("");
        double[] expectedFrequencies = new double[26];
        for (int i = 0; i < englishLettersProbabilities3.length; i++) {
            expectedFrequencies[i] = oneSubTextByte.length * englishLettersProbabilities3[i];
        }

        double[] tabChiSquare = new double[26];
        char letter = 'A';
        for (int shift = 0; shift < 26; shift++) { //maybe begin with 2, A to Z
            String uncipher = uncipherVernamWithKey(oneSubTextByte, String.valueOf(letter)); // A -> Z
            long[] lettersFrequencies = observedLettersFrequencies(uncipher);
            double chiSquare = chiSquareCompute(expectedFrequencies, lettersFrequencies);
            //System.out.println("Chi square for " + letter + " = " + chiSquare);
            tabChiSquare[shift] = chiSquare;
            letter++;
        }

        // garder tout ce qui est en dessous de 20
        double min = tabChiSquare[0];
        for (int index = 0; index < tabChiSquare.length; index++) {
            if (tabChiSquare[index] < min) {
                min = tabChiSquare[index];
            }
        }

        int shift = 0;
        for (int index = 0; index < tabChiSquare.length; index++) {
            if (tabChiSquare[index] == min) {
                break;
            }
            shift++;
        }
        System.out.println("SHIFT FIND " + shift);

        return shift; // ma clé pour le sous text
    }

    /**
     * This method takes in an array of byte arrays representing the subtexts and an array of shifts.
     * It then converts the shifts into letters, uses them to decrypt each subtext using the Vernam cipher,
     * and returns an array of the decrypted subtexts.
     * @param sousTextByte An array of byte arrays representing the subtexts to be decrypted
     * @param shift An array of integers representing the shifts used in the Vernam cipher
     * @return An array of strings representing the decrypted subtexts
     */
    public static String[] uncipherAllSubtext(byte[][] sousTextByte,int[] shift){
        //1. convertir les shifts en lettre
        char[] keys = new char[shift.length];
        for(int i=0; i < shift.length; i++){
            keys[i] = alphabet.charAt(shift[i]);
        }

        //1.1 Affichage des clé
        System.out.print("ma cle est : " );
        for(int i=0; i < shift.length; i++){
            System.out.print(keys[i]);
        }
        System.out.println("");

        //2. déchiffrer chaque sous text
        String[] sousText = new String[shift.length];
        for(int i=0; i < shift.length; i++){
            sousText[i] = uncipherVernamWithKey(sousTextByte[i],String.valueOf(keys[i]));
        }

        return sousText;

        /*
        //3. Assembler tous les sous text
        //3.0 compute sum length all sub text
        int sumLength = 0;
        for(int num_subText=0; num_subText < sousText.length; num_subText++){
            sumLength+= sousText[num_subText].length();
        }

        String originalTxt = "";
        int index = 0;
        for(int num_subText=0; num_subText < sousText.length && index < sumLength; num_subText++){
            if(num_subText == sousText.length){
                num_subText = 0;
            }

            int posIndex = index*sumLength+num_subText
            originalTxt+= sousText[num_subText].charAt(index);

            index++;
        }

         */
    }

    /**
     * This method takes an array of Caesar ciphered substrings and regroups
     * them into a single string that represents the original plaintext
     * that was encrypted using the Vernam cipher. The method works by
     * "aligning" the substrings based on their position in the original
     * plaintext.
     * @param sousTexteCesar an array of Caesar cipher subtexts
     * @return a string that is the result of regrouping the subtexts
     */
    private static String regroupementDesCesarSousTexte(String[] sousTexteCesar) {
        String uncipherText = "";
        //decalage = 5
        //Parcourir mes sous texte
        // Pour le 1er je donne la val 0 5 10 15 20 a mon texte final 40 cara
        // Pour le 2e je donne la val 1 6 11 16 21                    39 carac
        // Pour le 3e je donne la val 2 7 12 17 22
        // Pour le 4e je donne la val 3 8 13 18 23
        // Pour le 5e je donne la val 4 9 14 19 24
        int tailleUncipherTexte = 0;
        for (String sousTexteCesar1 : sousTexteCesar) {
            tailleUncipherTexte += sousTexteCesar1.length();
        }

        int cpt = 0;
        int nbLettreEncode = 0;
        for (int i = 0; i < tailleUncipherTexte / sousTexteCesar.length || nbLettreEncode != tailleUncipherTexte; i++) {
            for (String sousTexteCesar1 : sousTexteCesar) {
                if (cpt < sousTexteCesar1.length()) {
                    uncipherText += sousTexteCesar1.charAt(cpt);
                    nbLettreEncode++;
                }
            }
            cpt++;
        }

        return uncipherText;
    }

    /*
     for(int index=0; index < cipherByte.length/length || ((index*length)+num_sousText) < cipherByte.length; index++){
                int posCipherByte = (index*length)+num_sousText;
                initedSubText[num_sousText][cpt]+= cipherByte[posCipherByte];
                cpt++;
     */

}
