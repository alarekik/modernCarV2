import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation 5.11
import QtPositioning 5.0
import QtMultimedia 5.15

ApplicationWindow {
    id:root
    width: Screen.width
    height: Screen.height
    // visibility: "FullScreen"
    visible: true
    title: qsTr("Car Dashboard By Aksh")
    color: "#000000"
    property bool isIncrementing     : true
    property bool isIncrementingleft : true
    property bool batisinc           : true
    property bool mapon: false
    //------------test radar -----------

    Connections {
        target: uartport
        function onDataReceived(message) {
            console.log("Received in QML:", message)
            if(!mapon){

                if (message === "01") {
                    road.visible = false
                    roadalert.visible = true
                } else {
                    road.visible = true
                    roadalert.visible = false
                }
            }
        }
    }
    Connections{
        target: bcg
        function onBcgdatarecived(messageH,messageB){
            console.log("Received in QML value of heart",messageH)
            console.log("Received in QML value of breath",messageB)
            heartvalue.text=bcg.lastheartValue;
            breathvalue.text=bcg.lastbreathValue;
        }
    }
    Image {
        id : backgroundcluster
        anchors.centerIn: parent
        sourceSize: Qt.size(1200,720)
        source: "qrc:/icons/Base.svg"



        Image{
            id:topNavigation
            anchors{
                bottom:navigation_car.top
                bottomMargin: 50
                horizontalCenter: parent.horizontalCenter
            }

            source: "qrc:/icons/Top Navigation.svg"

            RowLayout{
                anchors.centerIn: parent
                spacing: 60
                MyButton{
                    setIcon: isGlow ? "qrc:/icons/light/bcgicon.png" : "qrc:/icons/bcg_icon.png"
                    onClicked: {

                        isGlow = !isGlow;
                        breathrate.visible=!(breathrate.visible);
                        heartbeat.visible=!(heartbeat.visible);
                    }

                }
                MyButton{
                    setIcon: isGlow ? "qrc:/icons/light/camera_icon.png" :  "qrc:/icons/cameraicon.png"
                    onClicked : {
                        isGlow = !isGlow;
                        //leftGauge.visible = ! ( leftGauge.visible);
                        blockcamera.visible = ! ( blockcamera.visible);
                    }
                }
                MyButton{
                    isGlow : true
                    setIcon: isGlow ? "qrc:/icons/light/on_volvo.png" : "qrc:/icons/off_volvo.png"
                    onClicked:{

                        isGlow = !isGlow;
                        canbus.sendCanMessage();
                    }
                }

                MyButton{
                    setIcon: isGlow ? "qrc:/icons/light/eva_phone-call-fill.svg" :  "qrc:/icons/eva_phone-call-fill.svg"
                    onClicked:{
                        isGlow = !isGlow;

                        // road.visible = !(road.visible);
                        // roadalert.visible = !(roadalert.visible);
                    }
                }
                MyButton{
                    id : mapButton
                    setIcon: isGlow ? "qrc:/icons/light/mapi_con.png" :  "qrc:/icons/mapicon.png"
                    onClicked : {
                        isGlow = !isGlow;
                        mapon =isGlow;
                        if (mapon){
                            rectanglemap.visible=true;
                            road.visible = false;
                            roadalert.visible =false;
                            light.visible =false;
                            car.visible = false;

                        }
                        else {
                            rectanglemap.visible=false;
                            road.visible = true;
                            light.visible = true;
                            car.visible = true;
                        }
                    }
                }
            }

        }


        SideGauge {
            id:leftGauge
            visible: true
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: parent.width/10
            }
            property bool accelerating
            //this value was change and the old value was height and width 400
            width: 400
            height: 400
            value: accelerating ? maximumValue : 0
            maximumValue: 250
            Component.onCompleted: forceActiveFocus()
            Behavior on value { NumberAnimation { duration: 1000 }}

            Keys.onSpacePressed: accelerating = true
            Keys.onReturnPressed: rightGauge.accelerating = true
            Keys.onReleased: {car
                if (event.key === Qt.Key_Space) {
                    accelerating = false;
                    event.accepted = true;
                }else if(event.key === Qt.Key_Return){
                    rightGauge.accelerating = false;
                    event.accepted = true;
                }
            }
        }

        Image {
            id:navigation_car
            visible: false
            anchors.centerIn: parent
            source: "qrc:/icons/Navigation.png"
        }

        RowLayout{
            id:speedLimit
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 26.50 + 65
            Label{
                text: "P"
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                color: "#FFFFFF"
            }

            Label{
                text: "R"
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
            Label{
                text: "N"
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
            Label{
                text: "D"
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
        }
        Image {
            id : light
            anchors{
                bottom: car.top
                bottomMargin: -60
                horizontalCenter:car.horizontalCenter
            }
            source: "qrc:/icons/Headlights.svg"
            width: 150
            height: 150
        }

        Image {
            id:car
            anchors{
                bottom: speedLimit.top
                bottomMargin: 10
                horizontalCenter:speedLimit.horizontalCenter
            }
            source: "qrc:/img/volvo.png"
            width: 200
            height: 150


        }
        //-------------------------road section ---------------------------------------
        Image {
            id: road
            visible: true
            source: "qrc:/img/road.png"
            width: 400
            height: backgroundcluster.height - 300
            anchors.centerIn: backgroundcluster
        }
        Image {
            id: roadalert
            visible: false
            source: "qrc:/img/roadalert.png"
            width: 400
            height: backgroundcluster.height - 300
            anchors.centerIn: backgroundcluster
        }
        RowLayout{
            spacing: 20
              //this op MPH
            anchors{
                left: parent.left
                leftMargin: 100
                bottom: parent.bottom
                bottomMargin: 26.50 + 65
            }

            RowLayout{
                spacing: 1
                Layout.topMargin: 10
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 31.25 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 62.5 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 93.75 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 125.25 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 156.5 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 187.75 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 219 ? leftGauge.speedColor : "#01E6DC"
                }
            }

            Label{
                text: leftGauge.value.toFixed(0) + " KM/H "
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                color: "#FFFFFF"
            }
        }
           //-----------------------------bat sec--------------------

        Image {
            id: battery
            property int batvalue: 0
            source: "qrc:/icons/battery.png"
            anchors{
                right:  backgroundcluster.right
                rightMargin:  250
                bottom: backgroundcluster.bottom
                bottomMargin: 75
            }
            width: 150
            height: 100
            ColumnLayout{
                spacing: 2
                Layout.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 2
                Rectangle{
                    width: 20
                    height: 9
                    color:  battery.batvalue >75 ? "#B8FF01" : "black"
                }
                Rectangle{
                    width: 20
                    height: 9
                    color: battery.batvalue > 50 ? "#B8FF01" : "black"
                }
                Rectangle{
                    width: 20
                    height: 9
                    color: battery.batvalue >25 ? "#B8FF01" : "black"
                }
                Rectangle{
                    width: 20
                    height: 9
                    color: battery.batvalue > 0 ? "#B8FF01" : "black"
                }
            }
            Label{
                text: battery.batvalue + " % "
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                color: "#FFFFFF"
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 2
                anchors.left: parent.right
                anchors.leftMargin: -55
            }
        }
        SideGauge {
            id:rightGauge
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: parent.width/10
            }
            property bool accelerating
            //-----------------
            width: 400
            height: 400
            //-------------------------------
            value: accelerating ? maximumValue : 0
            maximumValue: 250
            Behavior on value { NumberAnimation { duration: 1000 }}
        }
    }

    //-----------------------------animation section----------------------------------------------
    Timer {
            id: valueSenderTimer
            interval: 200
            repeat: true
            running: true

            onTriggered: {
                if (isIncrementing)
                {
                    rightGauge.value += 50;
                    if (rightGauge.value>= 250)
                    {
                        isIncrementing = false;
                    }
                }
                else
                {
                    rightGauge.value -= 50;
                    if (rightGauge.value <= 0)
                    {
                        isIncrementing = true;
                    }
                }
                if (isIncrementingleft)
                {
                    leftGauge.value  += 20;
                    if (leftGauge.value >= 250)
                    {
                        isIncrementingleft = false;
                    }
                }
                else
                {
                    leftGauge.value -= 20;
                    if (leftGauge.value  <= 0)
                    {
                        isIncrementingleft  = true;
                    }
                }
                if (batisinc){
                    battery.batvalue +=5;
                    if(battery.batvalue==100){
                        batisinc=false;
                    }
                }
                else{
                    battery.batvalue -=5;
                    if(battery.batvalue==0){
                        batisinc=true;
                    }
                }

            }

        }

    //------------------------------------Camera Section---------------------------------------

    Rectangle {
            id:blockcamera
            width: 300
            height: 300
            visible: false
            color: "transparent"
            radius: 150   // Half of width/height for perfect circle
            clip: true
            anchors{
                verticalCenter: backgroundcluster.verticalCenter
                left: backgroundcluster.left
                leftMargin: backgroundcluster.width/7
            }


//-------------------------------
            Camera {
                id: camera
                captureMode: Camera.CaptureViewfinder
                Component.onCompleted: {
                    camera.start();
                }
                onError: {
                    console.log("Camera error: " + errorString);
                }
            }

                VideoOutput {
                    id: viewfinder
                    anchors.fill: parent
                    source: camera
                    fillMode: VideoOutput.PreserveAspectFit
                    layer.enabled: true
                    layer.smooth: true
                    layer.effect: ShaderEffect {
                        property variant source: viewfinder

                        fragmentShader: "
                            uniform sampler2D source;
                            varying vec2 qt_TexCoord0;

                            void main() {
                                vec2 coord = qt_TexCoord0 - vec2(0.5);
                                if (length(coord) > 0.36) {
                                    discard;
                                }
                                gl_FragColor = texture2D(source, qt_TexCoord0);
                            }
                        "
                    }

                }
        }



    // //------------------------------------Map Section------------------------------------------

    property var destinationCoord: QtPositioning.coordinate(36.899, 10.2) // default


    Plugin {
            id: mapPlugin
            name: "osm"
        }
    Rectangle {
        id: rectanglemap
        width: backgroundcluster.width * 0.7
        height: width * 1
        color: "#dfdcd5"
        visible: false
        anchors.centerIn: backgroundcluster
        opacity: 1
        z: -1
        clip: true
        border.color: "#a0a0a0"
        border.width: 1
        layer.enabled: true
        layer.smooth: true
        layer.effect: ShaderEffect {
            property variant source: rectanglemap
            fragmentShader: "
                uniform sampler2D source;
                varying vec2 qt_TexCoord0;

                void main() {
                    vec2 coord = qt_TexCoord0 - vec2(0.5);
                    float x = coord.x;
                    float y = coord.y;

                    float a = 0.5;   // width
                    float b = 0.23;   // height
                    float k = 0.1;   // asymmetry (pointed end)

                    float oval = (x*x)/(a*a) + (y*y)/(b*b) * (1.0 + k * y);

                    if (oval > 1.0) discard;

                    gl_FragColor = texture2D(source, qt_TexCoord0);
                }
            "
        }
        Map {
            id: map
            width: parent.width * 0.9
            height: parent.height * 0.9
            anchors.centerIn: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(36.8984457, 10.1872208)
            zoomLevel: 14
        }
    }
    //-------BCG--------------------------------------------------------
    Rectangle{
        id : breathrate
        width: 210
        height: 210
        radius: width/2
        color: "#163546"
        visible: false
        anchors{
            verticalCenter: backgroundcluster.verticalCenter
            left: backgroundcluster.left
            leftMargin: backgroundcluster.width/5.6
        }
        Label{
            id : breathvalue
            text: "60"
            font.pixelSize: 40
            font.family: "Inter"
            color: "#FFFFFF"
            font.bold: Font.DemiBold
            Layout.alignment: Qt.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 25
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Image {
               id: breath
               source: "qrc:/img/breath.png"  // Path to your GIF
               anchors.top: parent.top
               anchors.topMargin: 20
               anchors.horizontalCenter: parent.horizontalCenter
               width: 65
               height: 65

               // Optional: Control playback

           }
        Rectangle{
            width: parent.width *0.8
            height: 5
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }
    Rectangle{
        id : heartbeat
        width: 210
        height: 210
        radius: width/2
        color: "#163546"
        visible: false
        anchors{
            verticalCenter: backgroundcluster.verticalCenter
            right:  backgroundcluster.right
            rightMargin:  backgroundcluster.width/5.6
        }
        Label{
            id : heartvalue
            text: "60"
            font.pixelSize: 40
            font.family: "Inter"
            color: "#FFFFFF"
            font.bold: Font.DemiBold
            Layout.alignment: Qt.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 25
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Image{
               id: heart
               source: "qrc:/img/heart.png"
               anchors.top: parent.top
               anchors.topMargin: 25
               anchors.horizontalCenter: parent.horizontalCenter
               width: 65
               height: 65

               // Optional: Control playback
               // Set to false to pause
           }
        Rectangle{
            width: parent.width *0.8
            height: 5
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

}


