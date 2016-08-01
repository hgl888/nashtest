#ifndef CURDTDVIEW_H
#define CURDTDVIEW_H

class QPushButton;
class QVBoxLayout;
class QTextEdit;

#include <QDialog>

class CurDtdView : public QDialog
{
    Q_OBJECT
public:
    explicit CurDtdView(QWidget *parent = 0);


private:
    void SetupDialog();

signals:

public slots:

private:
    // ��ʾ����
    QTextEdit*  iShow;

    // �رհ���
    QPushButton* iCloseDialog;

    // �Ű�
    QVBoxLayout* iLayout;

};

#endif // CURDTDVIEW_H
