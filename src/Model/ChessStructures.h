#ifndef CHESS_STRUCTURES_H
#define CHESS_STRUCTURES_H

typedef struct ChessCoordinateStruct ChessCoordinate;
typedef struct ChessPieceStruct ChessPiece;
typedef struct ChessPlayerStruct ChessPlayer;
typedef struct ChessMoveStruct ChessMove;

typedef enum {Pawn, Rook, Knight, Bishop, Queen, King, None}  ChessPieceTypeEnum;

typedef enum {Human, AI} 	PlayerControlEnum;
typedef enum {White, Black} 	PlayerColorEnum;

typedef enum {False, True}	Boolean;

struct ChessCoordinateStruct {
  unsigned char Rank, File;
  ChessPiece * Piece;
};


struct ChessPlayerStruct{
	PlayerColorEnum 	PlayerColor;
	PlayerControlEnum	PlayerControl;

	/*list all the pieces that could belong to a player*/
	ChessPiece * Pawn[8];
	ChessPiece * Rook[2];
	ChessPiece * Knight[2];
	ChessPiece * Bishop[2];
	ChessPiece * Queen[1];
	ChessPiece * King[1];
};


struct ChessPieceStruct{  
	ChessPieceTypeEnum 	Type;
	unsigned char		Index;
	ChessPlayer *		Player;
	ChessCoordinate *	Coordinate;
	Boolean			AliveFlag;
};

struct ChessMoveStruct{
	ChessMove * PrevMove;
	ChessMove * NextMove;
	ChessPlayer * Player;
	ChessCoordinate * Start;
	ChessCoordinate * End;
};


#endif
