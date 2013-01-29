/* 
 * File:   hamString.h
 * Author: hammy
 *
 * Created on July 7, 2012, 6:41 PM
 */

#ifndef __HL_STRING_H__
#define	__HL_STRING_H__

namespace hamLibs {
namespace containers {

class HL_API string {
	private:
		static const int nPos;
		
		char*		array;
		hlSize_t	Size;
	
	public:
		string		();
		string		(char c);
		string		(const char* str);
		string		(const string& str);
		~string		();

		//operators
		string&		operator =	(const string& str);
		string&		operator =	(const char* str);
		string&		operator =	(char c);
		
		string&		operator +=	(const string& str);
		string&		operator +=	(const char* str);
		string&		operator +=	(char c);
		
		string		operator +	(const string& str) const;
		string		operator +	(const char* str) const;
		string		operator +	(char c) const;
		
		bool		operator ==	(const string& str) const;
		bool		operator ==	(const char* str) const;
		bool		operator ==	(char c) const;
		
		bool		operator !=	(const string& str) const;
		bool		operator !=	(const char* str) const;
		bool		operator !=	(char c) const;
		
		char&		operator []	(int);
		char		operator []	(int) const;

		//character deletion
		void		clear		();
		void		popFront	();
		void		popBack		();
		void		pop			(hlSize_t index);

		//random accecss insertion
		void		push		(hlSize_t index, const char* str, hlSize_t strSize);
		void		pushAfter	(hlSize_t index, const char* str, hlSize_t strSize);
		
		void		push		(hlSize_t index, const string& str);
		void		pushAfter	(hlSize_t index, const string& str);
		
		void		push		(hlSize_t index, const char* str);
		void		pushAfter	(hlSize_t index, const char* str);
		
		void		push		(hlSize_t index, char c);
		void		pushAfter	(hlSize_t index, char c);
		
		//direct insertion
		void		pushFront	(const char* str, hlSize_t strSize);
		void		pushBack	(const char* str, hlSize_t strSize);
		
		void		pushFront	(const string& str);
		void		pushBack	(const string& str);
		
		void		pushFront	(const char* str);
		void		pushBack	(const char* str);
		
		void		pushFront	(char c);
		void		pushBack	(char c);

		//traversal
		char&		front		();
		char&		back		();
		
		//searching
		hlSize_t	find		(const char* str, hlSize_t strLength) const;
		hlSize_t	find		(const string& str) const;
		hlSize_t	find		(const char* str) const;
		hlSize_t	find		(char c) const;
		
		hlSize_t	rFind		(const char* str, hlSize_t strLength) const;
		hlSize_t	rFind		(const string& str) const;
		hlSize_t	rFind		(const char* str) const;
		hlSize_t	rFind		(char c) const;

		//utility functions
		void		copy		(const string& str);
		void		copy		(const char* str);
		void		copy		(char c);
		
		void		append		(const string& str);
		void		append		(const char* str, hlSize_t strLength);
		void		append		(const char* str);
		void		append		(char c);
		
		void		resize		(hlSize_t newSize, char c);
		void		resize		(hlSize_t newSize);
		
		//miscellaneous
		string	subStr		(hlSize_t pos, hlSize_t length) const;
		bool		empty		() const;
		hlSize_t	size		() const;
		void		swap		(string&);
		const char*	cStr		() const;
};

} // end containers namespace
} //end hamLibs namespace

#endif	/* __HL_STRING_H__ */
