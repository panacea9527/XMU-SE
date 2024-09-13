package com.example.painter;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.scene.shape.Circle;
import javafx.event.ActionEvent;

import java.util.Optional;

public class PainterController
{
    private enum PenSize
    {
        SMALL(2),
        MEDIUM(4),
        LARGE(6);
        private final int radius;
        PenSize(int radius) {this.radius = radius;}
        public int getRadius() {return radius;}
    }

    private enum Shape
    {
        PEN(0), CIRCLE(1), RECTANGLE(2), LINE(3), ERASER(4);
        private final int shapeChoice;
        Shape(int shape)
        {
            this.shapeChoice = shape;
        }
        public int getShapeChoice()
        {
            return shapeChoice;
        }
    }

    @FXML private RadioButton penRadioButton;
    @FXML private RadioButton circleRadioButton;
    @FXML private RadioButton rectangleRadioButton;
    @FXML private RadioButton lineRadioButton;
    @FXML private RadioButton eraserRadioButton;
    @FXML private RadioButton smallRadioButton;
    @FXML private RadioButton mediumRadioButton;
    @FXML private RadioButton largeRadioButton;
    @FXML private Button chooseColorButton;
    @FXML private Pane drawingAreaPane;
    @FXML private ToggleGroup shapeToggleGroup;
    @FXML private ToggleGroup sizeToggleGroup;
    @FXML private Label colorLabel;
    private PenSize radius = PenSize.MEDIUM;
    private Paint brushColor = Color.BLACK;
    private Shape shapeChoice = Shape.PEN;
    private double mouseEnterX;
    private double mouseEnterY;
    private double rectangleWidth;
    private double rectangleHeight;

    public void initialize()
    {
        penRadioButton.setUserData(Shape.PEN);
        circleRadioButton.setUserData(Shape.CIRCLE);
        rectangleRadioButton.setUserData(Shape.RECTANGLE);
        lineRadioButton.setUserData(Shape.LINE);
        eraserRadioButton.setUserData(Shape.ERASER);
        smallRadioButton.setUserData(PenSize.SMALL);
        mediumRadioButton.setUserData(PenSize.MEDIUM);
        largeRadioButton.setUserData(PenSize.LARGE);
    }

    @FXML
    private void drawingWhenMousePressed(MouseEvent e)
    {
        if(e.getX() <= 480 && e.getX() >= 0 && e.getY() >= 0 && e.getY() <= 460)
        {
            mouseEnterX = e.getX();
            mouseEnterY = e.getY();
        }
    }

    @FXML
    private void drawingWhenMouseReleased(MouseEvent e)
    {
        if(e.getX() <= 480 && e.getX() >= 0 && e.getY() >= 0 && e.getY() <= 460)
        {
            if(shapeChoice.getShapeChoice() == 1)
            {
                Circle newCircle = new Circle();
                double radius = Math.sqrt(Math.pow(e.getX() - mouseEnterX, 2) + Math.pow(e.getY() - mouseEnterY, 2));
                newCircle.setCenterX(mouseEnterX);
                newCircle.setCenterY(mouseEnterY);
                newCircle.setRadius(radius);
                newCircle.setStroke(brushColor);
                newCircle.setFill(brushColor);
                newCircle.setStrokeWidth(this.radius.getRadius());
                drawingAreaPane.getChildren().add(newCircle);
            }
            else if(shapeChoice.getShapeChoice() == 2)
            {
                rectangleWidth = Math.abs(e.getX() - mouseEnterX);
                rectangleHeight = Math.abs(e.getY() - mouseEnterY);
                if(mouseEnterX > e.getX())
                {
                    mouseEnterX = e.getX();
                }
                if(mouseEnterY > e.getY())
                {
                    mouseEnterY = e.getY();
                }
                Rectangle newRectangle = new Rectangle(mouseEnterX, mouseEnterY, rectangleWidth, rectangleHeight);
                newRectangle.setStroke(brushColor);
                newRectangle.setFill(brushColor);
                newRectangle.setStrokeWidth(radius.getRadius());
                drawingAreaPane.getChildren().add(newRectangle);
            }
            else if(shapeChoice.getShapeChoice() == 3)
            {
                Line newline = new Line(mouseEnterX, mouseEnterY, e.getX(), e.getY());
                newline.setStroke(brushColor);
                newline.setStrokeWidth(radius.getRadius());
                drawingAreaPane.getChildren().add(newline);
            }
        }
    }

    @FXML
    private void drawingMouseDragged(MouseEvent e)
    {
        if(e.getX() <= 480 && e.getX() >= 0 && e.getY() >= 0 && e.getY() <= 460)
        {
            if(shapeChoice.getShapeChoice() == 0)
            {
                Circle newCircle = new Circle(e.getX(), e.getY(),
                        radius.getRadius(), brushColor);
                drawingAreaPane.getChildren().add(newCircle);
            }
            if(shapeChoice.getShapeChoice() == 4)
            {
                Circle newCircle = new Circle(e.getX(), e.getY(),
                        radius.getRadius(), brushColor);
                newCircle.setStrokeWidth(5 * radius.getRadius());
                newCircle.setStroke(Color.WHITE);
                newCircle.setFill(Color.WHITE);
                drawingAreaPane.getChildren().add(newCircle);
            }
        }
    }

    @FXML
    private void setShapeChoice(ActionEvent e)
    {
        shapeChoice = (Shape) shapeToggleGroup.getSelectedToggle().getUserData();
    }

    @FXML
    private void sizeRadioButtonSelected(ActionEvent e)
    {
        radius = (PenSize) sizeToggleGroup.getSelectedToggle().getUserData();
    }

    @FXML
    private void undoButtonPressed(ActionEvent event)
    {
        int count = drawingAreaPane.getChildren().size();
        if (count > 0) {
            drawingAreaPane.getChildren().remove(count - 1);
        }
    }

    @FXML
    private void clearButtonPressed(ActionEvent event)
    {
        drawingAreaPane.getChildren().clear(); // clear the canvas
    }

    @FXML
    private void chooseColorButtonPressed(ActionEvent event)
    {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Color Choose Dialog");
        alert.setHeaderText("你可以从[Black Red Green Blue]中选取颜色");
        alert.setContentText("选择你喜欢的颜色：");
        ButtonType buttonTypeOne = new ButtonType("Black");
        ButtonType buttonTypeTwo = new ButtonType("Red");
        ButtonType buttonTypeThree = new ButtonType("Green");
        ButtonType buttonTypeFour = new ButtonType("Blue");
        ButtonType buttonTypeCancel = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(buttonTypeOne, buttonTypeTwo, buttonTypeThree, buttonTypeFour, buttonTypeCancel);
        Optional<ButtonType> result = alert.showAndWait();

        if (result.get() == buttonTypeOne)
        {
            brushColor = Color.BLACK;
            colorLabel.setText("Black");
        }
        else if (result.get() == buttonTypeTwo)
        {
            brushColor = Color.RED;
            colorLabel.setText("Red");
        }
        else if (result.get() == buttonTypeThree)
        {
            brushColor = Color.GREEN;
            colorLabel.setText("Green");
        }
        else if (result.get() == buttonTypeFour)
        {
            brushColor = Color.BLUE;
            colorLabel.setText("Blue");
        }
    }
}

