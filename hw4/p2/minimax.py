# from eval_funcs import positionalEval
# from make_move import makeMove
# from available_spot import getAvailableSpot

from .eval_funcs import posEval, posEvalEndgameVariation
from .make_move import makeMove
from .available_spot import getAvailableSpot

evalBoard = posEvalEndgameVariation

def minimax(obs, color, depth, alpha, beta):
    '''
    Find optimal position in the game.

    - inputs
      obs: 1d list, current board. white = 1, black = -1, empty = 0
      color: int, player color. same as obs
      depth: int, layers to search through.
      alpha: -infinity when starts, we'll work our way up
      beta: infinity when starts, we'll work our way down

      evalBoard: function that takes a board to evaluate, returns an integer. 
                 larger value if white is more likely to win, vise versa.

    - output
      integer: best position
      integer: value
    '''
    
    if depth == 0:
        return None, evalBoard(obs)

    moves = getAvailableSpot(obs, color)
    if color == 1:
        value = -float('inf')
        bestmove = None
        if len(moves) == 0: # no move, proceed to other player
            _ ,newValue = minimax(obs, -color, depth-1, alpha, beta)
            if newValue > value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _ ,newValue = minimax(newBoard, -color, depth-1, alpha, beta)
            if newValue > value:
                value = newValue
                bestmove = move
            alpha = max(alpha, value)
            if beta <= alpha:
                break

    else:
        value = float('inf')
        bestmove = None
        if len(moves) == 0:
            _, newValue = minimax(obs, -color, depth-1, alpha, beta)
            if newValue < value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _, newValue = minimax(newBoard, -color, depth-1, alpha, beta)
            if newValue < value:
                value = newValue
                bestmove = move
            beta = min(beta, value)
            if beta <= alpha:
                break
    return bestmove, value

def minimax_adj(obs, color, depth, alpha, beta, eval_func):
    if depth == 0:
        return None, eval_func(obs)

    moves = getAvailableSpot(obs, color)
    if color == 1:
        value = -float('inf')
        bestmove = None
        if len(moves) == 0: # no move, proceed to other player
            _ ,newValue = minimax(obs, -color, depth-1, alpha, beta)
            if newValue > value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _ ,newValue = minimax(newBoard, -color, depth-1, alpha, beta)
            if newValue > value:
                value = newValue
                bestmove = move
            alpha = max(alpha, value)
            if beta <= alpha:
                break

    else:
        value = float('inf')
        bestmove = None
        if len(moves) == 0:
            _, newValue = minimax(obs, -color, depth-1, alpha, beta)
            if newValue < value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _, newValue = minimax(newBoard, -color, depth-1, alpha, beta)
            if newValue < value:
                value = newValue
                bestmove = move
            beta = min(beta, value)
            if beta <= alpha:
                break
    return bestmove, value

def minimaxCount(obs, color, depth, alpha, beta):
    '''
    same as minimax, added count for statistics
    '''
    
    if depth == 0:
        return None, evalBoard(obs), 1

    moves = getAvailableSpot(obs, color)
    countSum = 0
    if color == 1:
        value = -float('inf')
        bestmove = None
        if len(moves) == 0: # no move, proceed to other player
            _ ,newValue, count = minimaxCount(obs, -color, depth-1, alpha, beta)
            countSum += count
            if newValue > value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _ ,newValue, count = minimaxCount(newBoard, -color, depth-1, alpha, beta)
            countSum += count
            if newValue > value:
                value = newValue
                bestmove = move
            alpha = max(alpha, value)
            if beta <= alpha:
                break

def minimax_color(obs, color, depth, alpha, beta, eval_func):
    '''
    Find optimal position in the game.

    - inputs
      obs: 1d list, current board. white = 1, black = -1, empty = 0
      color: int, player color. same as obs
      depth: int, layers to search through.
      alpha: -infinity when starts, we'll work our way up
      beta: infinity when starts, we'll work our way down

      evalBoard: function that takes a board to evaluate, returns an integer. 
                 larger value if white is more likely to win, vise versa.

    - output
      integer: best position
      integer: value
    '''

    if depth == 0:
        return None, eval_func(obs, color)

    moves = getAvailableSpot(obs, color)
    if color == 1:
        value = -float('inf')
        bestmove = None
        if len(moves) == 0:  # no move, proceed to other player
            _, newValue = minimax_color(obs, -color, depth-1, alpha, beta, eval_func)
            if newValue > value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _, newValue = minimax_color(newBoard, -color, depth-1, alpha, beta, eval_func)
            if newValue > value:
                value = newValue
                bestmove = move
            alpha = max(alpha, value)
            if beta <= alpha:
                break

    else:
        value = float('inf')
        bestmove = None
        if len(moves) == 0:
            _, newValue = minimax_color(obs, -color, depth-1, alpha, beta, eval_func)
            if newValue < value:
                value = newValue
        for move in moves:
            newBoard = makeMove(obs, move, color)
            _, newValue = minimax_color(newBoard, -color, depth-1, alpha, beta, eval_func)
            if newValue < value:
                value = newValue
                bestmove = move
            beta = min(beta, value)
            if beta <= alpha:
                break
    return bestmove, value
