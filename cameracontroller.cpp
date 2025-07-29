#include "cameracontroller.h"
#include <QTimer>
#include <QDebug>

CameraController::CameraController(QObject *parent)
    : QObject(parent)
    , m_camera(nullptr)
    , m_imageCapture(nullptr)
    , m_cameraAvailable(false)
{
    updateCameraDevices();
}

bool CameraController::isCameraAvailable() const
{
    return m_cameraAvailable && !m_cameraDevices.isEmpty();
}

QStringList CameraController::availableCameras() const
{
    QStringList cameraList;
    for (const QCameraInfo &info : m_cameraDevices) {
        cameraList.append(info.deviceName() + ": " + info.description());
    }
    return cameraList;
}

void CameraController::startCamera(const QString &cameraDevice)
{
    stopCamera();

    QCameraInfo selectedCameraInfo;

    if (cameraDevice.isEmpty() && !m_cameraDevices.isEmpty()) {
        selectedCameraInfo = m_cameraDevices.first();
    } else {
        for (const QCameraInfo &info : m_cameraDevices) {
            if (info.deviceName() == cameraDevice ||
                info.description() == cameraDevice) {
                selectedCameraInfo = info;
                break;
            }
        }
    }

    if (selectedCameraInfo.isNull()) {
        emit errorOccurred("No camera device found");
        return;
    }

    m_camera = new QCamera(selectedCameraInfo, this);
    m_imageCapture = new QCameraImageCapture(m_camera, this);

    // Set capture mode to viewfinder
    m_camera->setCaptureMode(QCamera::CaptureViewfinder);

    // Connect signals
    connect(m_imageCapture, &QCameraImageCapture::imageCaptured,
            this, &CameraController::onImageCaptured);

    connect(m_camera, QOverload<QCamera::Error>::of(&QCamera::error),
            this, [this]() {
                emit errorOccurred(m_camera->errorString());
            });

    m_camera->start();
    m_cameraAvailable = true;
    emit cameraStatusChanged();
}

void CameraController::stopCamera()
{
    if (m_camera) {
        m_camera->stop();
        delete m_camera;
        m_camera = nullptr;
        m_imageCapture = nullptr;
        m_cameraAvailable = false;
        emit cameraStatusChanged();
    }
}

void CameraController::switchCamera(const QString &cameraDevice)
{
    stopCamera();
    startCamera(cameraDevice);
}

void CameraController::captureImage()
{
    if (m_imageCapture && m_camera && m_camera->state() == QCamera::ActiveState) {
        m_imageCapture->capture();
    }
}

void CameraController::updateCameraDevices()
{
    m_cameraDevices = QCameraInfo::availableCameras();
    emit cameraListChanged();
}

void CameraController::onImageCaptured(int id, const QImage &preview)
{
    Q_UNUSED(id)
    emit imageCaptured(preview);
}
