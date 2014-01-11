#ifndef PLAYER_H
#define PLAYER_H
  typedef enum {Human, AI} 		PlayerControlEnum;
  typedef enum {White, Black} 		PlayerColorEnum;
  
  typedef struct {
    PlayerColorEnum 		PlayerColor;
    PlayerControlEnum		PlayerControl;
  } PlayerType;
#endif