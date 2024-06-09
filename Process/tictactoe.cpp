#include <iostream>
#include <vector>
#include <csignal>
#include <atomic>

using namespace std;

enum class Player
{
    None,
    X,
    O
};

class TicTacToe
{
public:
    TicTacToe();
    void playGame();

private:
    void printBoard();
    bool makeMove(int row, int col);
    Player checkWinner();
    void switchPlayer();

    vector<vector<Player>> board;
    Player currentPlayer;

    static void signalHandler(int signal);
    static atomic<bool> stopFlag; // Cờ dừng
};

atomic<bool> TicTacToe::stopFlag(false); // Khởi tạo cờ dừng

TicTacToe::TicTacToe()
    : board(3, vector<Player>(3, Player::None)), currentPlayer(Player::X) {}

void TicTacToe::playGame()
{
    // Đăng ký xử lý tín hiệu
    signal(SIGINT, TicTacToe::signalHandler);

    Player winner = Player::None;
    int moveCount = 0;

    while (winner == Player::None && moveCount < 9 && !stopFlag)
    {
        printBoard();
        if (stopFlag) // Kiểm tra cờ sau khi in bảng
        {
            break;
        }

        int row, col;
        cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << ", enter your move (row and column): ";
        cin >> row >> col;

        if (stopFlag) // Kiểm tra cờ sau khi nhận nhập liệu
        {
            break;
        }

        // Chuyển đổi từ chỉ mục người dùng nhập (1-3) sang chỉ mục mảng (0-2)
        if (makeMove(row - 1, col - 1))
        {
            winner = checkWinner();
            if (winner == Player::None)
            {
                switchPlayer();
                moveCount++;
            }
        }
        else
        {
            cout << "Invalid move. Try again." << endl;
        }
    }

    if (stopFlag)
    {
        cout << "\nGame interrupted. Exiting..." << endl;
        return;
    }

    printBoard();
    if (winner != Player::None)
    {
        cout << "Player " << (winner == Player::X ? "X" : "O") << " wins!" << endl;
    }
    else
    {
        cout << "It's a draw!" << endl;
    }
}

void TicTacToe::printBoard()
{
    cout << "  1 2 3" << endl; // Đánh số cột
    for (int i = 0; i < 3; ++i)
    {
        cout << i + 1 << " "; // Đánh số hàng
        for (int j = 0; j < 3; ++j)
        {
            char symbol = '.';
            if (board[i][j] == Player::X)
            {
                symbol = 'X';
            }
            else if (board[i][j] == Player::O)
            {
                symbol = 'O';
            }
            cout << symbol << " ";
        }
        cout << endl;
    }
}

bool TicTacToe::makeMove(int row, int col)
{
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != Player::None)
    {
        return false;
    }
    board[row][col] = currentPlayer;
    return true;
}

Player TicTacToe::checkWinner()
{
    // Check rows
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    // Check diagonals
    if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }
    return Player::None;
}

void TicTacToe::switchPlayer()
{
    currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
}

void TicTacToe::signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        stopFlag = true;
    }
}

int main()
{
    TicTacToe game;
    game.playGame();
    return 0;
}
