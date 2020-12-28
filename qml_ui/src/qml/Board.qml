import QtQuick 2.0
import BoardViewModel 1.0

Rectangle {
    id: board
    color: "#bbada0"
    focus: true
    radius: 3;

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
            cells[i] = []
            for (var j = 0; j < boardViewModel.columns; ++j) {
                cells[i][j] = 0
            }
        }
        boardViewModel.restart();
    }

    Keys.onPressed: {
        boardViewModel.swipe(event.key);
    }

    property var cells: []

    BoardViewModel {
        id: boardViewModel
    }

    Connections {
        target: boardViewModel
        onCellCreated: {
            var component = Qt.createComponent("Cell.qml");
            var cell = component.createObject(board);
            cell.value = value;
            cell.animMoveEnable = false;
            cell.animResizeEnable = true;
            cell.width = board.width / 4;
            cell.height = board.height / 4;
            cell.x = cell.width * col;
            cell.y = cell.height * row;
            cells[row][col] = cell;
        }

        onCellMoveStarted: {
            var cell = cells[fromRow][fromCol];
            cell.animMoveEnable = true;
            cell.animResizeEnable = false;
            cell.x = cell.width * toCol;
            cell.y = cell.height * toRow;
        }

        onCellMoveEnded: {
            if (cells[toRow][toCol] != 0) {
                cells[toRow][toCol].destroy();
            }
            cells[toRow][toCol] = cells[fromRow][fromCol];
            cells[fromRow][fromCol] = 0;
        }

        onCellChanged: {
            cells[row][col].value = value;
        }
    }
}
