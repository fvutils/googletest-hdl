/*
 * FilelistParser.cpp
 *
 *  Created on: Oct 27, 2018
 *      Author: ballance
 */

#include "FilelistParser.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

bool FilelistParser::parse(
		const std::string			&filelist,
		const std::string			&cwd,
		bool						is_caps_f,
		std::vector<std::string>	&args) {
	std::string basedir = cwd;
	std::vector<std::string> processed_paths;

	if (is_caps_f) {
		// Calculate the base directory
	}

	FilelistParser parser(0, filelist, basedir, args, processed_paths);

	return parser.parse();
}

FilelistParser::FilelistParser(
		FilelistParser				*parent,
		const std::string			&filelist,
		const std::string			&basedir,
		std::vector<std::string>	&args,
		std::vector<std::string>	&processed_paths) :
				m_parent(parent), m_filelist(filelist),
				m_basedir(basedir), m_args(args),
				m_processed_paths(processed_paths),
				m_fp(0), m_unget_c(-1) {
}

FilelistParser::~FilelistParser() {
	if (m_fp) {
		fclose(m_fp);
	}
	// TODO Auto-generated destructor stub
}

bool FilelistParser::parse() {
	std::string tok;

	for (std::vector<std::string>::const_iterator it=m_processed_paths.begin();
			it!=m_processed_paths.end(); it++) {
		if (*it == m_filelist) {
			// TODO: traceback
			return false;
		}
	}

	m_processed_paths.push_back(m_filelist);

	if (!(m_fp = fopen(m_filelist.c_str(), "rb"))) {
		// TODO: traceback
		fprintf(stdout, "Error: failed to open filelist %s\n", m_filelist.c_str());
		return false;
	}

	while ((tok = readtok()).size() > 0) {
		if (tok == "-f" || tok == "-F") {
			std::string filelist = expand(readtok());
			std::string basedir = m_basedir;

			// TODO: resolve path

			FilelistParser parser(this, filelist, basedir, m_args, m_processed_paths);

			if (!parser.parse()) {
				// Hit an error. The sub-parser should report the error
				return false;
			}
		} else {
			m_args.push_back(expand(tok));
		}
	}

	return true;
}

std::string FilelistParser::readtok() {
	std::string ret;
	int ch, ch2;

	while ((ch = getch()) != -1) {
		if (ch == '/') {
			ch2 = getch();

			if (ch2 == '*') {
				int cc1 = -1, cc2 = -1;

				while ((ch = getch()) != -1) {
					cc2 = cc1;
					cc2 = ch;

					if (cc1 == '/' && cc2 == '*') {
						break;
					}
				}
				continue;
			} else if (ch2 == '/') {
				while ((ch = getch()) != -1 && (ch != '\n')) {
					;
				}
				ungetch(ch);
				continue;
			} else {
				ungetch(ch2);
			}
		} else if (isspace(ch)) {
			while ((ch = getch()) != -1 && isspace(ch)) {
				;
			}
			ungetch(ch);
			continue;
		} else {
			break;
		}
	}

	if (ch == '"') {
		int last_ch = -1;
		ret.push_back(ch);
		while ((ch = getch()) != -1) {
			if (ch == '"' && last_ch == '\\') {
				// Replace an escaped double-quote with a quote
				ret.at(ret.size()-1) = ch;
			} else {
				ret.push_back(ch);
			}
			if (ch == '"' && last_ch != '\\') {
				break;
			}
		}
	} else {
		while (ch != -1 && !isspace(ch)) {
			ret.push_back(ch);
			ch = getch();
		}
		ungetch(ch);
	}


	return ret;
}

int FilelistParser::getch() {
	int ret = -1;

	if (m_unget_c != -1) {
		ret = m_unget_c;
		m_unget_c = -1;
	} else {
		ret = fgetc(m_fp);
	}

	return ret;
}

void FilelistParser::ungetch(int c) {
	m_unget_c = c;
}

std::string FilelistParser::expand(const std::string &str) {
	std::string ret;

	for (int i=0; i<str.size(); i++) {
		if (str.at(i) == '$') {
			char ch;
			int j;
			bool expect_closebrace = false;
			if (str.at(i+1) == '{') {
				expect_closebrace = true;
				i=i+2;
			}

			j=i;
			while (j<str.size()) {
				ch = str.at(j);

				if (!(ch >= 'a' && ch <= 'z') &&
						!(ch >= 'A' && ch <= 'Z') &&
						!(ch >= '0' && ch <= '9') &&
						ch != '_') {
					break;
				}
				j++;
			}

			std::string key = str.substr(i, (j-i));
			const char *val = getenv(key.c_str());

			if (!val) {
				val  = "";
			}

			if (!expect_closebrace) {
				i=j-1;
			} else {
				if (str.at(j) != '}') {
					fprintf(stdout, "Warning: expect close-brace in variable reference: %s\n",
							str.c_str());
				}
				i=j;
			}

			ret += val;
		} else {
			ret.push_back(str.at(i));
		}
	}

	return ret;
}

