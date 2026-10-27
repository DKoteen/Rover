import QtQuick
import QtQuick.Controls.Basic
import QtQuick3D

ApplicationWindow {
    id: window

    width: 1000
    height: 720
    visible: true
    title: "AppRover — Attitude"

    color: "#191D23"

    Column {
        anchors.fill: parent
        anchors.margins: 18
        spacing: 14

        Text {
            id: titleText
            text: "Ориентация полётного контроллера"
            color: "#F2F5F8"
            font.pixelSize: 26
            font.bold: true
        }

        View3D {
            width: parent.width
            height: parent.height
                    - titleText.height
                    - anglesRow.height
                    - parent.spacing * 2

            environment: SceneEnvironment {
                backgroundMode: SceneEnvironment.Color
                clearColor: "#272B32"

                // Высокое качество сглаживания
                antialiasingMode: SceneEnvironment.MSAA
                antialiasingQuality: SceneEnvironment.VeryHigh

                specularAAEnabled: true
                tonemapMode: SceneEnvironment.TonemapModeFilmic

                aoEnabled: true
                aoStrength: 35
                aoDistance: 18
            }

            // Камера с противоположной стороны
            PerspectiveCamera {
                id: sceneCamera

                position: Qt.vector3d(-185, 140, 260)
                lookAtNode: rover3D
            }

            camera: sceneCamera

            // Основной свет
            DirectionalLight {
                eulerRotation: Qt.vector3d(-45, -35, 0)
                brightness: 1.7
                ambientColor: "#89939E"
                castsShadow: true
            }

            // Дополнительная подсветка
            DirectionalLight {
                eulerRotation: Qt.vector3d(-20, 140, 0)
                brightness: 0.65
            }

            // Плоскость под моделью
            Model {
                source: "#Cube"
                position: Qt.vector3d(0, -40, 0)
                scale: Qt.vector3d(8, 0.06, 8)

                materials: PrincipledMaterial {
                    baseColor: "#30353C"
                    roughness: 0.95
                }
            }

            // Линии сетки вдоль Z
            Repeater3D {
                model: 15

                delegate: Model {
                    required property int index

                    source: "#Cube"

                    position: Qt.vector3d(
                        -350 + index * 50,
                        -36,
                        0
                    )

                    scale: Qt.vector3d(0.008, 0.008, 7)

                    materials: PrincipledMaterial {
                        baseColor: "#58616B"
                        roughness: 1.0
                    }
                }
            }

            // Линии сетки вдоль X
            Repeater3D {
                model: 15

                delegate: Model {
                    required property int index

                    source: "#Cube"

                    position: Qt.vector3d(
                        0,
                        -36,
                        -350 + index * 50
                    )

                    scale: Qt.vector3d(7, 0.008, 0.008)

                    materials: PrincipledMaterial {
                        baseColor: "#58616B"
                        roughness: 1.0
                    }
                }
            }

            // Наша модель полётного контроллера
            RoverModel {
                id: rover3D

                eulerRotation: Qt.vector3d(
                    roverController.pitch_qml,
                    -roverController.yaw_qml,
                    -roverController.roll_qml
                )
            }
        }

        Row {
            id: anglesRow
            spacing: 32

            Text {
                text: "Roll: " +
                      roverController.roll_qml.toFixed(2) + "°"
                font.pixelSize: 19
                color: "#F2F5F8"
            }

            Text {
                text: "Pitch: " +
                      roverController.pitch_qml.toFixed(2) + "°"
                font.pixelSize: 19
                color: "#F2F5F8"
            }

            Text {
                text: "Yaw: " +
                      roverController.yaw_qml.toFixed(2) + "°"
                font.pixelSize: 19
                color: "#F2F5F8"
            }
        }
    }
}
