int countBattleships(char** board, int boardSize, int* boardColSize)
{
    int res = 0;
    int row = boardSize;
    int col = boardColSize[0];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'X') {
                if (i > 0 && board[i - 1][j] == 'X') {
                    continue;
                }
                if (j > 0 && board[i][j - 1] == 'X') {
                    continue;
                }
                res++;
            }
        }
    }
    return res;
}
