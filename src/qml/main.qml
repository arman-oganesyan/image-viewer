import QtQuick 2.9
import QtQuick.Window 2.3
import Qt.labs.platform 1.0
import QtQuick.Controls 2.2
import CoreState 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image Viewer")

    property url selectedUrl: ""

    onClosing: {
        if (core.state != CoreState.Idle) {
            close.accepted = false
            warningDialog.open()
        }
    }

    MessageDialog {
        id: warningDialog
        text: qsTr('Application is still processing files. Please wait until it finishes or cancel the task')
        buttons: MessageDialog.Ok
    }

    FolderDialog {
        id: folderDialog
        flags: FolderDialog.ShowDirsOnly | FolderDialog.ReadOnly
        folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted: {
            textFolder.text = folder.toString().replace(/^(file:\/{3})/,"")
            selectedUrl = folder
        }
    }

    Item {
        anchors.fill: parent
        anchors.margins: 5

        Text {
            id: textFolder
            anchors.left: parent.left
            anchors.bottom: buttonSelectFolder.bottom
            anchors.right: buttonSelectFolder.left
            anchors.top: parent.top
            anchors.rightMargin: 5
            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideMiddle

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.width: 1
                border.color: "black"
            }
        }

        Button {
            id: buttonSelectFolder
            anchors.top: parent.top
            anchors.right: parent.right
            enabled: core.state === CoreState.Idle
            text: qsTr("Select folder...")
            onClicked: {
                folderDialog.open()
            }
        }

        ListView {
            id: listView
            anchors.top: buttonSelectFolder.bottom
            anchors.bottom: buttonStart.top
            anchors.left: parent.left
            anchors.right: slider.left
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            spacing: 10
            clip: true
            model: core.model()

            delegate: Item {
                width: Math.min(imageWidth, parent.width)
                height: imageHeight * (width / imageWidth)

                Image {
                    anchors.fill: parent
                    asynchronous: true
                    source: "file:///" + path
                    fillMode: Image.Stretch
                    cache: true
                }
            }

            Rectangle {
                anchors.fill: parent
                border.width: 1
                border.color: "black"
                color: "transparent"
            }

            Connections {
                id: connectionsSlider
                target: slider
                function onValueChanged() {
                    connectionListView.enabled = false
                    if (listView.count === 0 | slider.value == 0)
                        listView.positionViewAtBeginning()
                    else
                        listView.positionViewAtIndex(slider.value - 1, ListView.Beginning )
                    connectionListView.enabled = true
                }
            }
        }

        Slider {
            id: slider
            anchors.right: parent.right
            anchors.top: buttonSelectFolder.bottom
            anchors.bottom: buttonStart.top
            orientation: Qt.Vertical
            from: to === 0 ? 0 : 1
            stepSize: 1.0
            to: listView.count
            rotation: 180

            Timer {
                id: timerY
                interval: 250
                repeat: false
                onTriggered: {
                    connectionsSlider.enabled = false
                    var index = listView.indexAt(0, listView.contentY)
                    if (index !== -1) slider.value = index + 1
                    connectionsSlider.enabled = true
                }
            }

            Connections {
                id: connectionListView
                target: listView
                function onContentYChanged() {
                    timerY.restart()
                }
            }
        }

        Text {
            id: textCount
            anchors.left: parent.left
            anchors.top: buttonStart.top
            anchors.right: buttonStart.left
            anchors.bottom: buttonStart.bottom
            height: 20
            anchors.rightMargin: 5
            verticalAlignment: Text.AlignVCenter

            function updateText() {
                textCount.text = qsTr("At: ") + slider.value + qsTr(". Items count: ") + listView.count
            }

            Connections {
                target: listView
                function onCountChanged() {
                    textCount.updateText()
                }
            }

            Connections {
                target: slider
                function onValueChanged() {
                    textCount.updateText()
                }
            }

            elide: Text.ElideMiddle

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.width: 1
                border.color: "black"
            }
        }

        Button {
            id: buttonStart
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            text: core.state == CoreState.Idle ? qsTr("Go!") : (core.state == CoreState.Working ? qsTr("Stop") : qsTr("Stopping...") )
            enabled: textFolder.text && core.state != CoreState.Stopping
            onClicked: {
                if (core.state == CoreState.Idle)
                    core.start(selectedUrl)
                else if (core.state == CoreState.Working)
                    core.stop()
            }
        }
    }
}
