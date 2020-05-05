#include "settingform.h"
#include "ui_settingform.h"
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SettingForm::SettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);

    // 设置配置路径，并将配置文件中的信息同步到Setting界面
    setting_filename = "../BaiduAIStudy/assert/BaiduAi_Setting.xml";
    initSetting();
}

SettingForm::~SettingForm()
{
    delete ui;
}

/**
 * @brief SettingForm::initSetting
 * 程序启动的时候，调用此函数，将文件中的配置信息，同步到Setting界面
 * @return 0:OK
 */
int SettingForm::initSetting()
{
    // 读取配置文件，并配置到界面
    ReadSettingXml();

    return 0;
}


/**
 * @brief SettingForm::pushButton_readSetting_OnClick
 * 点击读取配置的时候，执行此函数，将文件配置内容同步到Setting界面
 */
void SettingForm::pushButton_readSetting_OnClick()
{
    // 读取配置文件，并配置到界面
    ReadSettingXml();
}

void SettingForm::pushButton_writeSetting_OnClick()
{
    // 将界面配置信息，记录到文件中
    WriteSettingXml();
}

/**
 * @brief SettingForm::ReadSettingXml
 * 从文件中读取信息，并配置到界面
 */
void SettingForm::ReadSettingXml()
{
    //打开或创建文件
    QFile file(setting_filename); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement(); //返回根节点
    qDebug()<<root.nodeName();
    QDomNode node=root.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        if(node.isElement()) //如果节点是元素
        {
            QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            initSettingItem(e.tagName(), e.toElement().text());
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}

/**
 * @brief SettingForm::initSettingItem
 * 更新界面name的配置内容
 * @param name : 需要配置的label名字
 * @param text : 需要配置的内容
 * @return : 0:OK
 */
int SettingForm::initSettingItem(QString name, QString text)
{

    if( name == ui->label_api_key->text() )
    {
        ui->lineEdit_api_key->setText(text);
        qDebug()<< ui->label_api_key->text() << " " << ui->lineEdit_api_key->text();
    }
    else if ( name == ui->label_app_id->text() )
    {
        ui->lineEdit_app_id->setText(text);
        qDebug()<< ui->label_app_id->text() << " " << ui->lineEdit_app_id->text();
    }
    else if ( name == ui->label_secret_key->text() )
    {
        ui->lineEdit_secret_key->setText(text);
        qDebug()<< ui->label_secret_key->text() << " " << ui->lineEdit_secret_key->text();
    }
    else
    {
        qDebug() << "tagName" << name << "  text:" << text << "  No Support";
    }

    return 0;
}


/**
 * @brief SettingForm::WriteSettingXml
 * 将界面的配置信息，构造成xml格式，并写入到文件中
 */
void SettingForm::WriteSettingXml()
{
    //打开或创建文件
    QFile file(setting_filename); //相对路径、绝对路径、资源路径都可以
    file.open(QFile::WriteOnly|QFile::Truncate);
    if(!file.isOpen()) //可以用QIODevice，Truncate表示清空原来的内容
    {
        qDebug()<< file.fileName() << "Open Err";
        return;
    }
    else
    {
        qDebug()<< file.fileName() << "Open Ok";
    }

    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root=doc.createElement("Setting");
    doc.appendChild(root);
    QDomElement item=doc.createElement(ui->label_api_key->text()); //创建子元素
    QDomText text; //设置括号标签中间的值
    text=doc.createTextNode(ui->lineEdit_api_key->text());
    item.appendChild(text);
    root.appendChild(item);

    item=doc.createElement(ui->label_app_id->text()); //创建子元素
    text=doc.createTextNode(ui->lineEdit_app_id->text());
    item.appendChild(text);
    root.appendChild(item);

    item=doc.createElement(ui->label_secret_key->text()); //创建子元素
    text=doc.createTextNode(ui->lineEdit_secret_key->text());
    item.appendChild(text);
    root.appendChild(item);

    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();

}
