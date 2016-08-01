/*
 * TabSecond�е�TabMap Group
 */

#include "TabSecond_GroupThree.h"
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include "TabSecond_GroupThree_Dialog.h"
#include "EasyXml.h"
#include "TabSecond_GroupThree_Item.h"
#include "CustomDefine.h"
#include "XVirtualKeyData.h"

TabSecond_GroupThree::TabSecond_GroupThree(QWidget *parent)
    :QGroupBox(parent)
{
    iDialog = new TabSecond_GroupThree_Dialog(this);

    // �Ű�
    iLayout = new QVBoxLayout;

    // ����
    SetupGroup();

    this->setLayout(iLayout);
}

void TabSecond_GroupThree::SetupGroup()
{
    this->setTitle(QLabel::tr("mouse_table_define"));

    SetupName();
    SetupNormal();
    SetupButtonBox();
}

void TabSecond_GroupThree::SetupName()
{
    iname = new QLabel(this);
    iname->setText(QLabel::tr("name"));

    iname_input = new QLineEdit(this);
    iname_input->setText(QLineEdit::tr("table"));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(iname);
    layout->addWidget(iname_input);

    iLayout->addLayout(layout);
}

void TabSecond_GroupThree::SetupNormal()
{
    inormal = new QListWidget(this);

    // ����˫��ITEM���Ի���
    QObject::connect(inormal, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     this, SLOT(ModifyItem_list(QListWidgetItem*)));

    iLayout->addWidget(inormal);
}

void TabSecond_GroupThree::SetupButtonBox()
{
    iButtonBox = new QDialogButtonBox(this);

    iAdd = new QPushButton(this);
    iAdd->setText(QPushButton::tr("Add"));
    QObject::connect(iAdd, SIGNAL(clicked()),
                     this, SLOT(AddItem()));
    iButtonBox->addButton(iAdd, QDialogButtonBox::ActionRole);

    iDel = new QPushButton(this);
    iDel->setText(QPushButton::tr("Del"));
    QObject::connect(iDel, SIGNAL(clicked()),
                     this, SLOT(DelCurrentItem()));
    iButtonBox->addButton(iDel, QDialogButtonBox::ActionRole);

    iLayout->addWidget(iButtonBox);
}

void TabSecond_GroupThree::Default()
{
    if(iname_input)
        iname_input->setText(QLineEdit::tr("table"));
    if(inormal)
    {
        for(int i=inormal->count()-1; i>=0; i--)
        {
            QListWidgetItem* item = inormal->item(i);
            inormal->takeItem(i);
            delete item;
        }

    }
}

void TabSecond_GroupThree::ReadData(XEasyXml *xml)
{
    if(xml)
    {
        // ���ģʽ����
        QString value;
        value = xml->FindAtt("mouse_table_define", "name");
        if(iname_input)
            iname_input->setText(value);

        // ���ⰴ���б�
        int count = 0;
        count = xml->ChildCount("mouse_table_define", "mouse_table_map");

        for(int i=0; i<count; i++)
        {
            TabSecond_GroupThree_Item* item = new TabSecond_GroupThree_Item;
            if(item)
            {
                value = xml->FindAttI("mouse_table_map", "virtual_key", i);
                if(value.length()!=0)
                {
                    for(int j=0; j<Key_Count; j++)
                    {
                        if(value==Key_Code[j])
                        {
                            item->SetVirtualKey(Key_Name[j]);
                            break;
                        }
                    }
                }
//                    item->SetVirtualKey(value);
                else
                {
                    delete item;
                    continue;
                }

                value = xml->FindAttI("mouse_table_map", "mouse_act", i);
                if(value.length()!=0)
                    item->SetMouseAct(value);
                else
                {
                    delete item;
                    continue;
                }

                QString itemtitle;
                itemtitle += ((TabSecond_GroupThree_Item*)item)->VirtualKey();
                itemtitle += QString("\t->\t");
                itemtitle += ((TabSecond_GroupThree_Item*)item)->MouseAct();
                item->setText(itemtitle);

                inormal->addItem(item);
            }
        }
    }
}

void TabSecond_GroupThree::SaveData(XEasyXml *xml)
{
    if(xml)
    {
        if(!xml->HasEle("operate_define", "mouse_table_define"))
            xml->AddEle("operate_define", "mouse_table_define");
        if(!xml->HasEle("operate_define", "mouse_table_define"))
            return;

        // ���ģʽ����
        if(xml->HasAtt("mouse_table_define", "name"))
            xml->DelAtt("mouse_table_define", "name");

        if(!xml->HasAtt("mouse_table_define", "name"))
            xml->AddAtt("mouse_table_define", "name");
        if(!xml->HasAtt("mouse_table_define", "name"))
            return;

        if(iname_input)
        {
            xml->ModifyAtt("mouse_table_define", "name", iname_input->text());
        }

        // �����������Ѵ��ڵ�ӳ��
        while(xml->HasEle("mouse_table_define", "mouse_table_map"))
            xml->DelEle("mouse_table_define", "mouse_table_map");

        // ����б�ģʽӳ��
        if(inormal)
        {
            // ����б��ж����ӳ��
            int count = inormal->count();
            for(int i=0; i<count; i++)
            {
                xml->AddEle("mouse_table_define", "mouse_table_map");

                for(int j=0; j<Key_Count; j++)
                {
                    if(((TabSecond_GroupThree_Item*)(inormal->item(i)))->VirtualKey()==Key_Name[j])
                    {
                        xml->AddAttI("mouse_table_map", "virtual_key", Key_Code[j], i);
                        break;
                    }
                }
                xml->AddAttI("mouse_table_map", "mouse_act", ((TabSecond_GroupThree_Item*)(inormal->item(i)))->MouseAct(), i);
            }
        }
    }
}

void TabSecond_GroupThree::AddItem()
{
    if(iDialog!=NULL)
        iDialog->ModifyItem_Item(inormal);
}

void TabSecond_GroupThree::DelCurrentItem()
{
    QListWidgetItem* item = inormal->takeItem(inormal->currentRow());
    delete item;
}

void TabSecond_GroupThree::ModifyItem_list(QListWidgetItem *item)
{
    if(iDialog!=NULL)
        iDialog->ModifyItem_Item(inormal, item);
}
