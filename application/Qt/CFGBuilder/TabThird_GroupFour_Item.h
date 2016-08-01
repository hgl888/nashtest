/*
 * TabThird��TxtInfo Group �е� Item
 */
#ifndef TABTHIRD_GROUPFOUR_ITEM_H
#define TABTHIRD_GROUPFOUR_ITEM_H

//

//
#include <QListWidgetItem>

class TabThird_GroupFour_Item : public QListWidgetItem
{
public:
    TabThird_GroupFour_Item(QListWidget * parent = 0, int type = Type);

public:
    // �ı�����
    void SetTxtname(const QString& name);
    QString Txtname() const;

    // �ı�����
    void SetTxtdefine(const QString& define);
    QString Txtdefine() const;

private:
    // �ı�����
    QString     itxtname;

    // �ı�����
    QString     itxtdefine;
};

#endif // TABTHIRD_GROUPFOUR_ITEM_H
