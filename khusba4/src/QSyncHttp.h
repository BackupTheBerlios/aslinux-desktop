#include <QtNetwork/QtNetwork>
#include <QEventLoop>
#include <QBuffer>

class QSyncHttp: public QHttp
{
	Q_OBJECT
	public:
		
		QSyncHttp(const QString &host):QHttp(host),status(false),idReq(-1) {}
		bool Get ( const QString & UrlPath, QIODevice * dataReceiver = 0 )
		{
			
			connect(this,SIGNAL(requestFinished(int,bool)),SLOT(finished(int,bool)));
			idReq = get(UrlPath, dataReceiver );
			Blockloop.exec();
			return status;
		}
	protected slots:
		virtual void finished(int reqIndex, bool error)
		{
			
			if(reqIndex!=idReq)
				return;
			status = !error;
			Blockloop.exit();
		}
	private:
		bool status;
		int idReq;
		QEventLoop Blockloop;
};


