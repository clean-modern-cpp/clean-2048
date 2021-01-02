import QtQuick 2.0

Rectangle {
    id: cell
    color: "transparent"
    
    property var colors: { "": "white", "2": "#eee4da", "4": "#ece0c8", "8": "#f2b179", "16": "#f59563",
        "32": "#f57c5f", "64": "#f95c3b", "128": "#edce71", "256": "#eecc61",
        "512": "#ebc850", "1024": "#edc53f" , "2048": "#eec22e", "4096": "#3d3a33",
        "8192": "#3d3a33", "16384": "#3d3a33" }

    property var fontSize: { 0: 1, 1: 45, 2: 40, 3: 35, 4: 30 }

    property var value: ""
    property var animMoveEnable: false
    property var animResizeEnable: false

    Rectangle {
        id: background
        width: parent.width - 10
        height: parent.height - 10
        color: colors[cell.value]
        radius: 3
        anchors.centerIn: parent

        Text {
            id: label
            color: cell.value == "2" || cell.value == "4" ? "#786f66" : "#f7f8f0"
            text: cell.value
            font.family: "Tahoma"
            font.bold: true
            anchors.centerIn: parent
            font.pixelSize: fontSize[cell.value.length]
            horizontalAlignment: Text.AlignHCenter
        }

        Behavior on width {
            enabled: animResizeEnable
            NumberAnimation {
                duration: 100
            }
        }

        Behavior on height {
            enabled: animResizeEnable
            NumberAnimation {
                duration: 100
            }
        }
    }

    Behavior on x {
        enabled: animMoveEnable
        NumberAnimation {
            duration: 100
        }
    }

    Behavior on y {
        enabled: animMoveEnable
        NumberAnimation {
            duration: 100
        }
    }
}
