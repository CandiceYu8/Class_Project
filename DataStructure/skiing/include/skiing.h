#ifndef SKIING_H
#define SKIING_H
#define MAX 10

class skiing
{
    public:
        skiing();
        void PrintLength();
        void SearchMaxLength();
        int MaxLength(int x, int y);
        int ReturnMaxLength();
        virtual ~skiing();
    private:
        int row;
        int col;
        int height[MAX][MAX];
        int length[MAX][MAX];
};

#endif // SKIING_H
