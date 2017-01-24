#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct piece{
  char* name;
  int x,y,color;
} piece;


char ** parse(char * scan) {
  
  *strchr(scan, '\n') = 0;
  
  char ** input = (char **) calloc(sizeof(char *), 10);
  
  int x = 0;
  while (input[x] = strsep(&scan, " ")) {
    if (strlen(input[x]))
      x++;
  }
  
  return input;

}

int * translateCoord(char * input)  {

  int letter;
  int num;
  
  letter = tolower(input[0]);
  //printf("%d\n",letter);
  num = input[1];
  
  letter -= 97;
  // printf("%d\n",letter);
  num -= 49;

  int * c = (int *) malloc(sizeof(int) * 2);
    
  c[0] = letter;
  c[1] = num;
  
  return c;
}

int * translatePiece(char * pieces) { 

  int color = -1;
  int type = -1;
  
  char defColor = 'b';

  if (tolower(pieces[0]) == defColor)
    color = 0;
  else 
    color = 1;
  
  int i = 1;
  char * temp;
  temp = malloc(sizeof(char) * 3);

  temp[0] = pieces[1];
  temp[1] = pieces[2];


  if (strcmp(temp, "pn") == 0)
    type = 0;
  if (strcmp(temp, "bs") == 0)
    type = 1;
  if (strcmp(temp, "kn") == 0)
    type = 2;
  if (strcmp(temp, "rk") == 0)
    type = 3;
  if (strcmp(temp, "qn") == 0)
    type = 4;
  if (strcmp(temp, "kg") == 0)
    type = 5;

  int * d = (int *) malloc(sizeof(int) *2);
  
  d[0] = color;
  d[1] = type;
  
  free(temp);
  return d;

}

int checkMoves(int * pieces, int * from, int * to, piece board[8][8]) {
  
  int color = pieces[0];
  int type = pieces[1];
  int x1 = from[0]; 
  int y1 = from[1];
  int x2 = to[0];
  int y2 = to[1];
  
  if ((x1 > 7 || x2 > 7 || y1 > 7 || y2 > 7 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) && (x1 != x2 && y1 != y2))
    return 0;
  
  //pawn
  if (type == 0) {
    //black
    if (color == 0) { 
      //starting position
      if (y1 == 6) {
	if ((y2-y1) == -2 || (y2-y1) == -1) {
	  //straight forward
	  if (x2-x1 == 0) {
	    //nothing is in to
	    if (strcmp(board[x2][y2].name, "---") == 0)
	      return 1;
	    //something is there
	    else
	      return 0;
	  }
	  //diagonal
	  else if (abs(x2-x1) == 1) {
	    //white piece
	    if (board[x2][y2].color == 1)
	      return 0;
	    //either nothing, or own piece
	    else
	      return 0;
	  }
	  else 
	    return 0;
	}
	//moving too many spaces forward/backward
	else 
	  return 0;
      }
      //anywhere else
      else {
	//moves 1 unit
	if ((y2-y1) == -1) {
	  //straight forward
	  if (x2-x1 == 0) {
	    //nothing is in to
	    if (strcmp(board[x2][y2].name, "---") == 0)
	      return 1;
	    //something is there
	    else
	      return 0;
	  }
	  //diagonal
	  else if (abs(x2-x1) == 1) {
	    //white piece
	    if (board[x2][y2].color == 1)
	      return 1;
	    //either nothing, or own piece
	    else
	      return 0;
	  }
	}
      }
    }
    //white
    if (color == 1) {
      //starting position
      if (y1 == 1) {
	if ((y2-y1) == 2 || (y2-y1) == 1) {
	  //straight forward
	  if (x2-x1 == 0) {
	    //nothing is in to
	    if (strcmp(board[x2][y2].name, "---") == 0)
	      return 1;
	    //something is there
	    else
	      return 0;
	  }
	  //diagonal
	  else if (abs(x2-x1) == 1) {
	    //black piece
	    if (board[x2][y2].color == 0)
	      return 1;
	    //either nothing, or own piece
	    else
	      return 0;
	  }
	  else 
	    return 0;
	}
	//moving too many spaces forward/backward
	else 
	  return 0;
      }
      //anywhere else
      else {
	//moves 1 unit
	if ((y2-y1) == 1) {
	  //straight forward
	  if (x2-x1 == 0) {
	    //nothing is in to
	    if (strcmp(board[x2][y2].name, "---") == 0)
	      return 1;
	    //something is there
	    else
	      return 0;
	  }
	  //diagonal
	  else if (abs(x2-x1) == 1) {
	    //black piece
	    if (board[x2][y2].color == 0)
	      return 0;
	    //either nothing, or own piece
	    else
	      return 0;
	  }
	}
      }
    }
  }
  
  //bishop
  if (type == 1) {
    //black
    if (color == 0) {
      //moving diagonally
      if (abs(y2-y1) == abs(x2-x1)) {
	if (x2 > x1 && y2 > y1) {
	  //increment x, increment y
	  int tempx = x1;
	  int tempy = y1;
	  while(tempx != x2 || tempy != y2) {
	    tempx++;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
      
	if (x2 > x1 && y2 < y1) {
	  //increment x, decrement y
	  int tempx = x1;
	  int tempy = y1;
	  while (tempx != x2 || tempy != y1) {
	    tempx++;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 > y1) {
	  //decrement x, increment y
	  int tempx = x2;
	  int tempy = y1;
	  while (tempx != x1 || tempy != y2) {
	    tempx--;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 < y1) {
	  //decrement x, decrement y
	  int tempx = x2;
	  int tempy = y2;
	  while (tempx != x1 || tempy != y1) {
	    tempx--;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;	 
	}
      }
    }
  }
  //white
  if (color == 1) { 
    //moving diagonally
    if (abs(y2-y1) == abs(x2-x1)) {
      if (x2 > x1 && y2 > y1) {
	//increment x, increment y
	int tempx = x1;
	int tempy = y1;
	while(tempx != x2 || tempy != y2) {
	  tempx++;
	  tempy++;
	  if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	    return 0;
	}
	if (strcmp(board[tempx][tempy].name, "---") == 0)
	  return 1;
	else if (board[tempx][tempy].color == 0)
	  return 1;
	else 
	  return 0;
      }
    }
    if (x2 > x1 && y2 < y1) {
      //increment x, decrement y
      int tempx = x1;
      int tempy = y1;
      while (tempx != x2 || tempy != y1) {
	tempx++;
	tempy--;
	if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	  return 0;
      }
      if (strcmp(board[tempx][tempy].name, "---") == 0)
	return 1;
      else if (board[tempx][tempy].color == 0)
	return 1;
      else 
	return 0;
    }
    if (x2 < x1 && y2 > y1) {
      //decrement x, increment y
      int tempx = x2;
      int tempy = y1;
      while (tempx != x1 || tempy != y2) {
	tempx--;
	tempy++;
	if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	  return 0;
      }
      if (strcmp(board[tempx][tempy].name, "---") == 0)
	return 1;
      else if (board[tempx][tempy].color == 0)
	return 1;
      else 
	return 0;
    }
    if (x2 < x1 && y2 < y1) {
      //decrement x, decrement y
      int tempx = x2;
      int tempy = y2;
      while (tempx != x1 || tempy != y1) {
	tempx--;
	tempy--;
	if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	  return 0;
      }
      if (strcmp(board[tempx][tempy].name, "---") == 0)
	return 1;
      else if (board[tempx][tempy].color == 0)
	return 1;
      else 
	return 0;	 
    }
  }

  
  //knight
  if (type == 2) {
    if (color == 0) {
      if (abs(x2-x1) == 1 && abs(y2-y1) == 2) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 1)
	  return 1;
	else 
	  return 0;
      }
      if (abs(x2-x1) == 2 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 1)
	  return 1;
	else
	  return 0;
      }
    }
    if (color == 1) {
      if (abs(x2-x1) == 1 && abs(y2-y1) == 2) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 0)
	  return 1;
	else 
	  return 0;
      }
      if (abs(x2-x1) == 2 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 0)
	  return 1;
	else
	  return 0;
      }
    }
  }

  //rook
  if (type == 3) {
    if (color == 0) {
      if (x2-x1 == 0) {
	if (y2 > y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy++;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 1)
	    return 1;
	  else
	    return 0;
	}
	if (y2 < y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy--;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
      }
      if (y2-y1 == 0) {
	if (x2 > x1) {
	  int tempx = x1;
	  while (tempx != x2) {
	    tempx++;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 1)
	    return 1;
	  else
	    return 0;
	}
	if (x2 < x1) {
	  int tempx= x1;
	  while (tempx != x2) {
	    tempx--;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 1)
	    return 1;
	  else 
	    return 0;
	}
      }
       
    }
    if (color == 1) {
      if (x2-x1 == 0) {
	if (y2 > y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy++;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 0)
	    return 1;
	  else
	    return 0;
	}
	if (y2 < y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy--;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 0)
	    return 1;
	  else 
	    return 0;
	}
      }
      if (y2-y1 == 0) {
	if (x2 > x1) {
	  int tempx = x1;
	  while (tempx != x2) {
	    tempx++;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 0)
	    return 1;
	  else
	    return 0;
	}
	if (x2 < x1) {
	  int tempx= x1;
	  while (tempx != x2) {
	    tempx--;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 0)
	    return 1;
	  else 
	    return 0;
	}
      }
       
    }
  }

  //queen
  if (type == 4) {
    if (color == 0) {
      //diagonals
      if (abs(y2-y1) == abs(x2-x1)) {
	if (x2 > x1 && y2 > y1) {
	  //increment x, increment y
	  int tempx = x1;
	  int tempy = y1;
	  while(tempx != x2 || tempy != y2) {
	    tempx++;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
	
	if (x2 > x1 && y2 < y1) {
	  //increment x, decrement y
	  int tempx = x1;
	  int tempy = y1;
	  while (tempx != x2 || tempy != y1) {
	    tempx++;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 > y1) {
	  //decrement x, increment y
	  int tempx = x2;
	  int tempy = y1;
	  while (tempx != x1 || tempy != y2) {
	    tempx--;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 < y1) {
	  //decrement x, decrement y
	  int tempx = x2;
	  int tempy = y2;
	  while (tempx != x1 || tempy != y1) {
	    tempx--;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 1)
	    return 1;
	  else 
	    return 0;	 
	}
      }
      //horizontal
      if (x2-x1 == 0) {
	if (y2 > y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy++;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 1)
	    return 1;
	  else
	    return 0;
	}
	if (y2 < y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy--;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 1)
	    return 1;
	  else 
	    return 0;
	}
      }
      //vertical
      if (y2-y1 == 0) {
	if (x2 > x1) {
	  int tempx = x1;
	  while (tempx != x2) {
	    tempx++;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 1)
	    return 1;
	  else
	    return 0;
	}
	if (x2 < x1) {
	  int tempx= x1;
	  while (tempx != x2) {
	    tempx--;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 1)
	    return 1;
	  else 
	    return 0;
	}
      }
       
    }
    if (color == 1) {
      //diagonals
      if (abs(y2-y1) == abs(x2-x1)) {
	if (x2 > x1 && y2 > y1) {
	  //increment x, increment y
	  int tempx = x1;
	  int tempy = y1;
	  while(tempx != x2 || tempy != y2) {
	    tempx++;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 0)
	    return 1;
	  else 
	    return 0;
	}
	
	if (x2 > x1 && y2 < y1) {
	  //increment x, decrement y
	  int tempx = x1;
	  int tempy = y1;
	  while (tempx != x2 || tempy != y1) {
	    tempx++;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 0)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 > y1) {
	  //decrement x, increment y
	  int tempx = x2;
	  int tempy = y1;
	  while (tempx != x1 || tempy != y2) {
	    tempx--;
	    tempy++;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 0)
	    return 1;
	  else 
	    return 0;
	}
	if (x2 < x1 && y2 < y1) {
	  //decrement x, decrement y
	  int tempx = x2;
	  int tempy = y2;
	  while (tempx != x1 || tempy != y1) {
	    tempx--;
	    tempy--;
	    if (!(strcmp(board[tempx][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][tempy].name, "---") == 0)
	    return 1;
	  else if (board[tempx][tempy].color == 0)
	    return 1;
	  else 
	    return 0;	 
	}
      }
      //horizontal
      if (x2-x1 == 0) {
	if (y2 > y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy++;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 0)
	    return 1;
	  else
	    return 0;
	}
	if (y2 < y1) {
	  int tempy = y1;
	  while (tempy != y2) {
	    tempy--;
	    if (!(strcmp(board[x2][tempy].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[x2][tempy].name, "---") == 0)
	    return 1;
	  else if (board[x2][tempy].color == 0)
	    return 1;
	  else 
	    return 0;
	}
      }
      //vertical
      if (y2-y1 == 0) {
	if (x2 > x1) {
	  int tempx = x1;
	  while (tempx != x2) {
	    tempx++;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 0)
	    return 1;
	  else
	    return 0;
	}
	if (x2 < x1) {
	  int tempx= x1;
	  while (tempx != x2) {
	    tempx--;
	    if (!(strcmp(board[tempx][y2].name, "---") == 0))
	      return 0;
	  }
	  if (strcmp(board[tempx][y2].name, "---") == 0)
	    return 1;
	  else if (board[tempx][y2].color == 0)
	    return 1;
	  else 
	    return 0;
	}
      }
      
    }
  }

  //king
  if (type == 5) {
    //black
    if (color == 0) {
      //vertical
      if (abs(x2-x1) == 1 && (y2-y1) == 0) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 1)
	  return 1;
	else
	  return 0;
      }
      //horizontal 
      if ((x2-x1) == 0 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 1)
	  return 1;
	else
	  return 0;
      }
      //diagonal
      if (abs(x2-x1) == 1 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;	
	else if (board[x2][y2].color == 1)
	  return 1;
	else return 0;
      }
    }
    //white
    if (color == 1) {
      //vertical
      if (abs(x2-x1) == 1 && (y2-y1) == 0) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 0)
	  return 1;
	else
	  return 0;
      }
      //horizontal 
      if ((x2-x1) == 0 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;
	else if (board[x2][y2].color == 0)
	  return 1;
	else
	  return 0;
      }
      //diagonal
      if (abs(x2-x1) == 1 && abs(y2-y1) == 1) {
	if (strcmp(board[x2][y2].name, "---") == 0)
	  return 1;	
	else if (board[x2][y2].color == 0)
	  return 1;
	else return 0;
      }
    }
  }
  return 0;
}

void move(char ** input, piece board[8][8]) {
  
  int *pieces;
  int *from;
  int *to;

  pieces = translatePiece(input[0]);
  from = translateCoord(input[1]);
  to = translateCoord(input[2]);

  int color = pieces[0];
  int type = pieces[1];
  int x1 = from[0]; 
  int y1 = from[1];
  int x2 = to[0];
  int y2 = to[1];
  
  char * tempName = (char *) malloc(sizeof(char) *3);
  int tempColor;

  if (checkMoves(pieces, from, to, board)) {
    
    tempName = board[x1][y1].name;
    tempColor = board[x1][y1].color;
    
    board[x1][y1].name = "---";
    board[x1][y1].color = -1;
    
    board[x2][y2].name = tempName;
    board[x2][y2].color = tempColor;
    

    free(pieces);
    free(from);
    free(to);
  }

  else {
    printf("Invalid move");
    free(pieces);
    free(from);
    free(to);
  }
      
    
    
}


void printboard(piece same[8][8]){
  int j,k;
  for ( j=0 ; j < 8; j++){
    for ( k=0; k < 8; k++){
      printf(" %s ", same[j][k].name);
    }
    printf("\n");
  }
}  
