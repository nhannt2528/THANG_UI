
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQuick.Controls 1.4
import QtQml 2.14


Item{
    id:root
    width: 300
    height: 300
    property int m_angle: 0

    Timer{
        id:m_timer
        interval: 500
        repeat: true
        running: true
        onTriggered: {
            m_angle=getRandomNumber(0,90);
        }
    }
    function getRandomNumber(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    Image {
        id: idAngle
        source: "qrc:/images/la ban.png"
        width: root.width
        height: root.height
        anchors.horizontalCenter: idNeedle.horizontalCenter
        anchors.verticalCenter: idNeedle.verticalCenter
        transformOrigin: root.Center
        rotation: m_angle
        //    RotationAnimation on rotation {
        //             id: rotationAnimation
        //             from: 0
        //             to: 90
        //             duration: 1 // milliseconds
        //             running: true
        //         }
    }
    Image {
        id: idNeedle
        width: root.width-25
        height: root.height-25
        source: "qrc:/images/Kim la ban.png"

    }
}
