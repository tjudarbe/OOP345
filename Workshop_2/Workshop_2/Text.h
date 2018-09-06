// Name: Lean Junio
// Seneca Student ID: 019-109-123
// Seneca email: ljjunio@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef _W2_TEXT_H
#define _W2_TEXT_H

#include <string>

namespace w2
{
	class Text
	{
		std::string* m_StringPtr;
		std::string m_FileName;
	public:
		explicit Text(std::string file = "Unknown");
		void readFile();
		Text(const Text&);
		Text& operator=(const Text&);
		Text(Text&&);
		Text& operator=(Text&&);
		~Text();

		// Returns the number of records of text data
		size_t size() const;
	};
}

#endif // !_W2_TEXT_H

