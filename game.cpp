#include <bits/stdc++.h>

using namespace std;

class Tic_Toe {
public:
  bool visited[3][3];
  int state = 0;
  char board[3][3];
  int turns = 0;
  void draw() {
    // Draws the board
    for (int i = 1; i <= 3; i++) {
      cout << "   "<< i;
    }
    cout << '\n';
    for (int i = 0; i < 3; i++) {
      cout << i + 1 << "  "<< board[i][0] << " | " << board[i][1] << " | " << board[i][2] << '\n';
      if (i < 2) {
        cout << "  ---+---+---\n";
      }
    }
  }
  void dialog() {
    turns++; cout << "Turn: " << turns << '\n';
  }
  void player1() {
    dialog();
    cout << "Player 1 to move, choose a position!\n";
    int x,y; cin >> x >> y;
    x--,y--;
    while (!is_legal(x,y)) {
      cout << "Invalid input\n";
      cin >> x >> y;
      x--,y--;
    }
    set_move(x,y);
    draw();
    game_state();
  }
  void player2() {
    dialog();
    cout << "Player 2 to move, choose a position!\n";
    int x,y; cin >> x >> y;
    x--, y--;
    while (!is_legal(x,y)) {
      cout << "Invalid input\n";
      cin >> x >> y;
      x--,y--;
    }
    set_move(x,y);
    draw();
    game_state();
  }
  void computer(bool flag) {
    dialog();
    cout << "It is the computer's turn!\n";
    tuple<int,int,int> kekw = minimax(turns,flag);
    int x = get<1>(kekw);
    int y = get<2>(kekw);
    cout << "Computer chooses: " << x + 1<< " " << y + 1<< '\n';
    set_move(x,y);
    draw();
    game_state();
  }
  void game_state() {
    int temp = check_for_winner();
    if (state == 1) {
      if (temp != 0) {
        if (temp == 1) {
          cout << "Player 1 wins!\n";
        } else {
          cout << "Player 2 wins!\n";
        }
      } else {
        if (turns == 9) {
          cout << "TIE!\n";
          return;
        }
        if (turns % 2 == 0) {
          player1();
        } else {
          player2();
        }
    }
    } else if (state == 2) {
      if (temp != 0) {
        if (temp == 1) {
          cout << "Player 1 wins!\n";
        } else {
          cout << "Computer wins!\n";
        }
      } else {
        if (turns == 9) {
          cout << "TIE!\n";
          return;
        }
        if (turns % 2 == 0) {
          player1();
        } else {
          computer(false);
        }
    }
    } else if (state == 3) {
      if (temp != 0) {
        if (temp == 1) {
          cout << "Computer wins!\n";
        } else {
          cout << "Player 2 wins!\n";
        }
      } else {
        if (turns == 9) {
          cout << "TIE!\n";
          return;
        }
        if (turns % 2 == 0) {
          computer(true);
        } else {
          player2();
        }
    }
    }
    return;
  }
  bool is_legal(int x, int y) {
    if ((x > 2 || x < 0) ||(y > 2 || y < 0)) {
        return false;
      }
    return !visited[x][y];
  }
  void set_move(int x, int y) {
    char current = current_character();
    board[x][y] = current;
    visited[x][y] = true;
  }
  char current_character() {
    return (turns % 2 == 0 ? 'o' : 'x');
  }
  int check_for_winner() {
    char current = current_character();
    // Diagonal cases
    if (board[0][0] != ' ' && (board[0][0] == board[1][1] && board[1][1] ==  board[2][2])) {
      if (current == 'x') {
        return 1;
      } else {
        return -1;
      }
    } else if (board[2][0] != ' ' && (board[2][0] == board[1][1] && board[1][1] == board[0][2])) {
      if (current == 'x') {
        return 1;
      } else {
        return -1;
      }
    }
    // horizontal case
    int counter = 0;
    for (int i = 0; i < 3; i++) {
      counter = 0;
      for (int j = 0; j < 2; j++) {
        if (board[i][j] != ' ' && (board[i][j + 1]  == board[i][j])) {
          counter++;
        } else {
          counter = 0;
        }

        if (counter == 2) {
          if (current == 'x') {
            return 1;
          } else {
            return -1;
          }
        }
      }
    }
    // vertical case
    counter = 0;
    for (int i = 0; i < 3; i++) {
      counter = 0;
      for (int j = 0; j < 2; j++) {
        if (board[j][i] != ' ' && (board[j + 1][i] == board[j][i])) {
          counter++;
        } else {
          counter = 0;
        }
        if (counter == 2) {
          if (current == 'x') {
            return 1;
          } else {
            return -1;
          }
        }
      }
    }
    return 0;
  }
  Tic_Toe() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = ' ';
        visited[i][j] = false;
      }
    }
    cout << "Please select a mode: \n" << "Selecting 1: player vs player\nSelecting 2: player vs computer\nSelecting 3: computer vs player\n";
    int n; cin >> n;
    while (n > 3 || n < 1) {
      cout << "Invalid input\n";
      cin >> n;
    }
    state = n;
    draw();
    cout << "Instructions: Pick a row, and then pick a column\n" << "Enter those in order, e.g. (1,1) denotes a move on the top left corner\n";
    cout << "Have fun!\n";
    if (state == 1 || state == 2) {
      player1();
    } else {
      computer(true);
    }
  }
  // Will pass in the current depth of each node instead of assuming that is the root
  tuple<int,int,int> minimax (int depth, bool maxi) {
    if (depth == 10 || check_for_winner() != 0) {
      return {-check_for_winner(), -1, -1};
    }
    int x = -1;
    int y = -1;
    if (maxi) {
      int maxeval = -1e9;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (is_legal(i,j)) {
            board[i][j] = 'x';
            visited[i][j] = true;
            turns++;
            int eval = get<0>(minimax(depth + 1, false));
            turns--;
            board[i][j] = ' ';
            visited[i][j] = false;
            if (eval > maxeval) {
              maxeval = eval;
              x = i, y = j ;
            }
          }
        }
      }
      return {maxeval,x,y};
    } else {
      int mineval = 1e9;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (is_legal(i,j)) {
            board[i][j] = 'o';
            visited[i][j] = true;
            turns++;
            int eval = get<0>(minimax(depth + 1, true));
            turns--;
            board[i][j] = ' ';
            visited[i][j] = false;
            if (eval < mineval) {
              mineval = eval;
              x = i, y = j;
            }
          }
        }
      }
      return {mineval, x, y};
    }
  }
};

int main() {
  Tic_Toe game;
  return 0;
}
