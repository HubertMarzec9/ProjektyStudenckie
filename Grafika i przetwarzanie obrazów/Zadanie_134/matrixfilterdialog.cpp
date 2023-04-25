#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "matrixfilterdialog.h"
#include <memory>

MatrixFilterDialog::MatrixFilterDialog(MatrixFilterImageProcessor &processor, QWidget *parent) : QDialog{parent}, processor(processor) {
    QTextEdit *matrixEdit = new QTextEdit(this);
    QFont font = matrixEdit->font();
    font.setFamily("Monospace");
    matrixEdit->setFont(font);

    QPushButton *previewButton = new QPushButton(tr("Preview"), this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(matrixEdit,0,0,1,1);
    mainLayout->addWidget(previewButton,1,0,1,1);

    connect(previewButton, &QPushButton::clicked, this, [&processor, matrixEdit, this]() {
        std::unique_ptr<std::vector<float>> matrix = std::make_unique<std::vector<float>>();
        QString matrixText = matrixEdit->toPlainText();

        QList<QString> lines = matrixText.split('\n');
        for(const QString& line : lines)
            for(const QString &valueString : line.simplified().split(' '))
                matrix->push_back(valueString.toFloat());

        int height = lines.size();
        int width = matrix->size()/height;

        processor.setValues(std::move(matrix), height, width);
        emit requestPreview();
    });
}
