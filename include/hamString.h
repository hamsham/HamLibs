/* 
 * File:   hamString.h
 * Author: hammy
 *
 * Created on July 7, 2012, 6:41 PM
 */

#ifndef __HAMSTRING_H__
#define	__HAMSTRING_H__
namespace hamLibs {

#ifndef nPos
	#define nPos (-1)
#endif

class hamString {
	private:
		char*		array;
		size_t		Size;
	
	public:
		hamString		();
		hamString		(char c);
		hamString		(const char* str);
		hamString		(const hamString& str);
		~hamString		();

		//operators
		hamString&	operator =	(const hamString& str);
		hamString&	operator =	(const char* str);
		hamString&	operator =	(char c);
		
		hamString&	operator +=	(const hamString& str);
		hamString&	operator +=	(const char* str);
		hamString&	operator +=	(char c);
		
		hamString	operator +	(const hamString& str) const;
		hamString	operator +	(const char* str) const;
		hamString	operator +	(char c) const;
		
		bool		operator ==	(const hamString& str) const;
		bool		operator ==	(const char* str) const;
		bool		operator ==	(char c) const;
		
		bool		operator !=	(const hamString& str) const;
		bool		operator !=	(const char* str) const;
		bool		operator !=	(char c) const;
		
		char&		operator []	(int);
		char		operator []	(int) const;

		//character deletion
		void		clear		();
		void		popFront	();
		void		popBack		();
		void		pop			(size_t index);

		//random accecss insertion
		void		push		(size_t index, const char* str, size_t strSize);
		void		pushAfter	(size_t index, const char* str, size_t strSize);
		
		void		push		(size_t index, const hamString& str);
		void		pushAfter	(size_t index, const hamString& str);
		
		void		push		(size_t index, const char* str);
		void		pushAfter	(size_t index, const char* str);
		
		void		push		(size_t index, char c);
		void		pushAfter	(size_t index, char c);
		
		//direct insertion
		void		pushFront	(const char* str, size_t strSize);
		void		pushBack	(const char* str, size_t strSize);
		
		void		pushFront	(const hamString& str);
		void		pushBack	(const hamString& str);
		
		void		pushFront	(const char* str);
		void		pushBack	(const char* str);
		
		void		pushFront	(char c);
		void		pushBack	(char c);

		//traversal
		char&		front		();
		char&		back		();
		
		//searching
		long int	find		(const char* str, size_t strLength) const;
		long int	find		(const hamString& str) const;
		long int	find		(const char* str) const;
		long int	find		(char c) const;
		
		long int	rFind		(const char* str, size_t strLength) const;
		long int	rFind		(const hamString& str) const;
		long int	rFind		(const char* str) const;
		long int	rFind		(char c) const;

		//utility functions
		void		copy		(const hamString& str);
		void		copy		(const char* str);
		void		copy		(char c);
		
		void		append		(const hamString& str);
		void		append		(const char* str, size_t strLength);
		void		append		(const char* str);
		void		append		(char c);
		
		void		resize		(size_t newSize, char c);
		void		resize		(size_t newSize);
		
		//miscellaneous
		hamString	subStr		(size_t pos, size_t length) const;
		bool		empty		() const;
		size_t		size		() const;
		void		swap		(hamString&);
		const char*	cStr		() const;
};

} //end hamLibs namespace
#endif	/* HAMSTRING_H */
