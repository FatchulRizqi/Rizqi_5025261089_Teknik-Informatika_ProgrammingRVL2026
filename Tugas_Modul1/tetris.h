#pragma once
#include <cstdio>
#include <iostream>
#include <cstdlib>

class Tetris {
  public:
    int x, y;
    int bentuk[4][4];

    Tetris() {
      x = 3;
      y = -2;

      bentuk_random();
    }
    
    void input(int arr[4][4]) {
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          bentuk[i][j] = arr[i][j];
        }
      } 
    }

    void move(int dx, int dy) {
      x += dx;
      y += dy;
    }
    
    void rotate() {
      int arr_sementara[4][4];

      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          arr_sementara[j][3 - i] = bentuk[i][j];
        }
  }

      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          bentuk[i][j] = arr_sementara[i][j];
        }
      }
    }
  
  private:
    void bentuk_random() {
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          bentuk[i][j] = 0;
        }
      }

      int tipe = rand() % 7;

      switch (tipe) {
        case 0:
          //Z
          bentuk[0][2] = 1; bentuk[1][2] = 1; bentuk[1][1] = 1; bentuk[2][1] = 1;
        case 1:
          //Kotak
          bentuk[1][1] = 1; bentuk[1][2] = 1; bentuk[2][1] = 1; bentuk[2][2] = 1;
          break;
        case 2:
          //I
          bentuk[0][1] = 1; bentuk[1][1] = 1; bentuk[2][1] = 1; bentuk[3][1] = 1;
        case 3:
          //T
          bentuk[1][1] = 1; bentuk[2][0] = 1; bentuk[2][1] = 1; bentuk[2][2] = 1;
        case 4:
          //L
          bentuk[0][1] = 1; bentuk[1][1] = 1; bentuk[2][1] = 1; bentuk[2][2] = 1;
        case 5:
          //S
          bentuk[1][2] = 1; bentuk[1][1] = 1; bentuk[2][1] = 1, bentuk[2][0] = 1;
        case 6:
          //J
          bentuk[0][2] = 1; bentuk[1][2] = 1; bentuk[2][2] = 1; bentuk[2][1] = 1;
      }
    }
};
