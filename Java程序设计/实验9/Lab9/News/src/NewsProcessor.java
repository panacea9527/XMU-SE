import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NewsProcessor {

    public static void main(String[] args) {
        String newsText = "PITTSBURGH (AP) — Carnegie Mellon University will hire a researcher from the Library of Congress to help it decode a collection that includes two WWII German Enigma machines.\n" +
                "The university wants to encourage the study of 19th and 20th century computers, calculators, encryption machines and other materials related to the history of computer science.\n" +
                "“When we look back and we see this, we see who we remember,” Andrew Moore, dean of CMU’s School of Computer Science, said, adding his students are increasingly asking for courses about the history of the field. “We see people who took technology to save lives and save the world.”\n" +
                "Pamela McCorduck, a prolific author on the history and future of artificial intelligence and the widow of Joseph Traub, a renowned computer scientist and the former head of CMU’s Computer Science Department, permanently loaned to the university a collection of early computers, books and letters. The collection, anchored by a three-rotor and four-rotor Enigma machine, is on display in the Fine and Rare Book Room in CMU’s Hunt Library in Oakland. The gift makes CMU one of a few institutions in the United States with Enigma machines. Even fewer display them.\n";
        printUniqueWords(newsText);
        printSentencesContainingThe(newsText);
    }

    private static void printUniqueWords(String text) {
        Set<String> uniqueWords = new HashSet<>();
        String[] words = text.toLowerCase().split("\\W+");
        for (String word : words) {
            uniqueWords.add(word);
        }

        System.out.println("新闻中不重复的单词:");
        uniqueWords.forEach(System.out::println);
    }

    private static void printSentencesContainingThe(String text) {
        Pattern pattern = Pattern.compile("[^.!?]+(?:[.!?](?!['\"]?\\s|$)[^.!?]*)*[.!?]?['\"]?(?=\\s|$)", Pattern.MULTILINE);
        Matcher matcher = pattern.matcher(text);

        System.out.println("新闻中包含单词‘the’的句子:");
        int count=1;
        while (matcher.find()) {
            String sentence = matcher.group();
            if (sentence.toLowerCase().contains(" the ")) {
                System.out.println(count+":"+sentence.trim());
                count++;
            }
        }
    }
}

