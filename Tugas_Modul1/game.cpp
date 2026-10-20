#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "papan.h"
#include "tetris.h"

int tombol_ditekan() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


class Game {
  private:
    Papan papan;
    Tetris tetris_game;
    bool gameOver;

  public:
    Game() {
      gameOver = false;
    }

    void input() {
      if(tombol_ditekan()) {
        char tombol = getchar();
        
        if(tombol == 27) {
          getchar();
          char panah = getchar();

          if(panah == 'A') {
            tetris_game.rotate();

            if(papan.tabrakan(tetris_game)) {
              tetris_game.rotate();
              tetris_game.rotate();
              tetris_game.rotate();
            }
          } else if(panah == 'B') {
            tetris_game.move(0, 1);
            if(papan.tabrakan(tetris_game)  ) {
              tetris_game.move(0, -1);
            } 
          } else if(panah == 'C') {
            tetris_game.move(1, 0);
            if(papan.tabrakan(tetris_game)) {
              tetris_game.move(-1, 0);
            }
          } else if(panah == 'D') {
            tetris_game.move(-1, 0);
            if(papan.tabrakan(tetris_game)) {
              tetris_game.move(1, 0);
            }
          }
        }

      }
    }

    void update() {
      tetris_game.move(0, 1);

      if(papan.tabrakan(tetris_game)) {
        papan.gabung_balok(tetris_game);
        papan.hapus_baris();
        
        tetris_game = Tetris();
        if(papan.tabrakan(tetris_game)) {
          gameOver = true;
        }
      }
    }

    void tampil() {
      system("clear");
      
      bool cek_satu = false;

      for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
          if(i >= tetris_game.y && i < tetris_game.y + 4 && 
            j >= tetris_game.x && j < tetris_game.x + 4) {
            int koor_baris = i - tetris_game.y;
            int koor_kolom = j - tetris_game.x;

            if(tetris_game.bentuk[koor_baris][koor_kolom] == 1) {
              cek_satu = true;
            }
          }

          if(cek_satu) {
            std::cout << "[]";
            cek_satu = false;
          } else if(papan.papan[i][j] == 1) {
            std::cout << "[]";
          } else {
            std::cout << " .";
          }
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    void run() {
      int waktu = 0;
      while(!gameOver) {
        input();

        if(waktu % 20 == 0) {
          update();
        }

        tampil();
        waktu++;
        usleep(50000);
      }

    }
};


int main() {
  Game game;
  game.run();
  
  return 0;
}

