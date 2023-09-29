#ifndef __SQLBRUTEForce
#define __SQLBRUTEForce

#include <stdio.h>
#include "../lpop/required/nix.hpp"
#include "../lpop/required/memory.hpp"
#include "../lpop/required/platform.hpp"
#include "../lpop/required/assert.hpp"
#include "../lpop/bucket.hpp"
#include "../lpop/array.hpp"
#include "../lpop/strings.hpp"
#include "../lpop/htmlparser.hpp"
#include "../lpop/curled.h"


class SQLBruteForce
{
	public:
		void start();
		bool HasAnInternalError(s32 *html);
		s32 *CreateCookie(char *injectionPayload);
		void setSession(s32 *sessionCookie);
		bool CheckLetter(int position, char letter);
		bool CheckPasswordLength(int number);
		i32 GetPasswordLength();
		void setURL(s32 *urlToBrute);
		SQLBruteForce();
		~SQLBruteForce();
	private:
		s32 *url;
		s32 *session;
		//CURLED *curl;
};

#endif
