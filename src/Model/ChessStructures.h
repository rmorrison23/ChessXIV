#ifndef CHESS_STRUCTURES_H
#define CHESS_STRUCTURES_H

#define CHESS_BOARD_MAX_ROW 8
#define CHESS_BOARD_MAX_COL 8


typedef struct ChessCoordinateStruct ChessCoordinate;
typedef struct ChessCoordinateListStruct ChessCoordinateList;
typedef struct ChessCoordinateNodeStruct ChessCoordinateNode;
typedef struct ChessPieceStruct ChessPiece;
typedef struct ChessPlayerStruct ChessPlayer;
typedef struct ChessMoveStruct ChessMove;
typedef struct ChessMoveListStruct ChessMoveList;
typedef struct ChessMoveNodeStruct ChessMoveNode;

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
  
  /*point back to the board, allows horizontal movement to other coordinate*/
  ChessBoard * MainBoard;
};

struct ChessCoordinateListStruct{
	ChessCoordinateNode * FirstNode, * LastNode;
};

struct ChessCoordinateNodeStruct{
	ChessCoordinateNode * NextNode, * PrevNode;
	ChessCoordinate * Coordinate;
	ChessCoordinateList * List;
};

struct ChessPlayerStruct{
	PlayerColorEnum 	PlayerColor;
	AIDifficultyLevel	AIDifficulty;
	PlayerControlEnum	PlayerControl;

	/*pointer to other player*/
	ChessPlayer *	OtherPlayer;
	
	/*list all the ];pieces that could belong to a player*/
	ChessPiece *	Pieces[16];
};


struct ChessPieceStruct{  
	ChessPieceTypeEnum 	Type;
	unsigned char		Index;
	ChessPlayer *		Player;
	ChessCoordinate *	Coordinate;
	Boolean			AliveFlag;
};

struct ChessMoveStruct{
	ChessPiece *	MovePiece;
	ChessCoordinate * StartPosition;
	ChessCoordinate * NextPosition;
	ChessPiece *	CapturePiece;
	Boolean CaptureFlag;
};

struct ChessMoveNodeStruct{
	ChessMove * Move;
	ChessMoveNode * PrevNode;
	ChessMoveNode * NextNode;
	ChessMoveList * List;
};

struct ChessMoveListStruct{
	ChessMoveNode * FirstNode, * LastNode;
};



#endif
