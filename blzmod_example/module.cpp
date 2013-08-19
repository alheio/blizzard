#include <stdlib.h>
#include <string>
#include <coda/logger.h>
#include <blizzard/plugin.hpp>
#include <coda/logger.h>
#include <pthread.h>

class blzmod_example : public blz_plugin
{
	std::string ret;

public:
	 blzmod_example() {}
	~blzmod_example() throw() {}

	int load(const char* fname);
	void easy_init();
	void easy_end();
	void hard_init();
	void hard_end();
	int easy(blz_task* task);
	int hard(blz_task* task);
	int rotate_custom_logs();
};

int blzmod_example::load(const char* fname)
{
	log_info("blzmod_example plugin loaded");

	return 0;
}

void blzmod_example::easy_init()
{
	log_notice("easy thread init, tid is %lu", ::pthread_self());
}

void blzmod_example::easy_end()
{
	log_notice("easy thread end, tid is %lu", ::pthread_self());
}

void blzmod_example::hard_init()
{
	log_notice("hard thread init, tid is %lu", ::pthread_self());
}

void blzmod_example::hard_end()
{
	log_notice("hard thread end, tid is %lu", ::pthread_self());
}

int blzmod_example::easy(blz_task* task)
{
	uint32_t nb = atoi(task->get_request_uri_path() + 1);

	ret.resize(nb);

	for (size_t i = 0; i < ret.size(); ++i)
	{
		ret[i] = 'x';
	}

	task->add_response_buffer(ret.c_str(), ret.size());
	task->add_response_header("Content-type", "text/plain; charset=utf-8");
	task->set_response_status(200);

	return BLZ_OK;
}

int blzmod_example::hard(blz_task* task)
{
	return BLZ_OK;
}

int blzmod_example::rotate_custom_logs()
{
	log_info("if you have some custom logs, you can rotate them here");

	return BLZ_OK;
}

extern "C" blz_plugin* get_plugin_instance()
{
	return new blzmod_example();
}

