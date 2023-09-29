#include "SetupOptions.hpp"

Options *SetupOptions(int argc,char* args[])
{
	Options *options = NULL;

	options = new Options(argc, args);

	CreateOptions(options);

	options->Execute();

	return options;
}

void CreateOptions(Options *options)
{
	struct options_params *url = NULL;
	struct options_params *session = NULL;

	url = Memory(struct options_params);
    url->trigger = S32("-u");
    url->name = S32("Url of the website");
    url->description = S32("Url of the website");
    url->type = OPTION_PARAM;
    url->value = NULL;
    url->hasArg = true;
    url->hasMultiParams = false;
    url->isRequired = true;
    url->callback = NULL;
    options->Add(url);

	session = Memory(struct options_params);
    session->trigger = S32("-s");
    session->name = S32("your session, usually found in cookies");
    session->description = S32("your session, usually found in cookies");
    session->type = OPTION_PARAM;
    session->value = NULL;
    session->hasArg = true;
    session->hasMultiParams = false;
    session->isRequired = false;
    session->callback = NULL;
    options->Add(session);

}

void DeleteOptions(Options *options)
{
	struct options_params *url = NULL;
	struct options_params *session= NULL;

	url = options->Get("-u");
	session = options->Get("-s");
	/*
	if (url)
	{
        Free(url->trigger);
        url->trigger = NULL;
        Free(url->description);
        url->description = NULL;
        Free(url->name);
        url->name = NULL;
        Free(url->value);
        url->value = NULL;
	}

	Free(url);
	url=NULL;

	if (session)
	{
        Free(session->trigger);
        session->trigger = NULL;
        Free(session->description);
        session->description = NULL;
        Free(session->name);
        session->name = NULL;
        Free(session->value);
        session->value = NULL;
	}

	Free(session);
	session=NULL;
	*/
}

void SetupCleanup(Options *options)
{
	DeleteOptions(options);
}
