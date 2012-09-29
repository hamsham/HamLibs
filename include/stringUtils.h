/* 
 * File:   stringUtils.h
 * Author: hammy
 *
 * Created on May 6, 2012, 2:55 PM
 */

#ifndef __HAMLIBS_STRINGUTILS_H__
#define	__HAMLIBS_STRINGUTILS_H__

namespace hamLibs {
	namespace stringUtils {
		//-------------------------------------------------------------
		//				Encryptions
		//-------------------------------------------------------------
		void encodeStr(const std::string& encryptKey, std::string& inputToencrypt);
		void decodeStr(const std::string& decryptKey, std::string& inputTodecrypt);
		
		void encodeFile(const std::string& encryptKey, const char* fileName);
		void decodeFile(const std::string& decryptKey, const char* fileName);
		
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		size_t convertToNum(const std::string& str);
		//the return value may not be large enough to hold the value of the converted string
		//use caution when converting large strings
		
		//-------------------------------------------------------------
		//miscellaneous function prototypes
		//-------------------------------------------------------------
		template <typename dataType>
		dataType convertToType(const std::string& stringToConvert);

		template <typename dataType>
		std::string convertToString(const dataType& dataToConvert);

		template <typename dataType>
		void convertToType(const std::string& stringToConvert, dataType& output);

		template <typename dataType>
		void convertToString(const dataType& dataToConvert, std::string& output);
	
		//-------------------------------------------------------------
		//miscellaneous function definitions
		//-------------------------------------------------------------
		template <typename dataType>
		dataType convertToType(const std::string& stringToConvert) {
			std::istringstream converter(stringToConvert);
			dataType returnVal;
			converter >> returnVal;
			return returnVal;
		}

		template <typename dataType>
		std::string convertToString(const dataType& dataToConvert) {
			std::ostringstream converter;
			converter << dataToConvert;
			return converter.str();
		}

		template <typename dataType>
		void convertToType(const std::string& stringToConvert, dataType& output) {
			std::istringstream converter(stringToConvert);
			converter >> output;
		}

		template <typename dataType>
		void convertToString(const dataType& dataToConvert, std::string& output) {
			std::ostringstream converter;
			converter << dataToConvert;
			output = converter.str();
		}
	} //string utilities namespace
} //hamlibs namespace

#endif	/* __HAMLIBS_STRINGUTILS_H__ */

