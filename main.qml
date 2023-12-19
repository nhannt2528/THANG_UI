import QtQuick 2.15
import QtQuick.Window 2.15

import "qrc:/background"
import "qrc:/gause"

Window {
    //    width: Qt.desktop.screenGeometry.width
    //    height: Qt.desktop.screenGeometry.height
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")
    //    visibility: Window.FullScreen
    CustomBackground{
        width: 1920
        height: 1080
    }
    GyroCompassGause{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }




}
