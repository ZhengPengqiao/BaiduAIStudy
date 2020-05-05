#ifndef OCRFORM_H
#define OCRFORM_H

#include <QWidget>

namespace Ui {
class OcrForm;
}

class OcrForm : public QWidget
{
    Q_OBJECT

public:
    explicit OcrForm(QWidget *parent = nullptr);
    ~OcrForm();

    void setOcrImage(QString filename);

public slots:
    void pushButton_Ocr_OnClick();
    void pushButton_OpenFile_OnClick();

private:
    Ui::OcrForm *ui;
    QString filename;
};

#endif // OCRFORM_H
