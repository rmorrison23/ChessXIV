#ifndef CHESS_STRUCTURES_H
#define CHESS_STRUCTURES_H

#define CHESS_BOARD_MAX_ROW 8
#define CHESS_BOARD_MAX_COL 8


typedef struct ChessCoordinateStruct ChessCoordinate;
typedef struct ChessCoordinateListStruct ChessCoordinateList;
typedef struct ChessPieceStruct ChessPiece;
typedef struct ChessPlayerStruct ChessPlayer;
typedef struct ChessMoveStruct ChessMove;
typedef struct ChessMoveListStruct ChessMoveList;
typedef struct ChessMoveNodeStruct 

typedef enum {Easy, Medium, Difficult} AIDifficultyLevel;

typedef enum {Pawn, Rook, Knight, Bishop, Queen, King, None}  ChessPieceTypeEnum;

typedef enum {Human, AI} 	PlayerControlEnum;
typedef enum {White, Black} 	PlayerColorEnum;

typedef enum {False, True}	Boolean;

typedef struct {
  ChessCoordinate * Board[CHESS_BOARD_MAX_ROW][CHESS_BOARD_MAX_COL];
  ChessPlayer * WhitePlayer, * BlackPlayer;
} ChessBoard;


struct ChessCoordinateStruct {
  unsigned char Rank, File;
  ChessPiece * Piece;
};

struct ChessPlayerStruct{
	PlayerColorEnum 	PlayerColor;
	AIDifficultyLevel	AIDifficulty;
	PlayerControlEnum	PlayerControl;

	/*list all the ];pieces that could belong to a player*/
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
	ChessPlayer * Player;
	ChessCoordinate * StartPosition;
	ChessCoordinate * NextPosition;
	Boolean CaptureFlag;
};

struct ChessMoveNodeStruct{
	ChessMove * Move;
	ChessMoveNode * PrevNode;
	ChessMoveNode * NextNode;
	ChessMoveList * List;
};

struct ChessMoveListStruct{
	ChessMove * FirstMove, * LastMove;
};

struct ChessCoordinateListStruct{
	ChessCoordinateList * NextNode, * PrevNode;
	ChessCoordinate * Coordinate;
};

#endif
