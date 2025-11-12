//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_POSITION_H
#define SOKOBANGAME_POSITION_H
struct Position {
public:
    Position(const int row, const int col): _row(row), _col(col) {}

    int getRow() const { return _row; }
    int getCol() const { return _col; }
    void setRow(const int row) { _row = row; }
    void setCol(const int col) { _col = col; }

protected:
    int _row;
    int _col;
};
#endif //SOKOBANGAME_POSITION_H