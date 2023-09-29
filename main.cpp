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
#include "../lpop/cl_options.hpp"
#include "./SetupOptions.cpp"
#include "./SQLBruteForce.cpp"

int main(int argc,char* args[])
{
	SQLBruteForce *bruteForcer = NULL;
	Options *coptions = NULL;
	struct options_params *url = NULL;
	struct options_params *sessionParam = NULL;

	coptions = SetupOptions( argc, args);

	url = coptions->Get("-u");
	sessionParam = coptions->Get("-s");

	if (coptions->CheckRequirements())
	{
		
		bruteForcer = new SQLBruteForce();
		
		if (sessionParam)
		{
			bruteForcer->setURL(url->value);

			if (sessionParam->isTriggered)
			{
				if (sessionParam->value)
				{
					bruteForcer->setSession(sessionParam->value);
				}
			}

			bruteForcer->start();
		}

		delete  bruteForcer;
		bruteForcer = NULL;
		
	}
	
	if (coptions)
	{
		delete coptions;
		coptions = NULL;
	}
	
	
 //   MemoryResults();
}


