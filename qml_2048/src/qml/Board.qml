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

        property var rows
        property var cols

        Repeater {
            model: grid.rows * grid.cols

            Rectangle {
                height: grid.height / grid.rows
                width: grid.width / grid.cols
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

    Keys.onPressed: {
        boardViewModel.swipe(event.key);
    }

    property var cells: []

    BoardViewModel {
        id: boardViewModel
    }

    Connections {
        target: boardViewModel

        function onInitWith(rows, cols) {
            for (var i = 0; i < cells.length; ++i) {
                for (var j = 0; j < cells[i].length; ++j) {
                    if (cells[i][j] != 0) {
                        cells[i][j].destroy();
                    }
                }
            }
            grid.rows = rows
            grid.cols = cols
            for (var i = 0; i < rows; ++i) {
                cells[i] = []
                for (var j = 0; j < cols; ++j) {
                    cells[i][j] = 0
                }
            }
        }

        function onNewCell(row, col, value) {
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

        function onStartCellMove(fromRow, fromCol, toRow, toCol) {
            var cell = cells[fromRow][fromCol];
            cell.animMoveEnable = true;
            cell.animResizeEnable = false;
            cell.x = cell.width * toCol;
            cell.y = cell.height * toRow;
        }

        function onCompleteCellMove(fromRow, fromCol, toRow, toCol) {
            if (cells[toRow][toCol] != 0) {
                cells[toRow][toCol].destroy();
            }
            cells[toRow][toCol] = cells[fromRow][fromCol];
            cells[fromRow][fromCol] = 0;
        }

        function onMergeCell(row, col, toValue) {
            cells[row][col].value = toValue;
        }
    }
}
