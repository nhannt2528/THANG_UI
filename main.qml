import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: Qt.desktop.screenGeometry.width
    height: Qt.desktop.screenGeometry.height
    visible: true
    title: qsTr("Hello World")
    visibility: Window.FullScreen
    Image {
        id: idBackground
        source: "qrc:/image/2.png"
        anchors.fill: parent
    }


}
