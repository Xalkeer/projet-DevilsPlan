// square.h
#ifndef SQUARE_H
#define SQUARE_H

class square {
private:
    int value = 0;
    char turn = ' ';

public:
    square(int val, char turn) ;
    int GetValue() const;

    void SetValue(int val);

    char GetTurn() const;

    void SetTurn(char t);
};

#endif // SQUARE_H