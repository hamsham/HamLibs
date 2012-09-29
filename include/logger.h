//logging class using allegro

#ifndef __HAMLIBS_LOGGER_H__
#define __HAMLIBS_LOGGER_H__

namespace hamLibs {

class logger {
	private:
		std::ostream* logFile;
		bool isLogging;

	public:
		
		logger	();
		logger	(std::ostream* streamToLogWith);
		~logger	();
		void		setLogStream	(std::ostream* streamToUse);
		bool		getLogState		() const;
		void		setLogState		(bool state);
		void		log			(const char* info2Log, ...);
};
} //end hamlibs namespace
#endif /*__LOGGER_H__*/
