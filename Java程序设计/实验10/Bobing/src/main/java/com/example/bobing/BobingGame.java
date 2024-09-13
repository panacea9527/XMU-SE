package com.example.bobing;

import java.util.Arrays;
import java.util.Random;

public class BobingGame {

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

    public static int[] generateRandomDices() {
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
}
