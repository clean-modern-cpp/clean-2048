import QtQuick 2.0
import BoardViewModel 1.0

Rectangle {
    id: board

    property var arrCells: []
    property var moving: false

    color: "#bbada0"
    focus: true
    radius: 3;

    BoardViewModel {
        id: boardViewModel
    }

    anchors {
        left: parent.left
        right: parent.right 
        top: parent.top
        bottom: parent.bottom 
        leftMargin: 5
        rightMargin: 5
        topMargin: 100
        bottomMargin: 5
    }

    Grid {
        id: grid
        anchors.fill: parent
        Repeater {
            model: boardViewModel.rows * boardViewModel.columns

            Rectangle {
                height: grid.height / boardViewModel.rows
                width: grid.width / boardViewModel.columns
                color: "transparent";
                Rectangle {
                    color: "#ccc0b2"
                    radius: 3
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                        top: parent.top
                        leftMargin: 5
                        rightMargin: 5
                        topMargin: 5
                        bottomMargin: 5
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        for (var i = 0; i < boardViewModel.rows; ++i) {
            arrCells[i] = []
            for (var j = 0; j < boardViewModel.columns; ++j) {
                arrCells[i][j] = 0;
            }
        }
        boardViewModel.board = board;
        boardViewModel.restart();
    }

    Timer {
        id: movingTimer
        interval: 100; running: false;
        onTriggered: {
            onAnimEnd();
        }
    }

    Keys.onPressed: {
        boardViewModel.swipe(event.key);
        movingTimer.start();
        for (var i = 0; i < boardViewModel.movePositionLength(); ++i) {
            var fromRow = boardViewModel.fromRow(i);
            var fromColumn = boardViewModel.fromColumn(i);
            var toRow = boardViewModel.toRow(i);
            var toColumn = boardViewModel.toColumn(i);
            var cell = arrCells[fromRow][fromColumn];
            cell.x = cell.width * toColumn;
            cell.y = cell.height * toRow;
            cell.animMoveEnable = true;
            arrCells[toRow][toColumn] = cell;
            arrCells[fromRow][fromColumn] = 0;
        }
    }

    function createCells() {
        cleanCells();
        for (var row = 0; row < boardViewModel.rows; ++row) {
            for (var column = 0; column < boardViewModel.columns; ++column) {
                var value = boardViewModel.numberOf(row, column);
                if (value !== 0) {
                    create(row, column, value, false);
                }
            }
        }
    }

    function cleanCells() {
        for (var i = 0; i < boardViewModel.rows; ++i) {
            for (var j = 0; j < boardViewModel.columns; ++j) {
                if (arrCells[i][j] != 0) {
                    arrCells[i][j].destroy()
                    arrCells[i][j] = 0;
                }
            }
        }
    }

    function create(row, col, value, respaun) {
        console.log(row, col, value, respaun);
        var component = Qt.createComponent("Cell.qml");
        var object = component.createObject(board);
        object.value = value;
        object.animResizeEnable = respaun;
        object.x = object.width * col;
        object.y = object.height * row;
        object.size = Qt.size(width / boardViewModel.rows - 10, height / boardViewModel.columns - 10);
        return object;
    }

    function onAnimEnd() {
        cleanCells();
        for (var i = 0; i < boardViewModel.rows; ++i) {
            for (var j = 0; j < boardViewModel.columns; ++j) {
                var value = boardViewModel.numberOf(i, j);
                if (value != 0) {
                    create(i, j, value, false);
                }
            }
        }
        moving = false;
        boardViewModel.rndBlock();
        for (var i = 0; i < boardViewModel.rows; ++i) {
            for (var j = 0; j < boardViewModel.columns; ++j) {
                var value = boardViewModel.numberOf(i, j);
                if (value != 0 && arrCells[i][j] == 0) {
                    create(i, j, value, true);
                }
            }
        }
    }
}
