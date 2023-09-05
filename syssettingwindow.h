#ifndef SYSSETTINGWINDOW_H
#define SYSSETTINGWINDOW_H

#include <QWidget>
#include <QPainter>

#include "canthread.h"

namespace Ui {
class SysSettingWindow;
}

class SysSettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SysSettingWindow(QWidget *parent = nullptr);
     static SysSettingWindow *getInstance();
    ~SysSettingWindow();
     CanThread *canThreadsend;

protected:
    void paintEvent(QPaintEvent *event);

private slots:


     void on_lineEdit_textChanged(const QString &arg1);

     void on_pushButton_4_clicked();

     void on_lineEdit_2_textChanged(const QString &arg1);

     void on_pushButton_5_clicked();

     void on_lineEdit_3_textChanged(const QString &arg1);

     void on_pushButton_7_clicked();

     void on_lineEdit_7_textChanged(const QString &arg1);

     void on_pushButton_8_clicked();

     void on_lineEdit_4_textChanged(const QString &arg1);

     void on_pushButton_9_clicked();

     void on_lineEdit_5_textChanged(const QString &arg1);

     void on_pushButton_10_clicked();

     void on_lineEdit_6_textChanged(const QString &arg1);

     void on_pushButton_11_clicked();

     void on_lineEdit_8_textChanged(const QString &arg1);

     void on_pushButton_12_clicked();

     void on_lineEdit_9_textChanged(const QString &arg1);

     void on_pushButton_13_clicked();

     void on_lineEdit_10_textChanged(const QString &arg1);

     void on_pushButton_14_clicked();

     void on_lineEdit_11_textChanged(const QString &arg1);

     void on_pushButton_15_clicked();

     void on_lineEdit_12_textChanged(const QString &arg1);

     void on_pushButton_16_clicked();

     void on_lineEdit_13_textChanged(const QString &arg1);

     void on_pushButton_17_clicked();

     void on_lineEdit_14_textChanged(const QString &arg1);

     void on_pushButton_18_clicked();

     void on_lineEdit_15_textChanged(const QString &arg1);

     void on_pushButton_19_clicked();

     void on_lineEdit_16_textChanged(const QString &arg1);

     void on_pushButton_20_clicked();

     void on_lineEdit_17_textChanged(const QString &arg1);

     void on_pushButton_22_clicked();

     void on_lineEdit_25_textChanged(const QString &arg1);

     void on_pushButton_21_clicked();

     void on_lineEdit_24_textChanged(const QString &arg1);

     void on_pushButton_23_clicked();

     void on_lineEdit_18_textChanged(const QString &arg1);

     void on_pushButton_24_clicked();

     void on_lineEdit_19_textChanged(const QString &arg1);

     void on_pushButton_25_clicked();

     void on_lineEdit_20_textChanged(const QString &arg1);

     void on_pushButton_28_clicked();

     void on_lineEdit_21_textChanged(const QString &arg1);

     void on_pushButton_26_clicked();

     void on_lineEdit_23_textChanged(const QString &arg1);

     void on_pushButton_27_clicked();

     void on_lineEdit_22_textChanged(const QString &arg1);

     void on_pushButton_29_clicked();

     void on_pushButton_6_clicked();

     void on_pushButton_30_clicked();

     void on_pushButton_31_clicked();

     void on_lineEdit_26_textChanged(const QString &arg1);

     void on_pushButton_33_clicked();

     void on_lineEdit_27_textChanged(const QString &arg1);

     void on_pushButton_34_clicked();

     void on_lineEdit_28_textChanged(const QString &arg1);

     void on_pushButton_35_clicked();

     void on_lineEdit_29_textChanged(const QString &arg1);

     void on_pushButton_36_clicked();

     void on_lineEdit_43_textChanged(const QString &arg1);

     void on_pushButton_50_clicked();

     void on_lineEdit_41_textChanged(const QString &arg1);

     void on_pushButton_52_clicked();

     void on_lineEdit_44_textChanged(const QString &arg1);

     void on_pushButton_51_clicked();

     void on_lineEdit_42_textChanged(const QString &arg1);

     void on_pushButton_53_clicked();

     void on_pushButton_32_clicked();

     void on_pushButton_49_clicked();

     void on_pushButton_37_clicked();

     void on_lineEdit_30_textChanged(const QString &arg1);

     void on_pushButton_38_clicked();

     void on_lineEdit_31_textChanged(const QString &arg1);

     void on_pushButton_39_clicked();

     void on_lineEdit_32_textChanged(const QString &arg1);

     void on_pushButton_40_clicked();

     void on_lineEdit_33_textChanged(const QString &arg1);

     void on_pushButton_41_clicked();

     void on_lineEdit_34_textChanged(const QString &arg1);

     void on_pushButton_42_clicked();

     void on_lineEdit_35_textChanged(const QString &arg1);

     void on_pushButton_43_clicked();

     void on_lineEdit_36_textChanged(const QString &arg1);

     void on_pushButton_44_clicked();

     void on_lineEdit_37_textChanged(const QString &arg1);

     void on_pushButton_45_clicked();

     void on_lineEdit_38_textChanged(const QString &arg1);

     void on_pushButton_46_clicked();

     void on_lineEdit_39_textChanged(const QString &arg1);

     void on_pushButton_47_clicked();

     void on_lineEdit_40_textChanged(const QString &arg1);

     void on_pushButton_48_clicked();

     void on_lineEdit_45_textChanged(const QString &arg1);

     void on_pushButton_54_clicked();

     void on_lineEdit_48_textChanged(const QString &arg1);

     void on_pushButton_56_clicked();

     void on_lineEdit_46_textChanged(const QString &arg1);

     void on_pushButton_58_clicked();

     void on_lineEdit_49_textChanged(const QString &arg1);

     void on_pushButton_57_clicked();

     void on_lineEdit_47_textChanged(const QString &arg1);

     void on_pushButton_59_clicked();

     void on_lineEdit_52_textChanged(const QString &arg1);

     void on_pushButton_61_clicked();

     void on_lineEdit_50_textChanged(const QString &arg1);

     void on_pushButton_63_clicked();

     void on_lineEdit_53_textChanged(const QString &arg1);

     void on_pushButton_62_clicked();

     void on_lineEdit_51_textChanged(const QString &arg1);

     void on_pushButton_64_clicked();

     void on_lineEdit_54_textChanged(const QString &arg1);

     void on_pushButton_66_clicked();

     void on_lineEdit_62_textChanged(const QString &arg1);

     void on_pushButton_67_clicked();

     void on_lineEdit_61_textChanged(const QString &arg1);

     void on_pushButton_68_clicked();

     void on_lineEdit_56_textChanged(const QString &arg1);

     void on_pushButton_69_clicked();

     void on_lineEdit_55_textChanged(const QString &arg1);

     void on_pushButton_71_clicked();

     void on_lineEdit_57_textChanged(const QString &arg1);

     void on_pushButton_72_clicked();

     void on_lineEdit_59_textChanged(const QString &arg1);

     void on_pushButton_73_clicked();

     void on_lineEdit_60_textChanged(const QString &arg1);

     void on_pushButton_70_clicked();

     void on_pushButton_55_clicked();

     void on_pushButton_60_clicked();

     void on_pushButton_65_clicked();

     void on_lineEdit_58_textChanged(const QString &arg1);

     void on_pushButton_75_clicked();

     void on_lineEdit_63_textChanged(const QString &arg1);

     void on_pushButton_76_clicked();

     void on_lineEdit_64_textChanged(const QString &arg1);

     void on_pushButton_77_clicked();

     void on_lineEdit_65_textChanged(const QString &arg1);

     void on_pushButton_78_clicked();

     void on_lineEdit_66_textChanged(const QString &arg1);

     void on_pushButton_79_clicked();

     void on_lineEdit_67_textChanged(const QString &arg1);

     void on_pushButton_80_clicked();

     void on_lineEdit_68_textChanged(const QString &arg1);

     void on_pushButton_81_clicked();

     void on_lineEdit_69_textChanged(const QString &arg1);

     void on_pushButton_82_clicked();

     void on_lineEdit_70_textChanged(const QString &arg1);

     void on_pushButton_83_clicked();

     void on_lineEdit_71_textChanged(const QString &arg1);

     void on_pushButton_84_clicked();

     void on_lineEdit_82_textChanged(const QString &arg1);

     void on_pushButton_97_clicked();

     void on_lineEdit_83_textChanged(const QString &arg1);

     void on_pushButton_98_clicked();

     void on_lineEdit_84_textChanged(const QString &arg1);

     void on_pushButton_99_clicked();

     void on_lineEdit_85_textChanged(const QString &arg1);

     void on_pushButton_100_clicked();

     void on_lineEdit_86_textChanged(const QString &arg1);

     void on_pushButton_101_clicked();

     void on_lineEdit_87_textChanged(const QString &arg1);

     void on_pushButton_102_clicked();

     void on_lineEdit_88_textChanged(const QString &arg1);

     void on_pushButton_103_clicked();

     void on_lineEdit_89_textChanged(const QString &arg1);

     void on_pushButton_104_clicked();

     void on_lineEdit_90_textChanged(const QString &arg1);

     void on_pushButton_105_clicked();

     void on_lineEdit_91_textChanged(const QString &arg1);

     void on_pushButton_106_clicked();

     void on_lineEdit_102_textChanged(const QString &arg1);

     void on_pushButton_119_clicked();

     void on_lineEdit_103_textChanged(const QString &arg1);

     void on_pushButton_120_clicked();

     void on_lineEdit_104_textChanged(const QString &arg1);

     void on_pushButton_121_clicked();

     void on_lineEdit_105_textChanged(const QString &arg1);

     void on_pushButton_122_clicked();

     void on_lineEdit_106_textChanged(const QString &arg1);

     void on_pushButton_123_clicked();

     void on_lineEdit_107_textChanged(const QString &arg1);

     void on_pushButton_124_clicked();

     void on_lineEdit_108_textChanged(const QString &arg1);

     void on_pushButton_125_clicked();

     void on_lineEdit_109_textChanged(const QString &arg1);

     void on_pushButton_126_clicked();

     void on_lineEdit_110_textChanged(const QString &arg1);

     void on_pushButton_127_clicked();

     void on_lineEdit_111_textChanged(const QString &arg1);

     void on_pushButton_128_clicked();

     void on_pushButton_74_clicked();

     void on_pushButton_96_clicked();

     void on_pushButton_118_clicked();

     void on_pushButton_3_clicked();

     void on_pushButton_140_clicked();

     void on_pushButton_147_clicked();

     void on_pushButton_154_clicked();

     void on_calendarWidget_selectionChanged();

     void on_pushButton_152_clicked();

     void on_lineEdit_136_textChanged(const QString &arg1);

     void on_pushButton_158_clicked();

     void on_lineEdit_122_textChanged(const QString &arg1);

     void on_pushButton_160_clicked();

     void on_lineEdit_141_textChanged(const QString &arg1);

     void on_pushButton_163_clicked();

     void on_lineEdit_138_textChanged(const QString &arg1);

     void on_pushButton_165_clicked();

     void on_lineEdit_143_textChanged(const QString &arg1);

     void on_pushButton_168_clicked();

     void on_lineEdit_144_textChanged(const QString &arg1);

     void on_pushButton_169_clicked();

     void on_lineEdit_145_textChanged(const QString &arg1);

     void on_pushButton_170_clicked();

     void on_lineEdit_146_textChanged(const QString &arg1);

     void on_pushButton_171_clicked();

     void on_lineEdit_147_textChanged(const QString &arg1);

     void on_pushButton_172_clicked();

     void on_lineEdit_148_textChanged(const QString &arg1);

     void on_pushButton_173_clicked();

     void on_lineEdit_149_textChanged(const QString &arg1);

     void on_pushButton_174_clicked();

     void on_lineEdit_150_textChanged(const QString &arg1);

     void on_pushButton_175_clicked();

     void on_lineEdit_151_textChanged(const QString &arg1);

     void on_pushButton_176_clicked();

     void on_pushButton_145_clicked();

     void on_pushButton_162_clicked();

     void on_pushButton_167_clicked();

     void on_pushButton_159_clicked();

     void on_btnKM13ON_clicked();

     void on_btnKM13OFF_clicked();

     void on_btnKM24ON_clicked();

     void on_btnKM13OFF_2_clicked();

     void on_btnKM910ON_clicked();

     void on_btnKM910OFF_clicked();

     void on_btnKM910ON_2_clicked();

     void on_btnKM910OFF_2_clicked();

     void on_btnKM910ON_3_clicked();

     void on_btnKM910OFF_3_clicked();

     void on_btnPMWON_3_clicked();

     void on_btnPMWOFF_3_clicked();

     void on_btnPMWON_clicked();

     void on_btnPMWOFF_clicked();

     void on_btnPMWON_2_clicked();

     void on_btnPMWOFF_2_clicked();

     void on_btnKA34ON_clicked();

     void on_btnKA34OFF_clicked();

     void on_btnPMWON_4_clicked();

     void on_btnPMWOFF_4_clicked();

     void on_btnKM13ON_2_clicked();

     void on_btnKM13OFF_4_clicked();

     void on_btnKM24ON_2_clicked();

     void on_btnKM13OFF_3_clicked();

     void on_btnKM910ON_6_clicked();

     void on_btnKM910OFF_6_clicked();

     void on_btnKM910ON_4_clicked();

     void on_btnKM910OFF_4_clicked();

     void on_btnKM910ON_5_clicked();

     void on_btnKM910OFF_5_clicked();

     void on_btnPMWON_6_clicked();

     void on_btnPMWOFF_6_clicked();

     void on_btnPMWON_7_clicked();

     void on_btnPMWOFF_7_clicked();

     void on_btnPMWON_5_clicked();

     void on_btnPMWOFF_5_clicked();

     void on_btnKA34ON_2_clicked();

     void on_btnKA34OFF_2_clicked();

     void on_btnPMWON_8_clicked();

     void on_btnPMWOFF_8_clicked();

     void on_btnKM13ON_4_clicked();

     void on_btnKM13OFF_7_clicked();

     void on_btnKM24ON_4_clicked();

     void on_btnKM13OFF_8_clicked();

     void on_btnKM910ON_11_clicked();

     void on_btnKM910OFF_11_clicked();

     void on_btnKM910ON_10_clicked();

     void on_btnKM910OFF_10_clicked();

     void on_btnPMWON_15_clicked();

     void on_btnPMWOFF_15_clicked();

     void on_btnPMWON_13_clicked();

     void on_btnPMWOFF_13_clicked();

     void on_btnPMWON_14_clicked();

     void on_btnPMWOFF_14_clicked();

     void on_btnKA34ON_4_clicked();

     void on_btnKA34OFF_4_clicked();

     void on_pushButton_161_clicked();

     void on_btnKA34ON_5_clicked();

     void on_btnKA34OFF_5_clicked();

private:
    Ui::SysSettingWindow *ui;
    static SysSettingWindow * setWin;
    void  sendcmd(long canid,uint8_t commmand,uint8_t value,uint8_t ch);
    void timer_update_window();
    QTimer * timer1;
    void senddata(long canid, uint8_t commmand,int byte0,uint8_t byte1);
};

#endif // SYSSETTINGWINDOW_H
