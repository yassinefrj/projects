import java.util.stream.IntStream;

public class Cesar {

    static String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /**
     * This method ciphers a given text using the Caesar cipher and a given key.
     * It shifts each letter of the text by the value of the key.
     * The key can be negative, in which case it takes the absolute value of the key.
     * @param textToCipher the text to cipher.
     * @param keyIndex the key to use for the cipher.
     * @return the ciphered text.
     */
    public static String cipherCesarWithKey(String textToCipher, int keyIndex) {
        if (keyIndex < 0) {
            keyIndex = -keyIndex;
        }
        String cipherText = "";

        for (int i = 0; i < textToCipher.length(); i++) {
            for (int j = 0; j < alphabet.length(); j++) {
                if (textToCipher.toUpperCase().charAt(i)
                        == alphabet.toUpperCase().charAt(j)) {
                    cipherText += alphabet.toLowerCase().charAt((j + keyIndex) % 26);
                }

            }
        }
        return cipherText;
    }

    /**
     * Decode a ciphered text using cipher with the key Use the algo To cipher
     * and make sure that the key is in the range of 0-26
     *
     * @param cipheredText
     * @param keyIndex the size of the offset
     * @return the orginal plain tex
     */
    public static String uncipherCesarWithKey(String cipheredText, int keyIndex) {
        return cipherCesarWithKey(cipheredText,
                alphabet.length() - (keyIndex % 26));
    }

    /**
     * Propabilité d'appartion de chaque lettre de l'alaphabet anglais.
     */
    static double[] englishLettersProbabilities = {0.073, 0.009, 0.030, 0.044, 0.130, 0.028, 0.016, 0.035, 0.074,
            0.002, 0.003, 0.035, 0.025, 0.078, 0.074, 0.027, 0.003,
            0.077, 0.063, 0.093, 0.027, 0.013, 0.016, 0.005, 0.019, 0.001};

    /**
     * Given a ciphertext as a string and a corresponding ciphertext as a byte array,
     * this method performs a brute-force attack to break the Vernam cipher on a single subtext.
     * It computes the chi-square statistic for each possible shift, selects the one that yields the lowest chi-square value,
     * and returns the corresponding shift.
     * @param oneSubText The ciphertext as a string.
     * @param oneSubTextByte The ciphertext as a byte array.
     * @return The shift that yields the lowest chi-square value.
     */
    public static int breakCipher(String message) {
        double[] expectedFrequencies = new double[26];
        for (int i = 0; i < englishLettersProbabilities.length; i++) {
            expectedFrequencies[i] = message.length() * englishLettersProbabilities[i];
        }

        double[] tabChiSquare = new double[26];
        for (int shift = 0; shift < 26; shift++) {
            String uncipher = uncipherCesarWithKey(message, shift);
            long[] lettersFrequencies = observedLettersFrequencies(uncipher);
            double chiSquare = chiSquareCompute(expectedFrequencies, lettersFrequencies);
            tabChiSquare[shift] = chiSquare;
        }

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
        System.out.println("SHIFT FIND = " + shift);

        return shift;
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
     * This method returns an array of frequencies of observed letters in the input message.
     * @param message the string to analyze.
     * @return an array of longs, where each element represents the frequency of a letter in the message.
     */
    public static long[] observedLettersFrequencies(String message) {
        return IntStream.rangeClosed('a', 'z')
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

}

