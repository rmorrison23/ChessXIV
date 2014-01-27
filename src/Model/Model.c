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
		/* send to grave yard*/
		move->CapturePiece = move->NextPosition->Piece;
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

	/* update move list */
	ChessMoveNode * newMoveNode = malloc(sizeof(ChessMoveNode));
	assert (newMoveNode);

	/* point new List to old list */
	newMoveNode->List = moveList;

	/* point new move to move */
	newMoveNode->Move = move;
	
	/* set next node to null */
	newMoveNode->NextNode = NULL;

	/* list is empty */
	if (moveList ->FirstNode == NULL)
	{
		moveList->FirstNode = newMoveNode;
		moveList->LastNode = newMoveNode;
		newMoveNode->PrevNode = NULL;
	}

	/* list is not empty */
	else
	{
		moveList->LastNode->NextNode = newMoveNode;
		newMoveNode->PrevNode = moveList->LastNode;
		moveList->LastNode = newMoveNode;
	}
	return board;
}

ChessBoard * Model_UndoLastMove(ChessBoard * board, ChessMoveList * moveList)
{
      int i = 0;
      /* move to delete */
      ChessMoveNode * tempNode = moveList->LastNode;
      
      /* need to move back twice */
      for (i = 0; i < 2; i ++)
      {
	 /* moving back a position (1 undo) */
	tempNode->Move->MovePiece->Coordinate = tempNode->Move->StartPosition;
	tempNode->Move->StartPosition->Piece = tempNode->Move->MovePiece;
	
	/* need to restore a piece from the graveyard */
	if (tempNode->Move->CaptureFlag)
	{
	    /* bring back the dead */
	    tempNode->Move->NextPosition->Piece = tempNode->Move->CapturePiece;
	    tempNode->Move->CapturePiece->Coordinate = tempNode->Move->NextPosition;
	}
	/*nothing to restore from graveyard */
	else
	{
	    tempNode->Move->NextPosition->Piece = NULL;
	}
	/*breaking the forward link of previous node*/
	tempNode->PrevNode->NextNode = NULL;
	/*moving the node back one */
	tempNode = tempNode->PrevNode;
	/*update the last node */
	moveList->LastNode = tempNode;

	free(tempNode->NextNode);
      }
      
      return board;
}
ChessCoordinateList * Model_GetAllLegalCoordinate( ChessBoard * board, ChessPlayer * player, ChessPlayer * PlayerInTurn)
{
	int i = 0;
	
	/* create a permanent coordinate list to be return */
	ChessCoordinateList *newChessCoordinateList1;
	/* create a temp coordinate list to be append */
	ChessCoordinateList *newChessCoordinateList2;

	/* storing the value of the permanent list */
	newChessCoordinateList1 = Model_GetLegalCoordinates(board, player->Pieces[0], PlayerInTurn);

	/* for loop to store the remaining 15 piece into a temp list, then appending new coordinate into 
	the permanent list */
	for (i = 1; i < 16; i++)
	{
		/* storing coordinate into the temp list */
		newChessCoordinateList2 = Model_GetLegalCoordinates(board, player->Pieces[i], PlayerInTurn);
		
		/* appending the two list so there is no duplicate coordinate */
		ChessCoordinateList_AppendNoRedundancy(newChessCoordinateList1, newChessCoordinateList2);
	}
	return newChessCoordinateList1;
}

Boolean Model_CheckCheckedPosition(ChessBoard * board, ChessPlayer * player)
{
	/* grab list of legal move of other player */
	ChessCoordinateList * newList = Model_GetAllLegalCoordinate(board, player->OtherPlayer, player);
	
	/* a temp node to traverse the list */
	ChessCoordinateNode *tempNode = newList->FirstNode;
	ChessPiece * king = ChessPlayer_GetChessPiece(player, King, 0);

	/* there is a legal move for other player */
	if (newList != NULL)
	{
		while (tempNode != NULL)
		{
		/* check the coordinate of the player king to the legal coordinate of other player */
			if (king->Coordinate == tempNode->Coordinate)
			{
				return True;
			}
			/* traverse the list */
			tempNode = tempNode->NextNode;
		}
	}
	return False;
}

Boolean Model_CheckCheckmate(ChessBoard * board, ChessPlayer * player)
{
	
	if (Model_CheckCheckedPosition(board, player) && Model_GetAllLegalCoordinate(board, player, player->OtherPlayer) == NULL)	
	{
		return True;
	}	
	return False;
}

Boolean Model_Stalemate(ChessBoard * board, ChessPlayer * player)
{
	if (!Model_CheckCheckedPosition(board, player) && Model_GetAllLegalCoordinate(board, player, player->OtherPlayer) == NULL)
	{
		return True;
	}	
	return False;
}

ChessCoordinateList * Model_GetLegalCoordinates(ChessBoard *chessboard, ChessPiece *piece, ChessPlayer *playerinturn) {
	ChessCoordinateList *output;
	ChessCoordinateList *OpponentLegalMoves;
	ChessCoordinate *checkSpace, * curr_coor, * target_coor;
	
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
                        targetRank = 1 + piece->Coordinate->Rank;
                        targetFile = piece->Coordinate->File;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank+1, file-1 to see if capture */
                        targetRank = piece->Coordinate->Rank + 1;
                        targetFile = piece->Coordinate->File - 1;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank+1, file+1 to see if capture */
                        targetRank = piece->Coordinate->Rank + 1;
                        targetFile = piece->Coordinate->File + 1;
                        if(targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* if hasn't moved yet, check rank+2 if empty */
                        if(piece->PawnMoveFirstFlag) {
                                targetRank = piece->Coordinate->Rank + 2;
                                targetFile = piece->Coordinate->File;
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
                        targetRank = -1 + piece->Coordinate->Rank;
                        targetFile = piece->Coordinate->File;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank-1, file-1 to see if capture */
                        targetRank = piece->Coordinate->Rank - 1;
                        targetFile = piece->Coordinate->File - 1;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* check rank-1, file+1 to see if capture */
                        targetRank = piece->Coordinate->Rank - 1;
                        targetFile = piece->Coordinate->File + 1;
                        if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                if(chessboard->Board[targetRank][targetFile]->Piece != NULL && chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
                                        /* add to valid move */
                                }
                        }
                        
                        /* if hasn't moved yet, check rank-2 if empty */
                        if(piece->PawnMoveFirstFlag) {
                                targetRank = piece->Coordinate->Rank - 2;
                                targetFile = piece->Coordinate->File;
                                if(targetRank >= 0 && targetFile >= 0 && targetFile <= 7) {
                                        if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
                                                /* add to valid move */
                                        }
                                }
                        }
                        
                }


	case Knight: {
					targetRank = 1 + piece->Coordinate->Rank;
			targetFile = 2 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = 2 + piece->Coordinate->Rank;
			targetFile = 1 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = -1 + piece->Coordinate->Rank;
			targetFile = 2 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = -2 + piece->Coordinate->Rank;
			targetFile = 1 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = 1 + piece->Coordinate->Rank;
			targetFile = -2 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = 2 + piece->Coordinate->Rank;
			targetFile = -1 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			
			targetRank = -1 + piece->Coordinate->Rank;
			targetFile = -2 + piece->Coordinate->File;
			if(targetRank >= 0 && targetRank <= 7 && targetFile >= 0 && targetFile <= 7) {
				if(chessboard->Board[targetRank][targetFile]->Piece == NULL) {
					/* add to valid move */
				}
				else if(chessboard->Board[targetRank][targetFile]->Piece->Player != piece->Player) {
					/* add to valid move */
					/* capture piece */
				}
			}
			targetRank = -2 + piece->Coordinate->Rank;
			targetFile = -1 + piece->Coordinate->File;
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
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
			  if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == Black)
			    curr_coor = NULL;
			  else if (chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player->PlayerColor == White)
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
			    OpponentLegalMoves = Model_GetAllLegalCoordinate(chessboard, piece->Player, playerinturn);
			    ChessCoordinateNode * checkSpace = OpponentLegalMoves->FirstNode;
			    while(checkSpace) {
			      if(target_coor == checkSpace->Coordinate) {
				inDanger = 1;
			      }
			      
			      else {
				checkSpace = checkSpace->NextNode;
			      }
			    }
			    if(!inDanger) {
				if(chessboard->Board[target_coor->Rank][target_coor->File]->piece == NULL) 
				  {
				    /* append */
				  }
				if(chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player != piece->Player)
				  { /*append*/
				  }
			      }
			  }

			else
			  {
			    if(chessboard->Board[target_coor->Rank][target_coor->File]->piece == NULL) 
			      {
				/* append */
			      }
			    if(chessboard->Board[target_coor->Rank][target_coor->File]->Piece->Player != piece->Player)
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
	MoveNode1 = MoveList->FirstNode;
	
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
