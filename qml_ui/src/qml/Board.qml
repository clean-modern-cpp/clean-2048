import QtQuick 2.0
import BoardViewModel 1.0

Rectangle {
    id: board
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
    }

    function onAnimEnd() {
        for (var i = 0; i < boardViewModel.rows; ++i) {
            for (var j = 0; j < boardViewModel.columns; ++j) {
                var value = boardViewModel.numberOf(i, j);
                if (value != 0) {
                    create(i, j, value, false);
                }
            }
        }
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
