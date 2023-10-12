import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

/**
 *
 * @author ymk
 */
public class Utils {
    static String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /**
     * Counts the occurences of each letters of the alphabet.
     *
     * @param cipherText the string to count.
     * @return the hashmap (key,value) of the number of occurence of each
     * alphabet letter.
     */
    public static HashMap countOccurencesLetter(String cipherText) {
        HashMap<Character, Integer> occurrencies = new HashMap<>(); // key - value

        //Setting all the letter of the alphabet at value 0.
        for (int i = 0; i < alphabet.length(); i++) {
            occurrencies.put(alphabet.toLowerCase().charAt(i), 0);
        }

        //Transform the alphabet String to char array.
        char[] cipherChar = cipherText.toCharArray();
        for (int indexLetter = 0; indexLetter < cipherChar.length; indexLetter++) {
            char letter = cipherChar[indexLetter];
            //If the the key is equals to the letter of the array , increment
            // increment the occurencies for each letter.
            occurrencies.put(letter, occurrencies.get(letter) + 1);
        }
        return occurrencies;
    }

    /**
     * get the key from the value.
     *
     * Credits to :
     * https://www.delftstack.com/howto/java/how-to-get-key-from-value-in-java-hashmap/
     *
     * @param <K>
     * @param <V>
     * @param map
     * @param value
     * @return
     */
    public static <K, V> K getSingleKeyFromValue(Map<K, V> map, V value) {
        for (Map.Entry<K, V> entry : map.entrySet()) {
            if (Objects.equals(value, entry.getValue())) {
                return entry.getKey();
            }
        }
        return null;
    }

    /**
     *This method performs a coincidence analysis on a given cipher text.
     * It calculates the coincidence index of the text, which is the probability that two randomly selected
     * letters in the text are the same. The coincidence index is calculated by summing the square of the
     * number of times each letter appears in the text, and then dividing by the product of the text length
     * and the text length minus 1.
     * @param cipherText the encrypted message.
     * @return the coincidence index of the message.
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
     * This method calculates the number of times a given letter appears in a given text.
     * It counts the number of times the letter appears in the text, ignoring case.
     * @param cipherText the text to search for the letter.
     * @param letter the letter to search for.
     * @return the number of times the letter appears in the text.
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

}