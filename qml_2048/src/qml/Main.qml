import QtQuick 2.2
import QtQuick.Controls 1.1
import Controller 1.0
import GameOverViewModel 1.0

ApplicationWindow {
    id: window;
    visible: true
    width: 380
    height: 480
    title: qsTr("2048")
    color: "#fbf8ef"

    ScoreBoard {
        id: scoreBoard;
    }

    Board {
       id: board
    }

    GameOverView {
        id: gameOverView
    }

    Controller {
        id: controller
    }

    GameOverViewModel {
        id: gameOverViewModel
    }

    Connections {
        target: gameOverViewModel

        function onGameOver() {
            gameOverView.visible = true;
            gameOverView.opacity = 1.0;
        }
    }

    Connections {
        target: gameOverView

        function onNewGameButtonClicked() {
            controller.newGame();
            gameOverView.opacity = 0.0;
            gameOverView.visible = false;
        }
    }

    Connections {
        target: scoreBoard

        function onNewGameButtonClicked() {
            controller.newGame();
        }
    }

    Component.onCompleted: {
        controller.loadGame();
    }

    Component.onDestruction: {
        controller.saveGame();
    }
}
