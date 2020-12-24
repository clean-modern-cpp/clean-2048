.pragma library

var columns = 4;
var rows = 4;

var arrGrid = [];
var arrCells = [];
var baseObj = null;
var moving = false;

function isNextStep() {
    for (var i = 0; i < rows; ++i) {
        for (var j = 0; j < columns - 1; ++j) {
            if (arrGrid[i][j] === arrGrid[i][j + 1])
                return true;
        }
    }

    for (var i = 0; i < rows - 1; ++i) {
        for (var j = 0; j < columns; ++j) {
            if (arrGrid[i][j] === arrGrid[i + 1][j])
                return true;
        }
    }

    return false;
}

function gameOver() {
    moving = true;
    baseObj.scoreBoard.bestScore = Math.max(baseObj.scoreBoard.score, baseObj.scoreBoard.bestScore);
    baseObj.gameOverWnd.visible = true;
    baseObj.gameOverWnd.animateOpacity.start();
    console.log("game over")
}
