#define BOOST_TEST_MODULE "tags"
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <notmuch.h>

BOOST_AUTO_TEST_CASE(destroy)
{

    std::string dbpath = "/home/dvhaeren/.mail";
    notmuch_database_t* database;
    notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

    notmuch_query_t* query = notmuch_query_create(database, "*");
    notmuch_threads_t *threads;
    notmuch_thread_t *thread;
    notmuch_tags_t* tags;

    status = notmuch_query_search_threads(query, &threads);

    thread = notmuch_threads_get(threads);
    tags = notmuch_thread_get_tags(thread);
    notmuch_tags_destroy(tags);

    tags = notmuch_thread_get_tags(thread);

    notmuch_query_destroy(query);
    notmuch_database_destroy(database);
}

BOOST_AUTO_TEST_CASE(thread_destroy)
{

    std::string dbpath = "/home/dvhaeren/.mail";
    notmuch_database_t *database;
    notmuch_status_t status = notmuch_database_open(dbpath.c_str(), NOTMUCH_DATABASE_MODE_READ_ONLY, &database);

    notmuch_query_t *query = notmuch_query_create(database, "*");
    notmuch_threads_t *threads;
    notmuch_thread_t *thread;
    notmuch_tags_t *tags;

    status = notmuch_query_search_threads(query, &threads);

    thread = notmuch_threads_get(threads);
    tags = notmuch_thread_get_tags(thread);

    notmuch_thread_destroy(thread);

    notmuch_query_destroy(query);
    notmuch_database_destroy(database);

    for (;notmuch_tags_valid(tags); notmuch_tags_move_to_next(tags))
    {
       const char* tag = notmuch_tags_get(tags);
       std::cout << "tag" << tag << std::endl;
    }

}

