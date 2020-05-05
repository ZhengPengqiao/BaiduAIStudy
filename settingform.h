#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
#include <QString>
#include <QDomDocument>

namespace Ui {
class SettingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = nullptr);
    ~SettingForm();
    int initSetting();
    int initSettingItem(QString name, QString text);
    void WriteSettingXml();
    void ReadSettingXml();

public slots:
    void pushButton_readSetting_OnClick();
    void pushButton_writeSetting_OnClick();

private:
    Ui::SettingForm *ui;
    QString setting_filename;
};

#endif // SETTINGFORM_H
