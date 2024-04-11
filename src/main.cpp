
#include <cstdio>
#include <ncurses.h>

#include <cstdio>
#include <ncurses.h>
#include <unistd.h>

int row = 0;
int col = 0;
int mode = 1; // should be 0 for insert and 1 for normal

int max_x;
int max_y;

int changeMode();
int moveCursor(int colDelta, int rowDelta);


int moveRight();
int moveLeft();
int moveUp();
int moveDown();



int main (int argc, char *argv[]) {
  int ch;
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  row = 0;
  col = 0;
  changeMode();

  getmaxyx(stdscr, max_y, max_x);
  changeMode();
  while((ch = getch()) != KEY_F(1)){
    if (ch == 127 || ch == KEY_BACKSPACE){
      if (col == 0){
        moveCursor(max_x, -1);
        delch();
      }
      else{
        moveLeft();
        delch();
      }
    }
    else if (ch == 27){
      changeMode();
    }
    
    else if (mode == 0){
      if (ch == '\n' || ch == KEY_ENTER) {
        moveCursor(-col,1);
        insertln();
      } else {
        insch(ch);
        moveRight();
      }
    }
    else if (mode == 1 && ch != KEY_ENTER){
      switch (ch) {
        case 'H': case 'h':
          moveLeft();
          break;
        case 'J': case'j':
          moveDown();
          break;
        case 'K': case 'k':
          moveUp();
          break;
        case 'L': case 'l':
          moveRight();
          break;
      }
    }

  }

  endwin();
  return 0;
}

int changeMode(){
  if (mode == 0){
    mode = 1;
    return 0;
  }
  mode = 0;
  return mode;
}

int moveCursor(int colDelta, int rowDelta){
  bool rowCheck = false;
  bool colCheck = false;

  if ((row + rowDelta >= 0) && (row + rowDelta <= max_x)){
    rowCheck = true;
  }
  if ((col + colDelta >= 0) && (col + colDelta <= max_y)){
    colCheck = true;
  }
  if (rowCheck && colCheck){
    col = col + colDelta;
    row = row + rowDelta;
    move(row,col);
    return 0;
  }
  return 1;
}

int moveDown(){
  moveCursor(0,1);
  return 0;
}
int moveLeft(){
  moveCursor(-1,0);
  return 0;
}
int moveRight(){
  moveCursor(1,0);
  return 0;
}
int moveUp(){
  moveCursor(0, -1);
  return 0;
}
