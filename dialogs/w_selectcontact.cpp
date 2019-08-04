#include "w_selectcontact.h"
#include "ui_w_selectcontact.h"
#include "../util/stringutils.h"
#include <QListWidgetItem>
#include "../control/messagebox.h"
#include "../state/w_contacts.h"

namespace dlg {

SelectContact::SelectContact(QWidget *parent, state::Contacts * _state ) :
    control::MwcDialog(parent),
    ui(new Ui::SelectContact),
    state(_state)
{
    ui->setupUi(this);

    initTableHeaders();
    updateContactTable("");
}

SelectContact::~SelectContact()
{
    delete ui;
}

void SelectContact::on_cancelButton_clicked()
{
    reject();
}

void SelectContact::initTableHeaders() {

    // Disabling to show the grid
    // Creatign columns
    QVector<int> widths = state->getColumnsWidhts();
    if ( widths.size() != 3 ) {
        widths = QVector<int>{30,100,300};
    }
    Q_ASSERT( widths.size() == 3 );
    ui->contactsTable->setColumnWidths( widths );
}

void SelectContact::saveTableHeaders() {
    state->updateColumnsWidhts( ui->contactsTable->getColumnWidths() );
}

void SelectContact::updateContactTable(const QString & searchStr) {
    contacts.clear();

    QVector<core::ContactRecord> contAll = state->getContacts();

    ui->contactsTable->clearData();
    for ( const auto & cont : contAll ) {
        if ( searchStr.isEmpty() || cont.name.contains( searchStr ) ) {
            ui->contactsTable->appendRow(QVector<QString>{
                    QString::number( contacts.size()),
                    cont.name,
                    cont.address
            });
            contacts.push_back(cont);
        }
    }
}

int  SelectContact::getSelectedContactIndex() const {
    QList<QTableWidgetItem*> selList = ui->contactsTable->selectedItems();
    if (selList.size()==0)
        return -1;

    int idx = selList[0]->row();
    if (idx>=0 && idx<contacts.size())
        return idx;

    return -1;
}

void SelectContact::on_lineEdit_textChanged(const QString &str)
{
    updateContactTable(str);
}

void SelectContact::on_selectButton_clicked()
{
    int idx = SelectContact::getSelectedContactIndex();

    if ( idx<0 || idx>=contacts.size() ) {
        control::MessageBox::message(this, "Need info", "Please select a contact that you are going to use");
        return;
    }

    selectedContact = contacts[idx];
    accept();
}

void SelectContact::on_contactsTable_itemDoubleClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
    on_selectButton_clicked();
}

}



