import java.util.Arrays;
import java.util.Random;

class BobingGame {
    public static String judgeAward(int[] dices) {
        Arrays.sort(dices);
        int[] count = new int[7];
        for (int dice : dices) {
            count[dice]++;
        }

        // 判断是否为六勃
        if (count[1] == 6) return "遍地锦";
        if (count[4] == 6) return "六勃黑";
        if (Arrays.equals(count, new int[]{0, 0, 0, 0, 0, 0, 6})) return "六勃红";

        // 判断状元
        if (count[4] == 4) {
            if(count[1] == 2)
                return "状元带金花";
            else
                return "状元";
        }

        // 判断是否为对堂
        if (dices[0] == 1 && dices[1] == 2 && dices[2] == 3 && dices[3] == 4 && dices[4] == 5 && dices[5] == 6)
            return "对堂";

        // 判断五王
        if (count[4] == 5) return "五王";

        // 判断五子（包括五子带一秀）
        for (int i = 1; i <= 6; i++) {
            if (i != 4 && count[i] == 5) {
                if (count[4] == 1) return "五子带一秀";
                return "五子";
            }
        }

        // 判断四进
        for (int i = 1; i <= 6; i++) {
            if (count[i] == 4) {
                // 四进带一秀或四进带二举
                if (count[4] == 1) return "四进带一秀";
                if (count[4] == 2) return "四进带二举";
                return "四进";
            }
        }

        // 判断三红
        if (count[4] == 3) return "三红";

        // 判断二举
        if (count[4] == 2) return "二举";

        // 判断一秀
        if (count[4] == 1) return "一秀";

        // 默认情况
        return "谢谢参与";
    }


    private static int[] generateRandomDices() {
        Random rand = new Random();
        int[] dices = new int[6];
        for (int i = 0; i < 6; i++) {
            dices[i] = rand.nextInt(6) + 1;
        }
        return dices;
    }

    public String playGame()
    {
        return judgeAward(generateRandomDices());
    }

    public static void testJudgeAward() {
        assert "遍地锦".equals(judgeAward(new int[]{1, 1, 1, 1, 1, 1})) : "Test for 遍地锦 failed.";

        assert "六勃黑".equals(judgeAward(new int[]{4, 4, 4, 4, 4, 4})) : "Test for 六勃黑 failed.";

        assert "状元带金花".equals(judgeAward(new int[]{1, 4, 1, 4, 4, 4})) : "Test for 状元带金花 failed.";

        assert "对堂".equals(judgeAward(new int[]{1, 2, 3, 6, 5, 4})) : "Test for 对堂 failed.";

        assert "五王".equals(judgeAward(new int[]{4, 4, 4, 2, 4, 4})) : "Test for 五王 failed.";

        assert "五子带一秀".equals(judgeAward(new int[]{2, 4, 2, 2, 2, 2})) : "Test for 五子带一秀 failed.";

        assert "四进带一秀".equals(judgeAward(new int[]{3, 2, 3, 3, 4, 3})) : "Test for 四进带一秀 failed.";

        assert "三红".equals(judgeAward(new int[]{4, 2, 4, 4, 2, 3})) : "Test for 三红 failed.";

        assert "二举".equals(judgeAward(new int[]{4, 3, 2, 4, 3, 5})) : "Test for 二举 failed.";

        assert "一秀".equals(judgeAward(new int[]{4, 2, 3, 5, 6, 1})) : "Test for 一秀 failed.";

        assert "谢谢参与".equals(judgeAward(new int[]{2, 3, 5, 6, 1, 3})) : "Test for 谢谢参与 failed.";

        System.out.println("All tests passed.");
    }
}
