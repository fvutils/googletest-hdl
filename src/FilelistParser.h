/*
 * FilelistParser.h
 *
 *  Created on: Oct 27, 2018
 *      Author: ballance
 */

#ifndef INCLUDED_FILELIST_PARSER_H
#define INCLUDED_FILELIST_PARSER_H
#include <string>
#include <vector>
#include <stdio.h>

class FilelistParser {
public:

	static bool parse(
			const std::string			&filelist,
			const std::string			&cwd,
			bool						is_caps_f,
			std::vector<std::string>	&args
			);

protected:
	FilelistParser(
			FilelistParser				*parent,
			const std::string			&filelist,
			const std::string			&basedir,
			std::vector<std::string>	&args,
			std::vector<std::string>	&processed_paths);

	virtual ~FilelistParser();

	bool parse();

	std::string readtok();

	int getch();

	void ungetch(int c);

	static std::string expand(const std::string &str);

private:
	FilelistParser				*m_parent;
	std::string					m_filelist;
	std::string					m_basedir;
	std::vector<std::string>	&m_args;
	std::vector<std::string>	&m_processed_paths;
	FILE						*m_fp;
	int							m_unget_c;
};

#endif /* INCLUDED_FILELIST_PARSER_H */
