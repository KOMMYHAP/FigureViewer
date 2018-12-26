#include "mainwidget.h"

#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent /* = nullptr */)
	: QWidget(parent)
{
	m_pViewer = new WidgetViewer(this);
	m_pSettings = new WidgetSettings(this);

	auto pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pViewer);
	pLayout->addWidget(m_pSettings);

	connect(m_pSettings, SIGNAL(scaleChanged(qreal)), 
		m_pViewer, SLOT(setScale(qreal)));

	connect(m_pSettings, SIGNAL(geometryChanged(QString const &)),
		m_pViewer, SLOT(setGeometryEngine(QString const &)));

	connect(m_pSettings, SIGNAL(enableSpeedAttenuation(bool)),
		m_pViewer, SLOT(enableSpeedAttenuation(bool)));
}