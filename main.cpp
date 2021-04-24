#include "Lprprprpr.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Lprprprpr w;
	w.setWindowTitle("License plate recognition system");
	QIcon icon;
	icon.addFile(QStringLiteral("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
	w.setWindowIcon(icon);
	w.show();
	return a.exec();
}
