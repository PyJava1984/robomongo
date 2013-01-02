#include <QtGui>
#include "ConnectionDialog.h"
#include "AppRegistry.h"
#include <QList>
#include "GuiRegistry.h"
#include "ConnectionAuthTab.h"
#include "ConnectionBasicTab.h"
#include "ConnectionAdvancedTab.h"

using namespace Robomongo;

/**
 * @brief Constructs dialog with specified connection
 */
ConnectionDialog::ConnectionDialog(ConnectionSettings *connection) : QDialog(),
    _connection(connection)
{
    setWindowTitle("Connection Settings");
    setWindowIcon(GuiRegistry::instance().serverIcon());

    // Remove help button (?)
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QPushButton *saveButton = new QPushButton("&Save");
    saveButton->setIcon(qApp->style()->standardIcon(QStyle::SP_ArrowRight));
    saveButton->setDefault(true);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(accept()));

    QPushButton *cancelButton = new QPushButton("&Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QPushButton *testButton = new QPushButton("&Test");
    testButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation));
    connect(testButton, SIGNAL(clicked()), this, SLOT(testConnection()));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(testButton, 1, Qt::AlignLeft);
    bottomLayout->addWidget(saveButton, 1, Qt::AlignRight);
    bottomLayout->addWidget(cancelButton);

    _tabWidget = new QTabWidget;

    _authTab = new ConnectionAuthTab(_connection);
    _basicTab = new ConnectionBasicTab(_connection);
    _basicTab->setFocus();
    _advancedTab = new ConnectionAdvancedTab();

    _tabWidget->addTab(_basicTab, "Connection");
    _tabWidget->addTab(_authTab, "Authentication");
    _tabWidget->addTab(_advancedTab, "Advanced");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_tabWidget);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
}

/**
 * @brief Accept() is called when user agree with entered data.
 */
void ConnectionDialog::accept()
{
    _basicTab->accept();
    _authTab->accept();

    QDialog::accept();
}

/**
 * @brief Close event handler
 */
void ConnectionDialog::closeEvent(QCloseEvent *event)
{
    if (canBeClosed())
        event->accept();
    else
        event->ignore();
}

/**
 * @brief Check that it is okay to close this window
 *        (there is no modification of data, that we possibly can loose)
 */
bool ConnectionDialog::canBeClosed()
{
    bool unchanged = true;
        /*_connection->connectionName() == _connectionName->text()
        && _connection->databaseAddress() == _serverAddress->text()
        && QString::number(_connection->databasePort()) == _serverPort->text()
        && _connection->userName() == _userName->text()
        && _connection->userPassword() == _userPassword->text()
        && _connection->databaseName() == _databaseName->text()*/;

    // If data was unchanged - simply close dialog
    if (unchanged)
        return true;

    // Ask user
    int answer = QMessageBox::question(this,
            "Connections",
            "Close this window and loose you changes?",
            QMessageBox::Yes, QMessageBox::No, QMessageBox::NoButton);

    if (answer == QMessageBox::Yes)
        return true;

    return false;
}

/**
 * @brief Test current connection
 */
void ConnectionDialog::testConnection()
{
    bool res = true; //_connection->test(_serverAddress->text(), _serverPort->text(), _userName->text(), _userPassword->text());

    if (res)
        QMessageBox::information(NULL, "Success!", "Success! Connection exists.", "Ok");
}

void ConnectionDialog::tabWidget_currentChanged(int index)
{
    /*
    const QSizePolicy ignored(QSizePolicy::Ignored, QSizePolicy::Ignored);
    const QSizePolicy preferred(QSizePolicy::Preferred, QSizePolicy::Preferred);
    if (index == 0) {
        _serverTab->setSizePolicy(preferred);
        _auth->setSizePolicy(ignored);
    } else {
        _serverTab->setSizePolicy(ignored);
        _auth->setSizePolicy(preferred);
    }

    layout()->activate();
    setFixedSize(minimumSizeHint());
    setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    */
}