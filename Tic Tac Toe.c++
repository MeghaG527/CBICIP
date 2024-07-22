
#include <iostream> 
#include <string> 
#include <vector> 
 
using namespace std; 
 
char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} }; 
char currentMarker; 
string currentPlayer; 
string player1; 
string player2; 
vector<string> movesHistory; 
 
void drawBoard() { 
    cout << "\n    1   2   3\n\n"; 
    cout << "1   " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl; 
    cout << "   ---|---|---\n"; 
    cout << "2   " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl; 
    cout << "   ---|---|---\n"; 
    cout << "3   " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl; 
} 
 
bool placeMarker(int row, int col) { 
    if (board[row][col] != 'X' && board[row][col] != 'O') { 
        board[row][col] = currentMarker; 
        return true; 
    } 
    return false; 
} 
 
string winner() { 
    // rows 
    for (int i = 0; i < 3; i++) { 
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') 
            return currentPlayer; 
    } 
    // columns 
    for (int i = 0; i < 3; i++) { 
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') 
            return currentPlayer; 
    } 
    // diagonals 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') 
        return currentPlayer; 
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') 
        return currentPlayer; 
 
    return ""; 
} 
 
void swapPlayerAndMarker() { 
    if (currentMarker == 'X') currentMarker = 'O'; 
    else currentMarker = 'X'; 
 
    if (currentPlayer == player1) currentPlayer = player2; 
    else currentPlayer = player1; 
} 
 
void game() { 
    cout << "Enter the name of player 1: "; 
    getline(cin, player1); 
    cout << "Enter the name of player 2: "; 
    getline(cin, player2); 
 
    while (true) { 
        cout << player1 << ", choose your marker (X or O): "; 
        cin >> currentMarker; 
        if (currentMarker == 'X' || currentMarker == 'O') { 
            break; 
        } else { 
            cout << "Invalid marker! Please choose either X or O." << endl; 
        } 
    } 
    cin.ignore();  // Clear the newline character from the buffer 
 
    currentPlayer = player1; 
 
    drawBoard(); 
 
    string playerWon = ""; 
 
    for (int i = 0; i < 9; i++) { 
        cout << "It's " << currentPlayer << "'s turn. Enter your row and column (e.g., 1 2): "; 
        int row, col; 
        cin >> row >> col; 
        row--; col--;  // Convert to 0-indexed 
 
        if (row < 0||  row > 2||  col < 0 || col > 2) { 
            cout << "Invalid input! Please enter row and column between 1 and 3." << endl; 
            i--; 
            continue; 
        } 
 
        if (!placeMarker(row, col)) { 
            cout << "That slot is occupied! Try another slot!" << endl; 
            i--; 
            continue; 
        } 
 
        movesHistory.push_back(currentPlayer + " placed " + currentMarker + " at (" + to_string(row + 1) + ", " + to_string(col + 1) + ")"); 
         
        drawBoard(); 
 
        playerWon = winner(); 
 
        if (playerWon == player1) { 
            cout << "\n" << player1 << " won! Congrats!" << endl; 
            break; 
        } 
        if (playerWon == player2) { 
            cout << "\n" << player2 << " won! Congrats!" << endl; 
            break; 
        } 
 
        swapPlayerAndMarker(); 
    } 
 
    if (playerWon == "") 
        cout << "\nIt's a tie game!" << endl; 
 
    cout << "\nMoves History:\n"; 
    for (const string& move : movesHistory) { 
        cout << move << endl; 
    } 
 
    cout << "\nDo you want to play again? (y/n): "; 
    char playAgain; 
    cin >> playAgain; 
 
    if (playAgain == 'y' || playAgain == 'Y') { 
        // Reset the board and move history 
        for (int i = 0; i < 3; ++i) { 
            for (int j = 0; j < 3; ++j) { 
                board[i][j] = ' '; 
            } 
        } 
        movesHistory.clear(); 
        game(); 
    } 
} 
 
int main() { 
    game(); 
    return 0; 
}