/**
 * Vigenere class
 */
public class Vigenere {
    static String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /**
     * Encode a plain text with Vigenere Algo : 1. Genere a key that has the
     * same length that the text 2.
     *
     * @param textToCipher the text to cipher
     * @param key to use to cipher
     * @return the ciphered Text
     */
    public static String cipherVigenereWithKey(String textToCipher, String key) {
        key = generateVigenereKey(textToCipher, key);
        if (key == null) {
            System.out.println("The key need a minus size or equals that the Plain Text");
            return "";
        }
        String cipher_text = "";

        for (int i = 0; i < textToCipher.length(); i++) {
            int indexText = 0;
            int indexKey = 0;

            for (int j = 0; j < alphabet.length(); j++) {
                if (alphabet.charAt(j) == textToCipher.toUpperCase().charAt(i)) {
                    break;
                }
                indexText++;
            }
            for (int j = 0; j < alphabet.length(); j++) {
                if (alphabet.charAt(j) == key.toUpperCase().charAt(i)) {
                    break;
                }
                indexKey++;
            }
            cipher_text += alphabet.charAt((indexText + indexKey) % 26);
        }

        return cipher_text;
    }

    /**
     * Decode a ciphered text with Vigenere algo
     *
     * @param cipherText the ciphered text
     * @param key the key used to cipher
     * @return the original text
     */
    public static String uncipherVigenereWithKey(String cipherText, String key) {
        String orig_text = "";
        key = generateVigenereKey(cipherText, key);

        for (int i = 0; i < cipherText.length(); i++) {
            int indexCipherText = 0;
            int indexKey = 0;

            for (int j = 0; j < alphabet.length(); j++) {
                if (alphabet.charAt(j) == cipherText.toUpperCase().charAt(i)) {
                    break;
                }
                indexCipherText++;
            }
            for (int j = 0; j < alphabet.length(); j++) {
                if (alphabet.charAt(j) == key.toUpperCase().charAt(i)) {
                    break;
                }
                indexKey++;
            }
            orig_text += alphabet.charAt((alphabet.length() + (indexCipherText - indexKey)) % 26);
        }
        return orig_text;
    }

    /**
     * Generate a key that have the same length of the key
     *
     * @param plainText the plainText used
     * @param key has to have a length smaller that the plainText length
     * @return the generate key
     */
    private static String generateVigenereKey(String plainText, String key) {
        int plainLength = plainText.length();
        if (key.length() > plainText.length()) {
            return null;
        }
        int index = 0;
        while (key.length() != plainText.length()) {
            if (plainLength == index) {
                index = 0;
            }
            key += key.charAt(index);
            index++;
        }
        return key;
    }

    /**
     * Divides a given string into substrings based on a given shift value.
     *
     * @param texte    the text to divide into substrings
     * @param decalage the shift value used to divide the text
     * @return an array of substrings obtained by taking every decalage-th character from the original text
     */
    private static String[] divisionSousTexte(String texte, int decalage) {
        String[] resultat = new String[decalage];
        for (int i = 0; i < decalage; i++) {
            int start = i;
            resultat[i] = "";
            for (int j = start; j < texte.length(); j += decalage) {
                resultat[i] += texte.charAt(j);
            }
        }

        return resultat;
    }

    /**
     * number of division choose
     */
    static final int nombreDeDivision = 25;

    /**
     * Divides a given text into a 2D array of substrings, where each substring is obtained by taking
     * every k-th character from the original text, where k ranges from 0 to the length of the text minus 1.
     *
     * @param texte the text to divide into a 2D array of substrings
     * @return a square matrix of substrings, where each row corresponds to a different value of k
     */
    private static String[][] divisionEnGroupeDeSousTexte(String texte) {
        //Initialisation
        String[][] resultatDivision = new String[nombreDeDivision][nombreDeDivision];
        for (int i = 0; i < resultatDivision.length; i++) {
            for (int j = 0; j < resultatDivision.length; j++) {
                resultatDivision[i][j] = "";
            }
        }

        //Division en k sous texte
        for (int k = 0; k < nombreDeDivision; k++) {
            resultatDivision[k] = divisionSousTexte(texte, k);
        }

        //Affichage des k sous textes avec leurs enfants
        return resultatDivision;
    }

    //coincidenceAnalysis

    /**
     * Computes the coincidence of each subtext and stores the result in a 2d array.
     * @param resulatDivision The 2d array containing the subtexts to analyze.
     * @return A 2d array of doubles containing the match results for each subtext.
     */
    private static double[][] calculCoincidence(String[][] resultatDivision) {
        double[][] resultatCoincidence = new double[nombreDeDivision][nombreDeDivision];
        for (int i = 0; i < resultatCoincidence.length; i++) {
            for (int j = 0; j < resultatCoincidence[i].length; j++) {
                resultatCoincidence[i][j] = 0.0;
            }
        }

        for (int i = 0; i < resultatDivision.length; i++) {
            for (int j = 0; j < resultatDivision[i].length; j++) {
                resultatCoincidence[i][j] = Utils.coincidenceAnalysis(resultatDivision[i][j]);
            }
        }

        return resultatCoincidence;
        //moyenne par groupe.
    }

    /**
     * Computes the average coincidence value for each group of subtexts.
     * @param resultatCoincidence the coincidence values for each subtext in each group
     * @return the average coincidence value for each group of subtexts
     */
    private static double[] moyenneCoincidenceParGroupe(double[][] resultatCoincidence) {
        double[] resultatFinaux = new double[nombreDeDivision];
        double moyenne = 0;
        double sum = 0;
        int cpt = 0;

        for (int i = 0; i < resultatCoincidence.length; i++) {

            cpt = 0;
            sum = 0;
            for (int j = 0; j < resultatCoincidence[i].length; j++) {
                sum += resultatCoincidence[i][j];
                if (resultatCoincidence[i][j] != 0.0) {
                    cpt++;
                }

            }
            moyenne = sum / cpt;
            resultatFinaux[i] = moyenne;
        }

        return resultatFinaux;
    }

    /**
     * Returns the index of the first potential Caesar cipher shift based on the mean coincidence analysis
     * of each group of substrings.
     * @param resultatFinaux The array of mean coincidence analysis results for each group of substrings.
     * @return The index of the first potential Caesar cipher shift, or -1 if none is found.
     */
    private static int getFirstIndiceCesar(double[] resultatFinaux) {
        for (int length = 0; length < resultatFinaux.length; length++) {
            if (resultatFinaux[length] >= 0.058) {
                return length;
            }
        }
        return -1; //si ce retour est detecté alors bug
    }

    //divisionSousTexte

    /**
     * Splits the given text into substrings based on a given shift value, and decrypts each substring using the Caesar cipher.
     * @param texte the text to be split and decrypted
     * @param decalage the shift value for splitting the text
     * @return an array of decrypted substrings
     */
    public static String[] getSousTexteCesar(String texte, int decalage) {
        String[] sousTexteCesar = divisionSousTexte(texte, decalage);
        for (int i = 0; i < sousTexteCesar.length; i++) {
            String texteToDecrypt = sousTexteCesar[i];
            sousTexteCesar[i] = Cesar.uncipherCesarWithKey(texteToDecrypt, Cesar.breakCipher(texteToDecrypt));
        }

        return sousTexteCesar;
    }

    /**
     * This method takes an array of Caesar ciphered substrings and regroups them into a single string by interleaving
     * their characters based on their positions in the substrings. The resulting string is the plain text version of
     * the ciphered text. This method assumes that the substrings were generated using the same Caesar cipher key.
     * @param sousTexteCesar the array of Caesar ciphered substrings to regroup
     * @return the plain text version of the ciphered text obtained by interleaving the characters of the substrings
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

    public static String uncipherVignereWithoutKey(String cipherTxt) {
        String[][] groupeSousTexte = divisionEnGroupeDeSousTexte(cipherTxt);
        double[][] groupeDeCoincidence = calculCoincidence(groupeSousTexte);
        double[] resultatFinaux = moyenneCoincidenceParGroupe(groupeDeCoincidence);
        int indexCesar = getFirstIndiceCesar(resultatFinaux);
        String[] sousTexteCesar = getSousTexteCesar(cipherTxt, indexCesar);
        String uncipher = regroupementDesCesarSousTexte(sousTexteCesar);
        return uncipher;
    }

}
