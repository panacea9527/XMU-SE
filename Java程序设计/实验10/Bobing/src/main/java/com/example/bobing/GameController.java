package com.example.bobing;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Label;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GameController {

    @FXML
    private TextField numberInput;
    @FXML
    private Button startButton;
    @FXML
    private Button restartButton;
    @FXML
    private TextArea outputArea;
    @FXML
    private Label promptLabel;

    private BobingGame game = new BobingGame();
    private Map<Integer, List<String>> playerAndAwards = new HashMap<>();
    private Map<String, Integer> awardCounts = new HashMap<>();
    private Map<String, Integer> awardLimits = new HashMap<>();

    public GameController() {
        // 初始化各奖项的份数
        awardLimits.put("状元", 1);
        awardLimits.put("对堂", 2);
        awardLimits.put("三红", 4);
        awardLimits.put("四进", 8);
        awardLimits.put("二举", 16);
        awardLimits.put("一秀", 32);
    }

    @FXML
    public void initialize() {
        restartButton.setDisable(true);  // Initially disable the restart button
    }

    @FXML
    private void handleStartGame() {
        int playerNum;
        try {
            playerNum = Integer.parseInt(numberInput.getText());
            if (playerNum < 6 || playerNum > 10) {
                outputArea.setText("玩家数必须在6到10之间，请重新输入。");
                return;
            }
        } catch (NumberFormatException e) {
            outputArea.setText("请输入有效的数字。");
            return;
        }

        outputArea.setText(""); // 清空输出区域
        initializeGame(playerNum);
        int currentPlayer = 1;
        while (!areAllAwardsDistributed()) {
            currentPlayer = currentPlayer > playerNum ? 1 : currentPlayer;
            String result = game.playGame();
            handleResult(currentPlayer, result);
            currentPlayer++;
        }

        printGameResults();
        startButton.setDisable(true);
        restartButton.setDisable(false);
    }

    private void initializeGame(int playerNum) {
        playerAndAwards.clear();
        awardCounts.clear();
        for (int i = 1; i <= playerNum; i++) {
            playerAndAwards.put(i, new ArrayList<>());
        }
    }

    private boolean areAllAwardsDistributed() {
        return awardLimits.entrySet().stream().allMatch(entry ->
                awardCounts.getOrDefault(entry.getKey(), 0) >= entry.getValue());
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

    private List<String> parseResult(String result) {
        List<String> awards = new ArrayList<>();
        List<String> zhuangYuanCases = Arrays.asList("五王", "状元", "遍地锦", "六勃黑", "六勃红", "状元插金花", "五子");
        if (result.contains("带")) {
            String[] parts = result.split("带");
            if (zhuangYuanCases.contains(parts[0])) {
                awards.add("状元");
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

    private void printGameResults() {
        StringBuilder results = new StringBuilder("\n游戏结束，各玩家所获奖项如下：\n");
        playerAndAwards.forEach((player, awards) -> {
            results.append("玩家 ").append(player).append(": ");
            if (awards.isEmpty()) {
                results.append("未获奖\n");
            } else {
                awards.forEach(award -> results.append(award).append(" "));
                results.append("\n");
            }
        });
        outputArea.setText(results.toString());
    }

    @FXML
    private void handleRestartGame() {
        outputArea.setText("");
        numberInput.setText("");
        startButton.setDisable(false);
        restartButton.setDisable(true);
    }
}
