#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    // Adds a new tile to the game grid
    void newTile();
    // Updates the labels on the board to reflect the current grid
    void updateBoard();
    // Shifts all the numbers up
    void shiftUp();
    // Shifts all the numbers left
    void shiftLeft();
    // Shifts all the numbers right
    void shiftRight();
    // Shifts all the numbers down
    void shiftDown();
    
    // Checks if the player has lost
    bool lost();
    
    private slots:
    void on_pushButton_4_clicked();
    
    void on_pushButton_2_clicked();
    
    void on_pushButton_clicked();
    
    void on_pushButton_3_clicked();
    
private:
    Ui::Widget *ui;
    int score;
    // In retrospect, I should've used an array since my game grid is fixed size.
    std::vector<std::vector<int>> grid;
};

#endif // WIDGET_H
