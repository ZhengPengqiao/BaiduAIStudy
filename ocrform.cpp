#include "ocrform.h"
#include "ui_ocrform.h"
#include "ocr.h"
#include <QWidget>
#include <QDebug>
#include <QImageReader>
#include <QFileDialog>
#include <QStringList>
#include <QImageWriter>
#include <QStandardPaths>
#include <QPixmap>

OcrForm::OcrForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcrForm)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    filename.clear();
    ui->lineEdit_Path->setText(filename);
    setOcrImage(":/assert/ocr_info.jpg");
}

OcrForm::~OcrForm()
{
    delete ui;
}

/**
 * @brief OcrForm::pushButton_Ocr_OnClick
 * 使用Baidu AI 进行图片识别
 */
void OcrForm::pushButton_Ocr_OnClick()
{

    // 设置APPID/AK/SK
    std::string app_id = "18878812";
    std::string api_key = "5OSRi8lVWO4Dxg3LqS8L2B5N";
    std::string secret_key = "vZEaFVtDT722CHcwlDmCkTUEcUp3uxPc";
    Json::Value result;
    std::string image;
    std::string tmp;

    aip::Ocr client(app_id, api_key, secret_key);

    if( filename.isEmpty() )
    {
        ui->statusBar->setText(QString("OcrForm->") + " filename: " + filename + " Is Empty");
        return;
    }
    aip::get_file_content(filename.toStdString().c_str(), &image);

    // 调用通用文字识别, 图片参数为本地图片
    result = client.general_basic(image, aip::null);

    // 如果有可选参数
    std::map<std::string, std::string> options;
    options["language_type"] = "CHN_ENG";
    options["detect_direction"] = "true";
    options["detect_language"] = "true";
    options["probability"] = "true";

    // 带参数调用通用文字识别, 图片参数为本地图片
    result = client.general_basic(image, options);

    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(result);

    qDebug() << QString::fromStdString(output);

    ui->textEdit_Result->setText(QString::fromStdString(output));
}



static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

/**
 * @brief OcrForm::pushButton_OpenFile_OnClick
 * 弹出文件选择框，选择文件，并将选择的文件图片显示出来
 */
void OcrForm::pushButton_OpenFile_OnClick()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted )
    {
        break;
    }

    filename = dialog.selectedFiles().first();
    ui->lineEdit_Path->setText(filename);
    ui->statusBar->setText(QString("OcrForm->") + "openFile: " + dialog.selectedFiles().first());
    setOcrImage(filename);
}

/**
 * @brief OcrForm::setOcrImage
 * 设置Ocr选择的图片，显示到界面上
 * @param filename : 设置图片的图片路径
 */
void OcrForm::setOcrImage(QString filename)
{
    if(filename.isEmpty())
    {
         return;
    }
    else
    {
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            delete img;
            return;
        }
        ui->label_Image->setPixmap(QPixmap::fromImage(*img));
    }
    ui->label_Image->resize( ui->label_Image->pixmap()->size());    //  将label控件resize到fame的尺寸
    ui->label_Image->setGeometry(0,0,ui->label_Image->sizeHint().width(),ui->label_Image->sizeHint().height());
    ui->scrollAreaWidgetContents->resize(ui->label_Image->sizeHint());
}
