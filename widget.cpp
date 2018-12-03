#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    // Initialize the score to zero
    score = 0;
    
    // Initialize game grid with all zeros
    for (int i = 0; i < 4; i++){
        std::vector<int> row (4, 0);
        grid.push_back(row);
    }
    
    // Add two random 2's onto the game board at unique random positions.
    srand(time(NULL));
    newTile();
    newTile();
    
    // Display the starting board
    updateBoard();
    
    // Create borders around game tiles
    ui->label->setStyleSheet("border: 1px solid black");
    ui->label_2->setStyleSheet("border: 1px solid black");
    ui->label_3->setStyleSheet("border: 1px solid black");
    ui->label_4->setStyleSheet("border: 1px solid black");
    ui->label_5->setStyleSheet("border: 1px solid black");
    ui->label_6->setStyleSheet("border: 1px solid black");
    ui->label_7->setStyleSheet("border: 1px solid black");
    ui->label_8->setStyleSheet("border: 1px solid black");
    ui->label_9->setStyleSheet("border: 1px solid black");
    ui->label_10->setStyleSheet("border: 1px solid black");
    ui->label_11->setStyleSheet("border: 1px solid black");
    ui->label_12->setStyleSheet("border: 1px solid black");
    ui->label_13->setStyleSheet("border: 1px solid black");
    ui->label_14->setStyleSheet("border: 1px solid black");
    ui->label_15->setStyleSheet("border: 1px solid black");
    ui->label_16->setStyleSheet("border: 1px solid black");
    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newTile(){
    // get random row and column to place new tile at
    int row = rand() % 4;
    int col = rand() % 4;
    // Keep trying new random points until there is an empty one to place the tile at
    if (!lost()){
        while (grid[row][col] != 0){
            row = rand() % 4;
            col = rand() % 4;
        }
        grid[row][col] = 2;
    }
}

void Widget::updateBoard()
{
    if (lost()){
        ui->label_19->setText("You lost!");
    } else {
        if (grid[0][0] > 0){
            ui->label->setNum(grid[0][0]);
        }
        else {
            ui->label->setText("");
        }
        
        if (grid[0][1] > 0){
            ui->label_2->setNum(grid[0][1]);
        }
        else {
            ui->label_2->setText("");
        }
        
        if (grid[0][2] > 0){
            ui->label_3->setNum(grid[0][2]);
        }
        else {
            ui->label_3->setText("");
        }
        
        if (grid[0][3] > 0){
            ui->label_4->setNum(grid[0][3]);
        }
        else {
            ui->label_4->setText("");
        }
        
        if (grid[1][0] > 0){
            ui->label_5->setNum(grid[1][0]);
        }
        else {
            ui->label_5->setText("");
        }
        
        if (grid[1][1] > 0){
            ui->label_6->setNum(grid[1][1]);
        }
        else {
            ui->label_6->setText("");
        }
        
        if (grid[1][2] > 0){
            ui->label_7->setNum(grid[1][2]);
        }
        else {
            ui->label_7->setText("");
        }
        
        if (grid[1][3] > 0){
            ui->label_8->setNum(grid[1][3]);
        }
        else {
            ui->label_8->setText("");
        }
        
        if (grid[2][0] > 0){
            ui->label_9->setNum(grid[2][0]);
        }
        else {
            ui->label_9->setText("");
        }
        
        if (grid[2][1] > 0){
            ui->label_10->setNum(grid[2][1]);
        }
        else {
            ui->label_10->setText("");
        }
        
        if (grid[2][2] > 0){
            ui->label_11->setNum(grid[2][2]);
        }
        else {
            ui->label_11->setText("");
        }
        
        if (grid[2][3] > 0){
            ui->label_12->setNum(grid[2][3]);
        }
        else {
            ui->label_12->setText("");
        }
        
        if (grid[3][0] > 0){
            ui->label_13->setNum(grid[3][0]);
        }
        else {
            ui->label_13->setText("");
        }
        
        if (grid[3][1] > 0){
            ui->label_14->setNum(grid[3][1]);
        }
        else {
            ui->label_14->setText("");
        }
        
        if (grid[3][2] > 0){
            ui->label_15->setNum(grid[3][2]);
        }
        else {
            ui->label_15->setText("");
        }
        
        if (grid[3][3] > 0){
            ui->label_16->setNum(grid[3][3]);
        }
        else {
            ui->label_16->setText("");
        }
        ui->label_18->setNum(score);
    }
}

void Widget::shiftUp()
{
    // in each column, shift all elements up, then work way back down combining and shifting
    for (int j = 0; j < 4; j++){
        // starting from top and moving down
        for (int i = 1; i < 4; i++){
            if (grid[i][j] != 0){
                // shift all the way up as long as the value above is zero
                for (int k = 1; i - k >= 0 && grid[i-k][j] == 0; k++){
                    grid[i-k][j] = grid[i-k+1][j];
                    grid[i-k+1][j] = 0;
                }
            }
        }
        // now combining back down
        for (int i = 1; i < 4; i++){
            if (grid[i][j] != 0){
                if (grid[i][j] == grid[i-1][j]){
                    grid[i-1][j] *= 2;
                    score += grid[i-1][j];
                    for (int k = i; k < 3; k++){
                        grid[k][j] = grid[k+1][j];
                    }
                    grid[3][j] = 0;
                }
            }
        }
    }
}

void Widget::shiftLeft()
{
    // in each row, shift all elements to left, then work way back to right combining and shifting
    for (int i = 0; i < 4; i++){
        for (int j = 1; j <= 3; j++){
            // if the current slot is not empty
            if (grid[i][j] != 0){
                // shift is all the way left as long as the value to the left is zero
                for (int k = 1; j - k >= 0 && grid[i][j-k] == 0; k++){
                    grid[i][j-k] = grid[i][j-k+1];
                    grid[i][j-k+1] = 0;
                }
            }
        }
        // now combine like numbers back across row
        for (int j = 1; j <= 3; j++){
            // if the current slot is not empty
            if (grid[i][j] != 0){
                if (grid[i][j] == grid[i][j-1]){
                    grid[i][j-1] *= 2;
                    score += grid[i][j-1];
                    for (int k = j; k < 3; k++){
                        grid[i][k] = grid[i][k+1];
                    }
                    grid[i][3] = 0;
                }
            }
        }
    }
}

void Widget::shiftRight()
{
    //in each row, shift all elements to right, then work way back to left combining and shifting
    for (int i = 0; i < 4; i++){
        // starting on right and working left
        for (int j = 2; j >= 0; j--){
            // if the current slot is not empty
            if (grid[i][j] != 0){
                // shift it all the way right as long as the value to the right is zero
                for (int k = 1; j + k < 4 && grid[i][j+k] == 0; k++){
                    grid[i][j+k] = grid[i][j+k-1];
                    grid[i][j+k-1] = 0;
                }
            }
        }
        // now combine like numbers backward across row
        for (int j = 2; j >= 0; j--){
            // if the current slot is not empty
            if (grid[i][j] != 0){
                // if the current slot is equal to the slot to the right,
                // combine them and shift all values right by one
                if (grid[i][j] == grid[i][j+1]){
                    grid[i][j+1] *= 2;
                    score += grid[i][j+1];
                    for (int k = j; k > 0; k--){
                        grid[i][k] = grid[i][k-1];
                    }
                    grid[i][0] = 0;
                }
            }
        }
    }
    
}

void Widget::shiftDown()
{
    // in each column, shift elements down, then work way back up combining
    for (int j = 0; j < 4; j++){
        for (int i = 2; i >= 0; i--){
            if (grid[i][j] != 0){
                // shift all the way down as long as values below are zero
                for (int k = 1; i + k < 4 && grid[i+k][j] == 0; k++){
                    grid[i+k][j] = grid[i+k-1][j];
                    grid[i+k-1][j] = 0;
                }
            }
        }
        // now recombine back up
        for (int i = 2; i >= 0; i--){
            if (grid[i][j] != 0){
                if (grid[i][j] == grid[i+1][j]){
                    grid[i+1][j] *= 2;
                    score += grid[i+1][j];
                    for (int k = i; k > 0; k--){
                        grid[k][j] = grid[k-1][j];
                    }
                    grid[0][j] = 0;
                }
            }
        }
    }
}

void Widget::on_pushButton_4_clicked()
{
    shiftDown();
    newTile();
    updateBoard();
}

void Widget::on_pushButton_2_clicked()
{
    shiftLeft();
    newTile();
    updateBoard();
}

void Widget::on_pushButton_clicked()
{
    
    shiftUp();
    newTile();
    updateBoard();
}

void Widget::on_pushButton_3_clicked()
{
    shiftRight();
    newTile();
    updateBoard();
}

bool Widget::lost(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (grid[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}
