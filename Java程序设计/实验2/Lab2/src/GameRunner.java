import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class GameRunner {
    private Scanner scanner = new Scanner(System.in);
    private BobingGame game = new BobingGame();
    private Map<Integer, List<String>> playerAndAwards = new HashMap<>();
    private Map<String, Integer> awardCounts = new HashMap<>();
    private Map<String, Integer> awardLimits = new HashMap<>();

    public GameRunner() {
        // 初始化各奖项的份数
        awardLimits.put("状元", 1);
        awardLimits.put("对堂", 2);
        awardLimits.put("三红", 4);
        awardLimits.put("四进", 8);
        awardLimits.put("二举", 16);
        awardLimits.put("一秀", 32);
    }

    public void startGame() {
        System.out.println("请输入玩家数（6-10）：");
        int playerNum = scanner.nextInt();

        while (playerNum < 6 || playerNum > 10) {
            System.out.println("玩家数必须在6到10之间，请重新输入：");
            playerNum = scanner.nextInt();
        }

        for (int i = 1; i <= playerNum; i++) {
            playerAndAwards.put(i, new ArrayList<>());
        }

        int currentPlayer = 1;
        while (!areAllAwardsDistributed()) {
            currentPlayer = currentPlayer > playerNum ? 1 : currentPlayer;
            String result = game.playGame();
            handleResult(currentPlayer, result);
            currentPlayer++;
        }

        printGameResults();
    }

    private boolean areAllAwardsDistributed() {
        for (Map.Entry<String, Integer> entry : awardLimits.entrySet()) {
            if (!awardCounts.containsKey(entry.getKey()) || awardCounts.get(entry.getKey()) < entry.getValue()) {
                return false;
            }
        }
        return true;
    }

    private void handleResult(int player, String result) {
        List<String> results = parseResult(result);
        for (String award : results) {
            if (awardCounts.getOrDefault(award, 0) < awardLimits.getOrDefault(award, 0)) {
                playerAndAwards.get(player).add(award);
                awardCounts.put(award, awardCounts.getOrDefault(award, 0) + 1);
            }
        }
    }

    // 解析结果字符串，包括处理特殊情况
    private List<String> parseResult(String result) {
        List<String> awards = new ArrayList<>();
        List<String> zhuangYuanCases = Arrays.asList("五王", "状元", "遍地锦", "六勃黑", "六勃红", "状元插金花", "五子");
        // 检查是否包含"带"字样，如果包含，则分割字符串处理
        if (result.contains("带")) {
            String[] parts = result.split("带");
            // 检查第一部分是否属于特殊状元情况
            if (zhuangYuanCases.contains(parts[0])) {
                awards.add("状元"); // 添加"状元"奖项
            }
            else{
            awards.add(parts[0]);
            }
            awards.add(parts[1]);
        } else {
            if (zhuangYuanCases.contains(result))
                awards.add("状元");
                else
                awards.add(result);
        }
        return awards;
    }

    // 输出游戏结束后的奖项统计和各玩家所获奖项
    private void printGameResults() {
        System.out.println("\n游戏结束，各玩家所获奖项如下：");
        playerAndAwards.forEach((player, awards) -> {
            System.out.printf("玩家 %d: ", player);
            if (awards.isEmpty()) {
                System.out.println("未获奖");
            } else {
                awards.forEach(award -> System.out.printf("%s ", award));
                System.out.println();
            }
        });
    }

}
