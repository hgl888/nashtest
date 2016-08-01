/*
 * TabThird��TxtInfo Group List Item������
 */
#ifndef TABTHIRD_GROUPFOUR_DIALOG_H
#define TABTHIRD_GROUPFOUR_DIALOG_H

// declearation
class QLabel;
class QLineEdit;
class QTextCodec;
class QTextEdit;
class QGridLayout;
class QPushButton;
class QListWidgetItem;
class QDialogButtonBox;
class QListWidget;
class TabThird_GroupFour;
class TabThird_GroupFour_Item;

// include
#include <QDialog>

class TabThird_GroupFour_Dialog : public QDialog
{
    Q_OBJECT

public:
    TabThird_GroupFour_Dialog(QWidget* parent = NULL);

public:
    // ������ӣ��鿴���޸�ITEM
    void ModifyItem_Item(QListWidget* parent, QListWidgetItem* item = NULL);

private:
    // ����Dialog
    void SetupDialog();

    // �ı�����
    // ����
    void SetupTxtname();

    // �ı�����
    // ����
    void SetupTxtdefine();

    // ����
    void SetupButtongroup();

private slots:
    // ������OK����
    void ClickOK();

private:
    // �ı�����
    QLabel*     itxtname;
    QLineEdit*  itxtname_input;

    // �ı�����
    QLabel*     itxtdefine;
    QTextEdit*  itxtdefine_input;

    // �Ű�
    QGridLayout*    iLayout;

    // ����
    QPushButton*    iOk;
    QPushButton*    iCancel;
    QDialogButtonBox*   iButtonbox;

    // List��ָ��
    QListWidget*    iListparent;

    // ��ǰITEM��ָ��
    QListWidgetItem*    iItem;
};

#endif // TABTHIRD_GROUPFOUR_DIALOG_H
