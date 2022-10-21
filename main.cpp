#include <iostream>
#include <vector>

using namespace std;

/**
 * Returns the player at the position x/y.
 * If the position is empty or is out of bounds, returns 0.
 */
int getPlayer(const vector<vector<int>> &board, int x, int y) {
    if (x >= board.size()) {
        return 0;
    }
    if (y >= board[x].size()) {
        return 0;
    }
    return board[x][y];
}

/**
 * Returns the number of consecutive boxes that the player has at position x/y in the
 * direction dx/dy.
 * Also counts the box at x,y.
 */
int countVector(const vector<vector<int>> &board, int player, int x, int y, int dx, int dy) {
    int count = 0;
    while (getPlayer(board, x, y) == player) {
        count++;
        x += dx;
        y += dy;
    }
    return count;
}

/**
 * Returns the number of consecutive boxes that the player has at position x/y in the
 * direction of dx/dy and -dx/-dy.
 */
int countVectorBi(const vector<vector<int>> &board, int player, int x, int y, int dx, int dy) {
    return countVector(board, player, x, y, dx, dy) +
           countVector(board, player, x, y, -dx, -dy) - 1;
}

/**
 * Returns the winning player if the position x,y resolves to a winning position.
 * This means it is filled by a player AND has 4 consecutive boxes
 * filled in either of the winning directions.
 */
int hasWinner(const vector<vector<int>> &board, int x, int y) {
    int player = getPlayer(board, x, y);
    if (player == 0) {
        return 0;
    }
    if (countVectorBi(board, player, x, y, 1, 1) == 4 ||
        countVectorBi(board, player, x, y, 1, -1) == 4 ||
        countVectorBi(board, player, x, y, 1, 0) == 4 ||
        countVectorBi(board, player, x, y, 0, 1) == 4) {
        return player;
    }
    return 0;
}

/**
 *  Returns if any of the two player has won.
 *  It returns the first player it finds with four consecutive
 *  boxes in a row in any of the four directions.
 *  If no player is found, it returns 0;
 */
int hasWinner2(vector<vector<int>> board) {
    const unsigned int width = board.size();
    const unsigned int height = board[0].size();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int winner = hasWinner(board, x, y);
            if (winner > 0) {
                return winner;
            }
        }
    }
}

/**
 *  Returns if any of the two player has won.
 *  It returns the first player it finds with four consecutive
 *  boxes in a row in any of the four directions.
 *  If no player is found, it returns 0;
 */
int hasWinner3(vector<vector<int>> board) {
    const unsigned int width = board.size();
    const unsigned int height = board[0].size();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int player = getPlayer(board, x, y);
            if (player == 0) {
                continue;
            }
            if (countVector(board, player, x, y, -1, -1) == 4) {
                return player;
            }
            if (countVector(board, player, x, y, -1, 0) == 4) {
                return player;
            }
            if (countVector(board, player, x, y, 0, -1) == 4) {
                return player;
            }
            if (countVector(board, player, x, y, -1, 1) == 4) {
                return player;
            }
        }
    }
    return 0;
}

/**
 * So it seems that checking only where the player put down their choice is
 * the smallest, as seen in `hasWinner`.
 * Using this, checking the full board can be quite small, as seen in `hasWinner2`.
 * If you have to do it all by itself, then it gets a bit longer, as seen in `hasWinner3`.
 *
 * The methods `getPlayer`, `countVector`, and `countVectorBi` are helper functions
 * that avoid to have to make too many checks and multi-line comparisons
 * against the player.
 */

void checkBoard(vector<vector<int>> board) {
    int x = 0, y = 0;
    if (board[x][y] == 0){
        // Suppose we're in the other diagonal
        x = 3;
    }
    for (int i = 0; i < 5; i++) {
        cout << "Testing " << i << endl;
        switch (i) {
            case 1:
                board.emplace(board.begin(), vector(board[0].size(), 0));
                x++;
                break;
            case 2:
                board.emplace(board.end(), vector(board[0].size(), 0));
                break;
            case 3:
                y++;
                for (auto & b : board) {
                    b.insert(b.begin(), 0);
                }
                break;
            case 4:
                for (auto & b : board) {
                    b.insert(b.end(), 0);
                }
                break;
            default:
                break;
        }
        for (const auto& bx: board) {
            for (auto by: bx) {
                cout << by << " ";
            }
            cout << endl;
        }
        assert(hasWinner(board, x, y) == 1);
        assert(hasWinner2(board) == 1);
        assert(hasWinner3(board) == 1);
    }
}

int main() {
    checkBoard({
                       {1, 0, 0, 0},
                       {0, 1, 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}
               });
    checkBoard({
                       {1},
                       {1},
                       {1},
                       {1}
               });
    checkBoard({
                       {1, 1, 1, 1},
               });
    checkBoard({
                       {0, 0, 0, 1},
                       {0, 0, 1, 0},
                       {0, 1, 0, 0},
                       {1, 0, 0, 0}
               });

    cout << "All is good" << endl;
    return 0;
}
