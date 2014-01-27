#include "Model.h"

ChessBoard * Model_Initialize(void){
	return InitializeChessBoard();
}

/* move piece to next location */
ChessBoard * Model_PerformMove(ChessBoard * board, ChessMoveList * moveList, ChessMove * move)
{
	/* the place to move to has an enemy piece */
	if (move->NextPosition->Piece != NULL)
	{
		/* kill it */
		move->NextPosition->Piece->AliveFlag = False;
		/* set that dead piece coordinate to null */
		move->NextPosition->Piece->Coordinate = NULL;
		
		/* it is dead */
		move->CaptureFlag = True;
	}
	/* piece to move, moved to next coordinate */
	move->StartPosition->Piece->Coordinate = move->NextPosition;
	
	/* delete piece pointer at previous location */
	move->StartPosition->Piece = NULL;

/*Need review to match new ChessMoveList*/
#if 0
	/* update move list */
	/* forward link */
	while (moveList->NextMove != NULL)
	{
		moveList = moveList->NextMove;
	}
	moveList->NextMove = move;
	
	/*backward link */
	moveList->NextMove->PrevMove = moveList;
	
	/*set the move of the next move */
	moveList->NextMove->Move = move;
#endif
	return board;
}

ChessCoordinateList * Model_GetLegalCoordinates(ChessBoard *chessboard, ChessPiece *piece, ChessPlayer *playerinturn) {
	ChessCoordinateList *output;
	ChessCoordinateList *OpponentLegalMoves;
	ChessCoordinate *checkSpace;
	/* DON'T FORGET MALLOCS*/
	int targetRank, targetFile;
	int dir_index = 0;
	int Rank_Offset8[8] = {1,1,1,0,0,-1,-1,-1};
	int File_Offset8[8] = {-1,0,1,-1,1,-1,0,1};
	int Rank_Offset_Bish[4] = {1,1,-1,-1};
	int File_Offset_Bish[4] = {-1,1,-1,1};
	int Rank_Offset_Rook[4] = {1,-1,0,0};
	int File_Offset_Rook[4] = {0,0,1,-1};
	int inDanger = 0;
	

	switch(piece->Type)
	  { 
	  case Pawn:
	      {
		  if(piece->Player->PlayerColor == White) {
                        /* check rank+1 to see if empty */
                        targetRank = 1 + piece->Coordinate->rank;
                        targetFile = piece->Coordinate->file;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank+1, file-1 to see if capture */
                        targetRank = piece->Coordinate->rank + 1;
                        targetFile = piece->Coordinate->file - 1;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank+1, file+1 to see if capture */
                        targetRank = piece->Coordinate->rank + 1;
                        targetFile = piece->Coordinate->file + 1;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* if hasn't moved yet, check rank+2 if empty */
                        if(firstMove) {
                                targetRank = piece->Coordinate->rank + 2;
                                targetFile = piece->Coordinate->file;
                                if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                        if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                                /* add to valid move */
                                        }
                                }
                        }
	      	}
}
                if(piece->Player->PlayerColor == Black) {
                        /* check rank-1 to see if empty */
                        targetRank = -1 + piece->Coordinate->rank;
                        targetFile = piece->Coordinate->file;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank-1, file-1 to see if capture */
                        targetRank = piece->Coordinate->rank - 1;
                        targetFile = piece->Coordinate->file - 1;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank-1, file+1 to see if capture */
                        targetRank = piece->Coordinate->rank - 1;
                        targetFile = piece->Coordinate->file + 1;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* if hasn't moved yet, check rank-2 if empty */
                        if(firstMove) {
                                targetRank = piece->Coordinate->rank - 2;
                                targetFile = piece->Coordinate->file;
                                if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                        if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                                /* add to valid move */
                                        }
                                }
                        }
                        
                }


	case Knight: {
					targetRank = 1 + piece->Coordinate->rank;
			targetFile = 2 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = 2 + piece->Coordinate->rank;
			targetFile = 1 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = -1 + piece->Coordinate->rank;
			targetFile = 2 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = -2 + piece->Coordinate->rank;
			targetFile = 1 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = 1 + piece->Coordinate->rank;
			targetFile = -2 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = 2 + piece->Coordinate->rank;
			targetFile = -1 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = -1 + piece->Coordinate->rank;
			targetFile = -2 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = -2 + piece->Coordinate->rank;
			targetFile = -1 + piece->Coordinate->file;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
	}


	  case Queen:
	    {
	      curr_coor = piece->Coordinate;
	      for(dir_index = 0; dir_index < 8; dir_index++)
		{
		  while (curr_coor)
		    {
		      if(piece->Player->PlayerColor == White)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset8[dir_index], File_Offset8[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		      if(piece->Player->PlayerColor == Black)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset8[dir_index], File_Offset8[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		    }
		}
	    }

	    case Bishop:
	      {
	      curr_coor = piece->Coordinate;
	      for(dir_index = 0; dir_index < 4; dir_index++)
		{
		  while (curr_coor)
		    {
		      if(piece->Player->PlayerColor == White)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset_Bish[dir_index], File_Offset_Bish[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		      if(piece->Player->PlayerColor == Black)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset_Bish[dir_index], File_Offset_Bish[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		    }
		}
	      }
	  case Rook:
	      {
	      curr_coor = piece->Coordinate;
	      for(dir_index = 0; dir_index < 4; dir_index++)
		{
		  while (curr_coor)
		    {
		      if(piece->Player->PlayerColor == White)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset_Rook[dir_index], File_Offset_Rook[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		      if(piece->Player->PlayerColor == Black)
			{
			  target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset_Rook[dir_index], File_Offset_Rook[dir_index]);
			  curr_coor = target_coor;
			  if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->rank][target_coor->file]->piece->Player->PlayerColor == White)
			    /*use Quan's append fxn*/
			    curr_coor = NULL;
			  else
			    {
			      /*use Quan's append fxn*/
			    }
			}
		    }
		}
	      }

	case King: {
	      curr_coor = piece->Coordinate;
	      for(dir_index = 0; dir_index < 8; dir_index++)
		{
		      target_coor = ChessCoordinate_Offset(curr_coor, Rank_Offset8[dir_index], File_Offset8[dir_index]);
		      if(target_coor) {
			if(piece->Player == playerinturn)
			  {
			    inDanger = 0;
			    OpponentLegalMoves = ChessCoordinateList(chessboard, piece->Player, playerinturn);
			    checkSpace = OpponentLegalMoves->First;
			    while(checkSpace) {
			      if(target_coor == checkSpace->Coordinate) {
				inDanger = 1;
			      }
			      
			      else {
				checkSpace = checkSpace->Next;
			      }
			    }
			    if!(inDanger) {
				if(chessboard->Board[target_coor->rank][target_coor->file]->piece == NULL) 
				  {
				    /* append */
				  }
				if(chessboard->Board[target_coor->rank][target_coor->file]->piece->Player != piece->Player)
				  { /*append*/
				  }
			      }
			  }

			else
			  {
			    if(chessboard->Board[target_coor->rank][target_coor->file]->piece == NULL) 
			      {
				/* append */
			      }
			    if(chessboard->Board[target_coor->rank][target_coor->file]->piece->Player != piece->Player)
			      { /*append*/
			      }
			  }
		      }
		}
	     }
	  }
	
	return output;
}

/* uses GetLegalCoordinates */
/* see if move is legal */
Boolean Model_CheckLegalMove(ChessBoard * board, ChessMove * moveTo)
{
	return True;
}

void Model_CleanUp(ChessBoard * CurrBoard, ChessMoveList * MoveList){
	ChessMoveNode * MoveNode1, * MoveNode2;
	MoveNode1 = MoveList->FirstMove;
	
	while (MoveNode1){
		MoveNode2 = MoveNode1->NextNode;
		free(MoveNode1->Move);
		free(MoveNode1);
		MoveNode1 = MoveNode2;
	}
		
	free(MoveList);
	
	int i,j;
	for (i = 0; i < CHESS_BOARD_MAX_ROW ; i++){
		for (j = 0; j < CHESS_BOARD_MAX_COL; j++){
			/*free the pieces*/
			if (CurrBoard->Board[i][j]->Piece) free(CurrBoard->Board[i][j]->Piece);
			/*free coordinate*/
			free(CurrBoard->Board[i][j]);
		}
	}
	
	/*free the player*/
	free(CurrBoard->WhitePlayer);
	free(CurrBoard->BlackPlayer);
	
	/*free the board*/
	free(CurrBoard);
	
}
