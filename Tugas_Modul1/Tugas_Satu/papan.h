#pragma once
#include <iostream>
#include <random>
#include <type_traits>
#include "tetris.h"

class Papan {
  private:
    int TINGGI = 20, LEBAR = 10;

  public:
    int papan[20][10];

    Papan() {
      for(int i = 0; i < TINGGI; i++) {
        for(int j = 0; j < LEBAR; j++) {
          papan[i][j] = 0;
        }
      }
    }
    
    bool tabrakan(Tetris blok) {
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          if(blok.bentuk[i][j] == 1) {
            int posisix = blok.x + j;
            int posisiy = blok.y + i;
            
            if(posisiy < 0) {continue;}
            
            if(papan[posisiy][posisix] == 1) {
              return true;
            }

            if (posisiy >= 20 || posisix < 0 || posisix >= 10) {
              return true; 
            }
            
            if(posisiy >= 20) {
              return true;
            } else if(posisix < 0 || posisix >= 10) {
              return true;
            }
          }
        }
      }
      return false;
    }

    void gabung_balok(Tetris blok) {
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          int posisix = blok.x + j;
          int posisiy = (blok.y - 1) + i;

          if (posisiy >= 0 && posisiy < 20 && posisix >= 0 && posisix < 10 && blok.bentuk[i][j] == 1) {
            papan[posisiy][posisix] = 1;
          }        
        }
      } 
    }

    void hapus_baris() {
      bool param = false;
      for(int i = TINGGI - 1; i >= 0; i--) {
        for(int j = 0; j < LEBAR; j++) {
          if(papan[i][j] == 0) {
            param = true;
            break;
          }
        }

        if(param) {
          param = false;
        } else {
          for(int k = i - 1; k >= 0; k--) {
            for(int l = 0; l < LEBAR; l++) {
              if(papan[k][l] == 1) {
                papan[k + 1][l] = 1;
              } else {
                papan[k + 1][l] = 0;
              }
            }   
          }
        }
      }  
    }
};
