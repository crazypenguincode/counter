#ifndef VSFLOATINGWIDGET_H_2BAB0890_ED39_4BF8_98A9_1AE6AADBEE38
#define VSFLOATINGWIDGET_H_2BAB0890_ED39_4BF8_98A9_1AE6AADBEE38
/************************************************************************/
/* ������һ�ָ�����ʵ��                                                                     */
/************************************************************************/
#include <QWidget>
#include <QPoint>
#include <QTimer>
#include <QColor>
#include <QLabel>

// ����չʾģʽ
enum EnVSFWShowMode
{
	esmHide,						// ����ʾ
	esmNormal,						// ��ͨ����ģʽ����ʾ����Ӧ����϶�����ͨ���ڣ�
	esmNormal_EdgeAutoHide,			// �����Զ����أ���Ӧ����϶�������ʱ���Զ����أ�����QQ�������أ�
	esmShowFixed,					// �̶�����ѡ�У���ʾ������Ӧ����¼��������ƶ����̶��������������ɴ�͸��
	esmShowFixed_SlippingAutoHide,	// �����Զ����أ���׽���������أ������ƶ�
	esmHide_SlippingAutoShow,		// ʼ���Զ����أ��������أ���׽��������ʾ�������ƶ�
};

// ��������λ��ö��
enum EnVSFWPositionType
{
	eptTopMid = 0,
	eptTopLeft,
	eptTopRight,
	eptBottomMid,
	eptBottomLeft,
	eptBottomRight,
};

// �Զ��ƶ�����ö�٣���ʱ��
enum EnVSFWHideDirection
{
	ehdTop = 0,
	ehdLeft,
	ehdRight,
	ehdBottom,
};

class VSFloatingWidget : public QWidget
{
	Q_OBJECT

public:
	//************************************
	// Remark:	  EnVSFWShowMode ָ���˴��ڹ���ģʽ
	// FullName:  VSFloatingWidget::VSFloatingWidget
	// Parameter: EnVSFWShowMode enShowMode
	// Parameter: EnAttachType enAttachType
	// Parameter: QPoint & oCurPosition
	// Parameter: QWidget * parent
	//************************************
	VSFloatingWidget(EnVSFWShowMode enShowMode = esmNormal, QPoint &oCurPosition = QPoint(0, 0), QWidget *parent = nullptr);
	virtual ~VSFloatingWidget();

public:
public:
	//************************************
	// Remark:    �����˻����show����Ҫ��QWidet��ָ��show����
	// FullName:  VSFloatingWidget::show
	// Returns:   void
	//************************************
	void show();

	//************************************
	// Remark:    ����չʾģʽ
	// FullName:  VSFloatingWidget::setShowMode
	// Returns:   void
	// Parameter: EnVSFWShowMode enShowMode
	//************************************
	virtual void setShowMode(EnVSFWShowMode enShowMode);
	EnVSFWShowMode getShowMode();

	//************************************
	// Remark:    ���㴰��λ��
	// FullName:  VSFloatingWidget::calcPosition
	// Returns:   QT_NAMESPACE::QPoint
	// Parameter: EnVSFWPositionType enAttachType
	//************************************
	QPoint calcPosition(EnVSFWPositionType enAttachType);
	// ��ʱֹͣ�ö�
	void pauseTopOn();
	// �ָ��ö�
	void resumeTopOn();

public:
	//************************************
	// Remark:    ���ء���ʾ����ʱ�Ķ����ٶȡ���ÿ���ƶ�����������Ϊ׼
	// FullName:  VSFloatingWidget::setSlidingSpeed
	// Returns:   void
	// Parameter: int nHideSpeed
	//************************************
	void setSlidingSpeed(int nHideSpeed = 2);
	//************************************
	// Remark:    ��Ե�ߡ������Ƴ�����󣬻��������ֵ�����ص�Ӱ�������ֵ֮�ڣ����ڻ��Զ���������Ե
	// FullName:  VSFloatingWidget::setAttachBoder
	// Access:    public 
	// Returns:   void
	// Parameter: int nAttachBorder
	//************************************
	void setAttachBoder(int nAttachBorder = 2);
	//************************************
	// Remark:    ���ô������岻͸����
	// FullName:  VSFloatingWidget::setWindowsOpacity
	// Returns:   void
	// Parameter: double dOpacity			��0-1����Ϊ0ʱ��ȫ͸��
	//************************************
	void setWidgetOpacity(double dOpacity = 1);
	//************* ���ô��ڱ���ɫ��֧��alphaͨ��***********************
	// Remark:    
	// FullName:  VSFloatingWidget::setBackgroundColor
	// Returns:   void
	// Parameter: QColor & oColor			Ĭ�Ϻ�ɫ
	// Parameter: double dAlpha				��0-1����Ϊ0ʱ��ȫ͸��
	//************************************
	void setBackgroundColor(QColor &oColor = QColor(0, 0, 0), double dAlpha = 0);
	//************************************
	// Remark:    �����ö�Ƶ�ʣ�Ĭ��ÿ��60��
	// FullName:  VSFloatingWidget::setFrequency
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int nFrequence
	//************************************
	void setFrequency(int nFrequence = 60);

private:
	virtual bool event(QEvent* e) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;

protected:
	void stackWidgetOnTop();
	void hideWidgetSliding();
	void showWidgetSliding();

private:
	void initWidgetProperty();
	void setIgnoreAllEvent(bool bIgnore = true);

private:// ״̬����
	EnVSFWShowMode m_enShowMode;

private:// ��ʱ
	QPoint m_oOldPos;							// �ƶ�����ʱ�����λ�ü�¼
	QRect m_oScreenRect;
	EnVSFWHideDirection m_enHideDirection;
	int m_nPausedCount;							// ��¼��ͣ�ö�����
    QLabel *m_oTextShow;
    QList<QLabel*> m_list;
    

private:// �����
	int m_nHideSpeed;							// ���ء���ʾ����ʱ�Ķ����ٶȡ���ÿ���ƶ�����������Ϊ׼
	int m_nAttachBorder;						// ��Ե�ߣ������Ƴ��󣬻��������ֵ�����ص�Ӱ�������ֵ֮�ڣ����ڻ��Զ���������Ե
	double m_dWidgetOpacity;					// ���ڲ�͸����
	QColor m_oBackgroundColor;					// ���ڱ�����ɫ
	QTimer m_oTimer;							// ��ʱ�������ڶ�ʱ�ö�����
    bool m_bPressed = false;
    QPoint m_point;
};

#endif //VSFLOATINGWIDGET_H_2BAB0890_ED39_4BF8_98A9_1AE6AADBEE38