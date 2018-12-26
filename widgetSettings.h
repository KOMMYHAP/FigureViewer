#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QWidget>

class WidgetSettings : public QWidget
{
	Q_OBJECT

public:
	WidgetSettings(QWidget *parent = nullptr);
	~WidgetSettings() = default;

signals:
	void scaleChanged(qreal) const;
	void geometryChanged(QString const &) const;
	void enableSpeedAttenuation(bool) const;

private slots:
	// Тригеры слайдеров
	void changedScale(int) const;
	void changedSpeedSpinX(int) const;
	void changedSpeedSpinY(int) const;

	// Тригер аттентюнуатора
	void changedAttentunuator(int) const;

	// Тригеры радиокнопок
	void chosenCube() const;
	void chosenTetrahedron() const;

private:
	
};

#endif