#include "widgetSettings.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QSlider>
#include <QCheckBox>

WidgetSettings::WidgetSettings(QWidget *parent /* = nullptr */)
	: QWidget(parent)
{
	// Доступные фигуры:
	auto pRadioTetrahedron = new QRadioButton("&Тетраэдр", this);
	auto pRadioCube = new QRadioButton("&Куб", this);
	pRadioTetrahedron->setChecked(true);

	auto pRadioLayout = new QVBoxLayout(this);
	pRadioLayout->addWidget(pRadioTetrahedron);
	pRadioLayout->addWidget(pRadioCube);

	auto pGroupButtons = new QGroupBox("Доступные фигуры: ", this);
	pGroupButtons->setLayout(pRadioLayout);

	// Масштабирование
	auto pScaleLabel = new QLabel("Масштабирование: ", this);
	auto pScale = new QSlider(Qt::Horizontal, this);
	pScale->setMinimum(5);
	pScale->setMaximum(70);
	pScale->setSingleStep(5);

	auto pAttentunuatorLabel = new QLabel("Затухание скорости: ", this);
	auto pAttentunuator = new QCheckBox("Включено", this);
	pAttentunuator->setChecked(true);

	// Вращение:
	auto pSpeedSpinX = new QSlider(Qt::Vertical, this);
	pSpeedSpinX->setMinimum(0);
	pSpeedSpinX->setMaximum(100);
	pSpeedSpinX->setSingleStep(10);

	auto pSpeedSpinY = new QSlider(Qt::Vertical, this);
	pSpeedSpinY->setMinimum(0);
	pSpeedSpinY->setMaximum(100);
	pSpeedSpinY->setSingleStep(10);

	auto pSpeedSpinLayout = new QHBoxLayout();
	pSpeedSpinLayout->addWidget(pSpeedSpinX);
	pSpeedSpinLayout->addWidget(pSpeedSpinY);

	auto pGroupSliders = new QGroupBox("Вращение: ", this);
	pGroupSliders->setLayout(pSpeedSpinLayout);

	// Объединение всего в один слой
	auto pLayout = new QVBoxLayout(this);
	pLayout->addWidget(pGroupButtons);
	pLayout->addWidget(pScaleLabel);
	pLayout->addWidget(pScale);
	pLayout->addWidget(pAttentunuatorLabel);
	pLayout->addWidget(pAttentunuator);
	pLayout->addWidget(pGroupSliders);
	pLayout->addStretch();

	// Связывание сигналов и слотов
	connect(pScale, SIGNAL(valueChanged(int)), this, SLOT(changedScale(int)));
	connect(pSpeedSpinX, SIGNAL(valueChanged(int)), this, SLOT(changedSpeedSpinX(int)));
	connect(pSpeedSpinY, SIGNAL(valueChanged(int)), this, SLOT(changedSpeedSpinY(int)));
	connect(pRadioTetrahedron, SIGNAL(pressed()), this, SLOT(chosenTetrahedron()));
	connect(pRadioCube, SIGNAL(pressed()), this, SLOT(chosenCube()));
	connect(pAttentunuator, SIGNAL(stateChanged(int)), this, SLOT(changedAttentunuator(int)));

	// Применение настроек по умолчанию
	changedScale(pScale->value());
	changedAttentunuator(pAttentunuator->checkState());
	if (pRadioTetrahedron->isChecked())
		chosenTetrahedron();
	else if (pRadioCube->isChecked())
		chosenCube();
}

void WidgetSettings::changedScale(int value) const
{
	emit scaleChanged(static_cast<qreal>(-value));
}

void WidgetSettings::changedSpeedSpinX(int) const
{
	
}

void WidgetSettings::changedSpeedSpinY(int) const
{
	
}

void WidgetSettings::chosenCube() const
{
	emit geometryChanged("Куб");
}

void WidgetSettings::chosenTetrahedron() const
{
	emit geometryChanged("Тетраэдр");
}

void WidgetSettings::changedAttentunuator(int state) const
{
	bool checked = state == Qt::Checked;
	emit enableSpeedAttenuation(checked);
}
