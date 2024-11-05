// square.h
#ifndef SQUARE_H
#define SQUARE_H

class square {
private:
    int value = 0;

public:
    square() = default;
    explicit square(int val) : value(val) {}


    int GetValue() const;

    void SetValue(int val);
};

#endif // SQUARE_H