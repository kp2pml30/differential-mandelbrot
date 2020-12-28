#include "sliderwindow.h"
#include "./ui_sliderwindow.h"

SliderWindow::SliderWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SliderWindow)
{
	ui->setupUi(this);
}

SliderWindow::~SliderWindow() { delete ui; }

static double Map(double value) { return (value / 1000.0 - 0.5) * 2; }

void SliderWindow::on_SliderGamma_valueChanged(int value)
{
	float val = Map(value);
	ui->LabelGamma->setText(QString::number(val));
	callback("GAMMA", val);
}

void SliderWindow::on_SliderB_valueChanged(int value)
{
	float val = Map(value);
	ui->LabelB->setText(QString::number(val));
	callback("B", val);
}

void SliderWindow::on_SliderEpsilon_valueChanged(int value)
{
	float val = Map(value);
	if (std::abs(val - 0.25) < 0.01)
		val = 0.25;
	ui->LabelEpsilon->setText(QString::number(val));
	callback("EPSILON", val);
}

void SliderWindow::on_SliderForce_valueChanged(int value)
{
	float val = Map(value);
	ui->LabelForce->setText(QString::number(val));
	callback("FORCE", val);
}
