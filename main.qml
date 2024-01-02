import QtQuick 2.15
import QtQuick.Window 2.15

import "qrc:/background"
import "qrc:/gause"


Window {
    //    width: Qt.desktop.screenGeometry.width
    //    height: Qt.desktop.screenGeometry.height
    property int scale_compoent: (3696-3001)/3696*100
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Gyro Compass")
    //    visibility: Window.FullScreen
    CustomBackground{
        width: 1920
        height: 1080
    }
           ADIGause{
                id: adiGauseId
                width: 400
                height: 400
            }
//    Row{
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenter: parent.verticalCenter
//        spacing: 50
//        ADIGause{
//            id: adiGauseId
//            width: 400
//            height: 400
//        }
//        GyroCompassGause{
//            id: gyroCompassId

//            width: 310
//            height: width
////            anchors.verticalCenter: adiGauseId.verticalCenter
//            anchors.top: adiGauseId.top
//            anchors.topMargin: 100

//        }

//    }




}
