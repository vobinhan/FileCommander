#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileManager(new FileManager(this))
    , m_networkManager(new NetworkManager(this))
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Setup drive comboboxes
    QStringList drives = m_fileManager->getDrives();
    ui->driveComboLeft->addItems(drives);
    ui->driveComboRight->addItems(drives);
    
    // Set default drives (C: and D: if available)
    int cIndex = drives.indexOf("C:/");
    int dIndex = drives.indexOf("D:/");
    
    if (cIndex != -1) ui->driveComboLeft->setCurrentIndex(cIndex);
    if (dIndex != -1) ui->driveComboRight->setCurrentIndex(dIndex);
    
    // Setup file system models
    m_leftModel = m_fileManager->getFileSystemModel(ui->driveComboLeft->currentText());
    m_rightModel = m_fileManager->getFileSystemModel(ui->driveComboRight->currentText());
    
    ui->leftView->setModel(m_leftModel);
    ui->rightView->setModel(m_rightModel);
    
    ui->leftView->setRootIndex(m_leftModel->index(ui->driveComboLeft->currentText()));
    ui->rightView->setRootIndex(m_rightModel->index(ui->driveComboRight->currentText()));
    
    // Setup progress bar in status bar
    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setMaximumSize(200, 20);
    progressBar->setTextVisible(false);
    statusBar()->addPermanentWidget(progressBar);
}

void MainWindow::setupConnections()
{
    // Drive selection
    connect(ui->driveComboLeft, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDriveComboLeftChanged);
    connect(ui->driveComboRight, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDriveComboRightChanged);
    
    // File selection
    connect(ui->leftView, &QTreeView::clicked, this, &MainWindow::onLeftViewClicked);
    connect(ui->rightView, &QTreeView::clicked, this, &MainWindow::onRightViewClicked);
    
    // Buttons
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyButtonClicked);
    connect(ui->moveButton, &QPushButton::clicked, this, &MainWindow::onMoveButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->newFolderButton, &QPushButton::clicked, this, &MainWindow::onNewFolderButtonClicked);
    connect(ui->renameButton, &QPushButton::clicked, this, &MainWindow::onRenameButtonClicked);
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::onUploadButtonClicked);
    connect(ui->downloadButton, &QPushButton::clicked, this, &MainWindow::onDownloadButtonClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    connect(ui->startServerButton, &QPushButton::clicked, this, &MainWindow::onStartServerButtonClicked);
    connect(ui->transferFileButton, &QPushButton::clicked, this, &MainWindow::onTransferFileButtonClicked);
    
    // Signals from managers
    connect(m_fileManager, &FileManager::operationStatus, this, &MainWindow::updateStatusBar);
    connect(m_networkManager, &NetworkManager::networkStatus, this, &MainWindow::updateStatusBar);
    connect(m_networkManager, &NetworkManager::uploadProgress, this, &MainWindow::updateProgress);
    connect(m_networkManager, &NetworkManager::downloadProgress, this, &MainWindow::updateProgress);
    connect(m_networkManager, &NetworkManager::fileReceived, this, &MainWindow::handleFileReceived);
}

// Implement other slot functions...

void MainWindow::onDriveComboLeftChanged(int index)
{
    QString path = ui->driveComboLeft->itemText(index);
    ui->leftView->setRootIndex(m_leftModel->index(path));
    m_currentLeftPath = path;
}

void MainWindow::onDriveComboRightChanged(int index)
{
    QString path = ui->driveComboRight->itemText(index);
    ui->rightView->setRootIndex(m_rightModel->index(path));
    m_currentRightPath = path;
}

void MainWindow::onLeftViewClicked(const QModelIndex &index)
{
    m_currentLeftPath = m_leftModel->filePath(index);
}

void MainWindow::onRightViewClicked(const QModelIndex &index)
{
    m_currentRightPath = m_rightModel->filePath(index);
}

void MainWindow::onCopyButtonClicked()
{
    QString source = getSelectedPath(true); // Left panel
    QString destination = m_currentRightPath;
    
    if (source.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file or folder to copy");
        return;
    }
    
    m_fileManager->copyFile(source, destination + QDir::separator() + QFileInfo(source).fileName());
}

void MainWindow::onMoveButtonClicked()
{
    QString source = getSelectedPath(true); // Left panel
    QString destination = m_currentRightPath;
    
    if (source.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file or folder to move");
        return;
    }
    
    m_fileManager->moveFile(source, destination + QDir::separator() + QFileInfo(source).fileName());
}

void MainWindow::onDeleteButtonClicked()
{
    QString path = getSelectedPath(ui->leftView->hasFocus());
    
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file or folder to delete");
        return;
    }
    
    if (QMessageBox::question(this, "Confirm", "Are you sure you want to delete this item?") == QMessageBox::Yes) {
        m_fileManager->deleteFile(path);
    }
}

void MainWindow::onNewFolderButtonClicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Folder", "Enter folder name:", QLineEdit::Normal, "", &ok);
    
    if (ok && !name.isEmpty()) {
        QString currentPath = ui->leftView->hasFocus() ? m_currentLeftPath : m_currentRightPath;
        m_fileManager->createDirectory(currentPath, name);
    }
}

void MainWindow::onRenameButtonClicked()
{
    QString path = getSelectedPath(ui->leftView->hasFocus());
    
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file or folder to rename");
        return;
    }
    
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename", "Enter new name:", 
                                          QLineEdit::Normal, QFileInfo(path).fileName(), &ok);
    
    if (ok && !newName.isEmpty()) {
        m_fileManager->renameFile(path, newName);
    }
}

void MainWindow::onUploadButtonClicked()
{
    QString filePath = getSelectedPath(true); // Left panel
    
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file to upload");
        return;
    }
    
    QUrl url(QString("ftp://example.com/uploads/%1").arg(QFileInfo(filePath).fileName()));
    m_networkManager->uploadFile(url, filePath);
}

void MainWindow::onDownloadButtonClicked()
{
    QString filePath = getSelectedPath(false); // Right panel
    QString destination = m_currentLeftPath;
    
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file to download");
        return;
    }
    
    QUrl url(QString("ftp://example.com/downloads/%1").arg(QFileInfo(filePath).fileName()));
    m_networkManager->downloadFile(url, destination + QDir::separator() + QFileInfo(filePath).fileName());
}

void MainWindow::onConnectButtonClicked()
{
    QString host = ui->serverAddressEdit->text();
    quint16 port = ui->serverPortEdit->text().toUShort();
    m_networkManager->connectToServer(host, port);
}

void MainWindow::onStartServerButtonClicked()
{
    quint16 port = ui->serverPortEdit->text().toUShort();
    m_networkManager->startServer(port);
}

void MainWindow::onTransferFileButtonClicked()
{
    QString filePath = getSelectedPath(ui->leftView->hasFocus());
    
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file to transfer");
        return;
    }
    
    m_networkManager->sendFileOverTcp(filePath);
}

void MainWindow::updateStatusBar(const QString &message, bool isError)
{
    statusBar()->showMessage(message, isError ? 5000 : 3000);
    if (isError) {
        QMessageBox::warning(this, "Error", message);
    }
}

void MainWindow::updateProgress(qint64 bytes, qint64 total)
{
    QProgressBar *progressBar = findChild<QProgressBar*>();
    if (progressBar) {
        progressBar->setMaximum(total);
        progressBar->setValue(bytes);
    }
}

void MainWindow::handleFileReceived(const QString &filePath)
{
    QMessageBox::information(this, "File Received", QString("File received: %1").arg(filePath));
}

QString MainWindow::getSelectedPath(bool isLeftPanel) const
{
    QTreeView *view = isLeftPanel ? ui->leftView : ui->rightView;
    QFileSystemModel *model = isLeftPanel ? m_leftModel : m_rightModel;
    
    QModelIndexList selected = view->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) return QString();
    
    return model->filePath(selected.first());
}