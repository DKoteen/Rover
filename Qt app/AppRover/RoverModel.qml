import QtQuick3D

Node {
    id: rover

    // Серый корпус полётного контроллера
    Model {
        source: "#Cube"
        scale: Qt.vector3d(1.35, 0.20, 1.15)

        materials: PrincipledMaterial {
            baseColor: "#B8BEC8"
            metalness: 0.25
            roughness: 0.45
        }
    }

    // Светлая верхняя поверхность
    Model {
        source: "#Cube"
        position: Qt.vector3d(0, 11, 0)
        scale: Qt.vector3d(1.28, 0.025, 1.08)

        materials: PrincipledMaterial {
            baseColor: "#E0E4EA"
            roughness: 0.6
        }
    }

    // Красная ось — вправо
    Model {
        source: "#Cylinder"
        position: Qt.vector3d(50, 20, 0)
        eulerRotation.z: -90
        scale: Qt.vector3d(0.07, 1.0, 0.07)

        materials: PrincipledMaterial {
            baseColor: "#F04444"
            roughness: 0.28
        }
    }

    // Зелёная ось — вперёд
    Model {
        source: "#Cylinder"
        position: Qt.vector3d(0, 20, -50)
        eulerRotation.x: -90
        scale: Qt.vector3d(0.07, 1.0, 0.07)

        materials: PrincipledMaterial {
            baseColor: "#31D86E"
            roughness: 0.28
        }
    }

    // Синяя ось — вверх
    Model {
        source: "#Cylinder"
        position: Qt.vector3d(0, 70, 0)
        scale: Qt.vector3d(0.07, 1.0, 0.07)

        materials: PrincipledMaterial {
            baseColor: "#3478FF"
            roughness: 0.28
        }
    }

    // Наконечники осей
    Model {
        source: "#Sphere"
        position: Qt.vector3d(103, 20, 0)
        scale: Qt.vector3d(0.11, 0.11, 0.11)
        materials: PrincipledMaterial {
            baseColor: "#F04444"
        }
    }

    Model {
        source: "#Sphere"
        position: Qt.vector3d(0, 20, -103)
        scale: Qt.vector3d(0.11, 0.11, 0.11)
        materials: PrincipledMaterial {
            baseColor: "#31D86E"
        }
    }

    Model {
        source: "#Sphere"
        position: Qt.vector3d(0, 123, 0)
        scale: Qt.vector3d(0.11, 0.11, 0.11)
        materials: PrincipledMaterial {
            baseColor: "#3478FF"
        }
    }
}
