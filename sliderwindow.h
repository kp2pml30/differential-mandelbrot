#ifndef SLIDERWINDOW_H
#define SLIDERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class SliderWindow;
}
QT_END_NAMESPACE

class SliderWindow : public QMainWindow
{
	Q_OBJECT

public:
	std::function<void(std::string const&, double)> callback;
	SliderWindow(QWidget* parent = nullptr);
	~SliderWindow();

public slots:
	void on_SliderGamma_valueChanged(int value);

	void on_SliderB_valueChanged(int value);

	void on_SliderEpsilon_valueChanged(int value);

	void on_SliderForce_valueChanged(int value);

public:
	Ui::SliderWindow* ui;
};
#endif // SLIDERWINDOW_H
