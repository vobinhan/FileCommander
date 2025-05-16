#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileManager(new FileManager(this))
    , Tcp_Server(new TcpServer(this))
    , Tcp_Client(new TcpClient(this))
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
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    connect(ui->startServerButton, &QPushButton::clicked, this, &MainWindow::onStartServerButtonClicked);
    connect(ui->transferFileButton, &QPushButton::clicked, this, &MainWindow::onTransferFileButtonClicked);
    
    // Signals from managers
    connect(m_fileManager, &FileManager::operationStatus, this, &MainWindow::updateStatusBar);
}

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

void MainWindow::onStartServerButtonClicked()
{
    quint16 port = ui->serverPortEdit->text().toUShort();

    if(Tcp_Server->startServer(port))
    {
        ui->statusbar->showMessage("TCP Server Started");
        ui->statusbar->setStyleSheet("color: green;");
    }
    else
    {
        ui->statusbar->showMessage("TCP Server not Started");
        ui->statusbar->setStyleSheet("color: red;");
    }
}

void MainWindow::onConnectButtonClicked()
{
    QString host = ui->serverAddressEdit->text();
    quint16 port = ui->serverPortEdit->text().toUShort();
    if(Tcp_Client->connectToServer(host, port))
    {
        ui->statusbar->showMessage("Client is connected");
        ui->statusbar->setStyleSheet("color: green;");
    }
    else
    {
        ui->statusbar->showMessage("Client is not connected");
        ui->statusbar->setStyleSheet("color: red;");
    }
}

void MainWindow::onTransferFileButtonClicked()
{
    QString source = getSelectedPath(true); // Left panel
    QString destination = m_currentRightPath;

    if(Tcp_Client->sendFile(source))
    {
        ui->statusbar->showMessage("Send File is Successful");
        ui->statusbar->setStyleSheet("color: green;");
    }
    else
    {
        ui->statusbar->showMessage("Send File is Unsuccessful");
        ui->statusbar->setStyleSheet("color: red;");
    }
}


void MainWindow::updateStatusBar(const QString &message, bool isError)
{
    statusBar()->showMessage(message, isError ? 5000 : 3000);
    if (isError) {
        QMessageBox::warning(this, "Error", message);
    }
}

QString MainWindow::getSelectedPath(bool isLeftPanel) const
{
    QTreeView *view = isLeftPanel ? ui->leftView : ui->rightView;
    QFileSystemModel *model = isLeftPanel ? m_leftModel : m_rightModel;
    
    QModelIndexList selected = view->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) return QString();
    
    return model->filePath(selected.first());
}
