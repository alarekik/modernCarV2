#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QImage>
#include <QStringList>

class CameraController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool cameraAvailable READ isCameraAvailable NOTIFY cameraStatusChanged)
    Q_PROPERTY(QStringList availableCameras READ availableCameras NOTIFY cameraListChanged)

public:
    explicit CameraController(QObject *parent = nullptr);

    bool isCameraAvailable() const;
    QStringList availableCameras() const;

public slots:
    void startCamera(const QString &cameraDevice = "");
    void stopCamera();
    void switchCamera(const QString &cameraDevice);
    void captureImage();

signals:
    void cameraStatusChanged();
    void cameraListChanged();
    void errorOccurred(const QString &error);
    void imageCaptured(const QImage &image);

private slots:
    void updateCameraDevices();
    void onImageCaptured(int id, const QImage &preview);

private:
    QCamera *m_camera;
    QCameraImageCapture *m_imageCapture;
    QList<QCameraInfo> m_cameraDevices;
    bool m_cameraAvailable;
};

#endif // CAMERACONTROLLER_H
