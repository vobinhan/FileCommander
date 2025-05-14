#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QInputDialog>
#include "FileManager.h"
#include "NetworkManager.h"
#include "TcpClient.h"
#include "TcpServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDriveComboLeftChanged(int index);
    void onDriveComboRightChanged(int index);
    void onLeftViewClicked(const QModelIndex &index);
    void onRightViewClicked(const QModelIndex &index);
    void onCopyButtonClicked();
    void onMoveButtonClicked();
    void onDeleteButtonClicked();
    void onNewFolderButtonClicked();
    void onRenameButtonClicked();

    void onUploadButtonClicked(); //
    void onDownloadButtonClicked(); // 
    void onStartServerButtonClicked(); //

    void onConnectButtonClicked();
    void onTransferFileButtonClicked();
    
    void updateStatusBar(const QString &message, bool isError); // show
    void updateProgress(qint64 bytes, qint64 total); //

    void handleFileReceived(const QString &filePath);

private:
    Ui::MainWindow *ui;
    FileManager *m_fileManager;
    NetworkManager *m_networkManager;
    QFileSystemModel *m_leftModel;
    QFileSystemModel *m_rightModel;
    QString m_currentLeftPath;
    QString m_currentRightPath;

    void setupUI();
    void setupConnections();
    void updateCurrentPaths();
    QString getSelectedPath(bool isLeftPanel) const;
};

#endif // MAINWINDOW_H