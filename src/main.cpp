#include <ncurses.h>
#include <unistd.h>



int row = 0;
int col = 0;
int mode = 1;//should be 0 for insert and 1 for normal

int max_x;
int max_y;

int changeMode();
int moveCursor(int colDelta, int rowDelta);

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
      moveCursor(-1, 0);
      delch();
    }
    else if (ch == 27){
      changeMode();
    }
    else if (mode == 0){
      addch(ch);
      col += 1;

    }
    else{
      switch (ch) {
        case 'H': case 'h':
          moveCursor(-1,0);
          break;
        case 'J': case'j':
          moveCursor(0, 1);
          break;
        case 'K': case 'k':
          moveCursor(0,-1);
          break;
        case 'L': case 'l':
          moveCursor(1,0);
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
